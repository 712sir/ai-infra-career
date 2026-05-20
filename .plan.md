# 执行计划与进度跟踪

> **目标**：AI Infra 工程师（推理引擎 | 训练框架）上岸
>
> **开始**：2026-05-20 | **周期**：9-10 个月 | **状态**：🟡 进行中
>
> **四线并行**：A 算法刷题 · B 基础技术栈 · C llm.c-learning · D cs224n-learning

---

# 四线总览

| 线 | 方向 | 目标 | 周期 |
|----|------|------|------|
| **A** | 手撕算法 | 代码随想录→Hot100→面试经典150→灵神题单 | Week 1–36 |
| **B** | 基础技术栈 | CUDA/C++/Python/GPU架构/分布式 | Week 1–36 |
| **C** | llm.c-learning | 从 nanoGPT 到 CUDA kernel 级理解 GPT-2 训练 | Week 1–18 |
| **D** | cs224n-learning | Stanford NLP 课程：词向量→RNN→Transformer→LLM | Week 4–24 |

---

# 周计划（Week 1–36）

## W1 (05.20–05.26)：环境 + 算法预热 + llm.c 收尾准备

### A 算法
- [ ] 代码随想录：01-array 全部 7 题（C++ + Python）`A-array`
  - 704 二分查找 | 27 移除元素 | 977 有序数组的平方
  - 209 长度最小的子数组 | 59 螺旋矩阵II | 35 搜索插入位置 | 34 排序数组查找
- [ ] 笔记输出：`algorithm/notes/01-programmercarl/01-array/` 章节总结

### B 基础
- [ ] 安装 CUDA Toolkit 12.x（nvcc 可用）`B-cuda-env`
- [ ] 配置 WSL2 Ubuntu（可选，Windows 下继续也可以）
- [ ] PMPP 第1章：CUDA 编程模型概述 `B-cuda-pmpp1`
- [ ] C++：move语义、智能指针复习 `B-cpp-review`
- [ ] Python：装饰器、生成器（yield）复习 `B-python-review`

### C llm.c-learning
- [ ] 回顾 Weeks 1–9 笔记，整理一份完整目录索引 `C-llmc-review`
- [ ] 将已有的 CUDA kernel 实验代码整理到 `experiments/cuda-kernels/`

### D cs224n ⏸️ 下周开始

### 本周产出
- [ ] algorithm/cpp/01-programmercarl/01-array/ 下 7 个 .cpp 文件
- [ ] algorithm/python/01-programmercarl/01-array/ 下 7 个 .py 文件
- [ ] fundamentals/cuda/ 下 PMPP ch1 笔记

---

## W2 (05.27–06.02)：链表 + PMPP 深入 + llm.c 第10周

### A 算法
- [ ] 代码随想录：02-linked-list 全部 10 题 `A-linked-list`
  - 203 移除链表元素 | 707 设计链表 | 206 反转链表
  - 24 两两交换 | 19 删除倒数第N | 160 链表相交
  - 142 环形链表II | 141 环形链表 | 234 回文链表 | 143 重排链表
- [ ] 链表章节总结

### B 基础
- [ ] PMPP 第2-3章：Grid/Block/Thread 模型、线程组织 `B-cuda-pmpp2-3`
- [ ] 手写 Vector Addition kernel（naive + grid-stride loop）
- [ ] C++：多线程（thread/mutex/atomic/condition_variable）`B-cpp-thread`
- [ ] Python：协程 async/await、asyncio 基础 `B-python-async`

### C llm.c-learning
- [ ] Week 10：attention 算子的 CUDA kernel 深入 `C-llmc-w10`
  - 对照 nanoGPT 的 PyTorch attention → llm.c 的 C 实现 → CUDA kernel
  - 画 attention 计算的数据流图

### D cs224n ⏸️

### 本周产出
- [ ] 10 个链表题双版本代码
- [ ] PMPP ch2-3 笔记 + Vector Addition kernel
- [ ] Attention 算子对照笔记

---

## W3 (06.03–06.09)：哈希表 + 字符串 + PMPP shared memory

### A 算法
- [ ] 代码随想录：03-hash-table 全部 10 题 `A-hash`
- [ ] 代码随想录：04-string 前 4 题（344, 541, 151, 28 KMP）`A-string`
- [ ] 哈希章节总结

