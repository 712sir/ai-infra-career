# 学习资源清单

> 整理自 `fundamentals/plan.md` 44 周学习计划，按类别汇总。

---

## 一、书籍

> 本地 PDF 在 `books/` 目录下。

| 序号 | 书名 | 作者 | 重点章节 | 本地文件 | 使用阶段 |
|------|------|------|----------|----------|----------|
| 1 | 《Programming Massively Parallel Processors》(PMMP) 4th ed | David Kirk / Wen-mei Hwu | Ch1–7 全部 | [01-PMMP-4th.pdf](books/01-Programming-Massively-Parallel-Processors-PMMP-4th.pdf) | Phase 1 |
| 2 | 《CUDA C++ Programming Guide》 | NVIDIA | §1–5, §7.24 (Tensor Core) | [02-CUDA-Programming-Guide.pdf](books/02-CUDA-C-Programming-Guide.pdf) | Phase 1–2 |
| 3 | 《CUDA C++ Best Practices Guide》 | NVIDIA | 全文 | [03-CUDA-Best-Practices.pdf](books/03-CUDA-C-Best-Practices-Guide.pdf) | Phase 2 |
| 4 | 《Effective Modern C++》 | Scott Meyers | Item 17–29 | [04-Effective-Modern-C++-en.pdf](books/04-Effective-Modern-C%2B%2B-en.pdf) / [中文版](books/04-Effective-Modern-C%2B%2B-zh.pdf) | Phase 1 |
| 5 | 《C++ Concurrency in Action》2nd ed | Anthony Williams | Ch1–8 | [05-C++-Concurrency-2nd.pdf](books/05-C%2B%2B-Concurrency-in-Action-2nd.pdf) | Phase 1 |
| 6 | 《C++ Templates: The Complete Guide》2nd ed | David Vandevoorde et al. | Part 1 | [06-C++-Templates-2nd.pdf](books/06-C%2B%2B-Templates-Complete-Guide-2nd.pdf) | Phase 1 |
| 7 | 《Fluent Python》2nd ed | Luciano Ramalho | Ch7, 14, 18, 19 | [07-Fluent-Python-2nd.pdf](books/07-Fluent-Python-2nd.pdf) | Phase 1 |
| 8 | 《CPython Internals》 | Anthony Shaw | Ch1–3, 5 | [08-CPython-Internals.pdf](books/08-CPython-Internals.pdf) | Phase 1 |
| 9 | 《STL 源码剖析》 | 侯捷 | 选读：vector / unordered_map / deque | [09-STL源码剖析.pdf](books/09-STL%E6%BA%90%E7%A0%81%E5%89%96%E6%9E%90-%E4%BE%AF%E6%8D%B7.pdf) | Phase 1 (W6) |
| 10 | 《Professional CMake》 | Craig Scott | Ch1–7 | [10-Professional-CMake.pdf](books/10-Professional-CMake.pdf) | Phase 1 (W4) |

---

## 二、论文（按阅读顺序）

> 本地 PDF 在 `papers/` 目录下（16/16 全部就位）。

