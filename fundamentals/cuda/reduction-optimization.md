# CUDA Parallel Reduction — 面经级详解

> 状态：🟡 进行中 | 前置：Shared Memory + Bank Conflict
> 面试权重：⭐⭐⭐（"手写 Reduction 的 7 个优化版本"是 NVIDIA 面试经典题）
> 参考：Mark Harris "Optimizing Parallel Reduction in CUDA" (NVIDIA)

---

## 问题定义

**输入**：长度为 N 的数组 `[a₀, a₁, a₂, ..., a_{N-1}]`
**输出**：所有元素的和 `S = Σ a_i`

CPU 上：一个 for 循环，O(N)。
GPU 上：怎么并行？关键挑战是**怎么把 N 个部分和合并成一个最终和**。

---

## 版本 0：Naive Interleaved Addressing

```cuda
__global__ void reduce_v0(float* g_idata, float* g_odata, int N) {
    extern __shared__ float sdata[];

    int tid = threadIdx.x;
    int i = blockIdx.x * blockDim.x + threadIdx.x;

    // 加载到 Shared Memory
    sdata[tid] = (i < N) ? g_idata[i] : 0.0f;
    __syncthreads();

    // 规约：步长翻倍，参与线程减半
    for (int stride = 1; stride < blockDim.x; stride *= 2) {
        if (tid % (2 * stride) == 0) {
            sdata[tid] += sdata[tid + stride];
        }
        __syncthreads();
    }

    // 写回
    if (tid == 0) g_odata[blockIdx.x] = sdata[0];
}
```

### 🔥 问题分析

```
步长 stride=1:
  Thread 0: sdata[0] += sdata[1]   ← 工作
  Thread 1: idle                   ← 闲着
  Thread 2: sdata[2] += sdata[3]   ← 工作
  Thread 3: idle                   ← 闲着
  ...
  
→ 只有一半 Thread 在工作！利用率 50%

更严重：Warp Divergence!
  Warp 0 (Thread 0-31):
    Thread 0: 工作 (tid%2==0)
    Thread 1: 跳过
    Thread 2: 工作
    ...
  → 每个 warp 内 if-else 分支 → 串行执行！
```

| 版本 | 技术 | 问题 |
|:--:|------|------|
| V0 | Interleaved Addressing | 50% 线程利用率 + 严重的 Warp Divergence + 非合并访问 |

---

## 版本 1：解决 Warp Divergence

```cuda
__global__ void reduce_v1(float* g_idata, float* g_odata, int N) {
    extern __shared__ float sdata[];
    int tid = threadIdx.x;
    int i = blockIdx.x * blockDim.x + threadIdx.x;
    sdata[tid] = (i < N) ? g_idata[i] : 0.0f;
    __syncthreads();

    // 关键变化：stride 从大到小！
    // stride=512: Thread 0-511 工作 ← 满负载
    // stride=256: Thread 0-255 工作
    // stride=128: Thread 0-127 工作
    // ...         连续 Thread 都在工作 → 无 divergence！
    for (int stride = blockDim.x / 2; stride > 0; stride >>= 1) {
        if (tid < stride) {
            sdata[tid] += sdata[tid + stride];
        }
        __syncthreads();
    }

    if (tid == 0) g_odata[blockIdx.x] = sdata[0];
}
```

### 为什么 V1 比 V0 好？

```
V0 (stride从小到大):            V1 (stride从大到小):
  stride=1: Thread 0,2,4,...    stride=512: Thread 0-511 (连续)
           → Warp 内混合              → 整个前半 Warp 工作
  stride=2: Thread 0,4,8,...    stride=256: Thread 0-255 (连续)
           → 更稀疏                  → 连续段缩小
  ...
  问题：活跃 Thread 分散在 Warp 间    优势：活跃 Thread 连续 → 无 Divergence
```

---

## 版本 2：解决 Shared Memory Bank Conflict

V1 虽然解决了 divergence，但还有 Bank Conflict：

```
stride=512: Thread 0 读 sdata[0] 和 sdata[512]
            Bank(sdata[0])   = 0 % 32 = Bank 0
            Bank(sdata[512]) = (512*4)/4 % 32 = 512 % 32 = Bank 0 ← 冲突！

stride=256: Thread 0 读 sdata[0] 和 sdata[256]
            Bank(0) = 0, Bank(256) = 256%32 = 0 ← 还是 Bank 0！

V1 每一步 stride 都是 2 的幂 → sdata[tid+stride] 和 sdata[tid] 必定在同一个 Bank！
→ 每一步都有 Bank Conflict！
```

**修复：顺序寻址 (Sequential Addressing)**：