### B 基础
- [ ] PMPP 第4-5章：Shared Memory + Bank Conflict `B-cuda-shared-mem`
- [ ] 手写 Matrix Multiply（naive 全局内存版）
- [ ] C++：STL 深入（vector扩容、unordered_map哈希、deque分段）`B-cpp-stl`
- [ ] Python：GIL 原理 + 多线程 vs 多进程对比 `B-python-gil`

### C llm.c-learning
- [ ] Week 11：多层 Transformer 的 CUDA 实现 `C-llmc-w11`
  - encoder block 的完整 CUDA 实现
  - LayerNorm / GeLU 的 CUDA kernel

### D cs224n ⏸️

### 本周产出
- [ ] 10 个哈希题 + 4 个字符串题
- [ ] Matrix Multiply naive kernel
- [ ] LayerNorm/GeLU CUDA kernel 笔记

---

## W4 (06.10–06.16)：字符串收尾 + 栈队列 + cs224n 开始

### A 算法
- [ ] 代码随想录：04-string 完成（459, 925, 844）`A-string-finish`
- [ ] 代码随想录：06-stack-queue 前 5 题（232, 225, 20, 1047, 150）`A-stack`
- [ ] 字符串章节总结（KMP 重点）

### B 基础
- [ ] PMPP 第6-7章：并行模式（Reduction、Scan）`B-cuda-reduction`
- [ ] 手写 Reduction kernel（shared memory 优化版）
- [ ] Python：内存管理（引用计数、GC、`__slots__`、memoryview）`B-python-mem`

### C llm.c-learning
- [ ] Week 12：训练循环的 CUDA 端到端 `C-llmc-w12`
  - forward + backward + optimizer step 的 CUDA 实现
  - 分析训练各阶段的时间占比

### D cs224n-learning（启动！）
- [ ] Lecture 1：Introduction to NLP & Deep Learning `D-cs224n-lec1`
  - NLP 历史、word2vec 动机
- [ ] Lecture 2：Word Vectors & Word2Vec `D-cs224n-lec2`
  - Skip-gram, CBOW, negative sampling, hierarchical softmax
- [ ] 建立 cs224n-learning 仓库目录结构

### 本周产出
- [ ] 5 个字符串题 + 5 个栈队列题
- [ ] Reduction kernel + PMPP ch6-7 笔记
- [ ] cs224n-learning 仓库初始化 + lec1-2 笔记

---

## W5 (06.17–06.23)：栈队列 + 单调栈 + 二叉树开始

### A 算法
- [ ] 代码随想录：06-stack-queue 完成（239 滑动窗口最大值，347 前K高频）`A-stack-finish`
- [ ] 代码随想录：07-monotonic-stack 全部 5 题（739, 496, 503, 42, 84）`A-monostack`
- [ ] 代码随想录：08-binary-tree 遍历（144, 145, 94, 102）`A-tree-traversal`
- [ ] 栈与队列章节总结

### B 基础
- [ ] CUDA C++ Programming Guide 精读前 3 章 `B-cuda-guide`
- [ ] Nsight Systems (`nsys`) 基础用法 `B-profiling-nsys`
- [ ] C++：CMake 基础（add_library、target_link_libraries）`B-cpp-cmake`

### C llm.c-learning
- [ ] Week 13：自定义 CUDA kernel 实战 `C-llmc-w13`
  - 自己写 Fused Attention CUDA Kernel
  - Benchmark vs PyTorch native implementation

### D cs224n
- [ ] Lecture 3：GloVe & Distributed Representations `D-cs224n-lec3`
  - 全局共现统计、子词模型
- [ ] Lecture 4：Neural Networks & Backpropagation `D-cs224n-lec4`
  - MLP、计算图、反向传播
- [ ] Assignment 1：Word2Vec from scratch `D-cs224n-a1`

### 本周产出
- [ ] 5 个单调栈题 + 4 个二叉树遍历题
- [ ] Nsight Systems profiling 笔记
- [ ] cs224n lec3-4 笔记 + A1 开始

---

## W6 (06.24–06.30)：二叉树 + 回溯基础

