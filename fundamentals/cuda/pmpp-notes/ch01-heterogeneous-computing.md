# PMPP Chapter 1: Introduction to Heterogeneous Computing

> 来源：《Programming Massively Parallel Processors》4th Edition
> 状态：🟡 笔记整理中

---

## 1.1 为什么需要异构计算

### CPU vs GPU 架构差异

```
CPU (Latency-Oriented)              GPU (Throughput-Oriented)
┌──────────────────────┐            ┌──────────────────────┐
│  ████  ████  ████    │            │  ··················  │
│  ████  ████  ████    │  ALU       │  ··················  │
│  大核心（4-16 核）     │            │  小核心（数千核）      │
│                       │            │                      │
│  ████████████████████ │  Cache     │  ██                  │
│  大容量 L1/L2/L3      │            │  小容量 L1/L2         │
│                       │            │                      │
│  ████████████████████ │  Control   │  ██                  │
│  分支预测、乱序执行    │            │  简化控制逻辑          │
└──────────────────────┘            └──────────────────────┘
```

| 特性 | CPU | GPU |
|------|-----|-----|
| 核心数 | 4-64（大核心） | 数千（小核心） |
| 线程数 | 数十 | 数万 |
| 设计目标 | 低延迟 | 高吞吐 |
| 晶体管分配 | 复杂控制 + 大缓存 | 大量 ALU |
| 内存带宽 | 50-100 GB/s | 200-2000 GB/s |
| 擅长的任务 | 串行、分支密集 | 数据并行、算术密集 |

### 关键概念：延迟 vs 吞吐

- **CPU**：目标是尽快完成单个任务（low latency），用复杂的缓存层次和分支预测来减少每个指令的执行时间
- **GPU**：目标是每个时钟周期完成尽可能多的工作（high throughput），用大量线程掩盖内存延迟

## 1.2 CUDA 平台概述

### GPU 计算的历史

1. **2001 前**：GPU 仅用于图形渲染，固定功能管线
2. **2001-2006**：可编程着色器出现（DirectX 8/9），GPGPU 萌芽
3. **2006**：NVIDIA 发布 CUDA（Compute Unified Device Architecture）
4. **2007**：Tesla 架构，第一款 CUDA-capable GPU
5. **现在**：Ampere → Hopper → Blackwell 架构

### CUDA 编程模型的核心思想

```
Host (CPU)                          Device (GPU)
┌──────────┐                       ┌────────────────────┐
│  main()  │                       │                    │
│    │     │                       │  Grid              │
│    ├─────┼── kernel<<< >>>>>──→ │  ├── Block (0,0)   │
│    │     │                       │  │   ├── Thread 0  │
│    ├─────┼── cudaMemcpy ←────── │  │   ├── Thread 1  │
│    │     │                       │  │   └── ...       │
│    ▼     │                       │  ├── Block (1,0)   │
│  free()  │                       │  └── ...           │
└──────────┘                       └────────────────────┘
```

**三个关键抽象**：
1. **线程层次**：Thread → Block → Grid
2. **内存层次**：Local → Shared → Global
3. **同步机制**：`__syncthreads()`（Block 内）

### 一个最简 CUDA 程序

```cuda
// 1. 在 GPU 上运行的函数 → kernel
__global__ void vecAdd(float* A, float* B, float* C, int N) {
    int i = blockIdx.x * blockDim.x + threadIdx.x;
    if (i < N) {
        C[i] = A[i] + B[i];
    }
}

int main() {
    // 2. 分配 GPU 内存
    float *d_A, *d_B, *d_C;
    cudaMalloc(&d_A, N * sizeof(float));
    cudaMalloc(&d_B, N * sizeof(float));
    cudaMalloc(&d_C, N * sizeof(float));

    // 3. 数据搬运：CPU → GPU
    cudaMemcpy(d_A, h_A, N * sizeof(float), cudaMemcpyHostToDevice);
    cudaMemcpy(d_B, h_B, N * sizeof(float), cudaMemcpyHostToDevice);

    // 4. 启动 kernel
    int threadsPerBlock = 256;
    int blocksPerGrid = (N + threadsPerBlock - 1) / threadsPerBlock;
    vecAdd<<<blocksPerGrid, threadsPerBlock>>>(d_A, d_B, d_C, N);

    // 5. 数据搬运：GPU → CPU
    cudaMemcpy(h_C, d_C, N * sizeof(float), cudaMemcpyDeviceToHost);

    // 6. 释放 GPU 内存
    cudaFree(d_A); cudaFree(d_B); cudaFree(d_C);
}
```

## 1.3 关键性能因素

### 计算强度（Arithmetic Intensity）

```
计算强度 = FLOPs / Bytes Accessed

高计算强度 → Compute-Bound → 受限于算力
低计算强度 → Memory-Bound  → 受限于带宽
```

### Roofline Model 直觉

```
Performance
    ↑
    │     / 算力天花板（Peak FLOPS）
    │    /
    │   /
    │  /   Memory-Bound 区域 → 优化访存
    │ /
    │/  带宽天花板（Peak Bandwidth）
    └────────────────────→ Arithmetic Intensity
```

---

## 本章要点（面试向）

1. **为什么 GPU 适合深度学习？** → 矩阵运算高度数据并行，GPU 数千核心天然适配
2. **CPU 和 GPU 晶体管分配策略不同** → CPU 大缓存+复杂控制，GPU 大量 ALU
3. **CUDA 程序的五个步骤**：alloc device mem → copy in → launch kernel → copy out → free
4. **Roofline Model 干什么用？** → 判断 kernel 是 memory-bound 还是 compute-bound，指导优化方向