```cuda
__global__ void reduce_v2(float* g_idata, float* g_odata, int N) {
    extern __shared__ float sdata[];
    int tid = threadIdx.x;
    int i = blockIdx.x * blockDim.x * 2 + threadIdx.x;

    // 每个 Thread 加载 2 个元素，做第一次规约
    sdata[tid] = g_idata[i] + g_idata[i + blockDim.x];
    __syncthreads();

    for (int stride = blockDim.x / 2; stride > 0; stride >>= 1) {
        if (tid < stride) {
            sdata[tid] += sdata[tid + stride];
            // tid=0: 读 sdata[0] + sdata[stride]
            // sdata[stride] → Bank (stride*4)/4 % 32 = stride % 32
            // 当 stride=16 时: Thread 0→Bank16, Thread 1→Bank17, ...
            // → 连续 Thread 访问不同 Bank → 无冲突 ✓
        }
        __syncthreads();
    }

    if (tid == 0) g_odata[blockIdx.x] = sdata[0];
}
```

| 版本 | 技术 | 改进 |
|:--:|------|------|
| V2 | Sequential Addressing | 消除大部分 Bank Conflict（除最后几步） |

---

## 版本 3：首次加法在加载时完成

V2 已经很好，但第一步规约可以合并到加载中：

```cuda
// V2 加载: 需要 2*blockDim 个元素的空间（grid 只用一半）
sdata[tid] = g_idata[i] + g_idata[i + blockDim.x];  // ← 加载时就做一次加法

// V3: 加载时做加法 = 减少一半的 stride 迭代
```

这个优化不需要改内核结构，只要在 Host 端把 grid 大小减半即可。  

---

## 版本 4：循环展开 (Loop Unrolling)

```cuda
__global__ void reduce_v4(float* g_idata, float* g_odata, int N) {
    extern __shared__ float sdata[];
    int tid = threadIdx.x;
    int i = blockIdx.x * blockDim.x * 2 + threadIdx.x;

    sdata[tid] = g_idata[i] + g_idata[i + blockDim.x];
    __syncthreads();

    // 手动展开：减少循环开销 + 减少 __syncthreads() 调用
    // 展开最后 6 步（warp 大小=32, 32→16→8→4→2→1）
    if (blockDim.x >= 1024) { if (tid < 512) sdata[tid] += sdata[tid + 512]; __syncthreads(); }
    if (blockDim.x >=  512) { if (tid < 256) sdata[tid] += sdata[tid + 256]; __syncthreads(); }
    if (blockDim.x >=  256) { if (tid < 128) sdata[tid] += sdata[tid + 128]; __syncthreads(); }
    if (blockDim.x >=  128) { if (tid <  64) sdata[tid] += sdata[tid +  64]; __syncthreads(); }
    // 64→32: 最后一个需要 __syncthreads 的步骤（跨 warp）
    if (tid < 32) {  // ← 从这里开始只有一个 warp，不需要 __syncthreads()！
        // V5: 用 volatile + warp shuffle 替代 shared memory
    }
}
```

---

## 版本 5：Warp Shuffle（面试最常问！）

进入单个 Warp（32 Thread）后，不需要 Shared Memory——直接用 Warp Shuffle：

```cuda
__global__ void reduce_v5(float* g_idata, float* g_odata, int N) {
    extern __shared__ float sdata[];
    int tid = threadIdx.x;
    int i = blockIdx.x * blockDim.x * 2 + threadIdx.x;
    float sum = g_idata[i] + g_idata[i + blockDim.x];

    // 阶段 1: Shared Memory 跨 Warp 规约
    sdata[tid] = sum;
    __syncthreads();
    if (blockDim.x >= 1024) { if (tid < 512) sdata[tid] += sdata[tid + 512]; __syncthreads(); }
    if (blockDim.x >=  512) { if (tid < 256) sdata[tid] += sdata[tid + 256]; __syncthreads(); }
    if (blockDim.x >=  256) { if (tid < 128) sdata[tid] += sdata[tid + 128]; __syncthreads(); }
    if (blockDim.x >=  128) { if (tid <  64) sdata[tid] += sdata[tid +  64]; __syncthreads(); }

    // 阶段 2: Warp Shuffle（单 warp 内规约，不需要 shared memory！）
    if (tid < 32) {
        sum = sdata[tid];
        // __shfl_down_sync: 从 lane_id+16 取数，mask=0xFFFFFFFF 表示全部参与
        sum += __shfl_down_sync(0xFFFFFFFF, sum, 16);  // stride=16
        sum += __shfl_down_sync(0xFFFFFFFF, sum, 8);   // stride=8
        sum += __shfl_down_sync(0xFFFFFFFF, sum, 4);   // stride=4
        sum += __shfl_down_sync(0xFFFFFFFF, sum, 2);   // stride=2
        sum += __shfl_down_sync(0xFFFFFFFF, sum, 1);   // stride=1
        // 现在 lane 0 拥有最终结果
        if (tid == 0) g_odata[blockIdx.x] = sum;
    }
}
```

