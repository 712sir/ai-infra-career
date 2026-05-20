# AI Infra 工程师求职路线图

> 目标岗位：**大模型推理优化工程师（推理引擎开发）** | **分布式训练框架工程师（大模型训练系统）**
>
> 初始化：2026-05-20 | 状态：🟡 进行中

---

## 仓库结构

```
ai-infra-career/
├── README.md                  ← 本文件：完整求职路线图
├── .plan.md                   ← 分步执行计划 + 进度跟踪
├── algorithm/                 ← 板块1：手撕算法
│   ├── cpp/                   ← C++ 题解
│   ├── python/                ← Python 题解
│   └── notes/                 ← 算法专题笔记
├── fundamentals/              ← 板块2：核心技术栈
│   ├── cuda/                  ← CUDA 内核编程
│   ├── cpp/                   ← C++ 深入
│   ├── gpu-arch/              ← GPU 架构
│   └── distributed/           ← 分布式训练/推理
├── projects.md                ← 板块3：项目索引
└── interview/                 ← 板块4：求职备战
    ├── bajin/                 ← 八股文整理
    ├── resume/                ← 简历版本管理
    └── companies/             ← 各大厂面经/真题
```

---

## 板块1：手撕算法

> 目标：中等题 10 分钟内 AC，高频 Hard 题覆盖 DP/贪心

### 学习路线

