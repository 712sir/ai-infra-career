/**
 * Softmax CPU Baseline
 *
 * 目标：
 *   1. 理解 Softmax 的数学定义
 *   2. 理解数值稳定性问题（overflow）及解决方案（平移技巧）
 *   3. 为后续 CUDA kernel 提供正确性对照
 *
 * Softmax 公式：
 *   softmax(x_i) = exp(x_i) / sum_j(exp(x_j))
 *
 * 数值不稳定原因：
 *   exp(100) ≈ 2.688e43，exp(1000) 直接溢出为 inf
 *   解决方案：所有 x_i 减去 max(x)，不影响结果但保证 exp 的输入 ≤ 0
 *   softmax(x_i) = exp(x_i - max(x)) / sum_j(exp(x_j - max(x)))
 *
 * 编译：g++ -std=c++17 -O2 softmax_cpu.cpp -o softmax_cpu
 * 运行：./softmax_cpu
 */

#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <cfloat>
#include <chrono>
#include <iomanip>

// ── Naive Softmax（会溢出！） ──
// 不做任何数值保护，直接用 exp(x_i) 计算
// 当输入值较大时（如 >88 for float32），exp 溢出为 inf
std::vector<float> softmax_naive(const std::vector<float>& x) {
    size_t n = x.size();
    std::vector<float> result(n);

    float sum = 0.0f;
    for (size_t i = 0; i < n; i++) {
        result[i] = std::exp(x[i]);  // 可能溢出！
        sum += result[i];
    }

    for (size_t i = 0; i < n; i++) {
        result[i] /= sum;
    }

    return result;
}

// ── 数值稳定版 Softmax（生产代码用这个） ──
// 所有 x_i 减去 max(x)，保证 exp 的输入 ≤ 0，不会溢出
std::vector<float> softmax_stable(const std::vector<float>& x) {
    size_t n = x.size();
    std::vector<float> result(n);

    // Step 1: 找到最大值
    float max_val = -FLT_MAX;
    for (size_t i = 0; i < n; i++) {
        if (x[i] > max_val) max_val = x[i];
    }

    // Step 2: exp(x_i - max) 并求和
    float sum = 0.0f;
    for (size_t i = 0; i < n; i++) {
        result[i] = std::exp(x[i] - max_val);
        sum += result[i];
    }

    // Step 3: 归一化
    for (size_t i = 0; i < n; i++) {
        result[i] /= sum;
    }

    return result;
}

// ── Log-Softmax（用于 CrossEntropyLoss，避免额外 log 调用） ──
// log_softmax(x_i) = x_i - max - log(sum_j(exp(x_j - max)))
// 优势：与 CrossEntropyLoss 配合时避免 exp→log 的数值往返误差
std::vector<float> log_softmax(const std::vector<float>& x) {
    size_t n = x.size();
    std::vector<float> result(n);

    // Step 1: max
    float max_val = -FLT_MAX;
    for (size_t i = 0; i < n; i++) {
        if (x[i] > max_val) max_val = x[i];
    }

    // Step 2: sum of exp(x_i - max)
    float sum = 0.0f;
    for (size_t i = 0; i < n; i++) {
        sum += std::exp(x[i] - max_val);
    }

    // Step 3: log_softmax(x_i) = x_i - max - log(sum)
    float log_sum = std::log(sum);
    for (size_t i = 0; i < n; i++) {
        result[i] = x[i] - max_val - log_sum;
    }

    return result;
}

// ── 矩阵版本：对 2D 矩阵的每一行做 softmax ──
// 这是 Transformer Attention 的实际使用场景
// input: [rows, cols]，output: [rows, cols]，每行独立做 softmax
std::vector<float> softmax_2d(const std::vector<float>& x,
                               size_t rows, size_t cols) {
    std::vector<float> result(rows * cols);

    for (size_t r = 0; r < rows; r++) {
        // 提取第 r 行
        const float* row_in = &x[r * cols];
        float* row_out = &result[r * cols];

        // 找该行的 max
        float max_val = -FLT_MAX;
        for (size_t c = 0; c < cols; c++) {
            if (row_in[c] > max_val) max_val = row_in[c];
        }

        // exp 并求和
        float sum = 0.0f;
        for (size_t c = 0; c < cols; c++) {
            row_out[c] = std::exp(row_in[c] - max_val);
            sum += row_out[c];
        }

        // 归一化
        for (size_t c = 0; c < cols; c++) {
            row_out[c] /= sum;
        }
    }

    return result;
}

// ── 验证：softmax 输出之和应该 ≈ 1.0 ──
bool verify_softmax(const std::vector<float>& output, float tol = 1e-5f) {
    float sum = 0.0f;
    for (float v : output) sum += v;
    return std::fabs(sum - 1.0f) < tol;
}

// ── 打印向量 ──
void print_vec(const std::vector<float>& v, const std::string& label,
               size_t max_show = 8) {
    std::cout << std::fixed << std::setprecision(4);
    std::cout << label << " [";
    size_t n = std::min(v.size(), max_show);
    for (size_t i = 0; i < n; i++) {
        std::cout << v[i];
        if (i < n - 1) std::cout << ", ";
    }
    if (v.size() > max_show) std::cout << ", ...";
    std::cout << "]  sum=" << [&]() {
        float s = 0; for (float x : v) s += x; return s;
    }() << std::endl;
}

