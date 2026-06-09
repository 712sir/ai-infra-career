# AI Infra 开源项目参考清单

> 整理日期：2026-06-09 · 持续挖掘中

---

## 一、综合学习路线 / 课程

### [zimei11/ai-infra-notes](https://github.com/zimei11/ai-infra-notes)

AI Infra 学习笔记 + 高清架构图 + 学习路线推荐。含 C++ 基础、量化基础、Qwen3 推理全流程。附高质量博客推荐清单。

### [Aaaqiu1/AI-Infra](https://github.com/Aaaqiu1/AI-Infra) — ZOMI 课程

最系统的中文 AI Infra 开源课，每节配 PPT + 视频 + 代码：

- 00 大模型系统概述（Scaling Law、训练/推理全流程）
- 01 AI 计算集群
- 02 通信与存储
- 04 **分布式训练**（Megatron/DeepSpeed/ZeRO/FlashAttention/FP8混合精度）
- 05 **分布式推理**（KV Cache优化/长序列推理/模型压缩）
- 06 大模型算法（Transformer/MoE/Tokenizer/Attention变种）

### [ai-infra-curriculum/ai-infra-performance-learning](https://github.com/ai-infra-curriculum/ai-infra-performance-learning)

200-250 小时 AI 性能工程师学习路径。8 模块 + 3 个大项目：

- Module 2: **手写 CUDA Kernel、Shared Memory、PyTorch C++ Extension**
- Module 3: Nsight 性能分析 + Roofline
- Module 4: **Transformer 优化（FlashAttention、RoPE、LayerNorm CUDA kernel）**
- Module 5: 量化（INT8/FP16、剪枝、TensorRT）
- Module 6: 分布式推理（TP、NCCL、Multi-GPU Serving）
- **Project 2: 手写 Custom CUDA Kernels（60h）**
- **Project 3: 高吞吐 LLM 推理系统（80h）**

### [ai-infra-curriculum/ai-infra-engineer-learning](https://github.com/ai-infra-curriculum/ai-infra-engineer-learning)

AI 基础设施工程师学习路径（10 模块），Module 7 专题 GPU 计算与分布式训练，基于 FAANG 面试要求设计。

### [ForceInjection/AI-fundermentals](https://github.com/ForceInjection/AI-fundermentals)

AI Infra 知识体系 v2.0（2025.8）。六大维度：硬件层 → 开发层 → 模型层 → 系统层 → 部署层 → 优化层。

### [caomaolufei/AIInfraGuide](https://github.com/caomaolufei/AIInfraGuide) ⭐ 680+

61篇文章 + 181道真题 + 65家公司。T0大厂 53篇 / T3芯片 22篇 / T5科大讯飞 3篇。

### [yuyouyu32/llm-interview](https://github.com/yuyouyu32/llm-interview)

LLM 算法岗面试题，标注公司+轮次。推理部署部分直接对应 B5 线。

---

## 二、CUDA / GPU Kernel

### [BBuf/how-to-optim-algorithm-in-cuda](https://github.com/BBuf/how-to-optim-algorithm-in-cuda) ⭐ 2k+

Reduce / Elementwise / Attention 等常见算子的 CUDA 优化实战。附带 CUDA-MODE 课程中文笔记（PyTorch Core Dev 主讲）。

**用在哪**：学 Reduce 时看它的 7 版优化链，理解"每一步为什么快"。

### [DefTruth/CUDA-Learn-Notes](https://github.com/DefTruth/CUDA-Learn-Notes) ⭐ 806

200+ CUDA/Tensor Core kernel。GEMM 达 cuBLAS 98-100% TFLOPS，含 flash-attn-mma。

### [Bruce-Lee-LY/cuda_hgemm](https://github.com/Bruce-Lee-LY/cuda_hgemm) ⭐ 379

半精度 GEMM 优化（WMMA + MMA PTX），注释详细。

### [shizhengLi/cutlass-learning](https://github.com/shizhengLi/cutlass-learning)

CUTLASS 深度解析与实战，中文。

**用在哪**：GEMM 写完 naive→shared→tensor core 三版后，用 CUTLASS 写工业级版本。

### [caibucai22/awesome-cuda](https://github.com/caibucai22/awesome-cuda)

CUDA 生态导航：教程 16 个 + 算子库 + 面试题。找资料入口。

### [nguyenhuykhang/FlashAttention-PyTorch-Triton](https://github.com/nguyenhuykhang/FlashAttention-PyTorch-Triton)

从零构建 FlashAttention，9 阶段渐进。

---

## 三、推理引擎

### [zjhellofss/KuiperInfer](https://github.com/zjhellofss/KuiperInfer) ⭐ 2.5k+

9 讲从零写推理引擎，支持 Llama2/Qwen2.5。C++20 + CUDA 双后端，Int8 量化。你的目标课程。

### [andrewkchan/yalm](https://github.com/andrewkchan/yalm) ⭐ 228

纯 C++/CUDA 推理引擎，零依赖，代码极简。RTX 4090 上 Mistral-7B 达 63.8 tok/s。配套博客 [Fast LLM Inference From Scratch](https://andrewkchan.dev/posts/yalm.html)。

**用在哪**：KuiperInfer 之外的第二参考。代码量小，适合对着学设计思路。

### [jmaczan/tiny-vllm](https://github.com/jmaczan/tiny-vllm)

C++/CUDA 手写 mini-vLLM。

### Nano-vLLM（GitHub 搜 "Nano-vLLM"）

纯 Python，~1200 行。覆盖 PagedAttention / Continuous Batching / Prefix Caching / TP。vLLM 源码的前置理解。

### [RussWong/vLLM_SGLang_cuteDSL_tutorial](https://github.com/RussWong/vLLM_SGLang_cuteDSL_tutorial)

vLLM / SGLang Jupyter Notebook 教程，单卡部署 + 异步并发实战。

### [Codedestructor56/LLama-from-scratch](https://github.com/Codedestructor56/LLama-from-scratch)

纯 C++/CUDA 从零实现 LLM，含 FlashAttention / RoPE / 训练推理全流程。路线图清晰。

### [flashinfer](https://github.com/flashinfer-ai/flashinfer) ⭐ 5k+

工业级推理 kernel 库。写完 MiniInfer 后用来做性能对标。

### [bobozi-org/llama.cpp-tutorials](https://github.com/bobozi-org/llama.cpp-tutorials)

llama.cpp 带教程的 fork。学 CUDA 推理的工业参考。

