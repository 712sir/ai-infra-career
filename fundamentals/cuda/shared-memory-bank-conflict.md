# CUDA Shared Memory & Bank Conflict — 面经级详解

> 状态：🟡 进行中 | 前置：PMPP Ch1-2
> 面试权重：⭐⭐⭐（AI Infra 面试必问——所有 GEMM/Attention kernel 优化都从 Shared Memory 开始）

---

## 一、CUDA 内存层次全景

### 先建立全局概念

```
Grid
├── Block (0,0)
│   ├── Shared Memory  ← 同一 Block 内所有 Thread 共享
│   │   ┌──────────────────────────┐
│   │   │  ~48-164 KB (on-chip SRAM)│  ← 快！比 Global Memory 快 ~100×
│   │   │  32 banks, 4B/bank       │
│   │   └──────────────────────────┘
│   ├── Thread 0
│   │   ├── Register    ← 最快（~0 cycle latency），每个 Thread 私有
│   │   └── Local Mem   ← 寄存器溢出时用（实际在 Global Memory，慢）
│   ├── Thread 1 ...
│   └── Thread N ...
├── Block (1,0) ...
└── Block (N,0) ...

Global Memory (HBM / GDDR)
┌──────────────────────────────────────────┐
│  ~4-80 GB (off-chip DRAM)                │  ← 慢！~500 cycles latency
│  L2 Cache: ~2-40 MB (on-chip, all SM 共享) │
└──────────────────────────────────────────┘

Constant Memory / Texture Memory
┌──────────────┐
│  read-only   │  ← 有专用 cache，适合只读数据
└──────────────┘
```

### 内存性能对比（A100 为例）

| 内存类型 | 位置 | 大小 | 延迟 | 带宽 | 作用域 |
|------|:--:|------|:--:|------|:--:|
| Register | SM 内 | ~256KB/SM | ~0 cycle | — | 1 Thread |
| Shared Memory | SM 内 | 48-164KB/SM | ~20 cycles | ~1.5 TB/s | 1 Block |
| L1 Cache | SM 内 | 共享 Shared Mem | ~20 cycles | ~1.5 TB/s | 1 Block |
| L2 Cache | 芯片上 | 2-40MB | ~200 cycles | ~3 TB/s | All SMs |
| Global Memory | 片外 HBM/GDDR | 4-80GB | ~500 cycles | ~900 GB/s(A100) | All |

### 🔥 面试口诀

> **"Shared Memory = 程序员管理的 L1 Cache"**
>
> - L1 Cache：硬件自动管理，你不知道什么在 cache 里
> - Shared Memory：你显式 `__syncthreads()` 控制，你知道什么在里面
> - 为什么快？on-chip SRAM，物理上紧挨着 SM，省了从 HBM 搬运数据的时间

---

## 二、Shared Memory 基础

### 为什么需要 Shared Memory？

```
没有 Shared Memory（朴素 GEMM）：
  每次计算需要两个数 → 从 Global Memory 读 → 500 cycles 等待
  GPU 有大量线程 → 可以通过切换 warp 隐藏延迟
  但还是浪费了大量带宽

有 Shared Memory（Tiled GEMM）：
  ① 整块数据从 Global Memory → Shared Memory（一次搬运）
  ② Block 内所有 Thread 从 Shared Memory 读（快 100×）
  ③ 计算完毕，结果写回 Global Memory
  → 减少 Global Memory 访问次数 = 减少延迟 = 提升性能
```

### 基本用法

```cuda
// 静态分配（编译期已知大小）
__global__ void kernel() {
    __shared__ float tile[32][32];  // 所有 Thread 共享
    // ...
}

// 动态分配（运行时决定大小）
__global__ void kernel_dynamic(int tile_size) {
    extern __shared__ float tile[];  // 大小在 kernel launch 时指定
    // ...
}
// kernel<<<grid, block, shared_mem_bytes>>>(args);

// 同步：确保所有 Thread 都写完了再读
__global__ void kernel() {
    __shared__ float smem[256];
    smem[threadIdx.x] = data[threadIdx.x];  // 每个 Thread 写入
    __syncthreads();                         // ← 屏障！所有 Thread 到达后才继续
    // 现在可以安全读取其他 Thread 写入的数据
    float val = smem[255 - threadIdx.x];    // 读取其他 Thread 写的数据
}
```

### 🔥 `__syncthreads()` 面试必问

**Q: __syncthreads() 到底在等什么？**