int main() {
    std::cout << "=== Softmax CPU Baseline ===\n\n";

    // ──────────────────────────────────────
    // Test 1: 正常值（稳定版 vs 朴素版）
    // ──────────────────────────────────────
    std::cout << "--- Test 1: Normal values ---\n";
    std::vector<float> x1 = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f};

    auto r1_naive = softmax_naive(x1);
    auto r1_stable = softmax_stable(x1);
    print_vec(r1_stable, "stable");

    // 验证两个版本结果一致
    bool match = true;
    for (size_t i = 0; i < r1_naive.size(); i++) {
        if (std::fabs(r1_naive[i] - r1_stable[i]) > 1e-5f) {
            match = false;
            break;
        }
    }
    std::cout << "naive == stable: " << (match ? "YES" : "NO")
              << " | sum check: " << (verify_softmax(r1_stable) ? "PASS" : "FAIL")
              << "\n\n";

    // ──────────────────────────────────────
    // Test 2: 大数值——朴素版会溢出
    // ──────────────────────────────────────
    std::cout << "--- Test 2: Large values (naive overflows!) ---\n";
    std::vector<float> x2 = {100.0f, 200.0f, 300.0f};

    auto r2_stable = softmax_stable(x2);
    print_vec(r2_stable, "stable");
    std::cout << "  => stable gives clean result, largest input gets ~1.0\n\n";

    // 朴素版——会溢出！
    std::cout << "  Attempting naive softmax on [100, 200, 300]:\n";
    auto r2_naive = softmax_naive(x2);
    std::cout << "  naive result: [";
    for (size_t i = 0; i < r2_naive.size(); i++) {
        std::cout << r2_naive[i];
        if (i < r2_naive.size() - 1) std::cout << ", ";
    }
    std::cout << "]  (likely nan/inf!)\n\n";

    // ──────────────────────────────────────
    // Test 3: Log-Softmax
    // ──────────────────────────────────────
    std::cout << "--- Test 3: Log-Softmax ---\n";
    auto log_r = log_softmax(x1);
    print_vec(log_r, "log_sm");

    // 验证：exp(log_softmax) 应该等于 softmax
    auto recovered = std::vector<float>(log_r.size());
    for (size_t i = 0; i < log_r.size(); i++) {
        recovered[i] = std::exp(log_r[i]);
    }
    print_vec(recovered, "exp(log_sm)");
    std::cout << "  (should match stable softmax above)\n\n";

    // ──────────────────────────────────────
    // Test 4: 2D Softmax（模拟 Attention score）
    // ──────────────────────────────────────
    std::cout << "--- Test 4: 2D Softmax (row-wise, like Attention) ---\n";
    const size_t rows = 3, cols = 4;
    std::vector<float> x2d = {
        1.0f, 2.0f, 3.0f, 4.0f,   // row 0
        2.0f, 4.0f, 2.0f, 1.0f,   // row 1
        5.0f, 1.0f, 1.0f, 1.0f    // row 2
    };
    auto r2d = softmax_2d(x2d, rows, cols);

    for (size_t r = 0; r < rows; r++) {
        float row_sum = 0.0f;
        std::cout << "  row " << r << ": [";
        for (size_t c = 0; c < cols; c++) {
            float val = r2d[r * cols + c];
            std::cout << std::setprecision(4) << val;
            if (c < cols - 1) std::cout << ", ";
            row_sum += val;
        }
        std::cout << "] sum=" << row_sum << " " << (std::fabs(row_sum - 1.0f) < 1e-5f ? "PASS" : "FAIL") << "\n";
    }

    // ──────────────────────────────────────
    // Test 5: 性能基准（为后续 CUDA 对比准备）
    // ──────────────────────────────────────
    std::cout << "\n--- Test 5: Performance benchmark ---\n";
    const size_t N_large = 1 << 20;  // 1M elements
    std::vector<float> x_large(N_large);
    for (size_t i = 0; i < N_large; i++) {
        x_large[i] = (float)(std::rand()) / RAND_MAX * 10.0f;
    }

    const int warmup = 10;
    const int iters = 100;

    // Warmup
    for (int i = 0; i < warmup; i++) {
        auto _ = softmax_stable(x_large);
    }

    // Timed
    auto t0 = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < iters; i++) {
        auto _ = softmax_stable(x_large);
    }
    auto t1 = std::chrono::high_resolution_clock::now();

    double elapsed_us = std::chrono::duration<double, std::micro>(t1 - t0).count() / iters;
    double bandwidth = (N_large * sizeof(float)) / 1e9;  // GB
    std::cout << "  N = " << N_large << " elements\n";
    std::cout << "  Avg time: " << elapsed_us << " us\n";
    std::cout << "  Throughput: " << (N_large / elapsed_us * 1e6 / 1e9) << " G elements/s\n";
    std::cout << "  (CPU baseline for future CUDA comparison)\n";

    std::cout << "\n=== All tests done ===\n";
    return 0;
}