### 🔥 Warp Shuffle 原理

```
Warp = 32 Threads (lane 0..31)

__shfl_down_sync(mask, val, delta):
  lane 0 ← 读取 lane (0+delta) 的 val
  lane 1 ← 读取 lane (1+delta) 的 val
  ...
  
stride=16: lane 0 ← lane 16, lane 1 ← lane 17, ...
stride=8:  lane 0 ← lane  8, lane 1 ← lane  9, ...
stride=4:  lane 0 ← lane  4, ...
stride=2:  lane 0 ← lane  2, ...
stride=1:  lane 0 ← lane  1  (lane 0 拿到总和)
```

**Warp Shuffle vs Shared Memory**：
| | Shared Memory | Warp Shuffle |
|------|:--:|:--:|
| 延迟 | ~20 cycles | ~5 cycles |
| 需要 `__syncthreads` | 是 | 否（同一 warp 天然同步） |
| 需要显存 | 需要声明 `__shared__` | 不占 shared memory |
| 跨 Warp | 可以 | 不可以 |

---

## 版本 6：完全 Warp Shuffle

```cuda
__device__ float warpReduceSum(float val) {
    val += __shfl_down_sync(0xFFFFFFFF, val, 16);
    val += __shfl_down_sync(0xFFFFFFFF, val, 8);
    val += __shfl_down_sync(0xFFFFFFFF, val, 4);
    val += __shfl_down_sync(0xFFFFFFFF, val, 2);
    val += __shfl_down_sync(0xFFFFFFFF, val, 1);
    return val;
}

__global__ void reduce_v6(float* g_idata, float* g_odata, int N) {
    extern __shared__ float sdata[];
    int tid = threadIdx.x;
    int i = blockIdx.x * blockDim.x * 2 + threadIdx.x;

    // 每 Thread 先做自己的局部规约
    float sum = g_idata[i] + g_idata[i + blockDim.x];

    // 跨 Warp 规约到 sdata[warp_id]
    int warpId = tid / 32;
    int laneId = tid % 32;
    sum = warpReduceSum(sum);
    if (laneId == 0) sdata[warpId] = sum;
    __syncthreads();

    // 最后一个 warp 做最终规约
    sum = (tid < blockDim.x / 32) ? sdata[tid] : 0.0f;
    if (warpId == 0) sum = warpReduceSum(sum);
    if (tid == 0) g_odata[blockIdx.x] = sum;
}
```

---

## 7 版本性能对比（参考数据）

| 版本 | 技术 | 相对性能 | 瓶颈 |
|:--:|------|:--:|------|
| V0 | Naive Interleaved | 1.0× | Divergence + Bank Conflict |
| V1 | Stride 从大到小 | ~2× | Bank Conflict |
| V2 | Sequential Addressing | ~4× | 循环开销 |
| V3 | 加载时首次规约 | ~4.5× | 循环开销 |
| V4 | 循环展开 | ~6× | 跨 Warp Sync |
| V5 | Warp Shuffle 末段 | ~10× | 跨 Warp 仍需 SMEM |
| V6 | 完全 Warp Shuffle | ~15× | 带宽瓶颈（接近理论极限） |

---

## 面试拷问

**Q1: "给我手写一个 Reduction kernel" → 你写哪个？**

> 写 V1 或 V2（10 行代码，清晰）。展示你理解为什么 stride 从大到小，然后口头描述 V5/V6 的 Warp Shuffle 优化。

**Q2: 为什么 V0 的 stride 从小到大会有 Warp Divergence？**

> stride=1 时，只有 Thread 0, 2, 4, 6... 参与计算。Warp 内相邻 Thread 走不同分支（工作 vs 跳过）→ 串行执行。

**Q3: V1 没有 Bank Conflict 吗？**

> 有。sdata[tid+stride] 和 sdata[tid] 在 stride 足够大时在同一 Bank → 2-way conflict。V2 用 Sequential Addressing 解决了。

**Q4: Warp Shuffle 为什么不用 `__syncthreads()`？**

> 同一 Warp 内 32 个 Thread 在硬件上同步执行（SIMT），`__shfl_down_sync` 自带同步语义（mask 参数指定的所有 lane 在调用前已经同步）。

**Q5: Reduction 是 memory-bound 还是 compute-bound？**

> Memory-bound。每个加法只做一个 FLOP，但要读一个 float。计算强度极低 → Roofline Model 中远低于 ridge point。

---

## 手撕自测

1. [ ] 写出 V1（stride 从大到小）的完整 kernel
2. [ ] 写出 `warpReduceSum` 函数（5 行 `__shfl_down_sync`）
3. [ ] 口述 7 个版本的演进和每个版本解决的问题
4. [ ] 解释为什么 `__syncthreads()` 要放在 for 循环里面而不是外面