> 它是一个 **block 级同步屏障**：
> 1. 同一个 Block 内所有 Thread 都必须到达这行代码
> 2. 在此之前，所有 shared memory 写操作对之后的读操作可见
> 3. 任意 Thread 未到达 → 所有 Thread 都卡住（死锁风险！）

**Q: 为什么不能放在 if-else 里？**

```cuda
// ❌ 危险！可能导致死锁
if (threadIdx.x < 16) {
    __syncthreads();   // 只有 16 个 Thread 到达
    // ...
} else {
    // 另外 16 个 Thread 永远到不了 → 死锁！
}
```

> Warp 内所有 Thread 走同一分支时可能碰不到这个问题（warp 同步执行），但跨 warp 一定出问题。CUDA 9+ 的 Cooperative Groups 提供了更安全的替代方案。

---

## 三、Bank Conflict — Shared Memory 的性能杀手

### 什么是 Bank？

```
Shared Memory 被分为 32 个 Bank：

Bank 0:  [0x00] [0x80] [0x100] [0x180] ...  每行 4 Bytes
Bank 1:  [0x04] [0x84] [0x104] [0x184] ...
Bank 2:  [0x08] [0x88] [0x108] [0x188] ...
...
Bank 31: [0x7C] [0xFC] [0x17C] [0x1FC] ...

地址 % 128 = 属于哪个 Bank（128 bytes = 32 banks × 4 bytes）
地址 / 128 = 在 Bank 中的第几行
```

**每个 Bank 每个时钟周期只能服务一次读写。**

### 三种情况

```
假设 warp 内 32 个 Thread 同时访问 float (4B) 数组 smem[]：

情况 1：无冲突（No Conflict）
   Thread 0→Bank 0,  Thread 1→Bank 1, ... → 所有不同 Bank
   → 1 次访存完成 ✓

情况 2：广播（Broadcast）
   Thread 0→Bank 0,  Thread 1→Bank 0, ... → 所有同一 Bank 同一地址
   → 硬件广播，1 次访存完成 ✓（CC 2.0+ 支持）

情况 3：N 路冲突（N-way Bank Conflict）
   Thread 0→Bank 0,  Thread 32→Bank 0, ... → N 个 Thread 抢同一 Bank
   → 串行处理，N 次访存 ✗
```

### Bank Conflict 实战案例

```cuda
// ===== 案例 1: 无冲突 — 连续访问 =====
__global__ void no_conflict(float* out, float* in) {
    __shared__ float smem[1024];
    int tid = threadIdx.x;
    smem[tid] = in[tid];                     // Thread i → Bank i%32
    __syncthreads();
    out[tid] = smem[tid];                    // ← 32 Thread → 32 不同 Bank
    // → 1 way, 1 cycle ✓
}

// ===== 案例 2: 2 路冲突 — stride-16 访问 =====
__global__ void two_way_conflict(float* out, float* in) {
    __shared__ float smem[1024];
    int tid = threadIdx.x;
    smem[tid] = in[tid];
    __syncthreads();
    out[tid] = smem[tid * 16];               // Thread 0→Bank 0, Thread 2→Bank 0
    // Thread 0: smem[0]=Bank 0,  Thread 2: smem[32]=Bank 0 ← 冲突！
    // → 2 way, 2 cycles ✗
}

// ===== 案例 3: 32 路冲突 — 全挤一个 Bank =====
__global__ void worst_conflict(float* out, float* in) {
    __shared__ float smem[1024];
    int tid = threadIdx.x;
    smem[tid] = in[tid];
    __syncthreads();
    out[tid] = smem[tid * 32];               // Thread 0→Bank 0, Thread 1→Bank 0, ...
    // → 32 way, 32 cycles ✗✗✗ (最坏情况！)
}
```

### 🔥 解决 Bank Conflict：Padding

```cuda
// 朴素写法 — 有 bank conflict
__shared__ float tile[32][32];
float val = tile[threadIdx.x][threadIdx.y];  // 按列访问 → 同列同 Bank → 32 way！

// Padding 写法 — 消除 bank conflict
__shared__ float tile[32][32 + 1];        // ← +1 padding！
//          列数: 32 → 33（不是 4B 的倍数）
// Bank 分配错位：
//   无 padding: tile[0][0]=Bank0, tile[1][0]=Bank0 → 冲突！
//   有 padding: tile[0][0]=Bank0, tile[1][0]=Bank1 → 不冲突！
float val = tile[threadIdx.x][threadIdx.y];  // → 1 way ✓
```

