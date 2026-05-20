# 基础技术栈学习计划（B 线 · B+C 混合版）

> **策略**：5 条并行子轨道 + 3 个递进项目（MiniInfer → MiniQuant → MiniMegatron）
>
> **总周期**：W1–W44 | **每日投入**：~2h | **硬件**：GTX 1650 4GB + 云 GPU（W10 起）
>
> **当前日期**：2026-05-20 | **状态**：🟡 规划完成

---

# 五条子轨道总览

| 轨道 | 方向 | 周期 | 权重 |
|------|------|------|------|
| **B1** | CUDA/GPU 编程 | W1–W40 | 🔴 最高 |
| **B2** | C++ & Python 深度 | W1–W18 | 🔴 最高 |
| **B3** | 分布式系统 | W10–W34 | 🟡 高 |
| **B4** | PyTorch 内部 & Triton | W8–W24 | 🟡 高 |
| **B5** | 推理/训练框架源码 | W16–W44 | 🟢 中 |

# 三个项目总览

| 项目 | 周期 | 核心产出 |
|------|------|----------|
| **MiniInfer** | W10–W26 | 从零实现推理引擎（KV Cache / PagedAttention / Continuous Batching / TP） |
| **MiniQuant** | W22–W34 | 量化推理引擎（AWQ / GPTQ / INT4 GEMM / CUTLASS） |
| **MiniMegatron** | W30–W46 | 分布式训练框架（TP+PP+DP / ZeRO / 混合精度 / FlashAttention） |

---

# Phase 1：基础建设（W1–W10）

> **目标**：搭建 CUDA/C++/Python 能力底座，为 MiniInfer 项目准备。
> **项目状态**：MiniInfer 未启动，纯知识积累。

---

## W1 (05.20–05.26)：CUDA 编程模型 + C++ 智能指针

### B1 CUDA — CUDA 编程模型入门

| 项目 | 内容 |
|------|------|
| **资源** | 《PMMP》Ch1：Introduction（异构并行计算、CPU vs GPU 架构差异、CUDA 平台概述） |
|  | 《PMMP》Ch2：Heterogeneous Data Parallel Computing（数据并行的概念、CUDA C 程序结构、kernel launch 语义） |
|  | 代码：手写第一个 Vector Addition kernel（编译 → 运行 → 验证正确性） |
| **验收** | 能说出 host/device 代码的区别，理解 `<<<grid, block>>>` 语法，能写一个正确的 vecAdd kernel |
| **产出** | `fundamentals/cuda/pmpp-notes/ch01-heterogeneous-computing.md` |
|  | `fundamentals/cuda/pmpp-notes/ch02-data-parallel.md` |
|  | `fundamentals/cuda/kernels/01-vec-add/vec_add.cu` |

### B2 C++ — 智能指针 + 移动语义

| 项目 | 内容 |
|------|------|
| **资源** | 《Effective Modern C++》Item 17–25：`unique_ptr`、`shared_ptr`、`weak_ptr`、自定义 deleter |
|  | 《Effective Modern C++》Item 23–29：`std::move`、`std::forward`、万能引用、完美转发 |
|  | 代码：写一个自定义 `make_unique`，写一个使用 `shared_ptr` 的循环引用场景并用 `weak_ptr` 解决 |
| **验收** | 能解释 `shared_ptr` 控制块结构、`weak_ptr::lock()` 实现原理、`move` vs `forward` 的区别 |
| **产出** | `fundamentals/cpp/smart-pointers.md` |
|  | `fundamentals/cpp/move-semantics.md` |
|  | `fundamentals/cpp/code/smart-ptr-demo.cpp` |

### B2 Python — 装饰器 + 生成器

| 项目 | 内容 |
|------|------|
| **资源** | 《Fluent Python》Ch7：Decorators and Closures（装饰器语法糖、闭包原理、`functools.wraps`、参数化装饰器） |
|  | 《Fluent Python》Ch14：Iterables, Iterators, and Generators（`__iter__`/`__next__`、`yield from`、生成器表达式） |
|  | 代码：实现 `@timer`、`@retry` 装饰器；用生成器实现 lazy 文件读取 |
| **验收** | 能手写带参数和不带参数的装饰器，能用 `yield` 实现协程风格的消费者-生产者 |
| **产出** | `fundamentals/python/decorators.md` |
|  | `fundamentals/python/generators.md` |

---

## W2 (05.27–06.02)：Grid/Block/Thread + C++ 模板

### B1 CUDA — 线程组织 + 内存层次

| 项目 | 内容 |
|------|------|
| **资源** | 《PMMP》Ch2（续）：Grid、Block、Thread 的三层组织，`threadIdx`/`blockIdx`/`blockDim`/`gridDim` |
|  | 《PMMP》Ch3：多维 Grid/Block 组织方式，边界处理 |
|  | CUDA C++ Programming Guide §3.2：Memory Hierarchy（global/local/shared/register/constant/texture） |
|  | 代码：手写 grid-stride loop 版 Vector Addition |
| **验收** | 能画出 Grid→Block→Thread→Warp 的层级图，理解 grid-stride loop 为什么能处理任意大数组 |
| **产出** | `fundamentals/cuda/pmpp-notes/ch03-thread-organization.md` |
|  | `fundamentals/cuda/kernels/02-grid-stride/grid_stride_vec_add.cu` |

### B2 C++ — 模板深入

| 项目 | 内容 |
|------|------|
| **资源** | 《C++ Templates: The Complete Guide》Part 1：函数模板、类模板、非类型模板参数、模板特化 |
|  | CppCon Back to Basics: Templates (YouTube) |
|  | 代码：实现一个 `Array<T, N>` 编译期固定大小数组；实现 `is_same<T, U>` type trait |
| **验收** | 能解释 SFINAE 的基本思想、模板特化和偏特化的区别 |
| **产出** | `fundamentals/cpp/templates.md` |
|  | `fundamentals/cpp/code/template-demo.cpp` |

### B2 Python — GIL 与多线程/多进程

| 项目 | 内容 |
|------|------|
| **资源** | David Beazley: "Understanding the Python GIL" (YouTube) |
|  | 《Fluent Python》Ch18：Concurrency with asyncio（event loop、coroutine、`await`、`asyncio.gather`） |
|  | 代码：对比 CPU 密集型任务用 `threading` vs `multiprocessing` vs `asyncio` 的性能 |
| **验收** | 能解释 GIL 为什么在 IO 密集时影响小、在 CPU 密集时致命；知道何时用 `pool.map` 何时用 `asyncio.gather` |
| **产出** | `fundamentals/python/gil-multiprocessing.md` |
|  | `fundamentals/python/code/gil-benchmark.py` |

---

## W3 (06.03–06.09)：Shared Memory + 多线程

### B1 CUDA — Shared Memory + Bank Conflict

| 项目 | 内容 |
|------|------|
| **资源** | 《PMMP》Ch5：Memory Architecture and Locality（shared memory 详细、bank conflict、memory coalescing） |
|  | 《PMMP》Ch6：Performance Considerations（occupancy、latency hiding、warp divergence） |
|  | CUDA C++ Programming Guide §3.2.3 Shared Memory |
|  | 代码：Matrix Multiply naive global version，用 `nvprof`/`nsys` profile |
| **验收** | 能解释 bank conflict 的成因和解决方法（padding），理解 warp divergence 对性能的影响 |
| **产出** | `fundamentals/cuda/pmpp-notes/ch05-memory-architecture.md` |
|  | `fundamentals/cuda/pmpp-notes/ch06-performance.md` |
|  | `fundamentals/cuda/kernels/03-matmul-naive/matmul_naive.cu` |

