# AI Infra 工程师求职路线图

> 目标岗位：**大模型推理优化工程师（推理引擎开发）** | **分布式训练框架工程师（大模型训练系统）**
>
> 初始化：2026-05-20 | 状态：🟡 进行中

---

## 仓库结构

```
ai-infra-career/
├── README.md                  ← 本文件：完整求职路线图
├── 520plan.md                  ← 分步执行计划 + 进度跟踪
├── algorithm/                 ← 板块1：手撕算法
│   ├── cpp/                   ← C++ 题解
│   ├── python/                ← Python 题解
│   └── notes/                 ← 算法专题笔记
├── fundamentals/              ← 板块2：核心技术栈
│   ├── cuda/                  ← CUDA 内核编程
│   ├── cpp/                   ← C++ 深入
│   ├── python/                ← Python 深入
│   ├── gpu-arch/              ← GPU 架构
│   └── distributed/           ← 分布式训练/推理
├── projects.md                ← 板块3：项目索引
└── interview/                 ← 板块4：求职备战
```
```
../cs224n-learning/             ← 独立仓库：Stanford NLP 课程学习
../llm.c-learning/              ← 独立仓库：C/CUDA 训练 GPT-2
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
| 巩固 | [Hot 100](https://leetcode.cn/problem-list/2cktkvj/) + [面试经典 150 题](https://leetcode.cn/studyplan/top-interview-150/) | ~250 | 6 周 |
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
  - Python 专项（装饰器、生成器、协程、GIL、内存管理）

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

**关键产出**：`fundamentals/cuda/` 下每个 kernel 有正确性测试 + 性能对比（naive vs optimized）

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

### 2.4 Python 深入 ⭐

> Python 是 AI Infra 的"胶水语言"——模型导出、Kernel 原型、分布式调度全用它。

| 主题 | 核心内容 | 与 Infra 的关系 |
|------|----------|-----------------|
| **PyTorch 源码** | autograd 引擎、nn.Module、Tensor 内存布局、CUDA 扩展 | 推理引擎需理解模型的计算图导出 |
| **PyTorch Distributed** | DDP 实现、`torch.distributed`、ProcessGroup、Store | 训练框架核心 |
| **Triton DSL** | 用 Python 写 GPU kernel（block-level）、自动调优 | 快速原型验证 CUDA kernel 思路 |
| **Python/C++ 绑定** | pybind11 写 C++ 扩展、Python C API、ctypes | 推理引擎暴露 Python 接口的核心技术 |
| **Python 性能** | GIL 原理与绕过（subprocess/multiprocessing）、asyncio | 推理服务高并发调度 |
| **内存与对象模型** | 引用计数、GC、`__slots__`、memoryview、buffer protocol | 零拷贝数据传输 |
| **构建与打包** | setuptools、wheel、conda package、CMake + Python | 引擎 SDK 发布 |
| **Profiling** | cProfile、line_profiler、memory_profiler、py-spy | 推理服务性能调优 |

**核心产出**：
- 精读 PyTorch autograd 源码并输出笔记
- 用 Triton DSL 重写 GEMM / FlashAttention 作为原型
- 用 pybind11 给 C++ 推理引擎绑定 Python 接口

### 2.5 推理优化核心技术

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

### 2.6 分布式训练核心技术

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
| cs224n-learning | [链接](https://github.com/) | Stanford NLP 课程：词向量→Transformer→LLM |
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
| **Triton Kernel 实验** | `triton-kernels` | 用 Triton DSL 实现和对比各种 Attention/GEMM kernel 性能 | ⭐⭐ |

### 开源贡献清单（vLLM 为核心 🆕）

vLLM 是当前 AI Infra 方向性价比最高的开源贡献目标：
- 不需要面试，代码说话
- 社区活跃，Good First Issue 友好
- 简历上「vLLM Contributor」含金量极高
- 招聘方（字节/阿里/NVIDIA）都在用 vLLM

| 阶段 | 内容 | 目标 |
|:--:|------|------|
| Phase 0 | fork + 环境搭建 + 通读 CONTRIBUTING.md | 1天 |
| Phase 1 | Good First Issue（文档/翻译/Bug fix）→ 首个 PR | W8-W10 |
| Phase 2 | 模型支持/功能增强 → 累计 3-5 个合并 PR | W10-W20 |
| Phase 3 | CUDA kernel 优化/Attention 实现 | W20-W30 |
| Phase 4 | 社区融入：参加双周会议 + 投递 talentpool@vllm.ai | 持续 |

> Good First Issue：https://github.com/vllm-project/vllm/issues?q=label%3A%22good+first+issue%22  
> 贡献指南：https://docs.vllm.ai/en/latest/contributing/

其他开源贡献（次要优先级）：

- [ ] DeepSpeed：提 1-2 个 PR
- [ ] llama.cpp：了解 GGUF 量化实现
- [ ] PyTorch：提 1 个 PR（了解 PyTorch 贡献流程）
- [ ] SGLang：vLLM 竞品，了解差异化设计

---

## 板块4：求职备战

### 4.1 八股文

按模块系统整理在 `interview/bajin/` 下：

| 文件 | 内容 |
|------|------|
| `cuda.md` | GPU 架构、内存层次、Bank Conflict、Tensor Core、Roofline |
| `cpp.md` | 智能指针、多线程、内存模型、STL 原理、虚函数 |
| `python.md` | GIL、装饰器、生成器、asyncio、内存管理、pybind11 |
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

### 4.3 AI Infra 厂谱攻略

`interview/companies/` 下按三类厂商整理：

#### 第一类：互联网大厂（推理引擎 / 端侧 AI SDK 团队）

| 文件 | 厂商 | AI Infra 相关团队 |
|------|------|-------------------|
| `bytedance.md` | 字节跳动 | 豆包推理引擎、AI Infra 团队，算法要求最高 |
| `tencent.md` | 腾讯 | 混元大模型、腾讯云 AI 平台，底层原理问得深 |
| `alibaba.md` | 阿里 | 通义千问、PAI 平台，重系统设计 |
| `baidu.md` | 百度 | 文心一言、飞桨框架，AI 岗占比最高 |
| `huawei.md` | 华为 | 昇腾生态、MindSpore、CANN，国产芯方向 |
| `sensetime.md` | 商汤 | SenseNova 大模型、推理引擎、端侧 SDK |
| `megvii.md` | 旷视 | 端侧 AI SDK、Brain++ 平台 |
| `cloudwalk.md` | 云从 | 金融/安防 AI 推理 |
| `yitu.md` | 依图 | 医疗 AI 推理引擎 |

#### 第二类：AI 芯片厂（SDK / Compiler 团队）

| 文件 | 厂商 | 方向 |
|------|------|------|
| `cambricon.md` | 寒武纪 | 思元 AI 芯片、Bangbang SDK、CNML/CNDRV |
| `horizon.md` | 地平线 | 征程自动驾驶芯片、BPU 编译器、推理 SDK |
| `enflame.md` | 燧原 | 云燧训练/推理芯片、TopsRider 软件栈 |
| `bitmain.md` | 比特大陆（算能） | 算丰 AI 芯片、BMNNSDK |
| `biren.md` | 壁仞 | BR100 通用 GPU、Biren Compiler |

#### 第三类：端侧 AI SDK 厂商

| 文件 | 厂商 | 方向 |
|------|------|------|
| `arcsoft.md` | 虹软 | 端侧 AI 引擎（ArcSoft AI Engine）、手机影像 SDK |
| `megvii.md` | 旷视 | MegEngine 端侧推理、手机/车载 SDK |
| `sensetime.md` | 商汤 | SenseMARS 端侧方案 |

> 注：旷视、商汤同时覆盖大厂和端侧两类，文件共用。

#### 第四类：大模型创业公司 🆕（推理引擎/训练框架核心团队）

| 文件 | 厂商 | 方向 |
|------|------|------|
| `deepseek.md` | DeepSeek | 推理加速、CUDA 优化（门槛极高） |
| `zhipu.md` | 智谱AI | GLM 训练/推理 Infra（明确岗位） |
| `minimax.md` | MiniMax | vLLM/SGLang 推理社区协作、支持远程 |
| `moonshot.md` | 月之暗面(Kimi) | 长文本推理、MoE 推理优化 |
| `vllm.md` 🆕 | vLLM 开源社区 | 远程贡献、talentpool@vllm.ai 投递 |

### 4.4 实习目标与优先级 🆕

> 优先级按含金量和对口度排列，详细列表见 [studyplan.md](../../studyplan.md#实习目标清单)

**第一档（推理引擎/训练框架核心团队，薪资天花板）：**

| 优先级 | 公司 | 团队 | 方向 |
|:--:|------|------|------|
| 1 | 字节跳动 | Seed 豆包大模型 | 推理引擎优化、vLLM/SGLang、GPU集群调度 |
| 2 | NVIDIA | TensorRT-LLM | CUDA 算子优化、推理引擎、AI Compiler |
| 3 | 阿里云 | PAI / 通义实验室 | Agent Infra、推理优化、分布式训练 |
| 4 | 华为 | 昇腾 CANN | AI编译器、推理引擎、算子迁移 |
| 5 | vLLM | 开源社区 | 远程贡献 → 人才库 → 合作公司实习 |

**第二档（成长快，scope好）：**

| 优先级 | 公司 | 方向 |
|:--:|------|------|
| 6 | DeepSeek | 推理加速、CUDA 优化 |
| 7 | 智谱AI | 训练/推理 Infra（明确岗位） |
| 8 | MiniMax | vLLM/SGLang 推理框架协作、支持远程 |
| 9 | 寒武纪 | AI芯片编译器、推理引擎（合肥有研发中心） |
| 10 | 科大讯飞 | 星火大模型推理、讯飞+华为昇腾联合实验室（合肥总部） |

**第三档（备选）：**

| 公司 | 方向 |
|------|------|
| 月之暗面(Kimi) | 长文本推理引擎 |
| 地平线 | BPU编译器/SDK |
| 燧原 / 壁仞 | AI芯片软件栈 |
| 腾讯混元 | 推理引擎、分布式训练 |
| SGLang | 开源推理框架贡献（远程） |

**投递策略：**
1. 研一上学期：vLLM 贡献积累 GitHub 记录（随时可开始）
2. 研一下学期（3-5月）：投第一档+第二档共 8-10 家
3. 未拿到满意 offer：合肥本地保底（讯飞/寒武纪）+ 继续 vLLM 贡献，研二再战

---

## 硬件与环境

| 项目 | 当前配置 | 后续计划 |
|------|----------|----------|
| GPU | GTX 1650 (4GB) | Phase 2 租云 GPU（AutoDL / 恒源云 / Vast.ai） |
| CUDA | CUDA 12.1 (PyTorch 内置) | 安装 CUDA Toolkit 12.x 完整版 |
| Python | 3.9.13 | 够用，后续升级 3.11+ |
| C++ 编译器 | gcc 16.1.0 | 够用 |
| OS | Windows 10 | WSL2 Ubuntu 做 CUDA 开发体验更好 |

---

## 时间线总览

```
Month 1-2  │ CUDA入门 + PMPP + 代码随想录刷题 + C++/Python复习 + llm.c收尾 + cs224n词向量/RNN + vLLM Good First Issue
Month 3-4  │ how-to-optimize-gemm + PyTorch autograd源码 + LeetCode Hot100 + cs224n Transformer/LLM + vLLM 首个PR合并
Month 5-6  │ MiniInfer + Triton DSL + DeepSpeed源码 + 灵神题单 + vLLM 累计3+ PR
Month 7-8  │ MiniQuant + vLLM源码笔记 + pybind11实践 + 整理八股 + 暑期实习投递
Month 9-10 │ MiniMegatron + vLLM CUDA性能PR + 研一末决策（申博 vs 就业）+ 简历v1
Month 11-12│ 实习面试 + 实习进行中 + MiniInfer v1.0 开源发布
```

---

## 关键原则

1. **先通后专**：CUDA 是底座，学好 CUDA 再决定推理/训练方向
2. **双语言同等重视**：手撕算法每道题 C++ + Python 两个版本；引擎开发 C++ 是武器，Python 是胶水，两个都不可或缺
3. **五线并行，主线优先**：A（算法）和 B（基础技术栈）不可压缩；C（llm.c）和 D（cs224n）可灵活调整；**E（vLLM）是简历杠杆最高的线**
4. **造轮子**：手写推理引擎 > 只看源码，手写 GEMM > 只看书
5. **理论与实践结合**：cs224n 学完 Transformer → 立刻看 llm.c 的 CUDA 实现；vLLM 源码读完后 → 立刻写 MiniInfer
6. **开源 PR**：vLLM/PyTorch 提 PR，面试时比"我看过源码"强 10 倍
7. **量化成果**：所有项目描述必须有数字对比（延迟降了 X%，吞吐提了 Y 倍）
8. **芯片厂 + 大厂双线关注**：芯片厂 Compiler/SDK 岗位对 CUDA 要求更深，互联网厂对系统设计更看重
9. **🆕 双轨并行，研一末决策**：研一科研试水→2027.06 判断申博 or 就业；AI Infra 实习经历是双赢筹码
10. **🆕 vLLM 是当前最大杠杆**：每天投入 30 分钟，三个月就能写进简历；比任何校内项目都更接近工业界真实代码

---

## 路线决策树 🆕

```
研一（2026.09–2027.07）
  │
  ├─ 研一上学期：打基础 + vLLM 贡献 + MiniInfer v0
  │
  ├─ 研一下学期：MiniInfer v1 (GPU) + 投递暑期实习 + 论文投稿
  │
  └─ 研一末（2027.06）🔴 决策点
        │
        ├─ 产出论文 + 热爱研究 → 申博路线
        │     │
        │     ├─ 研二：完善论文 + 联系华五导师 + 参加复试
        │     └─ 毕业：华五博 → 人才引进/选调
        │
        └─ 无产出 or 不爱研究 → 就业路线
              │
              ├─ 研二：全力冲 Infra 实习（字节/NVIDIA/阿里/智谱）
              └─ 毕业：大厂 AI Infra SP（50-70万）
```

---

## 每日时间分配（参考）

| 时段 | 内容 |
|------|------|
| 上午 2h | A 线：算法刷题（C++ + Python） |
| 下午 2h | B 线：基础技术栈（CUDA/C++/Python/源码阅读） |
| 下午 1h | C 或 D 线：llm.c-learning / cs224n（交替进行） |
| 晚上 1h | 复习 + 笔记整理 + 八股积累 |

> 每天 5-6 小时，四线交替推进，重点在"持续"而非"突击"