**Padding 的代价**：多了 1 列 `float` = 32 × 4B = 128B per row，共 32 × 128B ≈ 4KB 额外开销。换来的是一倍速度提升。

---

## 四、Tiled Matrix Multiplication — Shared Memory 的经典应用

### 朴素 GEMM 的问题

```cuda
// 朴素 GEMM：每个 Thread 从 Global Memory 各读一次 A 的一行和 B 的一列
__global__ void gemm_naive(float* A, float* B, float* C, int N) {
    int row = blockIdx.y * blockDim.y + threadIdx.y;
    int col = blockIdx.x * blockDim.x + threadIdx.x;
    if (row < N && col < N) {
        float sum = 0.0f;
        for (int k = 0; k < N; k++) {
            sum += A[row * N + k] * B[k * N + col];  // ← 每次都读 Global Mem！
        }
        C[row * N + col] = sum;
    }
}
// 问题：2N 次 Global Memory 读 / 每个结果元素
// N=1024 → 2048 次 Global Memory 读 → 极慢！
```

### Tiled GEMM 核心思想

```
将大矩阵切分成小 Tile，一次搬运一个 Tile 到 Shared Memory：

     A (N×N)              B (N×N)              C (N×N)
┌──────────┬──┐      ┌────┬────┬──┐      ┌──────────┬──┐
│  tileA   │  │      │tile│    │  │      │          │  │
│   (32×32)│  │      │ B  │    │  │      │  tileC   │  │
├──────────┼──┤      │32× │    │  │      │  32×32   │  │
│          │  │      │ 32 │    │  │      │          │  │
│          │  │      ├────┼────┼──┤      ├──────────┼──┤
└──────────┴──┘      └────┴────┴──┘      └──────────┴──┘

算法：
for k_tile in range(0, N, TILE_SIZE):
    ① 从 Global Memory 搬运 A[k_tile:k_tile+TILE] 到 Shared Memory
    ② 从 Global Memory 搬运 B[k_tile:k_tile+TILE] 到 Shared Memory
    ③ __syncthreads()
    ④ 在 Shared Memory 上计算 tileC += tileA @ tileB（全在片上！）
    ⑤ __syncthreads()

结果：每个 Thread 只做 N/TILE_SIZE 次 Global Memory 读
     N=1024, TILE=32 → 32 次（vs 朴素版的 2048 次）→ 64× 提升！
```

### Tiled GEMM 代码（手撕级）

```cuda
#define TILE 32

__global__ void gemm_tiled(float* A, float* B, float* C, int N) {
    // Shared Memory tiles
    __shared__ float As[TILE][TILE];
    __shared__ float Bs[TILE][TILE];

    // 计算该 Thread 负责的 C[row][col]
    int row = blockIdx.y * TILE + threadIdx.y;
    int col = blockIdx.x * TILE + threadIdx.x;

    float sum = 0.0f;

    // 遍历所有 tile
    for (int t = 0; t < (N + TILE - 1) / TILE; t++) {

        // ① 协作加载 A 的 tile
        if (row < N && (t * TILE + threadIdx.x) < N)
            As[threadIdx.y][threadIdx.x] =
                A[row * N + t * TILE + threadIdx.x];
        else
            As[threadIdx.y][threadIdx.x] = 0.0f;

        // ② 协作加载 B 的 tile
        if (col < N && (t * TILE + threadIdx.y) < N)
            Bs[threadIdx.y][threadIdx.x] =
                B[(t * TILE + threadIdx.y) * N + col];
        else
            Bs[threadIdx.y][threadIdx.x] = 0.0f;

        __syncthreads();  // ← 确保整个 tile 都加载完毕！

        // ③ 在 Shared Memory 上计算（片上，快！）
        for (int k = 0; k < TILE; k++) {
            sum += As[threadIdx.y][k] * Bs[k][threadIdx.x];
        }

        __syncthreads();  // ← 确保所有 Thread 用完再覆盖 tile
    }

    if (row < N && col < N)
        C[row * N + col] = sum;
}
```

### Tile GEMM 的 Shape 追踪

```
Grid:  blockIdx.x = 0..N/32-1,  blockIdx.y = 0..N/32-1
Block: threadIdx.x = 0..31,      threadIdx.y = 0..31

每个 Block:
  - 计算 C 的一个 32×32 子块
  - Block 内 32×32=1024 个 Thread，每个 Thread 算一个 C[row][col]

Shared Memory:
  - As[32][32] = 32×32×4B = 4KB
  - Bs[32][32] = 32×32×4B = 4KB
  - 总共 8KB（GTX 1650 的 64KB Shared Memory 绰绰有余）
```

