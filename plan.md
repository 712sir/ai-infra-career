# 执行计划与进度跟踪

> **目标**：AI Infra 工程师（推理引擎 | 训练框架）上岸 | 备选：华五博→人才引进
>
> **开始**：2026-05-20 | **B线周期**：~12 个月（44 内容周 + 9 缓冲周） | **整体周期**：~13 个月（入学前热身）| **状态**：🟡 进行中
>
> **🛡️ 缓冲带规则**：每 4 周内容后跟 1 个「追赶周」——不排新内容，只补前面落下的；若没落下，提前推进后续内容。别把计划排成玻璃。
>
> **五线并行**：A 算法刷题 · B 基础技术栈（5轨+3项目）· C llm.c-learning · D cs224n-learning · **E vLLM 开源贡献**
>
> **关键决策点**：研一末（2027.06）判断 → 申博路线 or 就业路线
>
> **B 线详细计划**：[→ fundamentals/plan.md](fundamentals/plan.md)

---

# 论文研究方向（入学前确定）

> **策略**：选能复用 44 周计划代码的方向。论文 = 项目的学术化包装，不另起炉灶。

## 🥇 首选：基于 Triton/CUTLASS 的推理算子优化

**示例题目**：面向大模型推理的 FlashAttention 风格高性能 Attention 算子设计与实现

