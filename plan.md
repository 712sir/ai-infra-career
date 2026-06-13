# AI Infra 学习计划

> 目标：AI Infra 工程师 | 路径：初级工程师 → 工程师 | 出师标准：工程师阶段全部完成
>
> 状态：🟡 初级 M004 ML 基础 + CUDA 同步推进 | 算法同步

---

## 学习路线

### 阶段一：初级工程师（440h，11 周全职 / 22 周兼职）

| 模块 | 主题 | 预估 | 策略 | 状态 |
|------|------|:--:|------|:--:|
| 001 | Python 基础 | 15h | CS 科班，快速复习 | ⏭️ |
| 002 | Linux 基础 | 15h | 已会用，快速复习 | ⏭️ |
| 003 | Git 版本控制 | 10h | 已会用，跳过 | ⏭️ |
| 004 | ML 基础（PyTorch/TF + GPU + LLM） | 20h | **重点：GPU Fundamentals 练习** | 🟡 |
| 005 | Docker 容器 | 15h | 必学 | ⬜ |
| 006 | Kubernetes 入门 | 20h | 必学，Infra 核心 | ⬜ |
| 007 | API 与 Web 服务（Flask/FastAPI） | 15h | 必学，模型部署基础 | ⬜ |
| 008 | 数据库与 SQL | 15h | 快速复习 | ⏭️ |
| 009 | 监控与日志（Prometheus/Grafana） | 15h | 必学 | ⬜ |
| 010 | 云平台（AWS/GCP + Terraform） | 20h | 必学 | ⬜ |

| 项目 | 内容 | 预估 | 状态 |
|------|------|:--:|:--:|
| P1 | Simple Model API Deployment | 60h | ⬜ |
| P2 | Kubernetes Model Serving | 80h | ⬜ |
| P3 | ML Pipeline with Experiment Tracking | 100h | ⬜ |
| P4 | Monitoring & Alerting System | 80h | ⬜ |
| P5 | Production-Ready ML System (Capstone) | 120h | ⬜ |

### 阶段二：工程师（500+h，含 3 个项目）

> 初级完成后启动。覆盖：GPU Computing、MLOps、LLM 基础设施、分布式训练/推理。

---

## 并行线：CUDA/GPU（每天进行，不依赖初级课程进度）

| 阶段 | 内容 | 状态 |
|------|------|:--:|
| Grid/Block/Thread 模型 + vecAdd | PMPP Ch1-2 + 飞书 CUDA 课程 Ch1-2 | 🟡 |
| Shared Memory + Bank Conflict | 飞书 CUDA 课程 Ch3 | ⬜ |
| Reduction kernel（7 版优化链） | how-to-optim-algorithm-in-cuda | ⬜ |
| GEMM naive → shared memory → Tensor Core | CUDA-Learn-Notes 对照 | ⬜ |
| FlashAttention forward | FlashAttention-PyTorch-Triton | ⬜ |
| CUDA Graph + NVTX + Profiling | Nsight Compute/Systems | ⬜ |

---

## 算法（不变）

> 先核心题，再拓展题。每天 1 题，Python + C++ 双版本。

| 章节 | 进度 |
|------|------|
| 01-array 核心 5 题 | ✅ |
| 01-array 拓展 | ⏸️ |
| 02-linked-list 核心 7 题 | 🟡 已到 206，下一个 24 |
| 03-hash-table → 12-graph | ⬜ |

后续：Hot 100 → 面试经典 150 → 灵神题单

---

## 每日节奏

| 块 | 内容 | 时间 |
|----|------|:--:|
| 1 | CUDA/GPU（飞书课程 + kernel 手写） | 45min |
| 2 | C++（智能指针 / move 语义 / 模板） | 25min |
| 3 | Python（装饰器 / 生成器 / 协程） | 25min |
| 4 | D2L 李沐（每天 1 集） | 25min |
| 5 | 算法（每天 1 题） | 30min |
| 6 | 初级课程当前模块 | 35min |
| 7 | llm.c（Week 3 自测 + Week 4 主循环） | 35min |

---

## 核心资源

| # | 资源 | 用途 |
|---|------|------|
| ⭐1 | [飞书 CUDA 编程基础](https://tvle9mq8jh.feishu.cn/docx/BnqMdyaJ9oyXb1xwktgc7esMn4c) | CUDA 主教材 |
| ⭐2 | [飞书 AI Infra 配套课程](https://tvle9mq8jh.feishu.cn/drive/folder/B10Ff92fCl4IVHdH7U3cccAMn1V) | CUDA + Triton/PyTorch 专题 |
| ⭐3 | [D2L 李沐 B站 171 集](https://b23.tv/IjnkTRm) | 每天 1 集基石 |
| ⭐4 | [CUDA-Learn-Notes](https://github.com/DefTruth/CUDA-Learn-Notes) | 200+ kernel 参考 |
| ⭐5 | [how-to-optim-algorithm-in-cuda](https://github.com/BBuf/how-to-optim-algorithm-in-cuda) | Reduce/Attention 优化 |
| ⭐6 | [AIInfraGuide](https://caomaolufei.github.io/AIInfraGuide/) | 面试宝典 |
| ⭐7 | [KuiperInfer](https://github.com/zjhellofss/KuiperInfer) | 从零写推理引擎 |
| ⭐8 | [yalm](https://github.com/andrewkchan/yalm) | 纯 C++/CUDA 推理引擎 |
| ⭐9 | [Nano-vLLM](https://github.com) | 理解 vLLM 核心 |
| ⭐10 | [tiny-vllm](https://github.com/jmaczan/tiny-vllm) | C++ PagedAttention |
| ⭐11 | [ZOMI AI-Infra](https://github.com/Aaaqiu1/AI-Infra) | 分布式训练 + 推理 |
| ⭐12 | [vLLM 飞书课程](https://l0kzvikuq0w.feishu.cn/drive/folder/FEHnfpzWel2BVgdERTvcQ8oLnWh) | 推理部署 |

---

## 当前进度

| 线 | 进度 | 状态 |
|------|------|:--:|
| 初级课程 | M004 ML 基础开始 | 🟡 |
| CUDA | 环境就绪，Grid/Block/Thread 学习中 | 🟡 |
| 算法 | 链表核心 7 题，已到 206 | 🟡 |
| C++ | 智能指针 | 🟡 |
| Python | 装饰器 | 🟡 |
| D2L | 第 1 集 ✅ | 🟡 |
| llm.c | Week 1 ✅，Week 2 ✅，Week 3 待自测 | 🟡 |

---

## 当前迭代

| 迭代 | 时间 | 目标 |
|------|------|------|
| 第 1 迭代 | 6/9 – 7/6 | 初级 M004-M005 + CUDA Grid/Block/Thread + 链表核心 7 题收尾 |
| 第 2 迭代 | 7/7 – 8/3 | 初级 M006-M007 + CUDA Shared Memory/MatMul + 哈希表核心题 |

---

## 研究方向

| 方向 | 说明 |
|------|------|
| 🥇 推理算子优化 | Triton/CUDA 做 tiling 优化，利用 Tensor Core/FP8 |
| 🥈 KV Cache 量化压缩 | FP8/INT4 量化策略，重要 token 保留 + 非重要压缩 |

---

*开始：2026-06-09 | 学到工程师阶段出师。每天推进。*