| 阶段 | 内容 | 题量 | 预计时间 |
|------|------|------|----------|
| 入门 | [代码随想录](https://programmercarl.com/) + B站视频逐题敲 | ~200 | 8 周 |
| 巩固 | [LeetCode Hot 100](https://leetcode.cn/problem-list/2cktkvj/) + 剑指 Offer + 面试经典 150 | ~300 | 6 周 |
| 冲刺 | [灵神题单](https://leetcode.cn/u/endlesscheng/) + 高频 Hard（DP/贪心/图论） | ~100 | 4 周 |

### 规则

- **每道题写两个版本**：C++ 和 Python，代码放在 `algorithm/cpp/` 和 `algorithm/python/`
- **每周一次模拟**：随机 3 题，限时 90 分钟，模拟面试节奏
- **重点题型**（推理/训练岗高频）：
  - 动态规划（背包、区间、状态压缩）
  - 贪心
  - 图论（BFS/DFS/拓扑排序/最短路径）
  - 设计题（LRU/LFU → 顺手理解 KV Cache 淘汰策略）
  - C++ 专项（智能指针、多线程、内存池、lock-free queue）

### 参考资源

| 资源 | 链接 |
|------|------|
| 代码随想录 | https://programmercarl.com/ |
| B站：手把手带你撕出正确的二分法 | [BV1fA4y1o715](https://www.bilibili.com/video/BV1fA4y1o715) |
| LeetCode Hot 100 | https://leetcode.cn/problem-list/2cktkvj/ |
| 灵神题单 | https://leetcode.cn/u/endlesscheng/ |

---

## 板块2：核心技术栈

### 2.1 CUDA 内核编程 ⭐ 最高优先级

> 推理引擎和训练框架的底层都是 CUDA kernel。两个方向共同的基石。

| 阶段 | 内容 | 资源 | 时间 |
|------|------|------|------|
| 入门 | Grid/Block/Thread/Warp 模型 | 《CUDA C++ Programming Guide》前5章 | 2周 |
| 内存 | Global/Shared/Register/Constant Memory + Bank Conflict | PMPP 第3-5章 | 1周 |
| 进阶 | Warp Shuffle、Warp Vote、Cooperative Groups | CUDA Programming Guide | 1周 |
| 实战 | Tensor Core（mma.sync）+ 手写 GEMM | [how-to-optimize-gemm](https://github.com/nicelyqin/how-to-optimize-gemm) | 2周 |
| 实战 | 手写 FlashAttention forward | FlashAttention 论文 + Triton教程 | 2周 |

**核心书目**：《Programming Massively Parallel Processors》(PMPP) 第4版

**关键产出**：
- `fundamentals/cuda/` 下每个 kernel 有正确性测试 + 性能对比（naive vs optimized）

### 2.2 GPU 架构理解

| 主题 | 核心知识点 |
|------|------------|
| SM 微架构 | Warp Scheduler、Dispatch Unit、Register File、Warp Occupancy |
| Roofline Model | 判断 kernel 是 memory-bound 还是 compute-bound |
| Tensor Core | FP16/FP8/FP4 矩阵乘加、Tile 切分策略 |
| 互联 | NVLink、NVSwitch、PCIe 带宽对比 |
| Profiling | Nsight Systems (`nsys`) + Nsight Compute (`ncu`) |

### 2.3 C++ 强化

> 推理引擎（vLLM/TensorRT-LLM）全是 C++/CUDA，C++ 是面试必考项。

| 主题 | 面试重点 |
|------|----------|
| C++11/14/17 | move语义、lambda、template、constexpr |
| 多线程 | `std::thread`、`std::mutex`、`std::atomic`、`std::condition_variable` |
| 内存管理 | smart pointer（unique/shared/weak）、memory pool、NUMA |
| STL 深入 | vector扩容、unordered_map哈希冲突、deque分段 |
| 编译工具 | CMake、Makefile、GDB 调试 |
| pybind11 | Python 与 C++ 绑定（引擎开发常用） |

### 2.4 推理优化核心技术

#### 引擎源码深度阅读

| 引擎 | 重点模块 | 优先级 |
|------|----------|--------|
| **vLLM** | BlockManager（PagedAttention）、Scheduler、Worker、ModelRunner | ⭐⭐⭐ |
| **SGLang** | RadixAttention、Structured Generation、Prefix Caching | ⭐⭐ |
| **TensorRT-LLM** | Graph Optimization、Kernel Auto-Tuning、Quantization Toolkit | ⭐⭐ |

学习路径：**vLLM → SGLang（理解改进点）→ TensorRT-LLM（理解编译优化）**

#### 必懂技术清单

| 技术 | 一句话说明 | 深入方式 |
|------|------------|----------|
| **Continuous Batching** | 动态合并请求，不让 GPU 闲着 | 读 vLLM Scheduler 源码 |
| **PagedAttention** | KV Cache 按 Page 管理，类比 OS 虚拟内存 | 读 vLLM BlockManager 源码 |
| **Prefix Caching** | 相同前缀复用 KV Cache | vLLM + SGLang RadixAttention |
| **Chunked Prefill** | 长 prefill 切块，减少排队延迟 | vLLM/SGLang 源码 |
| **Speculative Decoding** | 小模型猜 + 大模型验证 | 论文 + vLLM 实现 |
| **Medusa / EAGLE** | 多头并行预测 | 论文 + 开源实现 |
| **FlashAttention-3** | 更高效的 Attention 计算 | 论文 + 代码 |

#### 量化技术全景

| 方法 | 适用场景 | 代表工具 |
|------|----------|----------|
| INT8 后训练量化 | 通用推理 | TensorRT |
| INT4 权重量化（GPTQ） | GPU 推理 | AutoGPTQ |
| INT4 全量化（AWQ） | GPU 推理 | vLLM 内置 |
| GGUF（k-quant） | CPU/混合推理 | llama.cpp |
| FP8 训练+推理 | H100/L40S | Transformer Engine |
| SmoothQuant | 激活量化 | 论文实现 |

### 2.5 分布式训练核心技术

#### 通信基础

| 主题 | 核心内容 |
|------|----------|
| NCCL 原语 | AllReduce、Broadcast、AllGather、ReduceScatter、All2All |
| 通信算法 | Ring AllReduce、Tree AllReduce、Butterfly、NVLS |
| 计算-通信重叠 | 将 AllReduce 隐藏在反向传播中 |
| 网络 | InfiniBand、RoCE、RDMA、NVLink 带宽计算 |

#### 并行策略对比

| 策略 | 通信量 | 显存优化 | 适用场景 |
|------|--------|----------|----------|
| DP (Data Parallel) | 梯度 AllReduce | 无 | 小模型多卡 |
| TP (Tensor Parallel) | 每次前向/反向都通信 | 中等 | 单层放不下 |
| PP (Pipeline Parallel) | 仅边界通信 | 高 | 层数多 |
| SP (Sequence Parallel) | 与 TP 结合 | 降低激活 | 长序列 |
| EP (Expert Parallel) | 少 | 高 | MoE 模型 |
| ZeRO-1/2/3 | 分片优化器/梯度/参数 | 极高 | 通用 |
| CP (Context Parallel) | Ring Attention | 高 | 超长上下文 |

#### 训练框架源码阅读

| 框架 | 重点模块 | 优先级 |
|------|----------|--------|
| **DeepSpeed** | ZeRO-1/2/3 分片策略、ZeRO++ 通信、CPU/NVMe Offload | ⭐⭐⭐ |
| **Megatron-LM** | PP 调度（1F1B）、TP 切分通信、DataLoader | ⭐⭐⭐ |
| **FSDP** | PyTorch 原生实现、与 DeepSpeed 对比 | ⭐⭐ |

学习路径：**DeepSpeed（API友好）→ Megatron-LM（工业级并行）→ FSDP（理解PyTorch设计）**

#### 其他关键知识

- 混合精度训练（AMP）：FP16/BF16 + 损失缩放
- 激活重计算（Activation Checkpointing / Gradient Checkpointing）
- FlashAttention 在训练中的反向传播
- 3D 并行（TP+PP+DP）调度算法
- 容错训练：弹性训练 + 断点续训
- RLHF/DPO 训练流程（了解即可）

---

## 板块3：项目经历

> 每个项目有独立仓库，本仓库仅做索引和链接

### 已有项目

| 项目 | 仓库 | 涉及技术 |
|------|------|----------|
| llm.c-learning | [链接](https://github.com/) | C 语言训练 GPT-2、CUDA kernel |
| nanoGPT | `../Project-nanoGPT` | GPT 训练全流程、PyTorch |
| llm.c | `../Project-llm.c` | C/CUDA 高效 GPT 训练 |

### 规划项目

| 项目 | 预计仓库名 | 目标 | 含金量 |
|------|------------|------|--------|
| **MiniInfer** | `mini-infer` | C++/CUDA 手写 LLM 推理引擎（KV Cache → PagedAttention → Continuous Batching） | ⭐⭐⭐ |
| **MiniQuant** | `mini-quant` | 实现 AWQ/GPTQ 量化 + CUDA INT4 GEMM kernel | ⭐⭐⭐ |
| **vLLM 源码笔记** | `vllm-notes` | 模块级架构图 + 数据流 + 开源 PR 2-3 个 | ⭐⭐⭐ |
| **MiniMegatron** | `mini-megatron` | PyTorch 手写 TP+PP+DP 训练 GPT-2 | ⭐⭐ |
| **CUDA Kernel 合集** | `cuda-kernels` | GEMM/FlashAttention/LayerNorm/RoPE，含正确性测试和性能对比 | ⭐⭐ |

### 开源贡献清单

- [ ] vLLM：提 2-3 个 PR（bug fix / 文档 / 小功能）
- [ ] DeepSpeed：提 1-2 个 PR
- [ ] llama.cpp：了解 GGUF 量化实现

---

## 板块4：求职备战

### 4.1 八股文

按模块系统整理在 `interview/bajin/` 下：

| 文件 | 内容 |
|------|------|
| `cuda.md` | GPU 架构、内存层次、Bank Conflict、Tensor Core、Roofline |
| `cpp.md` | 智能指针、多线程、内存模型、STL 原理、虚函数 |
| `inference.md` | PagedAttention 原理、Continuous Batching、量化算法对比、vLLM 架构 |
| `training.md` | NCCL 通信、ZeRO 各阶段对比、TP/PP 通信量计算、混合精度 |
| `pytorch.md` | autograd 原理、DDP 实现、DataLoader、CUDA Stream |
| `os-network.md` | 虚拟内存、页表、TCP/UDP、零拷贝、RDMA |

**八股来源**：牛客面经、LeetCode 讨论区、各厂面经汇总

### 4.2 简历管理

`interview/resume/` 下按版本迭代：

```
resume/
├── v1.0/           ← 初版
├── v2.0/           ← 优化版
└── latest/         ← 当前在用版本
```

简历结构建议：
1. 个人信息 + 求职意向
2. **职业技能**（按方向分组：推理/训练/通用，标注熟练度）
3. **项目经历**（3-4 个核心项目，每个含技术栈 + 量化成果）
4. 实习经历（如有）
5. 教育背景

### 4.3 大厂攻略

`interview/companies/` 下每厂一个文件：

| 文件 | 内容 |
|------|------|
| `bytedance.md` | 字节跳动：算法要求最高，每轮 2-3 道手撕，项目挖到极致 |
| `tencent.md` | 腾讯：流程长，底层原理深（TCP/Redis/OS），LRU 必考 |
| `alibaba.md` | 阿里：HR 权力大，价值观必问，STAR 法则准备案例 |
| `meituan.md` | 美团：务实风格，量化成果说话，分布式高并发是重点 |
| `baidu.md` | 百度：90% AI 岗，技术氛围浓，ML/DL 基础理论问得细 |
| `jingdong.md` | 京东：看重执行力，对跨专业包容，聚焦项目实际结果 |
| `pinduoduo.md` | 拼多多：薪资最高强度最大，DP 高频，流程快（1周内） |
| `huawei.md` | 华为：昇腾生态/MindSpore，国产芯片方向 |

---

## 硬件与环境

| 项目 | 当前配置 | 后续计划 |
|------|----------|----------|
| GPU | GTX 1650 (4GB) | Phase 2 租云 GPU（AutoDL / 恒源云 / Vast.ai） |
| CUDA | CUDA 12.1 (PyTorch 内置) | 安装 CUDA Toolkit 12.x 完整版 |
| Python | 3.9.13 | 够用 |
| C++ 编译器 | gcc 16.1.0 | 够用 |
| OS | Windows 10 | WSL2 Ubuntu 做 CUDA 开发体验更好 |

---

## 时间线总览

```
Month 1-2  │ CUDA入门 + PMPP + 代码随想录刷题 + C++复习
Month 3-4  │ how-to-optimize-gemm + vLLM源码 + LeetCode Hot100
Month 5-6  │ MiniInfer + PyTorch/DeepSpeed源码 + 灵神题单
Month 7-8  │ MiniQuant + vLLM笔记输出 + 整理八股
Month 9-10 │ MiniMegatron + vLLM开源PR + 简历投递 + 面试
```

---

## 关键原则

1. **先通后专**：CUDA 是底座，学好 CUDA 再决定推理/训练方向
2. **双语言**：手撕算法每道题 C++ + Python 两个版本
3. **造轮子**：手写推理引擎 > 只看源码，手写 GEMM > 只看书
4. **开源 PR**：vLLM 提 2-3 个 PR，面试时比"我看过源码"强 10 倍
5. **量化成果**：所有项目描述必须有数字对比（延迟降了 X%，吞吐提了 Y 倍）