| 维度 | 说明 |
|------|------|
| **做什么** | 用 Triton 或手写 CUDA，针对特定 seq_len / head_dim 做 tiling 优化，利用 Tensor Core / FP8 量化计算，实现可测量的加速比 |
| **为什么** | 跟 B1 CUDA + B4 Triton + MiniInfer 项目 100% 重合；论文就是把你写的 kernel 学术化 |
| **资源要求** | 一张 3090/4090 即可跑通全部实验 |
| **就业价值** | 面试官问"硕士做了什么"→"我写了一个高性能 Attention kernel，比基线快 30%"→直接对口 |
| **申博价值** | CCF-C 以上会议/期刊可投，MLSys / EuroSys 体系结构方向 |
| **参考工作** | FlashAttention (Dao, 2022) / FlashInfer / DeepGEMM / SpInfer (EuroSys'25 Best Paper) |

## 🥈 次选：KV Cache 量化压缩

**示例题目**：面向长上下文推理的自适应 KV Cache 混合精度量化压缩方法

| 维度 | 说明 |
|------|------|
| **做什么** | 研究 KV Cache 的 FP8/INT4 量化策略、重要 token 保留 + 非重要 token 压缩、跨层 cache 复用 |
| **为什么** | KV Cache 是大模型推理的最大内存瓶颈，工业界刚需；跟 MiniQuant 项目高度重合 |
| **资源要求** | 一台 GPU 即可完成对比实验 |
| **就业价值** | vLLM/SGLang/TensorRT-LLM 都在做这个方向，面试直接对上路子 |
| **参考工作** | AWQ (Lin et al., 2023) / LMCache / vLLM PagedAttention |

## ⚠️ 别碰的方向

| 方向 | 原因 |
|------|------|
| 纯模型炼丹（训新模型、刷 SOTA） | 合工大算力撑不起，就业用不上 |
| 纯理论推导（收敛性证明、复杂度） | 数学门槛高，AI Infra 面试不考 |
| 跟推理/训练框架无关的 CV/NLP 应用 | 面试没人关心你做过目标检测 |

## 入学见导师话术

> "老师，我对大模型推理引擎的算子优化比较感兴趣，想从 FlashAttention 方向切入，用 Triton 实现改进版，做系统性性能分析，希望研一能出一篇 CCF-C 以上的论文。"

---

# 五线总览

| 线 | 方向 | 目标 | 周期 |
|----|------|------|------|
| **A** | 手撕算法 | 代码随想录→Hot100→面试经典150→灵神题单 | Week 1–36 |
| **B** | 基础技术栈 | B1 CUDA编程 · B2 C++/Python · B3 分布式 · B4 PyTorch/Triton · B5 框架源码<br>+ 3 项目：MiniInfer → MiniQuant → MiniMegatron<br>📖 详细路径见 [fundamentals/plan.md](fundamentals/plan.md) | Week 1–44 |
| **C** | llm.c-learning | 从 nanoGPT 到 CUDA kernel 级理解 GPT-2 训练 | Week 1–18 |
| **D** | cs224n-learning | Stanford NLP 课程：词向量→RNN→Transformer→LLM | Week 4–24 |
| **E** 🆕 | **vLLM 开源贡献** | Good First Issue → 提 PR → 成为 Contributor；简历硬通货，申博/就业双赢 | Week 8→持续 |

---

# 周计划（Week 1–36）

## W1 (05.20–05.26)：环境 + 算法预热 + llm.c Week1

> 📅 每天 2-3 道算法题，llm.c 实际在 Week 1（非 Week 1-9 回顾）

### A 算法（代码随想录数组篇：核心 5 + 拓展 10，每天 2-3 题）

> 正确顺序按 代码随想录：先核心 5，再按技巧分组刷拓展。

**核心 5 题**（Day A1–A2）
- [x] **Day A1 (5/21 四)**：704 二分查找 + 27 移除元素 ✅
- [x] **Day A2 (5/23 五→5/24 六)**：977 有序数组的平方 + 209 长度最小的子数组 + 59 螺旋矩阵II ✅

**拓展题**（Day A3–A6，按技巧分组）
- [ ] **Day A3**：35 搜索插入位置 + 34 排序数组查找边界 `A-ext-bsearch`
- [ ] **Day A4**：26 删除重复项 + 283 移动零 + 844 比较含退格 `A-ext-twoptr`
- [ ] **Day A5**：69 x平方根 + 367 完全平方数 `A-ext-bsearch2`
- [ ] **Day A6**：904 水果成篮 + 76 最小覆盖子串 `A-ext-sliding`
- [ ] **Day A7**：54 螺旋矩阵 `A-ext-sim`
- [x] 章节笔记：`algorithm/notes/01-programmercarl/01-array/` ✅（随进度更新）

### B 基础 → [详细路径](fundamentals/plan.md#w1-0520-0526cuda-编程模型--c-智能指针)
- [ ] 安装 CUDA Toolkit 12.x（nvcc 可用）`B-cuda-env`
- [ ] B1 CUDA：PMPP Ch1（异构计算概述）`B-cuda-w1`
- [ ] B2 C++：智能指针 + move 语义（Effective Modern C++ Item 17-29）`B-cpp-w1`
- [ ] B2 Python：装饰器 + 生成器（Fluent Python Ch7, Ch14）`B-python-w1`

### C llm.c-learning（Week 1 继续）
- [x] Day 1：环境搭建 + 首次训练（Shakespeare, 100 iters）✅
- [x] Day 2：超参实验（block_size / n_layer / lr 对照）✅
- [x] Day 3：Temperature 生成对比 + 100→1000 步续训 ✅（OpenWebText 国内网络不可达）`C-w1-d3`
- [ ] Day 4-5：Wandb 可视化 + 5000 步完整训练 `C-w1-d4`

### D cs224n ⏸️ 下周开始

### 本周产出
- [ ] `algorithm/cpp/01-programmercarl/01-array/` 下 7 个 .cpp 文件
- [ ] `algorithm/python/01-programmercarl/01-array/` 下 7 个 .py 文件
- [ ] `fundamentals/cuda/` 下 PMPP ch1 笔记
- [ ] llm.c Week 1 笔记完整（含超参实验数据 + 完整训练结果）

---

## W2 (05.27–06.02)：链表 + PMPP 深入 + llm.c Week2

### A 算法（代码随想录 02-linked-list：核心 7 题）

> 每天 2-3 题，核心 7 题分 3 天完成。

- [ ] 203 移除链表元素（虚拟头节点）`A-linked-list`
- [ ] 707 设计链表（基本操作）
- [ ] 206 反转链表（双指针/头插法）
- [ ] 24 两两交换链表中的节点
- [ ] 19 删除链表的倒数第 N 个节点（快慢指针）
- [ ] 160 链表相交（双指针换轨）
- [ ] 142 环形链表 II（快慢指针 + 数学推导）
- [ ] 链表章节总结

> 拓展题（后续穿插）：141 环形链表 / 234 回文链表 / 143 重排链表

### 本周产出
- [ ] 7 个链表题双版本代码

---

## W3 (06.03–06.09)：哈希表 + 字符串 + PMPP shared memory

### A 算法（代码随想录 03-hash-table 核心 8 题 + 04-string 开始）

- [ ] 242 有效的字母异位词（数组作哈希表）`A-hash`
- [ ] 349 两个数组的交集（set 作哈希表）
- [ ] 202 快乐数（set 判重）
- [ ] 1 两数之和（map 作哈希表）
- [ ] 454 四数相加 II（map 分组 + 两两组合）
- [ ] 383 赎金信（数组作哈希表）
- [ ] 15 三数之和（双指针 + 去重）
- [ ] 18 四数之和（双指针 + 剪枝 + 去重）
- [ ] 代码随想录：04-string 前 4 题：344 反转字符串 / 541 反转字符串II / 剑指05 替换空格 / 151 翻转字符串里的单词 `A-string`
- [ ] 哈希章节总结

### B 基础 → [详细路径](fundamentals/plan.md#w3-0603-0609shared-memory--多线程)
- [ ] B1 CUDA：Shared Memory + Bank Conflict + MatMul naive `B-cuda-w3`
- [ ] B2 C++：多线程编程（mutex/atomic/condition_variable/有界阻塞队列）`B-cpp-w3`
- [ ] B2 Python：asyncio 实战 `B-python-w3`

### C llm.c-learning
- [ ] Week 11：多层 Transformer 的 CUDA 实现 `C-llmc-w11`
  - encoder block 的完整 CUDA 实现
  - LayerNorm / GeLU 的 CUDA kernel

### D cs224n ⏸️

### 本周产出
- [ ] 8 个哈希题 + 4 个字符串题双版本代码
- [ ] Matrix Multiply naive kernel
- [ ] LayerNorm/GeLU CUDA kernel 笔记

---

## W4 (06.10–06.16)：字符串收尾 + 栈队列 + cs224n 开始

### A 算法（04-string 收尾 + 06-stack-queue 开始）

- [ ] 代码随想录 04-string 完成：剑指58-II 左旋转字符串 / 28 实现 strStr (KMP) / 459 重复的子字符串 `A-string-finish`
- [ ] 代码随想录 06-stack-queue 前 5 题：232 用栈实现队列 / 225 用队列实现栈 / 20 有效的括号 / 1047 删除相邻重复项 / 150 逆波兰表达式求值 `A-stack`
- [ ] 字符串章节总结（KMP 重点）

### B 基础 → [详细路径](fundamentals/plan.md#w4-0610-0616reduction--cmake--内存管理)
- [ ] B1 CUDA：Reduction（7 版优化链）+ PMPP Ch7 `B-cuda-w4`
- [ ] B2 C++：CMake 工程化 + CUDA 项目组织 `B-cpp-w4`
- [ ] B2 Python：内存管理（引用计数/GC/`__slots__`/buffer protocol）`B-python-w4`

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
- [ ] 3 个字符串题 + 5 个栈队列题双版本代码
- [ ] Reduction kernel + PMPP ch6-7 笔记
- [ ] cs224n-learning 仓库初始化 + lec1-2 笔记

---

## 🛡️ 追赶周 1（W4 之后）

> **不排新内容。** 补 W1–W4 落下的坑。全部清完 → 提前推进 W5 内容。别带着债往下走。

- [ ] 检查 W1–W4 所有 `[ ]` 项，未完成的标 `⚠️`
- [ ] 补漏优先：B1 CUDA kernel 没写的补写，算法题没刷的补刷
- [ ] 复盘：4 周学习节奏可持续吗？每天几小时？需要调整什么？

---

## W5 (06.17–06.23)：栈队列 + 单调栈 + 二叉树开始

### A 算法
- [ ] 代码随想录：06-stack-queue 完成（239 滑动窗口最大值，347 前K高频）`A-stack-finish`
- [ ] 代码随想录：07-monotonic-stack 全部 5 题（739, 496, 503, 42, 84）`A-monostack`
- [ ] 代码随想录：08-binary-tree 遍历（144, 145, 94 递归+迭代）`A-tree-traversal`
- [ ] 代码随想录：08-binary-tree 层序遍历 10 连（102, 107, 199, 637, 429, 515, 116, 117, 104, 111）`A-tree-levelorder`
- [ ] 栈与队列章节总结

### B 基础 → [详细路径](fundamentals/plan.md#w5-0617-0623scan--pybind11--profiling)
- [ ] B1 CUDA：Parallel Scan（Blelloch）+ Profiling 工具链（nsys/ncu）`B-cuda-w5`
- [ ] B2 C++：pybind11 基础（暴露 CUDA kernel 给 Python）`B-cpp-w5`

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
- [ ] 5 个单调栈题 + 13 个二叉树遍历/层序遍历题
- [ ] Nsight Systems profiling 笔记
- [ ] cs224n lec3-4 笔记 + A1 开始

---

## W6 (06.24–06.30)：二叉树 + 回溯基础

### A 算法
- [ ] 代码随想录：08-binary-tree 属性题 13 题（101→113）`A-tree-prop`
  - 101 对称 + 100 相同 + 572 子树 + 104/559 最大深度 + 111 最小深度
  - 222 完全二叉节点数 + 110 平衡 + 257 所有路径
  - 404 左叶子 + 513 左下角 + 112/113 路径总和
- [ ] 代码随想录：09-backtracking 前 5 题（77, 216, 17, 39, 40）`A-backtrack`

### B 基础 → [详细路径](fundamentals/plan.md#w6-0624-0630cuda-c-guide--stl-深入)
- [ ] B1 CUDA：CUDA C++ Programming Guide §1-3, §5（occupancy 分析）`B-cuda-w6`
- [ ] B2 C++：STL 内部原理（vector扩容/hash表/deque分段）`B-cpp-w6`

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
- [ ] 13 个二叉树属性题 + 5 个回溯题
- [ ] LayerNorm kernel + pybind11 demo
- [ ] cs224n lec5-6 笔记 + A1 提交

---

## W7 (07.01–07.07)：二叉树收尾 + 回溯完成

### A 算法
- [ ] 代码随想录：08-binary-tree 修改+构造+BST+进阶 18 题 `A-tree-bst`
  - 修改与构造（5）：226 翻转 + 106/105 构造 + 654 最大二叉树 + 617 合并
  - BST 属性（5）：700 搜索 + 98 验证 + 530 最小差 + 501 众数 + 538 累加
  - 公共祖先（2）：236 普通LCA + 235 BST-LCA
  - BST 修改（5）：701 插入 + 450 删除 + 669 修剪 + 108 有序→BST + 1382 平衡
  - 进阶（1）：129 求根到叶子节点数字之和
- [ ] 代码随想录：09-backtracking 完成（131→37）`A-backtrack-finish`
- [ ] 二叉树章节总结（重点：遍历、构造、BST）

### B 基础 → [详细路径](fundamentals/plan.md#w7-0701-0707gemm-入门--cpython-内部)
- [ ] B1 CUDA：GEMM naive + shared memory tiled（how-to-optimize-gemm）`B-cuda-w7`
- [ ] B2 Python：CPython 内部（PyObject/引用计数/bytecode）`B-python-w7`

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
- [ ] 18 个二叉树 BST+构造题 + 10 个回溯题
- [ ] Softmax kernel + GPU 架构笔记
- [ ] cs224n lec7-8 笔记 + A2 开始

---

## W8 (07.08–07.14)：贪心算法

### A 算法
- [ ] 代码随想录：10-greedy 全部 17 题 `A-greedy`
  - 重点：跳跃游戏系列、区间问题系列、分发糖果
- [ ] 贪心章节总结（和 DP 对比）

### B 基础 → [详细路径](fundamentals/plan.md#w8-0708-0714gemm-进阶--pytorch-tensor-源码)
- [ ] B1 CUDA：GEMM 优化链（coalescing + bank conflict fix）`B-cuda-w8`
- [ ] B4 PyTorch：Tensor 内部（stride/contiguous/storage）`B-pytorch-w8`

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

## 🛡️ 追赶周 2（W8 之后）

> **不排新内容。** 补 W5–W8 落下的。全清 → 提前推进 W9。

- [ ] 检查 W5–W8 所有产出项完成度
- [ ] 重点检查：FlashAttention/GEMM kernel 进度 + 贪心/二叉树算法正确率
- [ ] 决策：如果 CUDA kernel 连续两周落后 → 调整 B 线每日投入比例

---

## W9 (07.15–07.21)：DP 基础 + 背包问题

### A 算法
- [ ] 代码随想录：11-dynamic-programming 基础DP 7 题 `A-dp-basic`
  - 509, 70, 746, 62, 63, 343, 96
- [ ] 背包：01背包理论 + 416, 1049, 494, 474 `A-dp-01knap`

### B 基础 → [详细路径](fundamentals/plan.md#w9-0715-0721warp-level--pytorch-autograd)
- [ ] B1 CUDA：Warp Shuffle + Cooperative Groups `B-cuda-w9`
- [ ] B4 PyTorch：autograd 源码（计算图/build_fn/backward）`B-pytorch-w9`

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

### B 基础 → [详细路径](fundamentals/plan.md#w10-0722-0728tensor-core--b3-分布式启动)
- [ ] B1 CUDA：Tensor Core 编程（mma.sync.f16）+ GEMM 全链性能图 `B-cuda-w10`
- [ ] B3 分布式：MPI 基础 + AllReduce 算法（Ring/RH-D）`B-dist-w10`
- [ ] 🚀 MiniInfer v0.1：CPU 单 token 推理 `B-project-w10`

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

### B 基础 → [详细路径](fundamentals/plan.md#w11-0729-0804cuda-graph--nvtx--miniinfer-v02)
- [ ] B1 CUDA：CUDA Graph + NVTX + cuBLAS/cuDNN 基础 `B-cuda-w11`
- [ ] 🚀 MiniInfer v0.2：完整模型前向（Attention/FFN/LayerNorm）`B-project-w11`

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
- [ ] 回文：647, 5, 516, 132 `A-dp-palindrome`
- [ ] 动态规划章节总结（核心：五部曲、背包、编辑距离）

### B 基础 → [详细路径](fundamentals/plan.md#w12-0805-0811gemm-优化链2--miniinfer-v10)
- [ ] B1 CUDA：GEMM 优化链 register tiling + double buffering `B-cuda-w12`
- [ ] B3 分布式：NCCL 通信原语（AllReduce/AllGather/ReduceScatter）`B-dist-w12`
- [ ] 🚀 MiniInfer v1.0：GPU 推理 + KV Cache `B-project-w12`

### D cs224n
- [ ] Lecture 17：Large Language Models `D-cs224n-lec17`
  - Scaling laws、instruction tuning、RLHF
- [ ] Lecture 18：Multilingual NLP `D-cs224n-lec18`
- [ ] A3 完成

### 本周产出
- [ ] 6 个编辑距离+回文题
- [ ] FlashAttention 完整 kernel + DP 章节总结
- [ ] cs224n lec17-18 + A3 提交

---

## 🛡️ 追赶周 3（W12 之后）

> **不排新内容。** 补 W9–W12 的坑。全清 → 提前推进 W13。

- [ ] 检查 DP 章节掌握度 + MiniInfer v1.0 是否跑通
- [ ] 重点补漏：编辑距离/回文 DP 题正确率 < 70% → 重刷
- [ ] 里程碑对账：W12 原计划 MiniInfer v1.0 GPU+KV Cache，完成了吗？

---

## W13 (08.12–08.18)：图论开始 + LeetCode Hot100 启动

### A 算法
- [ ] 代码随想录：12-graph DFS/BFS 岛屿系列（卡码网 0098→0106）`A-graph-dfs-bfs`
- [ ] LeetCode Hot100：01-hash（1, 49, 128）+ 02-two-pointers（283, 11, 15, 42）`A-hot100-start`
- [ ] 图论 DFS/BFS 章节总结

### B 基础 → [详细路径](fundamentals/plan.md#w13w14-0812-0825flashattention--triton-入门)
- [ ] B1 CUDA：FlashAttention 完整推导 + forward kernel `B-cuda-w13`
- [ ] B4 Triton：DSL 入门 + GEMM kernel `B-triton-w13`
- [ ] B3 分布式：Ring AllReduce 深入（公式推导 + MPI 实现）`B-dist-w13`

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

### B 基础 → [详细路径](fundamentals/plan.md#w15w16-0826-0908flashattention-2--triton-flashattention)
- [ ] B1 CUDA：FlashAttention-2 改进 + FlashAttn forward kernel 完成 `B-cuda-w14`
- [ ] B4 Triton：FlashAttention kernel（对比 CUDA 手写版）`B-triton-w14`
- [ ] B3 分布式：NCCL Topology + NVLink/NVSwitch `B-dist-w14`
- [ ] 🚀 MiniInfer v1.1：集成 FlashAttention + baseline benchmark `B-project-w14`

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

### B 基础 → [详细路径](fundamentals/plan.md#w17w18-0909-0922cutlass--triton-autotune)
- [ ] B1 CUDA：CUTLASS 基础（template hierarchy + FP16 GEMM）`B-cuda-w15`
- [ ] B4 Triton：autotune + GEMM 优化 `B-triton-w15`
- [ ] B3 分布式：ZeRO-1 理论（optimizer state partitioning）`B-dist-w15`
- [ ] 🚀 MiniInfer v2.0：PagedAttention（BlockManager）`B-project-w15`

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

### B 基础 → [详细路径](fundamentals/plan.md#w19w20-0923-1006ptxsass--pytorch-nnmodule)
- [ ] B1 CUDA：PTX/SASS 基础（cuobjdump/nvdisasm）`B-cuda-w16`
- [ ] B4 PyTorch：nn.Module 源码（state_dict/`_apply`/hooks）`B-pytorch-w16`
- [ ] B3 分布式：ZeRO-2/3（gradient/parameter partitioning）`B-dist-w16`
- [ ] 🚀 MiniInfer v2.1：Continuous Batching（Scheduler）`B-project-w16`

### D cs224n
- [ ] Final Project：文献调研
- [ ] 输出 cs224n 全部课程总结笔记

### 本周产出
- [ ] Hot100 19 题（二叉树7 + 图4 + 回溯8）
- [ ] vLLM 源码笔记 × 2 模块
- [ ] ZeRO-1 笔记

---

## 🛡️ 追赶周 4（W16 之后）

> **不排新内容。** 补 W13–W16 的坑。全清 → 提前推进 W17。

- [ ] 检查 Hot100 进度（计划完成 54 题，实际？）+ FlashAttention/Triton 进度
- [ ] 重点补漏：MiniInfer v2.0 PagedAttention+Continuous Batching 是否跑通？
- [ ] 节奏决策：如果 Hot100 + B 线项目同时落后 → 暂时降频 D 线 cs224n

---

## W17 (09.09–09.15)：Hot100 二分 + 栈 + 堆

### A 算法
- [ ] Hot100：10-binary-search 6 题 `A-hot100-bsearch`
- [ ] Hot100：11-stack 5 题 `A-hot100-stack`
- [ ] Hot100：12-heap 3 题 `A-hot100-heap`

### B 基础 → [详细路径](fundamentals/plan.md#w21w23-1007-1027tensor-parallelism--异步拷贝--miniinfer-v3)
- [ ] B1 CUDA：Async Copy + Pipeline（producer-consumer overlap）`B-cuda-w17`
- [ ] B3 分布式：Tensor Parallelism（Megatron 风格 col/row parallel）`B-dist-w17`
- [ ] B5 框架：vLLM 源码 — LLM/LLMEngine 入口 `B-vllm-w17`
- [ ] 🚀 MiniInfer v3.0：Tensor Parallelism 推理 `B-project-w17`

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

### B 基础 → [详细路径](fundamentals/plan.md#w22w23-1014-1027量化入门)
- [ ] B1 CUDA：INT8/FP8 GEMM（CUTLASS INT8 内置 kernel）`B-cuda-w18`
- [ ] 🚀 MiniQuant 启动：量化工具 + AWQ/GPTQ 论文精读 `B-project-w18`

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
- [ ] 代码随想录：12-graph 并查集 + 最短路（卡码网 0107→0119）`A-graph-adv`

### B 基础 → [详细路径](fundamentals/plan.md#w24w25-1028-1110awq-实现--vllm-worker)
- [ ] 🚀 MiniQuant：AWQ 核心算法（salient channel + per-channel scaling）`B-project-w19`
- [ ] B5 框架：vLLM Worker + ModelRunner 源码 `B-vllm-w19`

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

### B 基础 → [详细路径](fundamentals/plan.md#w26w28-1111-1201int4-gemm-kernel--pipeline-parallelism)
- [ ] 🚀 MiniQuant：INT4 GEMM CUDA kernel（CUTLASS 或纯 CUDA）`B-project-w20`
- [ ] B3 分布式：Pipeline Parallelism（GPipe/1F1B）`B-dist-w20`

### 本周产出
- [ ] 面试经典150 12 题
- [ ] MiniInfer 模型加载 + 单 token 推理

---

## 🛡️ 追赶周 5（W20 之后）

> **不排新内容。** 补 W17–W20 的坑。全清 → 提前推进 W21。

- [ ] 检查面试经典150启动进度 + MiniQuant AWQ 论文是否精读完
- [ ] 重点补漏：vLLM 源码阅读是否按计划推进？E 线 vLLM PR 进展？
- [ ] 全局对账：对标「2027.01 实习投递门槛」，三个硬指标目前各完成了多少？

---

## W21 (10.07–10.13)：面试经典150题 继续

### A 算法
- [ ] 面试经典150：01-array-string 后 12 题 `A-top150-arr2`
  - 238, 134, 135, 42, 13, 12, 58, 14, 151, 6, 28, 68

### B 基础 → [详细路径](fundamentals/plan.md#w29w30-1202-1215flashattention-3--kernel-fusion)
- [ ] B1 CUDA：FlashAttention-3 + Kernel Fusion 模式 `B-cuda-w21`
- [ ] B5 框架：DeepSpeed 源码启动（DeepSpeedEngine）`B-deepspeed-w21`

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

## W22–W26 期间 B 基础技术栈 → [详细路径](fundamentals/plan.md#phase-3miniquant--量化深入w22w34)

> B 线各轨道推进与项目里程碑见 fundamentals/plan.md Phase 3。此处仅保留八股任务。

### B 技术栈重点（详见 plan.md）
- [ ] B5 框架：vLLM BlockManager + Scheduler 源码 `B-vllm-w22-24`
- [ ] B5 框架：DeepSpeed ZeRO 源码（stage 1/2/3）`B-deepspeed-w24-26`
- [ ] CUTLASS 进阶（自定义 Epilogue）+ GEMM 优化链完稿 `B-cuda-w22-24`
- [ ] 🚀 MiniQuant：AWQ 实现 + INT4 GEMM + integration benchmark `B-project-w22-26`
- [ ] 🚀 MiniInfer 收尾：完整 benchmark + 项目总结 `B-project-miniinfer-final`

### 八股整理（并行推进）
- [ ] W22：`interview/bajin/cuda.md` 初版
- [ ] W23：`interview/bajin/cpp.md` 初版
- [ ] W24：`interview/bajin/python.md` 初版
- [ ] W25：`interview/bajin/inference.md` 初版
- [ ] W26：`interview/bajin/training.md` + `pytorch.md` 初版

### 开源贡献（备用）
- [ ] vLLM：浏览 Issues 找 beginner-friendly `B-oss-vllm-issue`
- [ ] vLLM PR #1（W24 前）`B-oss-vllm-pr1`

---

## 🛡️ 追赶周 6（W26 之后）

> **不排新内容。** 补 W22–W26 的坑 + 全局对账。

- [ ] 面试经典150 全部完成了吗？没完成的部分标出优先级
- [ ] MiniQuant AWQ 实现 + INT4 GEMM kernel 进度对账
- [ ] 八股文档（cuda/cpp/python/inference）写了几个了？
- [ ] **对标「2027.01 实习投递门槛」**：CUDA kernel / MiniInfer v1.0 / vLLM PR 各到哪了？

---

## W27–W31 (11.18–12.22)：灵神题单冲刺 + 简历准备

### A 算法：灵神题单核心专题
- [ ] W27：滑动窗口专题（20 题，难度分 1400–1700）`A-lingshen-sliding`
- [ ] W28：二分算法专题（20 题，难度分 1500–1800）`A-lingshen-bsearch`
- [ ] W29：单调栈 + 网格图专题（20 题）`A-lingshen-stack`
- [ ] W30：DP 入门 + 背包专题（30 题，难度分 1400–1700）`A-lingshen-dp1`
- [ ] W31：DP 区间 + 状压 + 树形专题（20 题，难度分 1700+）`A-lingshen-dp2`

### B 项目完善 → [详细路径](fundamentals/plan.md#phase-4minimegatron--冲刺w30w46)
- [ ] 🚀 MiniMegatron v0：单卡 DP 训练 loop（W30）`B-project-w27`
- [ ] 🚀 MiniMegatron v1：TP+PP 训练（W33-W37）`B-project-w28-31`
- [ ] B5 框架：Megatron-LM TP/PP 源码 `B-megatron-w27-31`
- [ ] 🚀 MiniQuant 收尾 + 集成进 MiniInfer `B-project-w27`

### 简历
- [ ] W28：简历 v1.0 初版 `B-resume-v1`
- [ ] W31：简历 v2.0（量化成果 + 项目亮点）`B-resume-v2`

---

## 🛡️ 追赶周 7（W31 之后）

> **不排新内容。** 补 W27–W31 的坑 + 简历检查。

- [ ] 灵神题单 110 题完成度？正确率？错题本整理了没？
- [ ] 简历 v2.0 写完了吗？让师兄/朋友 review 过吗？
- [ ] MiniMegatron DP 训练跑通了吗？没跑通卡在哪？
- [ ] W32 启动前的硬性前置：简历 + 八股 + MiniMegatron v0

---

## W32–W36 (2027.01.06–02.09)：MiniMegatron 核心

### A 算法冲刺
- [ ] 各厂高频真题（字节/腾讯/阿里/百度/华为）`A-company`
- [ ] 模拟面试：每天 3 题限时 60 分钟 `A-mock`
- [ ] 错题本回顾

### B 项目冲刺 → [详细路径](fundamentals/plan.md#w33w35-1230-0119tp--megatron-源码)
- [ ] 🚀 MiniMegatron v1：TP+PP 集成训练（W33-W35）`B-project-w32-35`
- [ ] B5 框架：Megatron-LM TP/PP 源码精读 `B-megatron-w32-35`
- [ ] B3 分布式：3D Parallelism 理论 + communication analysis `B-dist-w32`

### 八股冲刺（W32+）
- [ ] 全部 7 个八股文件反复背诵 + 模拟问答 `B-bajin-final`

---

## 🛡️ 追赶周 8（W36 之后）

> **不排新内容。** 全面对账 + 决策窗。

- [ ] **🔴 实习投递门槛终检**：10+ CUDA kernel / MiniInfer v1.0 GitHub / vLLM 1-2 PR — 三项全达标？
- [ ] 达标 → 投第一批简历（NVIDIA/昆仑芯/科大讯飞/寒武纪）
- [ ] 未达标 → 哪项差多少？推迟投递 to W40，W37-W40 集中补齐
- [ ] **申博决策前置**：有论文产出吗？对研究有热情吗？→ 做初步判断

---

## W37–W44 (2027.02.10–04.06)：MiniMegatron 冲刺 + 收尾 → [详细路径](fundamentals/plan.md#phase-4minimegatron--冲刺w30w46)

### W37–W38：混合精度 + ZeRO
- [ ] 🚀 MiniMegatron v2：FP16/BF16 混合精度训练（AMP + loss scaling）`B-project-w37`
- [ ] 🚀 MiniMegatron v2：ZeRO-1/2 集成（optimizer state + gradient partitioning）`B-project-w38`
- [ ] B5 框架：Megatron-LM PP 源码（1F1B schedule）`B-megatron-w37-38`

### W39–W41：FSDP + MoE + 完整训练
- [ ] B3 分布式：FSDP + Expert Parallelism（MoE 基础）`B-dist-w39`
- [ ] 🚀 MiniMegatron v3：完整 GPT-2 3D 并行训练 `B-project-w39-41`
- [ ] B5 框架：Megatron-LM Dataset + Checkpoint `B-megatron-w39-41`

### W42–W44：Scaling Test + 全面收尾
- [ ] 🚀 MiniMegatron v3：云 GPU（4×A100）scaling test + report `B-project-w42-44`
- [ ] B5 框架收尾：vLLM/DeepSpeed/Megatron-LM 源码索引完成 `B-source-final`
- [ ] B 线全面复盘：`fundamentals/retrospective.md` `B-retro`
- [ ] 简历 v2.0 最终版 `B-resume-final`

### 面试启动
- [ ] W42–43：投递简历
- [ ] W44+：各厂一面 → 复盘 → 改进

---

# 里程碑

## 技术线里程碑

| 时间 | 里程碑 | 状态 |
|------|--------|------|
| 2026.05.20 | 仓库初始化 + 五线启动 | ✅ |
| 2026.06.20 | B1 CUDA：PMPP Ch1-7 + Reducation 7版优化；B2 C++：智能指针/模板/多线程 | ⬜ |
| 2026.07.15 | B1 GEMM naive→shared memory + B2 CPython内部 + B4 PyTorch Tensor/autograd | ⬜ |
| 2026.08.10 | B1 Tensor Core GEMM + B3 MPI/AllReduce + MiniInfer v0 (CPU推理) | ⬜ |
| 2026.08.31 | FlashAttention forward kernel + B3 NCCL/Ring AllReduce + MiniInfer v1 (GPU+KV Cache) | ⬜ |
| 2026.09.30 | CUTLASS 基础 + Triton GEMM/FlashAttn + ZeRO 1/2/3 + MiniInfer v2 (PagedAttn+ContBatch) | ⬜ |
| 2026.10.31 | PTX/SASS + PyTorch nn.Module 源码 + vLLM 源码 2 模块 + MiniInfer v3 (TP) | ⬜ |
| 2026.11.30 | AWQ 实现 + INT4 GEMM kernel + DeepSpeed ZeRO 源码 + MiniQuant 完成 | ⬜ |
| 2026.12.31 | FlashAttention-2/3 + CUTLASS 进阶 + Megatron-LM TP/PP 源码 + MiniMegatron DP训练 | ⬜ |
| 2027.01.31 | 3D 并行 + 混合精度 + ZeRO 集成 + MiniMegatron TP+PP 训练跑通 | ⬜ |
| 2027.02.28 | Kernel Fusion + FSDP/MoE + 源码收尾 + MiniMegatron 完整版 + 八股全部 | ⬜ |
| 2027.03.31 | 简历 v2.0 + 面试开始 | ⬜ |
| 2027.04.30 | 第一个 offer | ⬜ |

## E 线 vLLM 开源贡献里程碑 🆕

| 时间 | 里程碑 | 状态 |
|------|--------|------|
| W8 (2026.07) | 环境搭建 + fork vLLM + 通读贡献指南 + 加入 Slack `#contributors` | ⬜ |
| W10 (2026.08) | 认领首个 Good First Issue（文档/翻译/Bug修复），提交第一个 PR | ⬜ |
| W14 (2026.09) | 首个 PR 合并 🎉 + 开始认领第二个 Issue（功能增强/模型支持） | ⬜ |
| W20 (2026.10) | 累计 3+ 合并 PR，简历标注「vLLM Contributor」 | ⬜ |
| W30 (2027.01) | 累计 5+ 合并 PR，尝试提交 CUDA kernel 相关性能优化 PR | ⬜ |
| 持续 | 保持活跃，参与社区会议，投递 talentpool@vllm.ai | ⬜ |

## 🎯 研一上学期末 · 实习投递门槛（2027.01）

> **目标**：研一上学期结束时，以下三项必须完成，缺一项不投简历。
> 达不到就继续积累，不凑数、不碰运气。

| # | 硬指标 | 验收标准 | 关联 |
|---|--------|----------|------|
| **1** | **10+ CUDA kernel 写完** | 含 GEMM（naive→shared→tensor core）、FlashAttention、Reduction、Scan、量化 GEMM（INT4/INT8）各版本，有 `ncu` profile 数据 | B1 轨道 |
| **2** | **MiniInfer v1.0 GitHub 开源** | GPU 推理 + KV Cache，README 含 benchmark vs PyTorch 基线，代码规范、有单元测试 | B 线项目 |
| **3** | **vLLM 1–2 个 PR 合入** | 至少 1 个 merged PR（文档/翻译/Bug fix 起步），简历可标注「vLLM Contributor」 | E 线 |

> 三项全达标 = 研一寒假投第一批实习（NVIDIA / 百度昆仑芯 / 淘天T-Star / 科大讯飞 / 寒武纪）

---

## 关键决策与外部节点 🆕

| 时间 | 节点 | 说明 |
|------|------|------|
| 2026.09 | 研一入学，确定导师 | 优先选放实习的导师 or 跟企业有合作的导师 |
| 2027.01 | **🔴 实习投递门槛检查** | 10+ CUDA kernel + MiniInfer v1.0 + vLLM PR 合入 → 达标即投 |
| 2027.03 | 暑期实习投递窗口打开 | 目标：字节Seed/NVIDIA/阿里PAI/智谱/MiniMax |
| 2027.06 | **🔴 决策点：申博 vs 就业** | 申博条件：1+ 论文发表 or 1+ 顶会投稿 + 对研究有热情 |
| 2027.09 | MiniInfer GPU版 v1.0 + 开源发布 | 实习面试/申博的核心筹码 |
| 2028.01 | 拿到第一段 AI Infra 实习 offer | 研二寒假/暑期实习 |
| 2028.06 | 实习完成 → 申博结果 / 秋招投递 | 双轨切换点 |
| 2028.09 | 博导入围结果 / 秋招 offer | 最终选择 |
| 2029.06 | 硕士毕业 | 入职 or 博导入学 |

---

# 研究生三年 · 实习时间线

> **核心原则**：第一段破冰（要经历），第二段冲大厂（要深度），第三段锁转正（要 offer）。
> 一步拖后腿，全线往后推。

## 时间线总览

```
研一上（2026.09–2027.01）
├── 9月：入学，选导师
├── 10–12月：推进44周计划，攒实习筹码
├── 2027年1月：🔴 实习投递门槛检查 → 达标即投

研一下（2027.02–2027.08）
├── 2–3月：暑期实习投递窗口（字节/NVIDIA/阿里等集中开岗）
├── 3–5月：面试 + 同步继续推进学习计划
├── 6月：🔴 申博 vs 就业决策
├── 7–8月：第一段暑期实习 → or → 继续推进项目/论文

研二上（2027.09–2028.01）
├── 9–12月：继续日常实习 or 回校做论文/项目
├── 2028年1月：第二段实习投递（寒假/日常）

研二下（2028.02–2028.08）
├── 2–4月：暑期实习面试（第二次窗口）
├── 5–6月：实习结束 → 申博结果揭晓 or 准备秋招
├── 7–8月：最后一段实习 → or → 全力秋招

研三上（2028.09–2029.01）
├── 9–10月：秋招正式批（投递 + 笔试 + 面试）
├── 11–12月：offer 比较 + 签三方

研三下（2029.02–2029.06）
├── 春招补录（如果秋招不理想）
└── 6月：毕业，入职
```

## 三段实习的定位

| 段位 | 时间 | 类型 | 目标 | 目标公司 |
|------|------|------|------|------|
| **🥉 第一段** | 研一暑假（2027.07–08） | 暑期实习 | 攒 AI Infra 经历，简历破冰 | 科大讯飞、寒武纪合肥、合工大合作企业 |
| **🥈 第二段** | 研二日常（2028.01–06） | 日常/寒假实习 | 技术深度，拿 return offer | NVIDIA、百度昆仑芯、字节Seed、阿里PAI |
| **🥇 第三段** | 研二暑假（2028.07–08） | 暑期实习 | 冲转正 SP offer，锁定毕业去向 | 字节 Seed / NVIDIA / 华为昇腾 / 智谱 |

## 关键认知

**第一段最难拿。** 没经验、没论文、211 出身。目标公司放低——合肥本地企业（科大讯飞/寒武纪）缺人、门槛低、跟 AI Infra 直接对口。第一段的意义不是光鲜，是让简历上有"大模型推理引擎开发经验"这行字。

**第二段开始你有筹码了。** 一段 Infra 实习 + MiniInfer/MiniQuant/MiniMegatron 三个 GitHub 项目 + vLLM Contributor → 简历直接进面试池。

**第三段拿到转正 offer = 秋招无压力。** 手里有保底，只面更好的。心态完全不一样。

## 底线

**别等到研二暑假才投第一份实习。** 研一混过去 → 简历空的 → CUDA 没写过、项目没做过、开源没贡献 → 研二补来不及 → 一步慢步步慢。

2027 年 1 月「实习投递门槛」不达标 → 整个时间线往后推半年。

---

# 每日时间分配（参考）

| 时段 | 内容 |
|------|------|
| 上午 2h | A 线：算法刷题（C++ + Python） |
| 下午 45min | B1 CUDA/GPU（kernel 实现 + 笔记） |
| 下午 45min | B2/B3/B4/B5 轮流（语言/分布式/Triton/源码） |
| 下午 30min | 项目推进（MiniInfer/MiniQuant/MiniMegatron） |
| 下午 1h | C 或 D 线：llm.c-learning / cs224n（交替进行） |
| 晚上 30min | **E 线 🆕：vLLM 开源贡献**（读 Issue / 写 PR / review 讨论） |
| 晚上 30min | 复习 + 笔记 + 八股 + 论文精读 |

> 每天 5.5-6.5 小时，vLLM 贡献每天 30 分钟即可——重在持续，不在一日之功
> B 线详细时间分配见 [fundamentals/plan.md](fundamentals/plan.md#每日时间分配b-线专属-2h)

---

# 陈果记录

## B 线（基础技术栈）当前进度

> 详见 [fundamentals/plan.md](fundamentals/plan.md)

| 阶段 | 周期 | 核心产出 | 状态 |
|------|------|----------|------|
| Phase 1: 基础建设 | W1–W10 | PMPP + C++/Python 深度 + GEMM + PyTorch内部 | ⬜ |
| Phase 2: MiniInfer | W10–W26 | 推理引擎 4 版本（CPU→GPU→PagedAttn→TP） | ⬜ |
| Phase 3: MiniQuant | W22–W34 | 量化引擎（AWQ + INT4 GEMM） | ⬜ |
| Phase 4: MiniMegatron | W30–W46 | 分布式训练（TP+PP+DP+ZeRO+AMP） | ⬜ |

| 轨道 | 当前进度 | 状态 |
|------|----------|------|
| B1 CUDA/GPU | W1 进行中 | 🟡 |
| B2 C++/Python | W1 进行中 | 🟡 |
| B3 分布式 | W10 启动 | ⬜ |
| B4 PyTorch/Triton | W8 启动 | ⬜ |
| B5 框架源码 | W16 启动 | ⬜ |

## llm.c-learning 当前进度

| 周 | 主题 | 状态 |
|----|------|------|
| W1 Day1 | 环境搭建 + 首次训练（Shakespeare） | ✅ 已完成 |
| W1 Day2 | 超参实验 | 🟡 进行中 |
| W1 Day3-5 | 换数据集 + wandb + 完整训练 | ⬜ 待完成 |
| W2–W9 | 模型前向→自测→主循环→matmul→反向→perf→kernel→GEMM | ⬜ 待完成 |
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

## vLLM 开源贡献进度 🆕

| 阶段 | 内容 | 状态 |
|------|------|------|
| Phase 0: 环境搭建 | fork repo + uv 环境 + pre-commit + 通读 CONTRIBUTING.md | ⬜ |
| Phase 1: 入门贡献 | Good First Issue（文档/翻译/Bug fix）→ 首个 PR | ⬜ |
| Phase 2: 持续贡献 | 模型支持/功能增强 → 累计 3-5 个合并 PR | ⬜ |
| Phase 3: 深度贡献 | CUDA kernel 优化/Attention 实现/性能 PR | ⬜ |
| Phase 4: 社区融入 | 参加双周会议 + 投递 talentpool@vllm.ai + 申请实习 | ⬜ |

> vLLM 贡献指南：https://docs.vllm.ai/en/latest/contributing/  
> Good First Issue 入口：https://github.com/vllm-project/vllm/issues?q=label%3A%22good+first+issue%22

---

# 风险与应对

| 风险 | 应对 |
|------|------|
| GTX 1650 4GB 跑不动大模型 | W10 起租云 GPU（AutoDL/恒源云/Vast.ai）；MiniInfer 早期用 CPU+小模型 |
| CUDA 学习曲线陡峭 | PMPP → how-to-optimize-gemm → CUTLASS 渐进式；Plan B 五轨并行可跳转 |
| 五轨并行时间不够 | B1 不可压缩；B2–B5 按需调整节奏；项目驱动确保产出 |
| cs224n 数学要求高 | Assignment 慢慢做，重点是 Lecture 的直觉理解 |
| 面试时间与预期冲突 | 每 4 周评估进度（见 plan.md 检查点），动态调整里程碑 |
| 单打独斗效率低 | CUDA MODE Discord / vLLM Slack / cs224n Piazza / 牛客圈子 |
| 战线拉长（44周）动力不足 | 3 个项目（MiniInfer/MiniQuant/MiniMegatron）提供持续的正反馈和简历产出 |
| **🆕 vLLM 首 PR 迟迟合不进去** | 从文档翻译/拼写修正开始，难度最低；Slack 社区求助 reviewer |
| **🆕 实习投递全挂** | 寒武纪合肥/科大讯飞本地兜底 + 继续 vLLM 贡献积累，第二轮冲一线 |
| **🆕 研一末论文为零→申博无望** | 果断切就业路线，研二全力卷实习；AI Infra 就业不需要论文 |
| **🆕 导师不放实习** | 入学前打听导师风格；选有企业合作的导师（合工大与小米/讯飞/蔚来有联培）；最坏情况用 vLLM 远程贡献弥补 |
| **🆕 申博面试被刷** | 提前申 5-6 所学校，不吊死一棵树；就业路线作为 Plan B 已就绪 |