### A 算法
- [ ] 代码随想录：08-binary-tree 属性题 12 题（226→113）`A-tree-prop`
- [ ] 代码随想录：09-backtracking 前 5 题（77, 216, 17, 39, 40）`A-backtrack`

### B 基础
- [ ] CUDA C++ Programming Guide 第4-5章 `B-cuda-guide-finish`
- [ ] 手写 LayerNorm kernel `B-cuda-layernorm`
- [ ] Python：pybind11 基础（暴露 C++ 函数给 Python）`B-python-pybind11`

### C llm.c-learning
- [ ] Week 14：性能优化专题 `C-llmc-w14`
  - kernel fusion、减少 kernel launch overhead
  - 使用 Nsight Compute 分析瓶颈

### D cs224n
- [ ] Lecture 5：Dependency Parsing `D-cs224n-lec5`
- [ ] Lecture 6：RNNs & Language Models `D-cs224n-lec6`
  - 梯度消失/爆炸、perplexity
- [ ] A1 完成

### 本周产出
- [ ] 12 个二叉树属性题 + 5 个回溯题
- [ ] LayerNorm kernel + pybind11 demo
- [ ] cs224n lec5-6 笔记 + A1 提交

---

## W7 (07.01–07.07)：二叉树收尾 + 回溯完成

### A 算法
- [ ] 代码随想录：08-binary-tree 构造+BST 19 题（106→669）`A-tree-bst`
- [ ] 代码随想录：09-backtracking 完成（131→37）`A-backtrack-finish`
- [ ] 二叉树章节总结（重点：遍历、构造、BST）

### B 基础
- [ ] PMPP 复习 + 总结前 7 章核心概念 `B-cuda-review`
- [ ] 手写 Softmax kernel（safe softmax）`B-cuda-softmax`
- [ ] GPU 架构：SM 微架构、Warp Scheduler、Register File `B-gpu-arch`

### C llm.c-learning
- [ ] Week 15：Multi-GPU 训练（DP 实现）`C-llmc-w15`
  - 数据并行的实现方式
  - AllReduce 梯度同步

### D cs224n
- [ ] Lecture 7：LSTMs & GRUs `D-cs224n-lec7`
- [ ] Lecture 8：Machine Translation & Seq2Seq `D-cs224n-lec8`
  - Encoder-Decoder 架构
- [ ] Assignment 2 开始：Neural Dependency Parsing `D-cs224n-a2`

### 本周产出
- [ ] 19 个二叉树 BST 题 + 10 个回溯题
- [ ] Softmax kernel + GPU 架构笔记
- [ ] cs224n lec7-8 笔记 + A2 开始

---

## W8 (07.08–07.14)：贪心算法

### A 算法
- [ ] 代码随想录：10-greedy 全部 17 题 `A-greedy`
  - 重点：跳跃游戏系列、区间问题系列、分发糖果
- [ ] 贪心章节总结（和 DP 对比）

### B 基础
- [ ] 手写 GEMM kernel：naive 版 `B-cuda-gemm-naive`
- [ ] GPU 架构：Roofline Model 分析 kernel 瓶颈 `B-gpu-roofline`
- [ ] C++：pybind11 进阶（绑定类、NumPy 数组零拷贝）`B-cpp-pybind11-adv`

### C llm.c-learning
- [ ] Week 16：混合精度训练 `C-llmc-w16`
  - FP16 forward/backward、loss scaling
  - 混合精度下的 CUDA kernel 注意事项

### D cs224n
- [ ] Lecture 9：Attention Mechanism `D-cs224n-lec9`
  - Bahdanau & Luong attention
- [ ] Lecture 10：Self-Attention & Transformers `D-cs224n-lec10` ⭐
  - 多投注意力、位置编码、残差连接
  - **这是整个课程最重要的 lecture，对照 nanoGPT/llm.c 代码理解**

### 本周产出
- [ ] 17 个贪心题
- [ ] GEMM naive kernel + Roofline 笔记
- [ ] cs224n lec9-10（重点：Transformer）

---

## W9 (07.15–07.21)：DP 基础 + 背包问题

### A 算法
- [ ] 代码随想录：11-dynamic-programming 基础DP 7 题 `A-dp-basic`
  - 509, 70, 746, 62, 63, 343, 96