### B2 C++ — 多线程编程

| 项目 | 内容 |
|------|------|
| **资源** | 《C++ Concurrency in Action》Ch1–4：`std::thread`、`std::mutex`、`std::lock_guard`、`std::unique_lock`、`std::atomic`、`std::condition_variable` |
|  | 代码：线程安全的有界阻塞队列（`BoundedBlockingQueue<T>`）、用 `std::atomic` 实现无锁计数器 |
| **验收** | 能写出正确的生产者-消费者队列，能解释 `atomic` 的 memory order（relaxed/acquire/release/seq_cst） |
| **产出** | `fundamentals/cpp/multithreading.md` |
|  | `fundamentals/cpp/code/bounded-queue.hpp` |

### B2 Python — 异步编程

| 项目 | 内容 |
|------|------|
| **资源** | Real Python: "Async IO in Python: A Complete Walkthrough" |
|  | 《Fluent Python》Ch19：Concurrency Models（future、executor、queue）|
|  | 代码：用 `asyncio` 实现简易 HTTP 并发下载器 |
| **验收** | 能写出 `async`/`await` 的正确用法，理解 event loop 如何调度 coroutine |
| **产出** | `fundamentals/python/async-io.md` |
|  | `fundamentals/python/code/async-downloader.py` |

---

## W4 (06.10–06.16)：Reduction + CMake + 内存管理

### B1 CUDA — 并行规约（Reduction）

| 项目 | 内容 |
|------|------|
| **资源** | 《PMMP》Ch7：Parallel Patterns — Reduction（naive interleaved addressing → sequential addressing → warp shuffle） |
|  | Mark Harris: "Optimizing Parallel Reduction in CUDA" (NVIDIA Dev Blog) |
|  | 代码：实现 7 个版本 reduction，profile 对比性能 |
| **验收** | 能手写 share memory + warp shuffle 优化版 reduction kernel，理解 divergence 和 bank conflict 在各版本中如何变化 |
| **产出** | `fundamentals/cuda/pmpp-notes/ch07-reduction-scan.md` |
|  | `fundamentals/cuda/kernels/04-reduction/reduction_v1_to_v7.cu` |
|  | `fundamentals/cuda/kernels/04-reduction/benchmark.md`（7 版性能对比图） |

### B2 C++ — CMake 工程化

| 项目 | 内容 |
|------|------|
| **资源** | "Professional CMake" Ch1–7：`add_executable`/`add_library`、`target_*` 系列、`find_package`、`FetchContent` |
|  | Modern CMake (YouTube: "Effective Modern CMake" by Daniel Pfeifer) |
|  | 代码：把之前写的 CUDA kernel 用 CMake 组织成项目（`enable_language(CUDA)`） |
| **验收** | 能搭建一个包含 CUDA 源码 + C++ 测试的 CMake 项目 |
| **产出** | `fundamentals/cpp/cmake.md` |
|  | 重构 `fundamentals/cuda/kernels/` 目录，添加 `CMakeLists.txt` |

### B2 Python — 内存管理

| 项目 | 内容 |
|------|------|
| **资源** | 《CPython Internals》Ch5：Memory Management（引用计数、GC 分代回收、`gc` 模块、循环引用检测、`__slots__`、weakref） |
|  | Nina Zakharenko: "Memory Management in Python" (PyCon) |
|  | 代码：用 `memory_profiler` 对比 `__slots__` vs `__dict__` 的内存占用 |
| **验收** | 能解释 CPython 的三色标记 GC、`__slots__` 如何节省内存、buffer protocol 的原理 |
| **产出** | `fundamentals/python/memory-management.md` |
|  | `fundamentals/python/code/memory-demo.py` |

---

## W5 (06.17–06.23)：Scan + pybind11 + Profiling

### B1 CUDA — 并行前缀和（Scan）

| 项目 | 内容 |
|------|------|
| **资源** | 《PMMP》Ch7（续）：Scan（Blelloch scan vs Kogge-Stone、work-efficient parallel scan） |
|  | CUDA Toolkit Samples：`scan` example |
|  | 代码：实现 inclusive/exclusive scan |
| **验收** | 能画出 Blelloch scan 各 step 的数据流，理解 work-efficient 的含义 |
| **产出** | `fundamentals/cuda/pmpp-notes/ch07-scan-advanced.md` |
|  | `fundamentals/cuda/kernels/05-scan/scan.cu` |

### B1 CUDA — Profiling 工具链

| 项目 | 内容 |
|------|------|
| **资源** | NVIDIA: "NVIDIA Nsight Systems User Guide" §1–3 |
|  | NVIDIA: "NVIDIA Nsight Compute User Guide" §1–3 |
|  | 视频：cuda-mode Lecture: Introduction to Profiling (lecture 1) |
|  | 代码：用 `nsys` profile reduction kernel，用 `ncu` 分析 stall reasons |
| **验收** | 能用 `nsys` 看到 kernel launch timeline，用 `ncu` 看到 memory/compute throughput |
| **产出** | `fundamentals/cuda/profiling/tools-overview.md` |
|  | `fundamentals/cuda/profiling/nsys-quick-ref.md` |
|  | `fundamentals/cuda/profiling/ncu-quick-ref.md` |

### B2 C++ — pybind11 基础

| 项目 | 内容 |
|------|------|
| **资源** | pybind11 官方文档：First Steps, Functions, Classes, Build Systems |
|  | 视频：Robert Smallshire "Integrating Python and C++ with pybind11" |
|  | 代码：将 Vector Addition kernel 封装为 Python 可调用的函数，实现 numpy array 零拷贝 |
| **验收** | 能从 Python 调用 C++ 函数并传入/返回 numpy 数组 |
| **产出** | `fundamentals/python/pybind11-basics.md` |
|  | `fundamentals/python/code/pybind11-demo/`（完整 CMake 项目） |

---

## W6 (06.24–06.30)：CUDA C++ Guide + STL 深入

### B1 CUDA — Programming Guide 精读（1）

| 项目 | 内容 |
|------|------|
| **资源** | CUDA C++ Programming Guide §1–3：Programming Model（SIMT、线程层级、内存层级、异构编程） |
|  | CUDA C++ Programming Guide §5：Performance Guidelines（occupancy calculator、execution configuration） |
|  | 代码：对比不同 block size 对 occupancy 和性能的影响 |
| **验收** | 能根据 kernel 的 register/shared memory 使用量推算 occupancy |
| **产出** | `fundamentals/cuda/prog-guide/01-programming-model.md` |
|  |  occupancy 计算表格（Excel/CSV） |
| **更新主题** ✅ CUDA Programming Guide 前 3 章

### B2 C++ — STL 内部原理

| 项目 | 内容 |
|------|------|
| **资源** | "Inside STL" 系列博客（或侯捷《STL 源码剖析》选读）：`vector` 扩容策略、`unordered_map` hash 表实现、`deque` 分段结构 |
|  | cppreference：各容器的 iterator invalidation rules |
|  | 代码：手写简易 `vector`、`unordered_map`（开链法） |
| **验收** | 能解释 `vector::push_back` 的 amortized O(1) 扩容、`unordered_map` 的 load_factor 和 rehash、`deque` 的 chunk 管理 |
| **产出** | `fundamentals/cpp/stl-internals.md` |
|  | `fundamentals/cpp/code/tiny-stl/vector.hpp` |
|  | `fundamentals/cpp/code/tiny-stl/hashmap.hpp` |

---

## W7 (07.01–07.07)：GEMM 入门 + CPython 内部

### B1 CUDA — GEMM naive + shared memory

