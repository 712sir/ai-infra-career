# CUDA 课程 Ch2：线程模型和显存模型

> 来源：飞书 CUDA 编程基础 Ch2
> 状态：🟡 框架完成，内容待填充
>
> ⚠️ 本文对应夜班阅读飞书课程 Ch2 后，白天回电脑整理。

---

## 一、GPU 硬件结构速览

### SM (Streaming Multiprocessor) 内部

```
┌───────────────── SM ─────────────────┐
│  Warp Scheduler ×4                    │
│  ┌──────┐ ┌──────┐ ┌──────┐ ┌──────┐│
│  │Warp 0│ │Warp 1│ │Warp 2│ │Warp 3││
│  └──────┘ └──────┘ └──────┘ └──────┘│
│                                       │
│  CUDA Cores ×128                      │
│  SFU (Special Function Units) ×32     │
│  LD/ST Units ×32                      │
│                                       │
│  Register File (256 KB)               │
│  Shared Memory / L1 Cache (128 KB)    │
│  ┌──────────────────────────────────┐ │
│  │  可配置：smem 最多 100KB / L1 28KB│ │
│  └──────────────────────────────────┘ │
└───────────────────────────────────────┘
```

| 组件 | 说明 |
|------|------|
| SM | GPU 的基本计算单元，类似 CPU 的"核" |
| Warp Scheduler | 每个 SM 有 4 个，管理 warp 的发射和切换 |
| CUDA Core | 执行整数/单精度浮点运算 |
| SFU | 执行 sin/cos/exp/sqrt 等超越函数 |
| Register File | 每个 SM 的寄存器池，线程间瓜分 |

### 关键数据

| 指标 | A100 | GTX 1650 |
|------|------|----------|
| SM 数量 | 108 | 14 |
| CUDA Cores / SM | 64 | 64 |
| Max Threads / SM | 2048 | 1024 |
| Max Warps / SM | 64 | 32 |
| Max Blocks / SM | 32 | 16 |
| Shared Memory / SM | 164 KB | 64 KB |
| Register File / SM | 65536×32bit | 65536×32bit |

---

## 二、三级线程组织：Grid → Block → Thread

### 层级关系

```
Grid (1D/2D/3D)
├── Block (0,0)
│   ├── Thread (0,0,0)  ──┐
│   ├── Thread (1,0,0)    │ 组成 Warp(0)
│   │   ...               │ 32 threads / warp
│   └── Thread (31,0,0) ──┘
├── Block (1,0)
│   └── ...
└── Block (N,0)
    └── ...
```

### 全局索引计算公式

```cuda
// 1D Grid + 1D Block
int i = blockIdx.x * blockDim.x + threadIdx.x;

// 2D Grid + 2D Block
int row = blockIdx.y * blockDim.y + threadIdx.y;
int col = blockIdx.x * blockDim.x + threadIdx.x;

// 3D Grid + 3D Block
int i = blockIdx.z * blockDim.z + threadIdx.z;
```

### 面试高频问题

**Q1: Grid 和 Block 为什么设计成 3D？**
- 自然映射到问题域（图像 2D、视频 3D、矩阵 2D）
- 硬件限制：每个维度 ≤ 1024 threads，总共 ≤ 1024 threads/block

**Q2: Block 为什么要能被 32 整除？**
- Warp = 32 threads 是最小调度单元
- 不满一个 warp 的 block 浪费硬件资源

**Q3: Grid-Stride Loop 解决了什么问题？**
- 数据量远超线程数时，一个线程处理多个元素
- 步长 = gridDim.x * blockDim.x（总线程数）
- 好处：线程数固定（性能可预测）、自动适应任意大小数据

---

## 三、Warp：最小调度单元

### Warp 关键事实

| 事实 | 说明 |
|------|------|
| 大小 | 32 threads（所有 NVIDIA GPU 至今不变） |
| 调度 | 以 warp 为单位在 SM 上执行 |
| SIMT | Single Instruction, Multiple Threads |
| 切换 | warp 间零开销切换（寄存器已就绪） |

### Warp Divergence

```cuda
// 不好的写法 —— Warp Divergence！
if (threadIdx.x % 2 == 0) {
    // 偶数线程走这条（16 threads 活跃，16 等待）
    do_work_A();
} else {
    // 奇数线程走这条（16 threads 活跃，16 等待）
    do_work_B();
}
// 两个分支都串行执行，浪费 50% 算力！
```

**关键理解**：同一个 warp 内的线程走不同分支 = 串行执行两个分支。不同 warp 之间走不同分支 = 没问题。

### Latency Hiding

```
传统 CPU：Thread 1 stall → 上下文切换（OS 开销大）
GPU：    Warp 0 stall → 立即切 Warp 1（零开销，寄存器保存着状态）

这就是为什么 GPU 需要大量线程 —— 不是为了"并行"，
而是为了"隐藏内存延迟"。
Occupancy = active_warps / max_warps_per_SM
```

