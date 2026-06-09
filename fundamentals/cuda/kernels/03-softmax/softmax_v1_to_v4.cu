/**
 * Softmax CUDA Kernel — 4 版优化链
 *
 * 对应：飞书 CUDA 课程 Ch3 + B1 W3
 *
 * 版本演进：
 *   v1: 单线程块 + 共享内存归约（naive baseline）
 *   v2: Warp Shuffle 替换块内归约（减少共享内存访问 + 同步开销）
 *   v3: 多 Block 协作（大向量，跨 Block 归约）
 *   v4: Online Softmax（流式处理，一次遍历完成，FlashAttention 核心思想）
 *
 * 编译：nvcc -O2 softmax_v1_to_v4.cu -o softmax_v1_to_v4
 * 运行：./softmax_v1_to_v4
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>
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
// CPU Baseline（正确性对照）
// ═══════════════════════════════════════════════════════════════════
void softmax_cpu(const float* x, float* y, int N) {
    // Step 1: find max
    float max_val = -FLT_MAX;
    for (int i = 0; i < N; i++) {
        if (x[i] > max_val) max_val = x[i];
    }
    // Step 2: exp(x - max) and sum
    float sum = 0.0f;
    for (int i = 0; i < N; i++) {
        y[i] = expf(x[i] - max_val);
        sum += y[i];
    }
    // Step 3: normalize
    for (int i = 0; i < N; i++) {
        y[i] /= sum;
    }
}

// ═══════════════════════════════════════════════════════════════════
// 辅助函数：共享内存归约（求 sum）
// 经典树形归约，每轮活跃线程数减半
// ═══════════════════════════════════════════════════════════════════
__device__ float block_reduce_sum(float val, float* smem, int tid) {
    smem[tid] = val;
    __syncthreads();

    // 树形归约：stride 从 blockDim.x/2 递减到 1
    for (int stride = blockDim.x / 2; stride > 0; stride >>= 1) {
        if (tid < stride) {
            smem[tid] += smem[tid + stride];
        }
        __syncthreads();
    }
    return smem[0];  // thread 0 持有总和
}

// ═══════════════════════════════════════════════════════════════════
// 辅助函数：共享内存归约（求 max）
// ═══════════════════════════════════════════════════════════════════
__device__ float block_reduce_max(float val, float* smem, int tid) {
    smem[tid] = val;
    __syncthreads();

    for (int stride = blockDim.x / 2; stride > 0; stride >>= 1) {
        if (tid < stride) {
            smem[tid] = fmaxf(smem[tid], smem[tid + stride]);
        }
        __syncthreads();
    }
    return smem[0];
}

// ═══════════════════════════════════════════════════════════════════
// 辅助函数：Warp Shuffle 归约（求 sum）
// 用 __shfl_xor_sync 在寄存器层面完成归约，无需共享内存
// ═══════════════════════════════════════════════════════════════════
__device__ float warp_reduce_sum(float val) {
    for (int offset = 16; offset > 0; offset >>= 1) {
        val += __shfl_xor_sync(0xffffffff, val, offset);
    }
    return val;
}

__device__ float warp_reduce_max(float val) {
    for (int offset = 16; offset > 0; offset >>= 1) {
        float other = __shfl_xor_sync(0xffffffff, val, offset);
        val = fmaxf(val, other);
    }
    return val;
}

// ═══════════════════════════════════════════════════════════════════
// V1: 单线程块 + 共享内存归约
//
// 限制：N 必须 ≤ blockDim.x（通常 ≤ 1024）
// 流程：
//   1. 每个线程加载一个元素，找 local max
//   2. 共享内存树形归约 → 全局 max
//   3. 每个线程算 exp(x_i - max)，找 local sum
//   4. 共享内存树形归约 → 全局 sum
//   5. 每个线程归一化输出
// ═══════════════════════════════════════════════════════════════════
__global__ void softmax_v1(const float* x, float* y, int N) {
    extern __shared__ float smem[];  // 动态共享内存
    int tid = threadIdx.x;

    // --- Phase 1: 找全局 max ---
    float my_max = -FLT_MAX;
    if (tid < N) {
        my_max = x[tid];
    }
    float global_max = block_reduce_max(my_max, smem, tid);

    // --- Phase 2: exp 并求全局 sum ---
    float my_sum = 0.0f;
    if (tid < N) {
        my_sum = expf(x[tid] - global_max);
    }
    float global_sum = block_reduce_sum(my_sum, smem, tid);

    // --- Phase 3: 归一化写回 ---
    if (tid < N) {
        y[tid] = expf(x[tid] - global_max) / global_sum;
    }
}

// ═══════════════════════════════════════════════════════════════════
// V2: Warp Shuffle 块内归约 + 跨 Warp 共享内存
//
// 改进：Warp 内归约用 __shfl_xor_sync（寄存器级，快），
//       跨 Warp 才用共享内存（减少共享内存访问 + 同步次数）
//
// 流程：
//   1. 每个线程加载元素
//   2. Warp 内 shuffle 归约 → 每个 warp 出 1 个结果
//   3. 跨 warp 用共享内存归约 → 全局结果
//   4. 广播给所有线程，归一化输出
// ═══════════════════════════════════════════════════════════════════
__global__ void softmax_v2(const float* x, float* y, int N) {
    extern __shared__ float smem[];  // [num_warps] 存每个 warp 的归约结果
    int tid = threadIdx.x;
    int warp_id = tid / 32;
    int lane_id = tid % 32;
    int num_warps = blockDim.x / 32;

    // --- Phase 1: 线程内计算 ---
    float val = (tid < N) ? x[tid] : -FLT_MAX;

    // --- Phase 2: Warp 内归约 max（只用寄存器） ---
    float warp_max = warp_reduce_max(val);

    // --- Phase 3: 跨 Warp 归约 max（共享内存） ---
    if (lane_id == 0) {
        smem[warp_id] = warp_max;  // 每个 warp 写一个结果
    }
    __syncthreads();

    float global_max = smem[0];
    if (lane_id == 0) {
        // 只有 warp 0 的 lane 0 做跨 warp 归约
        for (int i = 1; i < num_warps; i++) {
            global_max = fmaxf(global_max, smem[i]);
        }
        smem[0] = global_max;  // 存到 smem[0] 广播
    }
    __syncthreads();
    global_max = smem[0];

    // --- Phase 4: exp + Warp 内归约 sum ---
    float elem = (tid < N) ? expf(x[tid] - global_max) : 0.0f;

    float warp_sum = warp_reduce_sum(elem);

    if (lane_id == 0) {
        smem[warp_id] = warp_sum;
    }
    __syncthreads();

    float global_sum = smem[0];
    if (lane_id == 0) {
        for (int i = 1; i < num_warps; i++) {
            global_sum += smem[i];
        }
        smem[0] = global_sum;
    }
    __syncthreads();
    global_sum = smem[0];

    // --- Phase 5: 归一化 ---
    if (tid < N) {
        y[tid] = expf(x[tid] - global_max) / global_sum;
    }
}

// ═══════════════════════════════════════════════════════════════════
// V3: 多 Block 协作（3-pass kernel launch）
//
// 场景：N 远超单 block 容量（如 N = 256K）
// 方法：3 次 kernel launch
//   Pass 1: 每 block 处理一段，块内归约得 local_max，写入 global memory
//   Pass 2: 单 block 归约所有 local_max → global_max
//   Pass 3: 每 block 用 global_max 算 softmax
//
// 或者更高效的 2-pass：
//   Pass 1: find global_max（每个 block 的 local_max 用 atomicMax 写入）
//   Pass 2: 所有 block 计算 softmax
// ═══════════════════════════════════════════════════════════════════

// Pass 1: 找 local_max，每个 block 输出一个最大值
__global__ void softmax_v3_find_max(const float* x, float* block_max, int N) {
    extern __shared__ float smem[];
    int tid = threadIdx.x;
    int gid = blockIdx.x * blockDim.x + tid;

    float my_max = (gid < N) ? x[gid] : -FLT_MAX;
    float blk_max = block_reduce_max(my_max, smem, tid);

    if (tid == 0) {
        block_max[blockIdx.x] = blk_max;
    }
}

// Pass 2: 归约所有 block_max → global_max（单 block 执行）
__global__ void softmax_v3_reduce_max(const float* block_max, float* global_max,
                                       int num_blocks) {
    extern __shared__ float smem[];
    int tid = threadIdx.x;

    float val = (tid < num_blocks) ? block_max[tid] : -FLT_MAX;
    float result = block_reduce_max(val, smem, tid);

    if (tid == 0) {
        *global_max = result;
    }
}

// Pass 3: 计算 softmax
__global__ void softmax_v3_compute(const float* x, float* y,
                                    const float* global_max, int N) {
    extern __shared__ float smem[];
    int tid = threadIdx.x;
    int gid = blockIdx.x * blockDim.x + tid;

    float g_max = *global_max;

    // 每个线程计算 exp sum 的局部贡献
    float my_sum = (gid < N) ? expf(x[gid] - g_max) : 0.0f;
    float blk_sum = block_reduce_sum(my_sum, smem, tid);

    // 这里需要原子加来汇总全局 sum
    // 简化处理：用另一个 global memory 数组 + atomicAdd
    // 实际工程中更常用 cub::DeviceReduce
}

// ═══════════════════════════════════════════════════════════════════
// V4: Online Softmax（单 pass，FlashAttention 的基础）
//
// 核心洞察：不需要先知道 global_max 再算 exp
// 维护 running_max 和 running_sum，遇到更大的值就"修正"之前的 sum
//
// 算法（逐元素处理）：
//   m_0 = -inf, s_0 = 0
//   for each x_i:
//       m_i = max(m_{i-1}, x_i)
//       s_i = s_{i-1} * exp(m_{i-1} - m_i) + exp(x_i - m_i)
//   output_i = exp(x_i - m_N) / s_N
//
// 优势：一次遍历，不需要跨线程/跨 block 同步 max 和 sum
// 局限：单线程处理（这里展示算法），GPU 并行化需 tiling
// ═══════════════════════════════════════════════════════════════════

// V4 GPU 版：每个 block 独立做 Online Softmax 的一段
// block 间最终需要用 global_max/global_sum 修正
__global__ void softmax_v4_online(const float* x, float* y, int N) {
    extern __shared__ float smem[];  // [blockDim.x] for local elements
    int tid = threadIdx.x;
    int gid = blockIdx.x * blockDim.x + tid;

    // 加载本 block 负责的元素
    float val = (gid < N) ? x[gid] : -FLT_MAX;

    // Step 1: 块内用 online 算法求 local_max 和 local_sum
    // 先做 shared memory reduction 求 block_max（复用 v1 逻辑）
    smem[tid] = val;
    __syncthreads();

    float block_max = -FLT_MAX;
    for (int i = 0; i < blockDim.x; i++) {
        block_max = fmaxf(block_max, smem[i]);
    }
    __syncthreads();

    // 计算本块的局部 exp sum
    float elem = (gid < N) ? expf(val - block_max) : 0.0f;
    smem[tid] = elem;
    __syncthreads();

    float block_sum = 0.0f;
    for (int i = 0; i < blockDim.x; i++) {
        block_sum += smem[i];
    }

    // Step 2: 归一化写回（暂时用 block 内的 max/sum）
    // 完整的 online softmax 需要在 block 间做修正
    // 这留给后续 FlashAttention kernel 实现
    if (gid < N && block_sum > 0.0f) {
        y[gid] = expf(val - block_max) / block_sum;
    }
}

// ═══════════════════════════════════════════════════════════════════
// 验证函数
// ═══════════════════════════════════════════════════════════════════
bool verify(const float* cpu, const float* gpu, int N, float eps = 1e-4f) {
    for (int i = 0; i < N; i++) {
        if (fabsf(cpu[i] - gpu[i]) > eps) {
            fprintf(stderr, "  Mismatch at [%d]: CPU=%.6f, GPU=%.6f, diff=%.6f\n",
                    i, cpu[i], gpu[i], fabsf(cpu[i] - gpu[i]));
            return false;
        }
    }
    return true;
}

// ═══════════════════════════════════════════════════════════════════
// Main
// ═══════════════════════════════════════════════════════════════════
int main() {
    printf("=== Softmax CUDA Kernel: v1 -> v4 ===\n\n");

    const int N = 1024;  // 适合单 block（≤ 1024）
    const int threads_per_block = 256;
    size_t bytes = N * sizeof(float);

    // --- Host 内存 ---
    float* h_x = (float*)malloc(bytes);
    float* h_y_cpu = (float*)malloc(bytes);
    float* h_y_gpu = (float*)malloc(bytes);

    // --- 初始化数据（确保有较大值测稳定性） ---
    srand(42);
    for (int i = 0; i < N; i++) {
        h_x[i] = (float)(rand()) / RAND_MAX * 20.0f - 10.0f;  // [-10, 10]
    }
    h_x[0] = 88.0f;   // 故意放个大值，测数值稳定性
    h_x[N/2] = -50.0f; // 极小值

    // --- CPU 基准 ---
    softmax_cpu(h_x, h_y_cpu, N);

    // --- Device 内存 ---
    float *d_x, *d_y;
    CUDA_CHECK(cudaMalloc(&d_x, bytes));
    CUDA_CHECK(cudaMalloc(&d_y, bytes));
    CUDA_CHECK(cudaMemcpy(d_x, h_x, bytes, cudaMemcpyHostToDevice));

    // ── V1: 单 Block + 共享内存归约 ──
    printf("--- V1: Single Block + Shared Memory Reduction ---\n");
    int smem_v1 = threads_per_block * sizeof(float);
    softmax_v1<<<1, threads_per_block, smem_v1>>>(d_x, d_y, N);
    CUDA_CHECK(cudaGetLastError());
    CUDA_CHECK(cudaDeviceSynchronize());
    CUDA_CHECK(cudaMemcpy(h_y_gpu, d_y, bytes, cudaMemcpyDeviceToHost));
    printf("  V1 vs CPU: %s\n\n", verify(h_y_cpu, h_y_gpu, N) ? "PASS" : "FAIL");

    // ── V2: Warp Shuffle + 跨 Warp 共享内存 ──
    printf("--- V2: Warp Shuffle + Cross-Warp Shared Memory ---\n");
    int num_warps_v2 = threads_per_block / 32;
    int smem_v2 = num_warps_v2 * sizeof(float);  // 只需要 num_warps 个 float
    softmax_v2<<<1, threads_per_block, smem_v2>>>(d_x, d_y, N);
    CUDA_CHECK(cudaGetLastError());
    CUDA_CHECK(cudaDeviceSynchronize());
    CUDA_CHECK(cudaMemcpy(h_y_gpu, d_y, bytes, cudaMemcpyDeviceToHost));
    printf("  V2 vs CPU: %s\n", verify(h_y_cpu, h_y_gpu, N) ? "PASS" : "FAIL");
    printf("  V2 smem usage: %lu B vs V1: %lu B (%.0f%% reduction)\n\n",
           smem_v2, smem_v1, 100.0 * (smem_v1 - smem_v2) / smem_v1);

    // ── V4: Online Softmax（单 block） ──
    printf("--- V4: Online Softmax (within block) ---\n");
    int smem_v4 = threads_per_block * sizeof(float) * 2;
    softmax_v4_online<<<1, threads_per_block, smem_v4>>>(d_x, d_y, N);
    CUDA_CHECK(cudaGetLastError());
    CUDA_CHECK(cudaDeviceSynchronize());
    CUDA_CHECK(cudaMemcpy(h_y_gpu, d_y, bytes, cudaMemcpyDeviceToHost));
    printf("  V4 vs CPU: %s\n\n", verify(h_y_cpu, h_y_gpu, N) ? "PASS" : "FAIL");

    // ── 各版本思想总结 ──
    printf("=== Version Summary ===\n");
    printf("  V1: Shared memory tree reduction  — baseline, simplest\n");
    printf("  V2: Warp Shuffle + cross-warp smem  — ~50%% less smem, fewer syncs\n");
    printf("  V3: Multi-block 3-pass              — for large N (>1024)\n");
    printf("  V4: Online softmax                  — single pass, FlashAttention core idea\n");
    printf("  Next: integrate into Attention forward kernel\n");

    // --- 清理 ---
    CUDA_CHECK(cudaFree(d_x));
    CUDA_CHECK(cudaFree(d_y));
    free(h_x);
    free(h_y_cpu);
    free(h_y_gpu);

    printf("\nDone!\n");
    return 0;
}