---

## 五、Bank Conflict 在 Tiled GEMM 中怎么发生的

```cuda
// 加载 A tile 时：Thread 按 threadIdx.x 变化连续读
As[threadIdx.y][threadIdx.x] = A[row * N + t * TILE + threadIdx.x];
// threadIdx.x = 0,1,2,... → 连续访问 → 无 Bank Conflict ✓

// 加载 B tile 时：Thread 按 threadIdx.y 变化（stride=32）连续读
Bs[threadIdx.y][threadIdx.x] = B[(t * TILE + threadIdx.y) * N + col];
// 但这里写入 Shared Memory 是按 threadIdx.x 变化的
// → Bs[0][0], Bs[1][0], Bs[2][0], ... → 不同行同列 → 无 Bank Conflict ✓

// ⚠️ 但在计算阶段：
for (int k = 0; k < TILE; k++)
    sum += As[threadIdx.y][k] * Bs[k][threadIdx.x];
// As[threadIdx.y][k] → 同一行不同列，32 Thread × 不同 k → 无冲突 ✓
// Bs[k][threadIdx.x] → 不同行同一列，32 Thread × 不同 k → 无冲突 ✓
//
// 但如果把 Bs 转置存放 → Bs_transposed[threadIdx.x][k]
// → Bs_transposed[0][k], Bs_transposed[1][k] → 连续地址 → 无冲突 ✓
//
// 经典优化：B 加载时就转置，让计算时的访问模式更友好
```

---

## 六、面试常见拷问

**Q1: Shared Memory 多大？一个 Block 最多用多少？**

> | GPU | 每 SM 的 Shared Memory | 每 Block 最大 |
> |------|:--:|:--:|
> | GTX 1650 (Turing) | 64KB | 48KB (默认) / 64KB (配置后) |
> | A100 (Ampere) | 164KB | 164KB |
> | H100 (Hopper) | 228KB | 228KB |
>
> 在 `cudaDeviceGetAttribute` 或 `cudaDeviceProp.sharedMemPerBlock` 查看。

**Q2: 怎么知道你写的 kernel 有 Bank Conflict？**

> `ncu --set full` 跑 profile，看 `shared_memory_bank_conflict` 指标。
> 如果没有 profiler：手动分析——按照 32 个 Thread 和 32 个 Bank 的映射关系，看有没有多个 Thread 访问同一 Bank 的不同地址。

**Q3: 为什么 Bank 是 32 个？**

> 因为一个 Warp 也是 32 个 Thread。如果 Warp 内 32 个 Thread 分到 32 个不同 Bank → 1 cycle 完成 → 理想情况。

**Q4: Shared Memory 和 L1 Cache 抢占同一块 SRAM——怎么配？**

> ```cuda
> // 偏向 Shared Memory（常用）
> cudaDeviceSetCacheConfig(cudaFuncCachePreferShared);
> // 偏向 L1 Cache
> cudaDeviceSetCacheConfig(cudaFuncCachePreferL1);
> ```
> Turing 架构 (GTX 1650): Shared Mem 和 L1 统一 64KB，默认各 32KB。

**Q5: 什么时候共享内存不够用了？**

> 当 Block 内 Thread 太多 + Tile 太大时。`Occupancy = Active Warps / Max Warps per SM`。
> 每个 Block 用更多 Shared Memory → 每个 SM 能同时跑的 Block 数量减少 → Occupancy 降低 → 隐藏延迟的能力下降。
>
> 需要在 Shared Memory 大小和 Occupancy 之间权衡。这是 GEMM 优化的核心 trade-off。

---

## 七、手撕自测题

1. [ ] 写出 Tiled GEMM 的完整 kernel 代码（含 `__syncthreads()` 的位置）
2. [ ] 为什么 `__syncthreads()` 有两次？第一次和第二次分别保护什么？
3. [ ] 如果 `TILE=16`，一个 Block 的 Shared Memory 用多少 KB？
4. [ ] Bank 冲突和 Warp 大小都是 32——这是巧合还是故意设计？
5. [ ] 为什么 B 矩阵加载时转置能提升性能？
6. [ ] 在 padding 示例中为什么是 `+1` 而不是 `+8` 或 `+16`？