- [ ] 背包：01背包理论 + 416, 1049, 494, 474 `A-dp-01knap`

### B 基础
- [ ] 手写 GEMM kernel：shared memory 版 `B-cuda-gemm-shared`
- [ ] 对比 naive vs shared memory 版性能
- [ ] Tensor Core 编程：mma.sync 基础 `B-cuda-tensorcore`

### C llm.c-learning
- [ ] Week 17：性能分析报告 + 技术博客 `C-llmc-w17`
  - GEMM 性能分析：naive → shared memory → Tensor Core 的演进
  - 写一篇完整的技术博客

### D cs224n
- [ ] Lecture 11：BERT & Pre-training `D-cs224n-lec11`
  - Masked LM、Next Sentence Prediction
- [ ] Lecture 12：GPT & Autoregressive LMs `D-cs224n-lec12`
  - 生成式预训练、prompting、in-context learning
  - **对照着你已经学过的 nanoGPT/llm.c 理解 GPT 训练**
- [ ] A2 完成

### 本周产出
- [ ] 11 个 DP 基础+01背包题
- [ ] GEMM shared memory kernel + 性能对比
- [ ] cs224n lec11-12（BERT/GPT）+ A2 提交

---

## W10 (07.22–07.28)：DP 完全背包 + 股票问题

### A 算法
- [ ] 代码随想录：完全背包理论 + 518, 377, 322, 279, 139 `A-dp-fullknap`
- [ ] 打家劫舍系列：198, 213, 337 `A-dp-house`

### B 基础
- [ ] 手写 GEMM kernel：Tensor Core 版（mma.sync）`B-cuda-gemm-tc`
- [ ] GEMM 三版（naive/shared/tc）性能图表
- [ ] GPU 架构：Tensor Core 工作原理详解 `B-gpu-tensorcore`

### C llm.c-learning
- [ ] Week 18：最终总结 + 开源贡献准备 `C-llmc-w18`
  - 将 18 周学习沉淀为一份系统化的技术文档
  - 在 llm.c 项目上提 1 个 PR

### D cs224n
- [ ] Lecture 13：Advanced Pre-training `D-cs224n-lec13`
  - RoBERTa, T5, ELECTRA, parameter-efficient fine-tuning
- [ ] Lecture 14：Question Answering `D-cs224n-lec14`
- [ ] Assignment 3 开始：RNN/LSTM for MT `D-cs224n-a3`

### 本周产出
- [ ] 8 个完全背包+打家劫舍题
- [ ] GEMM Tensor Core kernel + 性能对比图
- [ ] llm.c-learning 18 周总结文档
- [ ] cs224n lec13-14 + A3 开始

---

## W11 (07.29–08.04)：DP 股票问题

### A 算法
- [ ] 股票系列：121, 122, 123, 188, 309, 714 `A-dp-stock`
- [ ] 子序列：300, 674, 718, 1143, 1035 `A-dp-lis`

### B 基础
- [ ] 手写 FlashAttention forward（对照论文公式）`B-cuda-flash-attn`
- [ ] PyTorch autograd 源码：计算图构建 `B-python-autograd1`
- [ ] cuda-mode lectures 跟完前 5 讲 `B-cuda-mode`

### C llm.c-learning ✅ 主线完成，后续维护
- [ ] 将 llm.c-learning 核心笔记迁移到 `projects.md` 中作为项目成果

### D cs224n
- [ ] Lecture 15：Natural Language Generation `D-cs224n-lec15`
- [ ] Lecture 16：Coreference Resolution `D-cs224n-lec16`
- [ ] A3 继续

### 本周产出
- [ ] 11 个 DP 股票+子序列题
- [ ] FlashAttention forward kernel
- [ ] PyTorch autograd 笔记

---

## W12 (08.05–08.11)：DP 子序列收尾 + 回文

### A 算法
- [ ] 子序列：392, 115, 583, 72（编辑距离重点！）`A-dp-editdist`
- [ ] 回文：647, 516 `A-dp-palindrome`
- [ ] 动态规划章节总结（核心：五部曲、背包、编辑距离）

### B 基础
- [ ] FlashAttention 优化（tiling + recomputation）`B-cuda-flash-attn2`
- [ ] PyTorch autograd 源码：反向传播、grad_fn 链 `B-python-autograd2`
- [ ] cuda-mode lectures 6-10 `B-cuda-mode-finish`