| 项目 | 内容 |
|------|------|
| **资源** | "how-to-optimize-gemm" (GitHub: /hwu-dev/how-to-optimize-gemm) README + naive 版 |
|  | 《PMMP》Ch4（复习）：Tiled Matrix Multiplication |
|  | 代码：手写 naive GEMM → shared memory tiled GEMM |
| **验收** | 能写出 tiled GEMM，理解 tile size 如何影响 shared memory 使用量和 bank conflict |
| **产出** | `fundamentals/cuda/optimize-gemm/01-naive/` |
|  | `fundamentals/cuda/optimize-gemm/02-shared-mem/` |
|  | `fundamentals/cuda/optimize-gemm/notes.md`（每一步的优化原理和性能数据）|

### B2 Python — CPython 内部基础

| 项目 | 内容 |
|------|------|
| **资源** | 《CPython Internals》Ch1–3：编译过程（source → AST → bytecode → execution）、PyObject 结构、引用计数实现细节 |
|  | Philip Guo: "CPython internals: A ten-hour codewalk through the Python interpreter source code" (选择前 3 小时) |
|  | 代码：用 `dis` 模块拆解简单函数的 bytecode |
| **验收** | 能解释 Python 中 `a = 1` 这一行代码在解释器内部发生了什么 |
| **产出** | `fundamentals/python/cpython-internals.md` |
|  | `fundamentals/python/code/dis-demo.py` |

---

## W8 (07.08–07.14)：GEMM 进阶 + PyTorch Tensor 源码

### B1 CUDA — GEMM 优化链（1）

| 项目 | 内容 |
|------|------|
| **资源** | "how-to-optimize-gemm"：global memory coalescing、bank conflict fix、双缓冲 |
|  | cuda-mode Lecture 4: "CUDA Mode: GEMM" |
|  | 代码：实现 coalescing 优化版 + padding 消除 bank conflict |
| **验收** | 能用 `ncu` 测出 l1/shared/l2 命中率 |
| **产出** | `fundamentals/cuda/optimize-gemm/03-coalescing/` |
|  | `fundamentals/cuda/optimize-gemm/04-bank-conflict-fix/` |

### B4 PyTorch — Tensor 内部

| 项目 | 内容 |
|------|------|
| **资源** | ezyang "PyTorch Internals" blog post (Part 1: Tensor) |
|  | PyTorch 源码：`c10/core/TensorImpl.h`、`aten/src/ATen/core/TensorBase.h` |
|  | 代码：理解 `stride`、`contiguous`、`view` vs `reshape`、`storage` offset 机制 |
| **验收** | 能解释为什么 `a.T.contiguous()` 会触发数据拷贝，而 `a.view(-1)` 不会（如果 contiguous） |
| **产出** | `fundamentals/python/pytorch-internals/01-tensor.md` |
|  | 示意图：stride 与 contiguous 的关系 |

---

## W9 (07.15–07.21)：Warp-Level + PyTorch autograd

### B1 CUDA — Warp 级原语 + Cooperative Groups

| 项目 | 内容 |
|------|------|
| **资源** | CUDA C++ Programming Guide §4.3：Warp Shuffle Functions（`__shfl_sync`、`__shfl_down_sync`） |
|  | CUDA C++ Programming Guide §3.6：Cooperative Groups（`cooperative_groups::tiled_partition`、`thread_block_tile`） |
|  | 代码：用 warp shuffle 实现 block-level reduction 最终版 |
| **验收** | 能解释 warp shuffle 相比 shared memory reduction 的优势，理解 `__syncwarp()` 的必要性 |
| **产出** | `fundamentals/cuda/warp-shuffle.md` |
|  | `fundamentals/cuda/kernels/06-warp-reduce/` |

### B4 PyTorch — autograd 源码

| 项目 | 内容 |
|------|------|
| **资源** | ezyang "PyTorch Internals" Part 2: autograd |
|  | PyTorch 源码：`torch/csrc/autograd/engine.cpp`、`variable.cpp` |
|  | 代码：手动追踪一个简单计算图的 backward，打印 `grad_fn` 链 |
| **验收** | 能解释 autograd 如何构建计算图、`retain_graph` 的用途、`saved_tensors` 在反向传播中的作用 |
| **产出** | `fundamentals/python/pytorch-internals/02-autograd.md` |
|  | `fundamentals/python/code/autograd-trace.py` |

---

## W10 (07.22–07.28)：Tensor Core 入门 + B3 分布式启动

### B1 CUDA — Tensor Core 编程

| 项目 | 内容 |
|------|------|
| **资源** | NVIDIA: "Programming Tensor Cores in CUDA 9" (Dev Blog) |
|  | CUDA C++ Programming Guide §7.24：Warp Matrix Functions (`mma.sync`) |
|  | 代码：用 `mma.sync.f16.f16.f32` 实现 16×16×16 GEMM micro-kernel |
| **验收** | 能解释 Tensor Core 的矩阵分块方式（m16n8k16/m16n8k8），理解 FP16 accum 到 FP32 的数据流 |
| **产出** | `fundamentals/cuda/optimize-gemm/05-tensor-core/` |
|  | `fundamentals/gpu-arch/tensor-core-deep-dive.md` |

### B3 分布式 — MPI + AllReduce 基础

| 项目 | 内容 |
|------|------|
| **资源** | MPI 教程：MPI Tutorial 前 5 章（`MPI_Send`/`Recv`、`MPI_Bcast`、`MPI_Reduce`、`MPI_Allreduce`、`MPI_Gather`） |
|  | 论文：Thakur et al. "Optimization of Collective Communication Operations in MPICH" |
|  | 代码：用 MPI 实现 Ring AllReduce 的简化版 |
| **验收** | 能画出 Ring AllReduce 的 2×(N-1) 步数据流，理解 Recursive Halving-Doubling |
| **产出** | `fundamentals/distributed/mpi-basics.md` |
|  | `fundamentals/distributed/code/ring-allreduce-mpi/`（C++ 实现） |

---

# Phase 2：MiniInfer + 系统深入（W10–W26）

> **目标**：完成 MiniInfer 推理引擎的 4 个迭代版本，同时推进 B1（GEMM/FlashAttention）、B3（分布式通信）、B4（Triton）、B5（vLLM 源码）四个轨道。
>
> **MiniInfer 迭代路线**：
> - v0：CPU 单 token 推理（W10–W11）
> - v1：GPU 推理 + KV Cache（W12–W16）
> - v2：PagedAttention + Continuous Batching（W17–W23）
> - v3：Tensor Parallelism 分布式推理（W24–W26）

---

## W10 (07.22–07.28)：MiniInfer 启动

### 🚀 MiniInfer v0.1 — CPU 单 token 推理（启动）

| 项目 | 内容 |
|------|------|
| **目标** | 加载 GPT-2 权重（从 HuggingFace），跑通一次 CPU 前向推理，得到 logits |
| **资源** | karpathy/nanoGPT `model.py`（GPT-2 架构参考） |
| **验收** | 给定 prompt "Hello, my name is"，能正确输出 logits 值（与 PyTorch Transformer 对比验证） |
| **产出** | `projects/miniinfer/` 仓库初始化 |
|  | `projects/miniinfer/model.py`（GPT-2 模型定义，纯 CPU numpy/Python） |
|  | `projects/miniinfer/docs/00-overview.md`（架构设计文档） |

> **关键决策**：MiniInfer 第一阶段用 Python + NumPy 写，目的是理解 GPT-2 的计算流程（LayerNorm → Attention → FFN → Residual），第二阶段再逐步搬 GPU。