| 序号 | 论文 | arXiv / 来源 | 本地文件 | 阅读周 | 关联主题 |
|------|------|--------------|----------|--------|----------|
| 1 | Optimization of Collective Communication Operations in MPICH (Thakur et al., 2005) | [Semantic Scholar](https://www.semanticscholar.org/paper/b471f0b45d69c3fd3333f0322bab64b2a4ae9369) | [01-Thakur等-MPICH集合通信优化-2005.pdf](papers/01-Thakur%E7%AD%89-MPICH%E9%9B%86%E5%90%88%E9%80%9A%E4%BF%A1%E4%BC%98%E5%8C%96-2005.pdf) | W10 | B3 AllReduce |
| 2 | FlashAttention (Dao et al., 2022) | [2205.14135](https://arxiv.org/abs/2205.14135) | [02-Dao等-FlashAttention-2022.pdf](papers/02-Dao%E7%AD%89-FlashAttention-2022.pdf) | W13 | B1 Attention |
| 3 | FlashAttention-2 (Dao, 2023) | [2307.08691](https://arxiv.org/abs/2307.08691) | [03-Dao-FlashAttention2-2023.pdf](papers/03-Dao-FlashAttention2-2023.pdf) | W15 | B1 Attention |
| 4 | FlashAttention-3 (Shah et al., 2024) | [2407.08608](https://arxiv.org/abs/2407.08608) | [04-Shah等-FlashAttention3-2024.pdf](papers/04-Shah%E7%AD%89-FlashAttention3-2024.pdf) | W29 | B1 Attention |
| 5 | Horovod (Sergeev & Balso, 2018) | [1802.05799](https://arxiv.org/abs/1802.05799) | [05-Sergeev等-Horovod-2018.pdf](papers/05-Sergeev%E7%AD%89-Horovod-2018.pdf) | W14 | B3 Ring AllReduce |
| 6 | ZeRO (Rajbhandari et al., 2019) | [1910.02054](https://arxiv.org/abs/1910.02054) | [06-Rajbhandari等-ZeRO-2019.pdf](papers/06-Rajbhandari%E7%AD%89-ZeRO-2019.pdf) | W18 | B3 ZeRO |
| 7 | Megatron-LM (Shoeybi et al., 2019) | [1909.08053](https://arxiv.org/abs/1909.08053) | [07-Shoeybi等-MegatronLM-TP-2019.pdf](papers/07-Shoeybi%E7%AD%89-MegatronLM-TP-2019.pdf) | W22 | B3 TP |
| 8 | Megatron-LM 3D Parallelism (Narayanan et al., 2021) | [2104.04473](https://arxiv.org/abs/2104.04473) | [08-Narayanan等-MegatronLM-3D并行-2021.pdf](papers/08-Narayanan%E7%AD%89-MegatronLM-3D%E5%B9%B6%E8%A1%8C-2021.pdf) | W30 | B3 3D |
| 9 | GPipe (Huang et al., 2019) | [1811.06965](https://arxiv.org/abs/1811.06965) | [09-Huang等-GPipe-流水线并行-2019.pdf](papers/09-Huang%E7%AD%89-GPipe-%E6%B5%81%E6%B0%B4%E7%BA%BF%E5%B9%B6%E8%A1%8C-2019.pdf) | W28 | B3 PP |
| 10 | PipeDream (Narayanan et al., 2019) | [1806.03377](https://arxiv.org/abs/1806.03377) | [10-Narayanan等-PipeDream-2019.pdf](papers/10-Narayanan%E7%AD%89-PipeDream-2019.pdf) | W28 | B3 PP |
| 11 | vLLM / PagedAttention (Kwon et al., 2023) | [2309.06180](https://arxiv.org/abs/2309.06180) | [11-Kwon等-vLLM-PagedAttention-2023.pdf](papers/11-Kwon%E7%AD%89-vLLM-PagedAttention-2023.pdf) | W12 | B5 vLLM |
| 12 | AWQ (Lin et al., 2023) | [2306.00978](https://arxiv.org/abs/2306.00978) | [12-Lin等-AWQ-激活感知量化-2023.pdf](papers/12-Lin%E7%AD%89-AWQ-%E6%BF%80%E6%B4%BB%E6%84%9F%E7%9F%A5%E9%87%8F%E5%8C%96-2023.pdf) | W23 | MiniQuant |
| 13 | GPTQ (Frantar et al., 2022) | [2210.17323](https://arxiv.org/abs/2210.17323) | [13-Frantar等-GPTQ-2022.pdf](papers/13-Frantar%E7%AD%89-GPTQ-2022.pdf) | W23 | MiniQuant |
| 14 | FP8 Formats for Deep Learning (Micikevicius et al., 2022) | [2209.05433](https://arxiv.org/abs/2209.05433) | [14-Micikevicius等-FP8格式-2022.pdf](papers/14-Micikevicius%E7%AD%89-FP8%E6%A0%BC%E5%BC%8F-2022.pdf) | W22 | B1 FP8 |
| 15 | Mixed Precision Training (Micikevicius et al., 2017) | [1710.03740](https://arxiv.org/abs/1710.03740) | [15-Micikevicius等-混合精度训练-2017.pdf](papers/15-Micikevicius%E7%AD%89-%E6%B7%B7%E5%90%88%E7%B2%BE%E5%BA%A6%E8%AE%AD%E7%BB%83-2017.pdf) | W37 | Mixed Precision |
| 16 | Switch Transformers (Fedus et al., 2021) | [2101.03961](https://arxiv.org/abs/2101.03961) | [16-Fedus等-SwitchTransformers-MoE-2021.pdf](papers/16-Fedus%E7%AD%89-SwitchTransformers-MoE-2021.pdf) | W41 | MoE |

---

## 三、视频 / 课程

| 序号 | 名称 | 链接 | 重点集 / 说明 | 使用周 |
|------|------|------|---------------|--------|
| 1 | cuda-mode Lectures | [youtube.com/@CUDAMODE](https://www.youtube.com/@CUDAMODE) | Lecture 1 (Profiling), 4 (GEMM), 8 (CUTLASS), 12 (Flash Attention) | W5, W8, W12+ |
| 2 | David Beazley: Understanding the Python GIL | [youtu.be/Obt-vMVdM8s](https://www.youtube.com/watch?v=Obt-vMVdM8s) | PyCon 2010，~60min，GIL 经典必看 | W2 |
| 3 | Philip Guo: CPython Internals (10-hour codewalk) | [pgbovine.net/cpython-internals.htm](http://pgbovine.net/cpython-internals.htm) | 9 集系列，基于 CPython 2.7.8，前 3 小时 | W7 |
| 4 | Effective CMake (Daniel Pfeifer) | [youtu.be/bsXLMQ6WgIk](https://www.youtube.com/watch?v=bsXLMQ6WgIk) | C++Now 2017，现代 CMake 最佳实践 | W4 |
| 5 | Integrating Python and C++ with pybind11 (Robert Smallshire) | [youtu.be/YReJ3pSnNDo](https://www.youtube.com/watch?v=YReJ3pSnNDo) | NDC Techtown 2018 | W5 |
| 6 | CppCon Back to Basics: Templates | [youtube.com/@CppCon](https://www.youtube.com/@CppCon) | 搜索 "Back to Basics Templates" 最新版本 | W2 |
| 7 | FlashAttention Explained (Aleksa Gordic) | [youtube.com/@TheAiEpiphany](https://www.youtube.com/@TheAiEpiphany) | 频道内搜索 "FlashAttention" / "ELI5 FlashAttention" | W13 |
| 8 | CUDA Graphs: Reducing Launch Overhead | [nvidia.com/on-demand](https://www.nvidia.com/en-us/on-demand/) | GTC 搜索 "CUDA Graphs" | W11 |
| 9 | NVIDIA GTC Talks on Kernel Fusion | [nvidia.com/on-demand](https://www.nvidia.com/en-us/on-demand/) | GTC 搜索 "Kernel Fusion" | W29 |
| 10 | Triton Developer Conference 2023 | [YouTube playlist](https://youtube.com/playlist?list=PLc_vA1r0qoiRZfUC3o4_yjj0FtWvodKAz) | Phil Tillet keynote + 全部 talks | W13 |
| 11 | Memory Management in Python (Nina Zakharenko) | [youtu.be/F6u5rhUQ6dU](https://www.youtube.com/watch?v=F6u5rhUQ6dU) | PyCon 2016，~30min | W4 |
| 12 | NVIDIA Nsight Systems User Guide | [docs.nvidia.com/nsight-systems](https://docs.nvidia.com/nsight-systems/) | §1–3 入门 | W5 |
| 13 | NVIDIA Nsight Compute User Guide | [docs.nvidia.com/nsight-compute](https://docs.nvidia.com/nsight-compute/) | §1–3 入门 | W5 |

---

## 四、开源代码仓库

| 序号 | 仓库 | 链接 | 用途 | 使用周 |
|------|------|------|------|--------|
| 1 | `hwu-dev/how-to-optimize-gemm` | [github.com/hwu-dev/how-to-optimize-gemm](https://github.com/hwu-dev/how-to-optimize-gemm) | GEMM 优化链实战（naive → tensor core） | W7–W12 |
| 2 | `NVIDIA/cutlass` | [github.com/NVIDIA/cutlass](https://github.com/NVIDIA/cutlass) | 高性能 GEMM/Conv 模板库 | W17–W26 |
| 3 | `karpathy/nanoGPT` | [github.com/karpathy/nanoGPT](https://github.com/karpathy/nanoGPT) | GPT-2 训练参考（MiniInfer / MiniMegatron 基线） | W10, W30 |
| 4 | `karpathy/llm.c` | [github.com/karpathy/llm.c](https://github.com/karpathy/llm.c) | C/CUDA 版 GPT-2 训练参考 | — |
| 5 | `vllm-project/vllm` | [github.com/vllm-project/vllm](https://github.com/vllm-project/vllm) | 推理引擎参考（PagedAttention / Continuous Batching） | W17–W26 |
| 6 | `microsoft/DeepSpeed` | [github.com/microsoft/DeepSpeed](https://github.com/microsoft/DeepSpeed) | ZeRO 优化器实现参考 | W31–W40 |
| 7 | `NVIDIA/Megatron-LM` | [github.com/NVIDIA/Megatron-LM](https://github.com/NVIDIA/Megatron-LM) | TP / PP 实现参考 | W33–W39 |
| 8 | `mit-han-lab/llm-awq` | [github.com/mit-han-lab/llm-awq](https://github.com/mit-han-lab/llm-awq) | AWQ 量化参考实现 | W24–W25 |
| 9 | `IST-DASLab/gptq` | [github.com/IST-DASLab/gptq](https://github.com/IST-DASLab/gptq) | GPTQ 量化参考实现 | W23 |
| 10 | `triton-lang/triton` | [github.com/triton-lang/triton](https://github.com/triton-lang/triton) | Triton DSL 官方仓库 | W13–W18 |

---

## 五、在线文档 / 博客 / 教程

| 序号 | 名称 | 链接 | 说明 | 使用周 |
|------|------|------|------|--------|
| 1 | pybind11 官方文档 | [pybind11.readthedocs.io](https://pybind11.readthedocs.io/) | First Steps, Functions, Classes, Build Systems | W5 |
| 2 | Triton 官方文档 | [triton-lang.org](https://triton-lang.org/) | Quick Start, Tutorial 1–3, `@triton.autotune` | W13–W18 |
| 3 | CUTLASS Documentation | [github.com/NVIDIA/cutlass](https://github.com/NVIDIA/cutlass) | Quick Start, Fundamentals of GEMM, Epilogues（在 repo docs/ 下） | W17–W26 |
| 4 | NCCL Documentation | [docs.nvidia.com/deeplearning/nccl](https://docs.nvidia.com/deeplearning/nccl/) | AllReduce / AllGather / ReduceScatter / Broadcast API | W12 |
| 5 | cuBLAS Documentation | [docs.nvidia.com/cuda/cublas](https://docs.nvidia.com/cuda/cublas/) | `cublasSgemm` / `cublasGemmEx` API | W11 |
| 6 | cuDNN Developer Guide | [docs.nvidia.com/deeplearning/cudnn](https://docs.nvidia.com/deeplearning/cudnn/) | Convolution / Tensor ops 基础 API | W11 |
| 7 | NVIDIA NVTX Documentation | [docs.nvidia.com/cuda/nvtx](https://docs.nvidia.com/cuda/nvtx/) | NVTX range 标记 API | W11 |
| 8 | NVIDIA PTX ISA | [docs.nvidia.com/cuda/parallel-thread-execution](https://docs.nvidia.com/cuda/parallel-thread-execution/) | §1–5（并行执行模型、状态空间、类型、operand） | W19 |
| 9 | NVIDIA CUDA Binary Utilities | [docs.nvidia.com/cuda/cuda-binary-utilities](https://docs.nvidia.com/cuda/cuda-binary-utilities/) | `cuobjdump` / `nvdisasm` 用法 | W19 |
| 10 | PyTorch FSDP 文档 | [pytorch.org/docs/stable/fsdp.html](https://pytorch.org/docs/stable/fsdp.html) | FSDP 用法 + 论文 | W39 |
| 11 | NVIDIA NVLink / NVSwitch Whitepaper | [nvlink/nvswitch](https://www.nvidia.com/en-us/data-center/nvlink/) | GPU 互联拓扑 | W16 |
| 12 | ezyang "PyTorch Internals" | [blog.ezyang.com/2019/05/pytorch-internals](http://blog.ezyang.com/2019/05/pytorch-internals/) | Part 1: Tensor, Part 2: autograd | W8–W9 |
| 13 | Mark Harris: Optimizing Parallel Reduction in CUDA | [developer.download.nvidia.com/.../reduction.pdf](http://developer.download.nvidia.com/assets/cuda/files/reduction.pdf) | NVIDIA Dev Blog，7 版本 reduction 优化 | W4 |
| 14 | NVIDIA: Programming Tensor Cores in CUDA 9 | [developer.nvidia.com/blog/programming-tensor-cores-cuda-9](https://developer.nvidia.com/blog/programming-tensor-cores-in-cuda-9/) | WMMA API 入门 | W10 |
| 15 | NVIDIA: Using INT8 GEMM for Fast Inference | [developer.nvidia.com/blog](https://developer.nvidia.com/blog/) | 搜索 "INT8 GEMM" | W22 |
| 16 | Real Python: Async IO in Python — A Complete Walkthrough | [realpython.com/async-io-python](https://realpython.com/async-io-python/) | asyncio 全面教程 | W3 |
| 17 | MPI Tutorial | [mpitutorial.com](https://mpitutorial.com/) | 前 5 章（Send/Recv, Bcast, Reduce, Allreduce, Gather） | W10 |
| 18 | cppreference | [en.cppreference.com](https://en.cppreference.com/) | 各容器 iterator invalidation rules | W6 |
| 19 | Inside STL 系列博客 | 搜索 "Inside STL" 系列 | vector 扩容 / unordered_map / deque | W6 |
| 20 | CUDA Toolkit Samples | [github.com/NVIDIA/cuda-samples](https://github.com/NVIDIA/cuda-samples) | `scan` example 等 | W5 |

---

## 六、刷题资源（algorithm 板块）

| 序号 | 题单 | 链接 | 题目数 | 预计完成 |
|------|------|------|--------|----------|
| 1 | 代码随想录 | [programmercarl.com](https://programmercarl.com/) | 200+ | 2026.08 |
| 2 | Hot 100 | [leetcode.cn/problem-list/2cktkvj](https://leetcode.cn/problem-list/2cktkvj/) | 100 | 2026.10 |
| 3 | 面试经典 150 题 | [leetcode.cn/studyplan/top-interview-150](https://leetcode.cn/studyplan/top-interview-150/) | 150 | 2026.11 |
| 4 | 灵神题单 | [leetcode.cn/discuss/post/3141566](https://leetcode.cn/discuss/post/3141566/ru-he-ke-xue-shua-ti-by-endlesscheng-q3yd/) | ~500+ | 2027.03 |

---

## 七、PyTorch 源码阅读清单

| 序号 | 模块 | 关键文件 | 链接 | 使用周 |
|------|------|----------|------|--------|
| 1 | Tensor | `c10/core/TensorImpl.h` | [github.com/pytorch/pytorch/blob/main/c10/core/TensorImpl.h](https://github.com/pytorch/pytorch/blob/main/c10/core/TensorImpl.h) | W8 |
|  |  | `aten/src/ATen/core/TensorBase.h` | [github.com/pytorch/pytorch/blob/main/aten/src/ATen/core/TensorBase.h](https://github.com/pytorch/pytorch/blob/main/aten/src/ATen/core/TensorBase.h) |  |
| 2 | autograd | `torch/csrc/autograd/engine.cpp` | [github.com/pytorch/pytorch/blob/main/torch/csrc/autograd/engine.cpp](https://github.com/pytorch/pytorch/blob/main/torch/csrc/autograd/engine.cpp) | W9 |
|  |  | `torch/csrc/autograd/variable.cpp` | [github.com/pytorch/pytorch/blob/main/torch/csrc/autograd/variable.cpp](https://github.com/pytorch/pytorch/blob/main/torch/csrc/autograd/variable.cpp) |  |
| 3 | nn.Module | `torch/nn/modules/module.py` | [github.com/pytorch/pytorch/blob/main/torch/nn/modules/module.py](https://github.com/pytorch/pytorch/blob/main/torch/nn/modules/module.py) | W19 |

---

## 八、vLLM / DeepSpeed / Megatron-LM 源码阅读索引

### vLLM

| 序号 | 模块 | 关键文件 | 链接 | 使用周 |
|------|------|----------|------|--------|
| 1 | 入口 & Engine | `vllm/entrypoints/llm.py` | [github.com/vllm-project/vllm/blob/main/vllm/entrypoints/llm.py](https://github.com/vllm-project/vllm/blob/main/vllm/entrypoints/llm.py) | W21 |
|  |  | `vllm/engine/llm_engine.py` | [github.com/vllm-project/vllm/blob/main/vllm/engine/llm_engine.py](https://github.com/vllm-project/vllm/blob/main/vllm/engine/llm_engine.py) |  |
| 2 | BlockManager | `vllm/core/block_manager.py` | [github.com/vllm-project/vllm/blob/main/vllm/core/block_manager.py](https://github.com/vllm-project/vllm/blob/main/vllm/core/block_manager.py) | W24 |
| 3 | Scheduler | `vllm/core/scheduler.py` | [github.com/vllm-project/vllm/blob/main/vllm/core/scheduler.py](https://github.com/vllm-project/vllm/blob/main/vllm/core/scheduler.py) | W24 |
| 4 | Worker & ModelRunner | `vllm/worker/worker.py` | [github.com/vllm-project/vllm/blob/main/vllm/worker/worker.py](https://github.com/vllm-project/vllm/blob/main/vllm/worker/worker.py) | W25 |
|  |  | `vllm/worker/model_runner.py` | [github.com/vllm-project/vllm/blob/main/vllm/worker/model_runner.py](https://github.com/vllm-project/vllm/blob/main/vllm/worker/model_runner.py) |  |

### DeepSpeed

| 序号 | 模块 | 关键文件 | 链接 | 使用周 |
|------|------|----------|------|--------|
| 1 | Engine | `deepspeed/runtime/engine.py` | [github.com/microsoft/DeepSpeed/blob/master/deepspeed/runtime/engine.py](https://github.com/microsoft/DeepSpeed/blob/master/deepspeed/runtime/engine.py) | W29 |
| 2 | ZeRO Stage 1 | `deepspeed/runtime/zero/stage1.py` | [github.com/microsoft/DeepSpeed/blob/master/deepspeed/runtime/zero/stage1.py](https://github.com/microsoft/DeepSpeed/blob/master/deepspeed/runtime/zero/stage1.py) | W31 |
| 3 | ZeRO Stage 2 | `deepspeed/runtime/zero/stage2.py` | [github.com/microsoft/DeepSpeed/blob/master/deepspeed/runtime/zero/stage2.py](https://github.com/microsoft/DeepSpeed/blob/master/deepspeed/runtime/zero/stage2.py) | W31 |
| 4 | ZeRO Stage 3 | `deepspeed/runtime/zero/stage3.py` | [github.com/microsoft/DeepSpeed/blob/master/deepspeed/runtime/zero/stage3.py](https://github.com/microsoft/DeepSpeed/blob/master/deepspeed/runtime/zero/stage3.py) | W31 |

### Megatron-LM

| 序号 | 模块 | 关键文件 | 链接 | 使用周 |
|------|------|----------|------|--------|
| 1 | Tensor Parallel | `megatron/core/tensor_parallel/` | [github.com/NVIDIA/Megatron-LM/tree/main/megatron/core/tensor_parallel](https://github.com/NVIDIA/Megatron-LM/tree/main/megatron/core/tensor_parallel) | W33 |
| 2 | Pipeline Parallel | `megatron/core/pipeline_parallel/` | [github.com/NVIDIA/Megatron-LM/tree/main/megatron/core/pipeline_parallel](https://github.com/NVIDIA/Megatron-LM/tree/main/megatron/core/pipeline_parallel) | W36 |
| 3 | Dataset & Checkpoint | 相关模块 | 同上仓库按路径查找 | W39 |