### D cs224n
- [ ] Lecture 17：Large Language Models `D-cs224n-lec17`
  - Scaling laws、instruction tuning、RLHF
- [ ] Lecture 18：Multilingual NLP `D-cs224n-lec18`
- [ ] A3 完成

### 本周产出
- [ ] 5 个编辑距离+回文题
- [ ] FlashAttention 完整 kernel + DP 章节总结
- [ ] cs224n lec17-18 + A3 提交

---

## W13 (08.12–08.18)：图论开始 + LeetCode Hot100 启动

### A 算法
- [ ] 代码随想录：12-graph DFS/BFS 部分 `A-graph-dfs-bfs`
- [ ] LeetCode Hot100：01-hash（1, 49, 128）+ 02-two-pointers（283, 11, 15, 42）`A-hot100-start`
- [ ] 图论 DFS/BFS 章节总结

### B 基础
- [ ] PyTorch Tensor 源码：stride、contiguous、view vs reshape `B-python-tensor`
- [ ] PyTorch nn.Module 加载：state_dict 源码 `B-python-module`
- [ ] 分布式基础：MPI 概念、AllReduce 原理 `B-dist-allreduce`

### D cs224n
- [ ] Lecture 19：Ethics, Bias & Safety `D-cs224n-lec19`
- [ ] Lecture 20：Final Lecture / Project Info `D-cs224n-lec20`
- [ ] Assignment 4 开始：Transformers & BERT `D-cs224n-a4`

### 本周产出
- [ ] 图论 DFS/BFS 题 + Hot100 前 7 题
- [ ] PyTorch 源码笔记 + AllReduce 笔记
- [ ] cs224n lec19-20 + A4 开始

---

## W14 (08.19–08.25)：Hot100 推进

### A 算法
- [ ] Hot100：03-sliding-window（3, 438, 560, 239, 76）`A-hot100-sliding`
- [ ] Hot100：04-array（53, 56, 189, 238, 41）`A-hot100-array`
- [ ] Hot100：05-matrix（73, 54, 48, 240）`A-hot100-matrix`

### B 基础
- [ ] Triton DSL 入门：编程模型 + 第一个 kernel `B-triton-intro`
- [ ] 用 Triton 写 GEMM kernel（对比 CUDA 版）`B-triton-gemm`
- [ ] 分布式：NCCL 通信原语详解（AllReduce/Broadcast/AllGather）`B-dist-nccl`

### D cs224n
- [ ] A4 继续
- [ ] 开始 cs224n Final Project 选题：设计一个 Transformer 变体的训练/推理优化实验

### 本周产出
- [ ] Hot100 14 题
- [ ] Triton GEMM kernel
- [ ] NCCL 通信原语笔记

---

## W15 (08.26–09.01)：Hot100 链表 + 二叉树

### A 算法
- [ ] Hot100：06-linked-list 14 题 `A-hot100-linkedlist`
  - **重点**：146 LRU缓存（必考设计题）
- [ ] Hot100：07-binary-tree 前 8 题 `A-hot100-tree`

### B 基础
- [ ] Triton DSL：手写 FlashAttention forward `B-triton-flash-attn`
- [ ] Triton autotuning：`@triton.autotune` `B-triton-autotune`
- [ ] 分布式：Ring AllReduce 算法推导 `B-dist-ring`

### D cs224n
- [ ] A4 完成
- [ ] Final Project Proposal 提交

### 本周产出
- [ ] Hot100 22 题（链表14 + 二叉树8）
- [ ] Triton FlashAttention
- [ ] cs224n A4 提交 + Project Proposal

---

## W16 (09.02–09.08)：Hot100 二叉树收尾 + 图论 + 回溯

### A 算法
- [ ] Hot100：07-binary-tree 后 7 题 `A-hot100-tree-finish`
  - **重点**：124 二叉树最大路径和
- [ ] Hot100：08-graph（200, 994, 207, 208）`A-hot100-graph`
- [ ] Hot100：09-backtracking 8 题 `A-hot100-backtrack`