---

## W11 (07.29–08.04)：CUDA Graph + NVTX + MiniInfer v0.2

### B1 CUDA — CUDA Graph

| 项目 | 内容 |
|------|------|
| **资源** | CUDA C++ Programming Guide §3.2.5：CUDA Graphs（graph node types、`cudaGraphInstantiate`、`cudaGraphLaunch`） |
|  | NVIDIA GTC Talk: "CUDA Graphs: Reducing Launch Overhead" |
|  | 代码：将 GEMM kernel 用 CUDA Graph 封装，对比 launch overhead |
| **验收** | 能解释 CUDA Graph 适合什么场景（重复执行的小 kernel），不适合什么场景（动态 shape 变化） |
| **产出** | `fundamentals/cuda/cuda-graph.md` |
|  | `fundamentals/cuda/kernels/07-cuda-graph/graph_demo.cu` |

### B1 CUDA — NVTX

| 项目 | 内容 |
|------|------|
| **资源** | NVIDIA NVTX Documentation |
|  | 代码：在 GEMM 各阶段插入 NVTX range，用 `nsys` 可视化 |
| **验收** | 能用 NVTX 标记 kernel 的各个阶段并在 Nsight Systems 中清晰看到 timeline |
| **产出** | `fundamentals/cuda/profiling/nvtx-guide.md` |

### B1 CUDA — cuBLAS/cuDNN 基础

| 项目 | 内容 |
|------|------|
| **资源** | cuBLAS Documentation：`cublasSgemm`、`cublasGemmEx` API 用法 |
|  | cuDNN Developer Guide：Convolution、Tensor ops 基础 API |
|  | 代码：用 cuBLAS 调用 GEMM 和手写 kernel 对比性能 |
| **验收** | 知道何时应该用 cuBLAS 而不是手写 GEMM kernel |
| **产出** | `fundamentals/cuda/cublas-essentials.md` |

### 🚀 MiniInfer v0.2 — 完整模型前向

| 项目 | 内容 |
|------|------|
| **目标** | 实现 Attention、FFN、LayerNorm 的 CPU 前向逻辑，完成 `model.forward()` |
| **资源** | nanoGPT `model.py` |
| **验收** | 完整 forward pass 输出的 token 概率分布与 PyTorch 误差 < 1e-4 |
| **产出** | `projects/miniinfer/model.py` 完整版 |
|  | `projects/miniinfer/tests/test_forward.py`（数值验证） |

---

## W12 (08.05–08.11)：GEMM 优化链（2）+ MiniInfer v1.0

### B1 CUDA — GEMM 优化链（2）

| 项目 | 内容 |
|------|------|
| **资源** | "how-to-optimize-gemm"：thread coarsening、register tiling、double buffering |
|  | cuda-mode Lecture 8: "CUTLASS and the Fundamental Optimizations" |
|  | 代码：实现 register tiling（每个 thread 计算 8×8 块） |
| **验收** | 能说出 GEMM 优化链的所有阶段，并知道每个阶段的提升比例（相对 naive） |
| **产出** | `fundamentals/cuda/optimize-gemm/06-register-tiling/` |
|  | `fundamentals/cuda/optimize-gemm/complete-benchmark.md`（从 naive 到 tensor core 的全链性能对比图） |

### B3 分布式 — NCCL 通信原语

| 项目 | 内容 |
|------|------|
| **资源** | NCCL Documentation：AllReduce、AllGather、ReduceScatter、Broadcast |
|  | 论文：NCCL: "Massively Scalable Distributed Deep Learning on the GPU" |
|  | 代码：用 `nccl-tests` 测试各通信原语的 bandwidth |
| **验收** | 能解释 NCCL 如何根据 topology（NVLink/PCIe/IB）自动选择最优算法 |
| **产出** | `fundamentals/distributed/nccl-primitives.md` |

### 🚀 MiniInfer v1.0 — GPU 推理 + KV Cache

| 项目 | 内容 |
|------|------|
| **目标** | 将前向计算搬上 GPU（CuPy 或 PyTorch CUDA extension），实现 KV Cache |
| **资源** | vLLM paper §3 (PagedAttention), nanoGPT `generate()` |
| **验收** | 能完成多 token 自回归生成，正确使用 KV Cache 避免重复计算 |
| **产出** | `projects/miniinfer/gpu_ops/`（GEMM/Attention 的 CUDA kernel） |
|  | `projects/miniinfer/kv_cache.py` |
|  | `projects/miniinfer/docs/01-gpu-kvcache.md` |

---

## W13–W14 (08.12–08.25)：FlashAttention 完整推导 + Triton 入门

### B1 CUDA — FlashAttention 完整推导与实现

| 项目 | 内容 |
|------|------|
| **资源** | 论文：Dao et al. "FlashAttention: Fast and Memory-Efficient Exact Attention with IO-Awareness" |
|  | 博客：Tri Dao "FlashAttention Explained" |
|  | Aleksa Gordic: "FlashAttention Explained" (YouTube) |
|  | 代码：W13 手写 FlashAttention forward（tiling on Q, softmax rescaling, recomputation） |
|  | 代码：W14 验证数值正确性 vs PyTorch naive attention，profile 对比 HBM access |
| **验收** | 能手写完整的 FlashAttention forward kernel，能解释 tiling + recomputation 如何节省 HBM access |
| **产出** | `fundamentals/cuda/kernels/08-flash-attention/fwd.cu` |
|  | `fundamentals/cuda/kernels/08-flash-attention/fwd.md`（推导 + profile 数据） |

### B4 Triton — DSL 入门 + GEMM

| 任务 | 内容 |
|------|------|
| **资源** | Triton 官方文档：Quick Start, Tutorial 1–3（Vector Add, Fused Softmax, Matrix Multiply） |
|  | OpenAI Triton Conference Talk |
|  | 代码：用 Triton 写 Matrix Multiply（对比 CUDA 版），理解 block-level programming model |
| **验收** | 能写出正确的 Triton GEMM kernel，理解 `tl.program_id`、`tl.arange`、`tl.load`/`tl.store` |
| **产出** | `fundamentals/python/triton/01-basics/` |
|  | `fundamentals/python/triton/02-matmul/` |

### B3 分布式 — Ring AllReduce 深入

| 项目 | 内容 |
|------|------|
| **资源** | Horovod 论文：Sergeev & Del Balso "Horovod: fast and easy distributed deep learning in TensorFlow" |
|  | 代码：用 MPI 实现完整 Ring AllReduce（send/recv pipeline），测试不同 tensor size 的带宽利用率 |
| **验收** | 能推导 Ring AllReduce 的时间公式：`2(N-1) × (data/N + latency)` |
| **产出** | `fundamentals/distributed/ring-allreduce-deep-dive.md` |
|  | `fundamentals/distributed/code/ring-allreduce-bench/` |

---

## W15–W16 (08.26–09.08)：FlashAttention-2 + Triton FlashAttention + NCCL Topology

### B1 CUDA — FlashAttention-2 改进

| 项目 | 内容 |
|------|------|
| **资源** | 论文：Dao "FlashAttention-2: Faster Attention with Better Parallelism and Work Partitioning" |
|  | 代码：理解 FlashAttention-2 的改进点（减少 non-matmul FLOPs、forward pass parallelism over seqlen、better warp scheduling） |
| **验收** | 能说出 FlashAttention-2 相比 v1 的三个主要改进点 |
| **产出** | `fundamentals/cuda/kernels/08-flash-attention/flashattn2-improvements.md` |

### B4 Triton — FlashAttention

