/**
 * GEMM Naive Kernel — CUDA 白板手撕版
 *
 * 对应：本月目标「能白板写出 GEMM naive kernel」
 * 编译：nvcc -O2 matmul_naive.cu -o matmul_naive
 *
 * C = A × B
 *   A: M × K  (row-major)
 *   B: K × N  (row-major)
 *   C: M × N  (row-major)
 *
 * 每个线程算 C 的一个元素：C[row][col] = Σ(k=0..K-1) A[row][k] * B[k][col]
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <cuda_runtime.h>

#define CUDA_CHECK(call) do {                                         \
    cudaError_t err = call;                                           \
    if (err != cudaSuccess) {                                         \
        fprintf(stderr, "CUDA Error: %s at %s:%d\n",                  \
                cudaGetErrorString(err), __FILE__, __LINE__);          \
        exit(EXIT_FAILURE);                                           \
    }                                                                 \
} while(0)

// ═══════════════════════════════════════════════════════════════════
// Naive GEMM Kernel
//
// 每个线程算 C 的一个元素，线程直接读 Global Memory
// 内存访问模式分析：
//   - A[row][k]：同一 warp 内所有线程 row 相同，k 递增 → 广播，无冲突
//   - B[k][col]：同一 warp 内 col 递增（相邻线程读相邻列）
//     B 是 row-major，同一列不连续 → 访问不合并！这是性能瓶颈
//
// Grid:  (ceil(N/blockDim.x), ceil(M/blockDim.y), 1)
// Block: (blockDim.x, blockDim.y, 1)
// ═══════════════════════════════════════════════════════════════════
__global__ void gemm_naive(const float* A, const float* B, float* C,
                            int M, int N, int K) {
    // 全局索引：这个线程负责 C[row][col]
    int row = blockIdx.y * blockDim.y + threadIdx.y;  // C 的第几行
    int col = blockIdx.x * blockDim.x + threadIdx.x;  // C 的第几列

    if (row < M && col < N) {
        float sum = 0.0f;
        // 沿 K 维度累加：A[row][k] * B[k][col]
        for (int k = 0; k < K; k++) {
            // A 是 row-major: A[row][k] = A[row * K + k]
            // B 是 row-major: B[k][col] = B[k * N + col]
            sum += A[row * K + k] * B[k * N + col];
        }
        C[row * N + col] = sum;
    }
}

// ═══════════════════════════════════════════════════════════════════
// CPU Baseline（验证 GPU 结果）
// ═══════════════════════════════════════════════════════════════════
void gemm_cpu(const float* A, const float* B, float* C,
              int M, int N, int K) {
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            float sum = 0.0f;
            for (int k = 0; k < K; k++) {
                sum += A[i * K + k] * B[k * N + j];
            }
            C[i * N + j] = sum;
        }
    }
}

// ═══════════════════════════════════════════════════════════════════
// 工具函数
// ═══════════════════════════════════════════════════════════════════
void init_matrix(float* mat, int rows, int cols) {
    for (int i = 0; i < rows * cols; i++) {
        mat[i] = (float)(rand()) / RAND_MAX * 2.0f - 1.0f;  // [-1, 1]
    }
}

bool verify(const float* cpu, const float* gpu, int size, float eps = 1e-3f) {
    for (int i = 0; i < size; i++) {
        if (fabsf(cpu[i] - gpu[i]) > eps) {
            fprintf(stderr, "Mismatch at [%d]: CPU=%.6f, GPU=%.6f\n",
                    i, cpu[i], gpu[i]);
            return false;
        }
    }
    return true;
}

// ═══════════════════════════════════════════════════════════════════
// Main
// ═══════════════════════════════════════════════════════════════════
int main() {
    // 小矩阵方便验证（实际 GEMM 通常是 M,N,K ≥ 512）
    const int M = 256, N = 128, K = 64;
    const int size_A = M * K;
    const int size_B = K * N;
    const int size_C = M * N;
    const size_t bytes_A = size_A * sizeof(float);
    const size_t bytes_B = size_B * sizeof(float);
    const size_t bytes_C = size_C * sizeof(float);

    printf("=== GEMM Naive Kernel ===\n");
    printf("C[%d×%d] = A[%d×%d] × B[%d×%d]\n", M, N, M, K, K, N);
    printf("Total FLOPs: %d (2*M*N*K)\n\n", 2 * M * N * K);

    // Host 内存
    float *h_A = (float*)malloc(bytes_A);
    float *h_B = (float*)malloc(bytes_B);
    float *h_C_cpu = (float*)malloc(bytes_C);
    float *h_C_gpu = (float*)malloc(bytes_C);

    srand(42);
    init_matrix(h_A, M, K);
    init_matrix(h_B, K, N);

    // Device 内存
    float *d_A, *d_B, *d_C;
    CUDA_CHECK(cudaMalloc(&d_A, bytes_A));
    CUDA_CHECK(cudaMalloc(&d_B, bytes_B));
    CUDA_CHECK(cudaMalloc(&d_C, bytes_C));

    CUDA_CHECK(cudaMemcpy(d_A, h_A, bytes_A, cudaMemcpyHostToDevice));
    CUDA_CHECK(cudaMemcpy(d_B, h_B, bytes_B, cudaMemcpyHostToDevice));

    // Kernel launch
    dim3 block(16, 16);  // 16×16 = 256 threads/block
    dim3 grid((N + block.x - 1) / block.x,   // ceil(N / 16)
              (M + block.y - 1) / block.y);  // ceil(M / 16)

    printf("Grid: (%d, %d), Block: (%d, %d)\n",
           grid.x, grid.y, block.x, block.y);

    gemm_naive<<<grid, block>>>(d_A, d_B, d_C, M, N, K);
    CUDA_CHECK(cudaGetLastError());
    CUDA_CHECK(cudaDeviceSynchronize());

    CUDA_CHECK(cudaMemcpy(h_C_gpu, d_C, bytes_C, cudaMemcpyDeviceToHost));

    // CPU 验证
    gemm_cpu(h_A, h_B, h_C_cpu, M, N, K);
    bool pass = verify(h_C_cpu, h_C_gpu, size_C);
    printf("Correctness: %s\n", pass ? "PASS" : "FAIL");

    // 打印 C 的部分结果
    if (pass) {
        printf("\nC[0][0..3] = [%.4f, %.4f, %.4f, %.4f]\n",
               h_C_gpu[0], h_C_gpu[1], h_C_gpu[2], h_C_gpu[3]);
        printf("C[1][0..3] = [%.4f, %.4f, %.4f, %.4f]\n",
               h_C_gpu[N], h_C_gpu[N+1], h_C_gpu[N+2], h_C_gpu[N+3]);
    }

    // 性能分析
    printf("\n=== Performance Analysis ===\n");
    printf("Naive kernel 性能瓶颈：\n");
    printf("  1. B[k][col] 访问不合并：相邻线程的 col 差 1\n");
    printf("     但 B 是 row-major，B[k][N+1] 和 B[k][N] 不连续\n");
    printf("     → memory transaction 利用率 ~4/128 (4B/128B)\n");
    printf("  2. 每个元素从 Global Memory 读 2K 次（A 和 B 各 K 次）\n");
    printf("     本测试 K=%d，每个线程访问 Global Memory %d 次\n", K, 2*K);
    printf("  3. 没有任何数据复用 —— 同一 block 的线程不共享数据\n\n");
    printf("优化方向（下个 kernel）：\n");
    printf("  → Shared Memory Tiling：把 A 和 B 的 tile 加载到 smem\n");
    printf("  → 每个线程从 smem 读，不再从 Global Memory 读\n");
    printf("  → 数据复用率：每个 tile 被 TILE_SIZE 个线程共享\n");

    // 清理
    CUDA_CHECK(cudaFree(d_A));
    CUDA_CHECK(cudaFree(d_B));
    CUDA_CHECK(cudaFree(d_C));
    free(h_A); free(h_B); free(h_C_cpu); free(h_C_gpu);

    return pass ? 0 : 1;
}