### B 基础
- [ ] vLLM 源码：BlockManager（PagedAttention 实现）第一遍精读 `B-vllm-block`
- [ ] vLLM 源码：LLMEngine 入口 + 请求生命周期 `B-vllm-engine`
- [ ] 分布式：ZeRO-1（优化器状态分片）实现原理 `B-dist-zero1`

### D cs224n
- [ ] Final Project：文献调研
- [ ] 输出 cs224n 全部课程总结笔记

### 本周产出
- [ ] Hot100 19 题（二叉树7 + 图4 + 回溯8）
- [ ] vLLM 源码笔记 × 2 模块
- [ ] ZeRO-1 笔记

---

## W17 (09.09–09.15)：Hot100 二分 + 栈 + 堆

### A 算法
- [ ] Hot100：10-binary-search 6 题 `A-hot100-bsearch`
- [ ] Hot100：11-stack 5 题 `A-hot100-stack`
- [ ] Hot100：12-heap 3 题 `A-hot100-heap`

### B 基础
- [ ] vLLM 源码：Scheduler 模块精读（Continuous Batching）`B-vllm-scheduler`
- [ ] vLLM 源码：Worker/ModelRunner 精读 `B-vllm-worker`
- [ ] 分布式：ZeRO-2/3（梯度/参数分片）`B-dist-zero2-3`

### D cs224n
- [ ] Final Project：实验设计 + 初步代码
- [ ] cs224n-learning 仓库整理

### 本周产出
- [ ] Hot100 14 题
- [ ] vLLM Scheduler 源码笔记
- [ ] ZeRO-2/3 笔记

---

## W18 (09.16–09.22)：Hot100 DP 全部

### A 算法
- [ ] Hot100：13-greedy 4 题 `A-hot100-greedy`
- [ ] Hot100：14-dp-1d 10 题 `A-hot100-dp1d`
  - **重点**：300 LIS, 322 零钱兑换, 416 分割等和子集
- [ ] Hot100：15-dp-2d 5 题 `A-hot100-dp2d`
  - **重点**：72 编辑距离

### B 基础
- [ ] DeepSpeed 源码：ZeRO 初始化流程 `B-deepspeed-init`
- [ ] DeepSpeed 源码：Engine 前向/反向 `B-deepspeed-engine`
- [ ] Megatron-LM：TP 切分通信分析 `B-megatron-tp`

### D cs224n
- [ ] Final Project：实验运行 + 调参

### 本周产出
- [ ] Hot100 19 题
- [ ] DeepSpeed 源码笔记 × 2
- [ ] Megatron-LM TP 分析

---

## W19 (09.23–09.29)：Hot100 技巧题 + 代码随想录图论收尾

### A 算法
- [ ] Hot100：16-tricks 5 题 `A-hot100-tricks`
- [ ] Hot100 错题回顾 + 时间复盘 `A-hot100-review`
- [ ] 代码随想录：12-graph 并查集 + 最短路部分 `A-graph-adv`

### B 基础
- [ ] 量化：AWQ 论文精读 + 核心算法笔记 `B-quant-awq`
- [ ] 量化：GPTQ 论文理解 `B-quant-gptq`
- [ ] MiniInfer 项目启动：设计文档 + 模型加载模块 `B-miniinfer-start`

### D cs224n
- [ ] Final Project：实验完成 + 报告撰写

### 本周产出
- [ ] Hot100 5 题 + 错题复盘
- [ ] AWQ/GPTQ 笔记
- [ ] MiniInfer 设计文档
- [ ] cs224n Final Project 完成

---

## W20 (09.30–10.06)：面试经典150题 启动

### A 算法
- [ ] 面试经典150：01-array-string 前 12 题 `A-top150-arr1`
  - 88, 27, 26, 80, 169, 189, 121, 122, 55, 45, 274, 380

### B 基础
- [ ] MiniInfer：实现模型加载（读取权重 → Tensor）`B-miniinfer-model`
- [ ] MiniInfer：实现单 token 推理循环 `B-miniinfer-forward`
- [ ] 量化：GGUF 格式 + llama.cpp 量化代码阅读 `B-quant-gguf`

### 本周产出
- [ ] 面试经典150 12 题
- [ ] MiniInfer 模型加载 + 单 token 推理

---

## W21 (10.07–10.13)：面试经典150题 继续