| 项目 | 内容 |
|------|------|
| **资源** | Triton 官方教程：FlashAttention in Triton |
|  | 代码：用 Triton 实现 FlashAttention forward，与 CUDA 手写版对比 |
| **验收** | 能对比 Triton 版和 CUDA 手写版 FlashAttention 的代码量、性能和可维护性 |
| **产出** | `fundamentals/python/triton/03-flash-attention/` |
|  | `fundamentals/python/triton/03-flash-attention/benchmark.md` |

### B3 分布式 — NVLink/NVSwitch Topology

| 项目 | 内容 |
|------|------|
| **资源** | NVIDIA NVLink/NVSwitch Whitepaper |
|  | NCCL Topology Detection：`nvidia-smi topo -m`、`nccl-topo` |
|  | 代码：在 2/4 GPU 上测试 NCCL AllReduce bandwidth 随数据量的变化 |
| **验收** | 能画出 8×A100 节点的拓扑图（NVSwitch + IB），理解 ring vs tree 算法在哪种拓扑下更优 |
| **产出** | `fundamentals/distributed/gpu-topology.md` |

### 🚀 MiniInfer v1.1 — 优化与 benchmark

| 项目 | 内容 |
|------|------|
| **目标** | 集成 FlashAttention kernel 到 MiniInfer，性能 baseline |
| **产出** | `projects/miniinfer/docs/02-flashattn-integration.md` |
|  | `projects/miniinfer/benchmarks/baseline.md`（与 PyTorch/gpt2 对比） |

---

## W17–W18 (09.09–09.22)：CUTLASS 基础 + Triton autotune

### B1 CUDA — CUTLASS 基础

| 项目 | 内容 |
|------|------|
| **资源** | CUTLASS Documentation：Quick Start, Fundamentals of GEMM, Epilogues |
|  | 代码：用 CUTLASS 调用 FP16 GEMM（内置 kernel），理解 CUTLASS 的 template hierarchy（`GemmShape` → `Mainloop` → `Epilogue`） |
| **验收** | 能用 CUTLASS 调用标准 GEMM，能说出 CUTLASS 的 4 层抽象（tile iterators → collective → kernel → host API） |
| **产出** | `fundamentals/cuda/cutlass/basics.md` |
|  | `fundamentals/cuda/cutlass/01-basic-gemm/` |

### B4 Triton — autotuning

| 项目 | 内容 |
|------|------|
| **资源** | Triton 官方文档：`@triton.autotune` 教程 |
|  | 代码：给 Triton GEMM kernel 添加 autotune，搜索最优 tile size / num_stages / num_warps |
| **验收** | 能解释 autotune 如何通过 grid search 找到最优配置，理解 `prune_configs` 的用途 |
| **产出** | `fundamentals/python/triton/04-autotune/` |

### B3 分布式 — ZeRO-1 实现原理

| 项目 | 内容 |
|------|------|
| **资源** | 论文：Rajbhandari et al. "ZeRO: Memory Optimizations Toward Training Trillion Parameter Models" |
|  | DeepSpeed ZeRO-1 源码：`deepspeed/runtime/zero/stage_1_and_2.py` |
| **验收** | 能画出 ZeRO-1 的 optimizer state 分片 + AllGather 的数据流 |
| **产出** | `fundamentals/distributed/zero-1.md` |

### 🚀 MiniInfer v2.0 — PagedAttention

| 项目 | 内容 |
|------|------|
| **目标** | 实现 PagedAttention（BlockManager） |
| **资源** | vLLM paper §4, vLLM 源码 `vllm/core/block_manager.py` |
| **验收** | KV Cache 能按 block 粒度动态分配，支持随机访问 |
| **产出** | `projects/miniinfer/block_manager.py` |
|  | `projects/miniinfer/docs/03-paged-attention.md` |

---

## W19–W20 (09.23–10.06)：PTX/SASS + PyTorch nn.Module

### B1 CUDA — PTX/SASS 基础

| 项目 | 内容 |
|------|------|
| **资源** | NVIDIA: "PTX ISA" §1–5（并行执行模型、状态空间、类型、operand） |
|  | NVIDIA: "CUDA Binary Utilities"（`cuobjdump`、`nvdisasm`） |
|  | 代码：用 `cuobjdump -sass` 对比 naive GEMM vs tiled GEMM 生成指令的差异 |
| **验收** | 能读懂简单的 SASS 指令（`LDG`、`STG`、`LDS`、`STS`、`FFMA`、`HADD2`），理解 compiled kernel 的 register spill 现象 |
| **产出** | `fundamentals/cuda/ptx-sass-basics.md` |
|  | `fundamentals/cuda/profiling/read-sass.md` |

### B4 PyTorch — nn.Module 源码

| 项目 | 内容 |
|------|------|
| **资源** | PyTorch 源码：`torch/nn/modules/module.py`（`__setattr__`、`register_buffer`、`state_dict`、`load_state_dict`、`_apply`） |
|  | 代码：手写一个简易版 `nn.Module` |
| **验收** | 能解释 `model.cuda()` 如何把所有 parameter/buffer 移到 GPU（`_apply` 机制），`state_dict` 的 hook 机制 |
| **产出** | `fundamentals/python/pytorch-internals/03-nn-module.md` |

### B3 分布式 — ZeRO-2/3

| 项目 | 内容 |
|------|------|
| **资源** | 论文 ZeRO（续）：ZeRO-2 gradient partitioning、ZeRO-3 parameter partitioning |
|  | DeepSpeed 源码：`stage2.py`、`stage3.py` |
| **验收** | 能画出 ZeRO-1/2/3 的通信矩阵（各阶段有哪些 collective），知道 ZeRO-3 的通信量 |
| **产出** | `fundamentals/distributed/zero-2-3.md` |

### 🚀 MiniInfer v2.1 — Continuous Batching

| 项目 | 内容 |
|------|------|
| **目标** | 实现 Continuous Batching（动态调度请求） |
| **资源** | vLLM paper §5, vLLM 源码 `vllm/core/scheduler.py` |
| **验收** | 多个请求能共享一个 batch，按需加入/退出 |
| **产出** | `projects/miniinfer/scheduler.py` |
|  | `projects/miniinfer/docs/04-continuous-batching.md` |

---

## W21–W23 (10.07–10.27)：Tensor Parallelism + 异步拷贝 + MiniInfer v3

### B1 CUDA — Async Copy + Pipeline

| 项目 | 内容 |
|------|------|
| **资源** | CUDA C++ Programming Guide §3.2.6：Asynchronous Data Copies（`cuda::memcpy_async`、pipeline） |
|  | 代码：用 async copy + pipeline 实现 GEMM 的 global→shared 数据搬运 overlap |
| **验收** | 能写出带 pipeline 的 GEMM kernel，理解 producer-consumer 同步 |
| **产出** | `fundamentals/cuda/kernels/09-async-copy/` |

### B3 分布式 — Tensor Parallelism

| 项目 | 内容 |
|------|------|
| **资源** | 论文：Shoeybi et al. "Megatron-LM: Training Multi-Billion Parameter Language Models Using Model Parallelism" |
|  | 代码：手写 column-parallel linear + row-parallel linear（PyTorch + NCCL） |
| **验收** | 能画出 Megatron TP 的 forward/backward 通信矩阵 |
| **产出** | `fundamentals/distributed/tensor-parallelism.md` |
|  | `fundamentals/distributed/code/tp-linear/` |

### B5 框架源码 — vLLM（启动）

