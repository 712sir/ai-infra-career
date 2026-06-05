/**
 * Vector Addition - CUDA Kernel
 *
 * 这是 CUDA 的 "Hello World" —— 最基础的 kernel。
 * 目标：理解 host/device 代码分离、内存管理、kernel launch。
 *
 * 编译：nvcc vec_add.cu -o vec_add
 * 运行：./vec_add
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <cuda_runtime.h>

/* ===========================================================
 * 错误检查宏
 * =========================================================== */
#define CUDA_CHECK(call) do {                                         \
    cudaError_t err = call;                                           \
    if (err != cudaSuccess) {                                         \
        fprintf(stderr, "CUDA Error: %s at %s:%d\n",                  \
                cudaGetErrorString(err), __FILE__, __LINE__);          \
        exit(EXIT_FAILURE);                                           \
    }                                                                 \
} while(0)

/* ===========================================================
 * Kernel 1: Naive Version
 * 每个线程处理一个元素（一对一映射）
 *
 * <<<blocks, threads>>> 配置：
 *   threads = 256
 *   blocks  = ceil(N / 256)
 * =========================================================== */
__global__ void vecAdd_v1(const float* A, const float* B, float* C, int N) {
    int i = blockIdx.x * blockDim.x + threadIdx.x;
    if (i < N) {
        C[i] = A[i] + B[i];
    }
}

/* ===========================================================
 * Kernel 2: Grid-Stride Loop Version
 * 每个线程处理多个元素
 *
 * 优势：
 *   1. 线程数不依赖数据大小（可固定 32K threads）
 *   2. 每个线程的工作量自动适应数据大小
 *   3. 更好的 warp 级负载均衡
 * =========================================================== */
__global__ void vecAdd_v2(const float* A, const float* B, float* C, int N) {
    for (int i = blockIdx.x * blockDim.x + threadIdx.x;
         i < N;
         i += blockDim.x * gridDim.x) {
        C[i] = A[i] + B[i];
    }
}

/* ===========================================================
 * CPU Baseline（for correctness check）
 * =========================================================== */
void vecAddCPU(const float* A, const float* B, float* C, int N) {
    for (int i = 0; i < N; i++) {
        C[i] = A[i] + B[i];
    }
}

/* ===========================================================
 * Utility: 初始化随机数据
 * =========================================================== */
void initData(float* data, int N) {
    for (int i = 0; i < N; i++) {
        data[i] = (float)(rand()) / RAND_MAX * 10.0f;
    }
}

/* ===========================================================
 * Utility: 验证 GPU 结果 vs CPU 结果
 * =========================================================== */
bool verify(const float* cpu, const float* gpu, int N) {
    const float eps = 1e-5f;
    for (int i = 0; i < N; i++) {
        if (fabs(cpu[i] - gpu[i]) > eps) {
            fprintf(stderr, "Mismatch at index %d: CPU=%.6f, GPU=%.6f\n",
                    i, cpu[i], gpu[i]);
            return false;
        }
    }
    return true;
}

/* ===========================================================
 * Main
 * =========================================================== */
int main() {
    // --- 配置 ---
    const int N = 1 << 24;  // 16M elements = 64 MB per array
    const int threadsPerBlock = 256;
    const int blocksPerGrid_v1 = (N + threadsPerBlock - 1) / threadsPerBlock;
    const int blocksPerGrid_v2 = 128;  // grid-stride: 固定少量 block

    printf("Vector Addition: N = %d (%.2f MB per array)\n", N, N * sizeof(float) / 1e6);
    printf("v1: %d blocks x %d threads\n", blocksPerGrid_v1, threadsPerBlock);
    printf("v2: %d blocks x %d threads (grid-stride loop)\n", blocksPerGrid_v2, threadsPerBlock);

    // --- CPU 端分配内存 ---
    float *h_A = (float*)malloc(N * sizeof(float));
    float *h_B = (float*)malloc(N * sizeof(float));
    float *h_C_cpu = (float*)malloc(N * sizeof(float));
    float *h_C_gpu = (float*)malloc(N * sizeof(float));

    // --- 初始化数据 ---
    srand(42);
    initData(h_A, N);
    initData(h_B, N);

    // --- GPU 端分配内存 ---
    float *d_A, *d_B, *d_C;
    CUDA_CHECK(cudaMalloc(&d_A, N * sizeof(float)));
    CUDA_CHECK(cudaMalloc(&d_B, N * sizeof(float)));
    CUDA_CHECK(cudaMalloc(&d_C, N * sizeof(float)));

    // --- 数据搬运：CPU → GPU ---
    CUDA_CHECK(cudaMemcpy(d_A, h_A, N * sizeof(float), cudaMemcpyHostToDevice));
    CUDA_CHECK(cudaMemcpy(d_B, h_B, N * sizeof(float), cudaMemcpyHostToDevice));

    // --- Kernel 1: Naive ---
    printf("\n--- Kernel v1 (Naive) ---\n");
    vecAdd_v1<<<blocksPerGrid_v1, threadsPerBlock>>>(d_A, d_B, d_C, N);
    CUDA_CHECK(cudaGetLastError());
    CUDA_CHECK(cudaDeviceSynchronize());

    // 取回结果并验证
    CUDA_CHECK(cudaMemcpy(h_C_gpu, d_C, N * sizeof(float), cudaMemcpyDeviceToHost));
    vecAddCPU(h_A, h_B, h_C_cpu, N);
    printf("v1 correctness: %s\n", verify(h_C_cpu, h_C_gpu, N) ? "PASS" : "FAIL");

    // --- Kernel 2: Grid-Stride Loop ---
    printf("\n--- Kernel v2 (Grid-Stride Loop) ---\n");
    vecAdd_v2<<<blocksPerGrid_v2, threadsPerBlock>>>(d_A, d_B, d_C, N);
    CUDA_CHECK(cudaGetLastError());
    CUDA_CHECK(cudaDeviceSynchronize());

    // 取回结果并验证
    CUDA_CHECK(cudaMemcpy(h_C_gpu, d_C, N * sizeof(float), cudaMemcpyDeviceToHost));
    printf("v2 correctness: %s\n", verify(h_C_cpu, h_C_gpu, N) ? "PASS" : "FAIL");

    // --- 清理 ---
    CUDA_CHECK(cudaFree(d_A));
    CUDA_CHECK(cudaFree(d_B));
    CUDA_CHECK(cudaFree(d_C));
    free(h_A); free(h_B); free(h_C_cpu); free(h_C_gpu);

    printf("\nDone!\n");
    return 0;
}