### A 算法
- [ ] 面试经典150：01-array-string 后 12 题 `A-top150-arr2`
  - 238, 134, 135, 42, 13, 12, 58, 14, 151, 6, 28, 68

### B 基础
- [ ] MiniInfer：实现 KV Cache 管理 `B-miniinfer-kvcache`
- [ ] MiniInfer：实现 GPU 推理（将计算搬到 CUDA）`B-miniinfer-gpu`
- [ ] pybind11 实战：给 MiniInfer 绑定 Python 接口 `B-miniinfer-pybind`

### 本周产出
- [ ] 面试经典150 12 题
- [ ] MiniInfer KV Cache + GPU + Python 绑定

---

## W22–W26 (10.14–11.17)：面试经典150 全部完成

> 以下 5 周以约每周一个专题的速度，完成面试经典150题的剩余 21 章（约 126 题）

### W22
- [ ] 02-two-pointers（5题）+ 03-sliding-window（4题）+ 04-matrix（5题）

### W23
- [ ] 05-hashmap（9题）+ 06-intervals（4题）+ 07-stack（5题）

### W24
- [ ] 08-linked-list（11题）+ 09-binary-tree-general（14题）

### W25
- [ ] 10-binary-tree-bfs（4题）+ 11-bst（3题）+ 12-graph-general（6题）
- [ ] 13-graph-bfs（3题）+ 14-trie（3题）+ 15-backtracking（7题）

### W26
- [ ] 16-divide-conquer（4题）+ 17-kadane（2题）+ 18-binary-search（7题）
- [ ] 19-heap（4题）+ 20-bit（6题）+ 21-math（6题）
- [ ] 22-dp-1d（5题）+ 23-dp-multidimensional（9题）

---

## W22–W26 期间 B 基础技术栈

### MiniInfer 完善（W22–W24）
- [ ] W22：实现 PagedAttention（BlockManager）`B-miniinfer-paged`
- [ ] W23：实现 Continuous Batching `B-miniinfer-batch`
- [ ] W24：性能对比 vLLM baseline + 写 benchmark 报告 `B-miniinfer-bench`

### MiniQuant 启动（W25–W26）
- [ ] W25：实现 AWQ 核心算法 `B-miniquant-awq`
- [ ] W26：实现 CUDA INT4 GEMM kernel `B-miniquant-kernel`

### 开源贡献（W22–W26）
- [ ] vLLM：浏览 Issues 找 beginner-friendly `B-oss-vllm-issue`
- [ ] vLLM PR #1（W24 前）`B-oss-vllm-pr1`
- [ ] DeepSpeed PR #1（W26 前）`B-oss-deepspeed-pr1`

### 八股整理（W22–W26）
- [ ] W22：`interview/bajin/cuda.md` 初版
- [ ] W23：`interview/bajin/cpp.md` 初版
- [ ] W24：`interview/bajin/python.md` 初版
- [ ] W25：`interview/bajin/inference.md` 初版
- [ ] W26：`interview/bajin/training.md` + `pytorch.md` 初版

---

## W27–W31 (11.18–12.22)：灵神题单冲刺 + 简历准备

### A 算法：灵神题单核心专题
- [ ] W27：滑动窗口专题（20 题，难度分 1400–1700）`A-lingshen-sliding`
- [ ] W28：二分算法专题（20 题，难度分 1500–1800）`A-lingshen-bsearch`
- [ ] W29：单调栈 + 网格图专题（20 题）`A-lingshen-stack`
- [ ] W30：DP 入门 + 背包专题（30 题，难度分 1400–1700）`A-lingshen-dp1`
- [ ] W31：DP 区间 + 状压 + 树形专题（20 题，难度分 1700+）`A-lingshen-dp2`

### B 项目完善
- [ ] MiniInfer：完整版（TP 分布式推理）`B-miniinfer-final`
- [ ] MiniQuant：精度 + 性能 benchmark 对比 `B-miniquant-final`
- [ ] MiniMegatron：TP + PP + DP 训练 GPT-2 `B-minimegatron`

### 简历
- [ ] W28：简历 v1.0 初版 `B-resume-v1`
- [ ] W31：简历 v2.0（量化成果 + 项目亮点）`B-resume-v2`

---