| 项目 | 内容 |
|------|------|
| **资源** | vLLM 源码：`vllm/entrypoints/llm.py`（LLM class 入口）、`vllm/engine/llm_engine.py`（LLMEngine） |
|  | 代码：追踪一个请求从 `llm.generate()` 到返回 token 的完整生命周期 |
| **验收** | 能画出 vLLM 请求处理流程图 |
| **产出** | `fundamentals/distributed/vllm-source/01-entrypoint-engine.md` |

### 🚀 MiniInfer v3.0 — Tensor Parallelism

| 项目 | 内容 |
|------|------|
| **目标** | 实现 2/4 GPU 的 TP 推理 |
| **验收** | 2 GPU TP 推理结果与单 GPU 一致，throughput 有提升 |
| **产出** | `projects/miniinfer/tp_inference.py` |
|  | `projects/miniinfer/docs/05-tensor-parallelism.md` |
|  | `projects/miniinfer/benchmarks/tp-scaling.md` |

---

## W24–W26 (10.28–11.17)：CUTLASS 进阶 + vLLM 源码 + MiniInfer 收尾

### B1 CUDA — CUTLASS 进阶

| 项目 | 内容 |
|------|------|
| **资源** | CUTLASS Examples: 自定义 Epilogue（bias + ReLU fuse）、自定义 layout |
|  | 代码：用 CUTLASS 写一个 GEMM + Bias + GeLU 融合 kernel |
| **验收** | 能用 CUTLASS 自定义 epilogue 实现算子融合 |
| **产出** | `fundamentals/cuda/cutlass/02-custom-epilogue/` |
|  | `fundamentals/cuda/cutlass/cutlass-fusion.md` |

### B5 框架源码 — vLLM BlockManager + Scheduler

| 项目 | 内容 |
|------|------|
| **资源** | vLLM 源码：`vllm/core/block_manager.py`、`vllm/core/scheduler.py` |
|  | 代码：画出 BlockManager 的数据结构和 allocation/free 流程 |
| **验收** | 能解释 copy-on-write 机制在 beam search 中的作用 |
| **产出** | `fundamentals/distributed/vllm-source/02-blockmanager.md` |
|  | `fundamentals/distributed/vllm-source/03-scheduler.md` |

### 🚀 MiniInfer — 收尾 + Benchmark

| 任务 | 内容 |
|------|------|
| **产出** | `projects/miniinfer/docs/06-final-benchmark.md`（性能对比 vLLM/pytorch baseline） |
|  | `projects/miniinfer/README.md`（项目总结 + 技术亮点） |

---

# Phase 3：MiniQuant + 量化深入（W22–W34）

> **目标**：完成 MiniQuant 量化推理引擎，同时在 B1 学习 INT4/INT8/FP8 GEMM、B5 推进 vLLM+DeepSpeed 源码。
>
> **MiniQuant 路线**：量化工具 → AWQ 算法 → INT4 GEMM kernel → 集成到 MiniInfer

---

## W22–W23 (10.14–10.27)：量化入门

### B1 CUDA — INT8/FP8 GEMM（新主题 ✅）

| 项目 | 内容 |
|------|------|
| **资源** | NVIDIA: "Using INT8 GEMM for Fast Inference" |
|  | 论文：Micikevicius et al. "FP8 Formats for Deep Learning" |
|  | 代码：用 CUTLASS 调用 INT8 GEMM（内置 kernel），验证输出精度 |
| **验收** | 能解释 INT8 量化/反量化的数据流，FP8 E4M3 vs E5M2 格式差异 |
| **产出** | `fundamentals/cuda/quantization/int8-fp8-gemm.md` |
|  | `fundamentals/cuda/quantization/code/int8-gemm/` |

### 🚀 MiniQuant — 量化工具 + AWQ 论文

| 项目 | 内容 |
|------|------|
| **目标** | 实现基础模型量化工具：Weight-only INT8/INT4 量化，校准方法 |
| **资源** | 论文：Lin et al. "AWQ: Activation-aware Weight Quantization for LLM Compression and Acceleration" |
|  | GPTQ 论文：Frantar et al. "GPTQ: Accurate Post-Training Quantization for Generative Pre-trained Transformers" |
| **验收** | 能解释 per-channel vs per-tensor 量化、对称 vs 非对称量化的差异 |
| **产出** | `projects/miniquant/quantize.py`（INT8/INT4 weight packing） |
|  | `projects/miniquant/docs/01-awq-gptq-papers.md` |

---

## W24–W25 (10.28–11.10)：AWQ 实现 + vLLM Worker

### 🚀 MiniQuant — AWQ 核心算法

| 项目 | 内容 |
|------|------|
| **目标** | 实现 AWQ 的 salient channel detection + per-channel scaling |
| **资源** | AWQ 官方实现：`mit-han-lab/llm-awq` |
| **验收** | 量化后的模型在 WikiText-2 上的 PPL 退化 < 0.5 |
| **产出** | `projects/miniquant/awq/`（salient channel detection + scaling） |
|  | `projects/miniquant/docs/02-awq-implementation.md` |

### B5 框架源码 — vLLM Worker + ModelRunner

| 项目 | 内容 |
|------|------|
| **资源** | vLLM 源码：`vllm/worker/worker.py`、`vllm/worker/model_runner.py` |
| **验收** | 能解释 GPU cache 的管理策略 |
| **产出** | `fundamentals/distributed/vllm-source/04-worker-modelrunner.md` |

---

## W26–W28 (11.11–12.01)：INT4 GEMM kernel + Pipeline Parallelism

### 🚀 MiniQuant — INT4 GEMM CUDA kernel

| 项目 | 内容 |
|------|------|
| **目标** | 手写 INT4 GEMM kernel（CUTLASS 或纯 CUDA） |
| **资源** | CUTLASS: `cutlass/gemm/kernel/gemm_universal.h` INT4 specialization |
|  | 代码：dequant 逻辑（INT4 → FP16）+ 计算 + requant 的融合 kernel |
| **验收** | INT4 GEMM 推理速度达到 FP16 GEMM 的 1.5x+ |
| **产出** | `projects/miniquant/kernels/int4_gemm.cu` |
|  | `projects/miniquant/docs/03-int4-kernel.md` |

### B3 分布式 — Pipeline Parallelism

| 项目 | 内容 |
|------|------|
| **资源** | 论文：Huang et al. "GPipe: Efficient Training of Large Neural Networks using Pipeline Parallelism" |
|  | 论文：Narayanan et al. "PipeDream: Generalized Pipeline Parallelism for DNN Training" |
|  | 代码：用 PyTorch RPC 实现一个简化的 1F1B pipeline schedule |
| **验收** | 能画出 GPipe vs 1F1B 的 timeline，计算 pipeline bubble ratio |
| **产出** | `fundamentals/distributed/pipeline-parallelism.md` |
|  | `fundamentals/distributed/code/pp-demo/` |

---

## W29–W30 (12.02–12.15)：FlashAttention-3 + Kernel Fusion

### B1 CUDA — FlashAttention-3 + FP8 attention

| 项目 | 内容 |
|------|------|
| **资源** | 论文：Shah et al. "FlashAttention-3: Fast and Accurate Attention with Asynchrony and Low-precision" |
| **验收** | 能说出 FlashAttention-3 的三个主要改进点（async, FP8, producer-consumer overlap） |
| **产出** | `fundamentals/cuda/kernels/08-flash-attention/flashattn3-notes.md` |

### B1 CUDA — Kernel Fusion 模式（新增主题 ✅）

| 项目 | 内容 |
|------|------|
| **资源** | NVIDIA GTC Talks on Kernel Fusion |
|  | 代码：实现 GeLU + Dropout + Residual 三合一 kernel |
| **验收** | 能分析 kernel fusion 减少 HBM access 的次数 |
| **产出** | `fundamentals/cuda/kernel-fusion.md` |
|  | `fundamentals/cuda/kernels/10-fusion/` |