---

## 四、内存层次

### 层次全景

```
┌─────────────────────────────────────────────┐
│                  Global Memory               │  ~1.5 TB/s (HBM)
│                (所有线程可见)                  │  latency: ~400 cycles
│  ┌──────────────────────────────────────┐   │
│  │            L2 Cache                   │   │  ~40 MB (A100)
│  │  ┌──────────────────────────────┐    │   │
│  │  │         L1 Cache              │    │   │  ~128 KB / SM
│  │  │  ┌────────────────────┐      │    │   │
│  │  │  │   Shared Memory     │      │    │   │  ~164 KB / SM (A100)
│  │  │  │  (用户手动管理)       │      │    │   │  latency: ~20 cycles
│  │  │  │  ┌──────────────┐   │      │    │   │
│  │  │  │  │   Register    │   │      │    │   │  256 KB / SM
│  │  │  │  │  (最快)        │   │      │    │   │  latency: ~1 cycle
│  │  │  │  └──────────────┘   │      │    │   │
│  │  │  └────────────────────┘      │    │   │
│  │  └──────────────────────────────┘    │   │
│  └──────────────────────────────────────┘   │
└─────────────────────────────────────────────┘
```

### 内存类型对比

| 类型 | 位置 | 可见性 | 延迟 | 容量 | 用途 |
|------|------|--------|------|------|------|
| Register | SM 内部 | 单线程 | ~1 cycle | 256 KB/SM | 局部变量 |
| Shared Memory | SM 内部 | Block 内 | ~20 cycles | 164 KB/SM | 线程协作、数据复用 |
| L1 Cache | SM 内部 | SM 内 | ~30 cycles | 128 KB/SM | 自动缓存 |
| L2 Cache | 片外 | 所有 SM | ~200 cycles | 40 MB | 全局缓存 |
| Global Memory | 片外(显存) | 所有线程 | ~400 cycles | 40/80 GB | 主数据 |
| Constant Memory | 片外(缓存) | 所有线程 | ~10 cycles(命中) | 64 KB | 只读常量 |
| Texture Memory | 片外(缓存) | 所有线程 | ~10 cycles(命中) | — | 2D 空间局部性 |

### 面试拷问

**Q1: Shared Memory 和 L1 Cache 的区别？**
- Shared Memory：用户显式管理（`__shared__`），数据生命周期由程序员控制
- L1 Cache：硬件自动管理，对程序员透明
- 硬件上它们共享同一块 SRAM，可通过 `cudaFuncSetAttribute` 调整比例

**Q2: 什么时候用 Shared Memory？**
- 同一个 block 内线程需要交换数据
- 多次读取同一块 global memory 数据（tiling）
- 需要特定访问模式避免 bank conflict

**Q3: Register Spilling 是什么？**
- 寄存器不够用时，编译器将变量"溢出"到 local memory（实际存在 global memory 里）
- 严重影响性能！`--ptxas-options=-v` 查看寄存器用量

---

## 五、cudaMalloc / cudaMemcpy 语义

### 基本流程

```cuda
// 1. Host 分配
float *h_A = (float*)malloc(N * sizeof(float));

// 2. Device 分配
float *d_A;
cudaMalloc(&d_A, N * sizeof(float));

// 3. Host → Device
cudaMemcpy(d_A, h_A, N * sizeof(float), cudaMemcpyHostToDevice);

// 4. Kernel launch
kernel<<<grid, block>>>(d_A, N);
cudaDeviceSynchronize();

// 5. Device → Host
cudaMemcpy(h_A, d_A, N * sizeof(float), cudaMemcpyDeviceToHost);

// 6. 清理
cudaFree(d_A);
free(h_A);
```

### cudaMemcpy 种类

| 方向 | 枚举值 | 说明 |
|------|--------|------|
| Host → Device | `cudaMemcpyHostToDevice` | 上传数据 |
| Device → Host | `cudaMemcpyDeviceToHost` | 取回结果 |
| Device → Device | `cudaMemcpyDeviceToDevice` | GPU 间拷贝 |
| Default | `cudaMemcpyDefault` | 自动推断（UVA 下推荐） |

---

## 六、本章自测

1. Grid / Block / Thread 的层级关系？画出索引计算公式。
2. Warp 为什么是 32？Warp Divergence 什么时候真正影响性能？
3. GPU 靠什么隐藏内存延迟？为什么需要几万个线程？
4. Shared Memory 和 Global Memory 的延迟差多少倍？什么时候用它？
5. Register Spilling 是什么？怎么检查？
6. 一个 SM 最多能驻留多少个 Block？受什么限制？

---

## 七、补充阅读

- PMPP Ch2-3：Grid/Block/Thread 补充
- CUDA C++ Programming Guide §3.2：Memory Hierarchy
- [CUDA Refresher: The CUDA Programming Model (NVIDIA Blog)](https://developer.nvidia.com/blog/cuda-refresher-cuda-programming-model/)