## W32–W36 (12.23–2027.01.26)：面试冲刺

### A 算法冲刺
- [ ] 各厂高频真题（字节/腾讯/阿里/百度/华为）`A-company`
- [ ] 模拟面试：每天 3 题限时 60 分钟 `A-mock`
- [ ] 错题本回顾

### B 八股冲刺
- [ ] 全部 7 个八股文件反复背诵 + 模拟问答 `B-bajin-final`

### 面试循环
- [ ] W32–33：投递简历
- [ ] W34–36：各厂一面 → 复盘 → 改进
- [ ] 每轮面试后更新 `interview/companies/` 对应厂面经

---

# 里程碑

| 时间 | 里程碑 | 状态 |
|------|--------|------|
| 2026.05.20 | 仓库初始化 + 四线启动 | ✅ |
| 2026.06.20 | CUDA Toolkit + PMPP 前 5 章 + 代码随想录数组/链表/哈希完成 | ⬜ |
| 2026.07.15 | 代码随想录全部完成 + GEMM shared memory kernel 完成 | ⬜ |
| 2026.08.10 | llm.c-learning 18周主线完成 + cs224n lec1-12 完成 | ⬜ |
| 2026.08.31 | Hot100 完成 + FlashAttention kernel 完成 | ⬜ |
| 2026.09.30 | cs224n 全部完成（含 Final Project）+ vLLM 源码 3 模块 | ⬜ |
| 2026.10.31 | 面试经典150题完成 + MiniInfer 基础版 | ⬜ |
| 2026.11.30 | MiniQuant + 八股初版 + 简历 v1.0 | ⬜ |
| 2026.12.31 | 灵神题单核心完成 + MiniMegatron + MiniInfer 完整版 | ⬜ |
| 2027.01.31 | 简历 v2.0 + 面试开始 | ⬜ |
| 2027.03.31 | 第一个 offer | ⬜ |

---

# 每日时间分配（参考）

| 时段 | 内容 |
|------|------|
| 上午 2h | A 线：算法刷题（C++ + Python） |
| 下午 2h | B 线：基础技术栈（CUDA/C++/Python/源码阅读） |
| 下午 1h | C 或 D 线：llm.c-learning / cs224n（交替进行） |
| 晚上 1h | 复习 + 笔记整理 + 八股积累 |

> 每天 5-6 小时，四线交替推进，重点在"持续"而非"突击"

---

# 陈果记录

## llm.c-learning 当前进度

| 周 | 主题 | 状态 |
|----|------|------|
| W1–W9 | 环境→模型→主循环→GEMM→反向→kernel | ✅ 已完成 |
| W10–W18 | attention kernel→多层→训练循环→自定义kernel→性能优化→Multi-GPU→总结 | ⬜ 待完成 |

## cs224n 规划进度

| 模块 | 内容 | 状态 |
|------|------|------|
| Lec 1–4 | Intro → Word2Vec → GloVe → NN/BP | ⬜ |
| Lec 5–8 | DepParse → RNN → LSTM/GRU → Seq2Seq | ⬜ |
| Lec 9–12 | Attention → Transformer → BERT → GPT ⭐ | ⬜ |
| Lec 13–16 | Advanced Pre-train → QA → NLG → Coref | ⬜ |
| Lec 17–20 | LLMs → Multilingual → Ethics → Final | ⬜ |
| A1–A4 | Word2Vec / DepParse / RNN-MT / BERT | ⬜ |
| Final Project | NLP+Infra 交叉实验 | ⬜ |

---

# 风险与应对

| 风险 | 应对 |
|------|------|
| GTX 1650 4GB 跑不动大模型 | W10 起租云 GPU（AutoDL/恒源云/Vast.ai） |
| CUDA 学习曲线陡峭 | PMPP + how-to-optimize-gemm + llm.c 三线同步推进 |
| 四线并行时间不够 | 主线 A/B 不可压缩，C/D 线可灵活调整节奏 |
| cs224n 数学要求高 | Assignment 慢慢做，重点是 Lecture 的直觉理解 |
| 面试时间与预期冲突 | 每 4 周评估进度，动态调整里程碑 |
| 单打独斗效率低 | CUDA MODE Discord / vLLM Slack / cs224n Piazza / 牛客圈子 |