### B5 框架源码 — DeepSpeed 启动

| 项目 | 内容 |
|------|------|
| **资源** | DeepSpeed 源码：`deepspeed/runtime/engine.py`（DeepSpeedEngine） |
| **验收** | 能画出 DeepSpeedEngine 的初始化和 train loop 流程图 |
| **产出** | `fundamentals/distributed/deepspeed-source/01-engine-init.md` |

---

## W31–W34 (12.16–2027.01.12)：MiniQuant 收尾 + CUTLASS 完稿

### 🚀 MiniQuant — Integration + Benchmark

| 任务 | 内容 |
|------|------|
| **目标** | 将 MiniQuant 的 INT4 GEMM 集成到 MiniInfer，端到端推理 |
| **产出** | `projects/miniquant/docs/04-integration-benchmark.md` |
|  | `projects/miniquant/README.md` |

### B1 CUDA — CUTLASS 总结 + GEMM 优化链完稿

| 任务 | 内容 |
|------|------|
| **产出** | `fundamentals/cuda/cutlass/cutlass-cheatsheet.md`（CUTLASS 核心概念速查） |
|  | `fundamentals/cuda/optimize-gemm/gemm-optimization-full.md`（完整优化链文档） |

### B5 框架源码 — DeepSpeed ZeRO

| 项目 | 内容 |
|------|------|
| **资源** | DeepSpeed 源码：`deepspeed/runtime/zero/stage1.py`、`stage2.py`、`stage3.py` |
| **验收** | 能画出 ZeRO 1/2/3 的前向/反向/优化器更新全流程通信图 |
| **产出** | `fundamentals/distributed/deepspeed-source/02-zero-stages.md` |

---

# Phase 4：MiniMegatron + 冲刺（W30–W46）

> **目标**：完成 MiniMegatron（2D/3D 并行训练 GPT-2），深入 Megatron-LM 源码，完成剩余 B3 高级主题。
>
> **MiniMegatron 路线**：
> - v0：单卡 DP 训练 loop（W30–W32）
> - v1：TP + PP 集成（W33–W37）
> - v2：ZeRO + 混合精度（W38–W42）
> - v3：完整 GPT-2 训练 + scaling test（W43–W46）

---

## W30–W32 (12.09–12.29)：MiniMegatron 启动 + TP 实战

### B3 分布式 — 3D Parallelism

| 项目 | 内容 |
|------|------|
| **资源** | 论文：Narayanan et al. "Efficient Large-Scale Language Model Training on GPU Clusters Using Megatron-LM" |
|  | 代码：画出 3D 并行（TP+PP+DP）的 device mesh 和通信组划分 |
| **验收** | 能解释在 3D 并行下，一个 allreduce 在哪个通信组执行，经过几次通信 |
| **产出** | `fundamentals/distributed/3d-parallelism.md` |

### 🚀 MiniMegatron v0 — 单卡 DP 训练 loop

| 项目 | 内容 |
|------|------|
| **目标** | 实现 GPT-2 small 的单卡训练 loop（forward + backward + optimizer） |
| **资源** | nanoGPT `train.py`、PyTorch DDP 文档 |
| **验收** | 在 GTX 1650 上能训练 GPT-2 small（单 batch），loss 正常下降 |
| **产出** | `projects/minimegatron/train.py` |
|  | `projects/minimegatron/docs/01-single-gpu-train.md` |

---

## W33–W35 (12.30–2027.01.19)：TP + Megatron 源码

### 🚀 MiniMegatron v1 — Tensor Parallelism

| 项目 | 内容 |
|------|------|
| **目标** | 实现 2 GPU 的 TP 训练（col-parallel/row-parallel linear） |
| **资源** | Megatron-LM 源码：`megatron/core/tensor_parallel/layers.py` |
| **验收** | 2 GPU TP 训练的 loss 曲线与单卡一致 |
| **产出** | `projects/minimegatron/tp/`（TP 层实现） |
|  | `projects/minimegatron/docs/02-tp-training.md` |

### B5 框架源码 — Megatron-LM TP

| 项目 | 内容 |
|------|------|
| **资源** | Megatron-LM 源码：`megatron/core/tensor_parallel/` |
| **验收** | 能画出 Megatron 的 column/row parallelism 在 forward/backward 时的通信模式 |
| **产出** | `fundamentals/distributed/megatron-source/01-tensor-parallel.md` |

---

## W36–W38 (01.20–02.09)：PP + 混合精度

### 🚀 MiniMegatron v1（续） — Pipeline Parallelism

| 项目 | 内容 |
|------|------|
| **目标** | 实现 PP（GPipe / 1F1B）训练 |
| **资源** | Megatron-LM 源码：`megatron/core/pipeline_parallel/` |
| **验收** | 4 GPU TP+PP 训练能跑通，pipeline bubble 占比在合理范围 |
| **产出** | `projects/minimegatron/pp/`（PP 实现） |
|  | `projects/minimegatron/docs/03-pp-training.md` |

### B5 框架源码 — Megatron-LM PP

| 任务 | 内容 |
|------|------|
| **产出** | `fundamentals/distributed/megatron-source/02-pipeline-parallel.md` |

### 🚀 MiniMegatron v2 — 混合精度

| 项目 | 内容 |
|------|------|
| **目标** | 实现 FP16/BF16 混合精度训练（AMP + loss scaling） |
| **资源** | NVIDIA: "Mixed Precision Training" (paper + blog) |
|  | PyTorch AMP：`torch.cuda.amp` |
| **验收** | 混合精度训练的 loss 曲线与 FP32 一致，速度有 1.5x+ 提升 |
| **产出** | `projects/minimegatron/docs/04-mixed-precision.md` |

---

## W39–W41 (02.10–03.02)：ZeRO + 完整训练

### 🚀 MiniMegatron v2（续） — ZeRO 集成

| 项目 | 内容 |
|------|------|
| **目标** | 集成 ZeRO-1/2（optimizer state + gradient partitioning） |
| **资源** | DeepSpeed ZeRO 源码 |
| **验收** | ZeRO-2 训练内存占用比 DP-only 减少 ~50% |
| **产出** | `projects/minimegatron/zero/` |
|  | `projects/minimegatron/docs/05-zero-integration.md` |

### B3 分布式 — FSDP + Expert Parallelism

| 项目 | 内容 |
|------|------|
| **资源** | PyTorch FSDP 文档 + 论文 |
|  | Fedus et al. "Switch Transformers: Scaling to Trillion Parameter Models with Simple and Efficient Sparsity" |
| **验收** | 理解 FSDP vs ZeRO-3 的异同，MoE 通信量分析 |
| **产出** | `fundamentals/distributed/fsdp-moe.md` |

### B5 框架源码 — Megatron-LM Dataset + Checkpoint

| 任务 | 内容 |
|------|------|
| **产出** | `fundamentals/distributed/megatron-source/03-dataset-checkpoint.md` |

---

## W42–W46 (03.03–04.06)：最终冲刺 + 收尾

### 🚀 MiniMegatron v3 — 完整训练 + Scaling Test

| 项目 | 内容 |
|------|------|
| **目标** | 在云 GPU（4×A100）上完成 GPT-2 Medium 的 3D 并行训练，输出 scaling report |
| **验收** | 能跑出正确的 GPT-2 训练 loss + 下游任务评测 |
| **产出** | `projects/minimegatron/docs/06-scaling-report.md` |
|  | `projects/minimegatron/README.md` |

