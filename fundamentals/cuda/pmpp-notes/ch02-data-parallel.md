# PMPP Chapter 2: Heterogeneous Data Parallel Computing

> 来源：《Programming Massively Parallel Processors》4th Edition
> 状态：🟡 笔记整理中

---

## 2.1 数据并行的概念

### 什么是数据并行

```
标量操作（串行）        数据并行（SIMD/SIMT）
                       
for (i = 0; i < N; i++)  Thread 0: C[0] = A[0] + B[0]
    C[i] = A[i] + B[i];  Thread 1: C[1] = A[1] + B[1]
                         Thread 2: C[2] = A[2] + B[2]
                         ...
                         全部同时执行！
```

**数据并行** = 同样的操作，不同的数据。向量加法是最典型的例子。

### CUDA 的数据并行模型

CUDA 采用 **SIMT**（Single Instruction, Multiple Thread）模型：
- 所有 thread 执行同一段 kernel 代码
- 但每个 thread 有自己的寄存器和指令指针
- Warp（32 个 thread）是调度和执行的基本单位

---

## 2.2 CUDA C 程序结构

### Host 代码 vs Device 代码

| 位置 | 关键字 | 调用者 | 运行位置 |
|------|--------|--------|----------|
| Host 函数 | 普通 C 函数 | CPU | CPU |
| Global kernel | `__global__` | CPU（通过 `<<<>>>`） | GPU |
| Device 函数 | `__device__` | GPU kernel | GPU |
| Host+Device | `__host__ __device__` | 均可 | 均可 |

### Kernel Launch 语法

```cuda
kernel_name<<<gridDim, blockDim, sharedMemBytes, stream>>>(args...);
//            ^^^^^^^  ^^^^^^^^  ^^^^^^^^^^^^^^  ^^^^^^
//            grid 大小  block 大小  shared mem    CUDA stream
//            必须指定    必须指定    可选          可选
```

**计算全局索引**：

```cuda
// 1D grid + 1D block
int i = blockIdx.x * blockDim.x + threadIdx.x;

// 2D grid + 2D block
int col = blockIdx.x * blockDim.x + threadIdx.x;
int row = blockIdx.y * blockDim.y + threadIdx.y;
```

### Grid-Stride Loop（重要！）

当数据量远大于线程数时：

```cuda
__global__ void vecAdd(float* A, float* B, float* C, int N) {
    // 每个线程处理多个元素，步长 = 总线程数
    for (int i = blockIdx.x * blockDim.x + threadIdx.x;
         i < N;
         i += blockDim.x * gridDim.x) {  // grid-stride loop!
        C[i] = A[i] + B[i];
    }
}
```

**好处**：
1. 线程数量不依赖于数据大小 → 可以固定 block/grid 配置
2. 更好的负载均衡（每个线程自动越过数据边界）
3. 减少 kernel launch 的配置计算

---

## 2.3 线程组织

### Grid → Block → Thread 层次

```
                          Grid
   ┌──────────┬──────────┬──────────┐
   │ Block(0,0) │ Block(1,0) │ Block(2,0) │
   │  ┌──┬──┐  │  ┌──┬──┐  │  ┌──┬──┐  │
   │  │T0│T1│  │  │T0│T1│  │  │T0│T1│  │
   │  ├──┼──┤  │  ├──┼──┤  │  ├──┼──┤  │
   │  │T2│T3│  │  │T2│T3│  │  │T2│T3│  │
   │  └──┴──┘  │  └──┴──┘  │  └──┴──┘  │
   ├──────────┼──────────┼──────────┤
   │ Block(0,1) │ Block(1,1) │ Block(2,1) │
   └──────────┴──────────┴──────────┘
```

### 内置变量

| 变量 | 含义 | 维度 |
|------|------|------|
| `threadIdx.x/y/z` | 线程在 block 内的索引 | 3D |
| `blockIdx.x/y/z` | 线程所在的 block 索引 | 3D |
| `blockDim.x/y/z` | 每个 block 的线程数 | 3D |
| `gridDim.x/y/z` | grid 中的 block 数 | 3D |

### Warp

- **1 Warp = 32 个连续的 Thread**
- Warp 是 SM 上的调度单元
- Warp 内的 thread 执行同一条指令（SIMD 模式）
- **线程束分化（Warp Divergence）**：Warp 内 thread 走不同的 if-else 分支时，两部分串行执行

```
// Bad: Warp Divergence!
if (threadIdx.x % 2 == 0) {  // 偶数线程走这里
    // ...
} else {                      // 奇数线程走这里
    // ...                    // → 两个分支串行执行！
}

// Good: 避免 warp 内分支
if (threadIdx.x / 32 == 0) {  // 整个 warp 统一走
    // ...
}
```

---

## 2.4 内存管理基础

### CUDA 内存 API

```cuda
// 分配 GPU 内存
cudaError_t cudaMalloc(void** devPtr, size_t size);

// CPU ↔ GPU 数据传输
cudaError_t cudaMemcpy(void* dst, const void* src,
                       size_t count, cudaMemcpyKind kind);
// kind: cudaMemcpyHostToDevice, cudaMemcpyDeviceToHost,
//       cudaMemcpyDeviceToDevice

// 释放 GPU 内存
cudaError_t cudaFree(void* devPtr);
```

### 错误处理

```cuda
#define CUDA_CHECK(call) do {                             \
    cudaError_t err = call;                               \
    if (err != cudaSuccess) {                             \
        fprintf(stderr, "CUDA Error: %s at %s:%d\n",      \
                cudaGetErrorString(err), __FILE__, __LINE__); \
        exit(EXIT_FAILURE);                               \
    }                                                     \
} while(0)

// 使用
CUDA_CHECK(cudaMalloc(&d_A, N * sizeof(float)));
CUDA_CHECK(cudaMemcpy(d_A, h_A, N * sizeof(float), cudaMemcpyHostToDevice));
```

---

## 本章要点（面试向）

1. **CPU 调用 GPU 的流程** → malloc → memcpy(H2D) → kernel<<<>>> → memcpy(D2H) → free
2. **`<<<grid, block>>>` 的每个参数什么意思** → grid 是 block 数量，block 是 thread 数量
3. **Grid-Stride Loop 有什么用** → 解耦线程数与数据量，方便复用固定配置
4. **Warp Divergence 是什么** → warp 内线程走不同分支时串行执行，浪费算力
5. **线程索引怎么算** → `i = blockIdx.x * blockDim.x + threadIdx.x`
