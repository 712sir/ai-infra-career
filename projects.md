# 项目索引

> 每个项目有独立仓库，本文件仅做索引和进度跟踪

---

## 已有项目

### llm.c-learning
- **仓库**：`llm.c-learning`
- **状态**：🟡 进行中
- **内容**：跟随 [llm.c](https://github.com/karpathy/llm.c) 手写 C/CUDA 训练 GPT-2
- **目录**：`d:/study/llm.c-learning/`
- **涉及技术**：C 语言、CUDA kernel、GPT-2 架构、训练循环

### cs224n-learning
- **仓库**：[cs224n-learning](https://github.com/712sir/cs224n-learning)
- **状态**：🟡 进行中
- **内容**：Stanford CS224N 课程学习：词向量 → RNN → Transformer → LLM 全栈
- **目录**：`d:/study/cs224n-learning/`
- **涉及技术**：PyTorch、Word2Vec、RNN/LSTM、Transformer、BERT/GPT、LoRA/PEFT、RAG、LLM 评估

### nanoGPT
- **仓库**：`Project-nanoGPT`
- **状态**：✅ 已完成 Shakespeare 训练
- **内容**：Andrej Karpathy 的 GPT 教学实现
- **目录**：`d:/study/Project-nanoGPT/`
- **涉及技术**：PyTorch、GPT 架构、训练流程

### llm.c
- **仓库**：`Project-llm.c`
- **状态**：✅ 已编译
- **内容**：Karpathy 的 C 语言 GPT-2 训练实现
- **目录**：`d:/study/Project-llm.c/`
- **涉及技术**：C 语言、CUDA、GPT-2

---

## 规划项目

### MiniInfer — 手写 LLM 推理引擎 ⭐⭐⭐
- **计划仓库名**：`mini-infer`
- **目标**：用 C++/CUDA 实现一个极简 LLM 推理引擎
- **技术栈**：C++、CUDA、PyTorch（模型导出）
- **里程碑**：
  - [ ] Milestone 1：模型加载 + 单 token 推理（CPU）
  - [ ] Milestone 2：KV Cache 管理 + GPU 推理
  - [ ] Milestone 3：PagedAttention（BlockManager）
  - [ ] Milestone 4：Continuous Batching
  - [ ] Milestone 5：Prefix Caching
  - [ ] Milestone 6：TP 分布式推理
- **预计工期**：2 个月

### MiniQuant — 手写量化工具 ⭐⭐⭐
- **计划仓库名**：`mini-quant`
- **目标**：实现 AWQ/GPTQ 的核心量化算法
- **技术栈**：CUDA、Python、PyTorch
- **里程碑**：
  - [ ] Milestone 1：INT8 PTQ（最基础量化）
  - [ ] Milestone 2：AWQ 算法实现
  - [ ] Milestone 3：CUDA INT4 GEMM kernel
  - [ ] Milestone 4：精度 + 速度 benchmark 对比
- **预计工期**：1.5 个月

### vLLM 源码阅读笔记 ⭐⭐⭐
- **计划仓库名**：`vllm-notes`
- **目标**：输出系统化的 vLLM 源码阅读笔记 + 开源 PR
- **内容**：
  - [ ] 模块级架构图 + 数据流图
  - [ ] BlockManager / Scheduler / Worker 精读笔记
  - [ ] 关键技术深入（PagedAttention、Continuous Batching）
  - [ ] vLLM PR × 2-3
- **预计工期**：持续 2-3 个月

### MiniMegatron — 手写分布式训练 ⭐⭐
- **计划仓库名**：`mini-megatron`
- **目标**：PyTorch 手写 TP + PP + DP 训练 GPT-2
- **技术栈**：PyTorch、NCCL、torch.distributed
- **里程碑**：
  - [ ] Milestone 1：单卡训练 GPT-2
  - [ ] Milestone 2：DP 多卡训练
  - [ ] Milestone 3：TP 张量并行
  - [ ] Milestone 4：PP 流水线并行（1F1B）
  - [ ] Milestone 5：ZeRO 优化器状态分片
- **预计工期**：1.5 个月

### CUDA Kernel 合集 ⭐⭐
- **计划仓库名**：`cuda-kernels`
- **目标**：高质量 CUDA kernel 实现合集
- **技术栈**：CUDA C++
- **Kernel 列表**：
  - [ ] GEMM（naive → shared memory → Tensor Core）
  - [ ] FlashAttention forward
  - [ ] LayerNorm / RMSNorm
  - [ ] Rotary Embedding（RoPE）
  - [ ] Softmax（safe + online）
  - [ ] SwiGLU activation
  - [ ] KV Cache 更新
  - 每个 kernel：正确性测试 + 性能对比（naive vs optimized）
- **预计工期**：持续积累