### B5 框架源码收尾

| 任务 | 内容 |
|------|------|
| **产出** | `fundamentals/distributed/vllm-source/README.md`（vLLM 源码索引） |
|  | `fundamentals/distributed/deepspeed-source/README.md`（DeepSpeed 源码索引） |
|  | `fundamentals/distributed/megatron-source/README.md`（Megatron-LM 源码索引） |

### B 线全面复盘（W44）

| 任务 | 内容 |
|------|------|
| **产出** | `fundamentals/retrospective.md`（学习回顾 + 知识盲区 + 面试常见考点总结） |
|  | 更新简历项目经验描述 |

---

# 学习资源总索引

## 书籍

| 书名 | 重点章节 | 所用阶段 |
|------|----------|----------|
| 《PMMP》(Programming Massively Parallel Processors) 4th ed | Ch1–7 全部 | Phase 1 |
| 《CUDA C++ Programming Guide》 | §1–5, §7.24 (Tensor Core) | Phase 1–2 |
| 《CUDA C++ Best Practices Guide》 | 全文 | Phase 2 |
| 《Effective Modern C++》(Scott Meyers) | Item 17–29 | Phase 1 |
| 《C++ Concurrency in Action》(Anthony Williams) | Ch1–8 | Phase 1 |
| 《C++ Templates: The Complete Guide》 | Part 1 | Phase 1 |
| 《Fluent Python》(Luciano Ramalho) 2nd ed | Ch7, 14, 18, 19 | Phase 1 |
| 《CPython Internals》(Anthony Shaw) | Ch1–3, 5 | Phase 1 |

## 论文（按阅读顺序）

| 论文 | 阅读时间 | 关联主题 |
|------|----------|----------|
| Thakur et al. — MPICH Collective Communication | W10 | B3 AllReduce |
| Dao et al. — FlashAttention (2022) | W13 | B1 Attention kernel |
| Dao — FlashAttention-2 (2023) | W15 | B1 Attention kernel |
| Shah et al. — FlashAttention-3 (2024) | W29 | B1 Attention kernel |
| Sergeev & Balso — Horovod (2018) | W14 | B3 Ring AllReduce |
| Rajbhandari et al. — ZeRO (2019) | W18 | B3 ZeRO |
| Shoeybi et al. — Megatron-LM (2019) | W22 | B3 TP |
| Narayanan et al. — Megatron-LM 3D (2021) | W30 | B3 3D |
| Huang et al. — GPipe (2019) | W28 | B3 PP |
| Narayanan et al. — PipeDream (2019) | W28 | B3 PP |
| Kwon et al. — vLLM/PagedAttention (2023) | W12 | B5 vLLM |
| Lin et al. — AWQ (2023) | W23 | MiniQuant |
| Frantar et al. — GPTQ (2022) | W23 | MiniQuant |
| Micikevicius et al. — FP8 Formats (2022) | W22 | B1 FP8 |
| Micikevicius et al. — Mixed Precision Training (2017) | W37 | Mixed Precision |
| Fedus et al. — Switch Transformers (2021) | W41 | MoE |

## 视频

| 系列 | 来源 | 重点集 |
|------|------|--------|
| cuda-mode Lectures | YouTube | Lecture 1 (Profiling), 4 (GEMM), 8 (CUTLASS), 12+ (FlashAttention) |
| David Beazley: Understanding the GIL | YouTube/PyCon | 全部 |
| Philip Guo: CPython Internals | YouTube | 前 3 小时 |
| Effective Modern CMake (Daniel Pfeifer) | YouTube/CppCon | 全部 |
| Robert Smallshire: pybind11 | YouTube | 全部 |

## 开源代码仓库

| 仓库 | 用途 |
|------|------|
| `/hwu-dev/how-to-optimize-gemm` | GEMM 优化链实战 |
| `/NVIDIA/cutlass` | 高性能 GEMM/Conv 模板库 |
| `/karpathy/nanoGPT` | GPT-2 训练参考 |
| `/karpathy/llm.c` | C/CUDA 版 GPT-2 训练 |
| `/vllm-project/vllm` | 推理引擎参考 |
| `/microsoft/DeepSpeed` | ZeRO 实现参考 |
| `/NVIDIA/Megatron-LM` | TP/PP 实现参考 |
| `/mit-han-lab/llm-awq` | AWQ 参考实现 |
| `/IST-DASLab/gptq` | GPTQ 参考实现 |
| `/triton-lang/triton` | Triton DSL |

---

# 检查点与评估

每 4 周做一次自我评估，回答以下问题：

| 周 | 检查点 |
|------|--------|
| **W4** | PMPP Ch1–7 是否理解？C++ 智能指针/模板/多线程能独立写吗？ |
| **W8** | GEMM naive+tiled 能独立写吗？PyTorch Tensor/autograd 源码读了吗？ |
| **W12** | Tensor Core GEMM 能写吗？MiniInfer v0 完成了吗？FlashAttention 能用吗？ |
| **W16** | FlashAttention 推导能讲清楚吗？Triton GEMM 写了吗？MiniInfer v1 完成了吗？ |
| **W20** | CUTLASS 基础能用吗？PagedAttention 实现了吗？PTX/SASS 能读懂吗？ |
| **W24** | MiniInfer v2 (Continuous Batching) 完成了吗？vLLM 源码 2 个模块读了吗？ |
| **W28** | INT4 GEMM kernel 能写吗？AWQ 算法实现了吗？CUTLASS 进阶？ |
| **W32** | MiniQuant 集成进 MiniInfer 了吗？MiniMegatron DP 训练跑通了吗？ |
| **W36** | TP+PP 训练能跑吗？Megatron-LM 源码读了几个模块？ |
| **W40** | ZeRO 集成了吗？混合精度训练跑通了吗？ |
| **W44** | MiniMegatron 完整训练完成了吗？scaling report 写了吗？ |

---

# 每日时间分配（B 线专属 ~2h）

| 时段 | 内容 |
|------|------|
| B1 CUDA/GPU（45min） | kernel 实现 + 笔记 |
| B2/B3/B4/B5 轮流（45min） | 语言/分布式/Triton/源码 按当前 Phase 优先 |
| 项目推进（30min） | MiniInfer/MiniQuant/MiniMegatron 当前迭代 |
| 周末（1–2h 额外） | 论文精读 + 复盘 |

---

# 新增主题对照（相比原计划补全）

| 新增主题 | 所在周 | 轨道 |
|----------|--------|------|
| Profiling 工具链（nsys/ncu） | W5 | B1 |
| NVTX | W11 | B1 |
| CUDA Graph | W11 | B1 |
| cuBLAS/cuDNN 基础 | W11 | B1 |
| Warp Shuffle / Cooperative Groups | W9 | B1 |
| PTX/SASS 基础 | W19 | B1 |
| CUTLASS（基础+进阶） | W17–18, W24–W26 | B1 |
| Async Copy + Pipeline | W21 | B1 |
| INT8/FP8 GEMM | W22 | B1 |
| Kernel Fusion 模式 | W29 | B1 |
| FlashAttention-2/-3 改进 | W15, W29 | B1 |
| MPI 通信原语 | W10 | B3 |
| NCCL Topology | W16 | B3 |
| FSDP | W39 | B3 |
| Expert Parallelism (MoE) | W39 | B3 |
| CPython 内部 | W7 | B2 |
| TensorRT（预留） | W40+ | B1 扩展 |

---

> **下一步**：将此 plan.md 与 520plan.md 主计划对齐，B 线的每周条目统一引用本文件的详细内容。
