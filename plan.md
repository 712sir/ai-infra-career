# AI Infra 学习计划

> 目标：AI Infra 工程师 | 路径：初级工程师 → 工程师 | 出师标准：工程师阶段全部完成
>
> 状态：🟡 6/12

---

## CUDA/GPU（主线 · 每天 45min）

> 融合 NVIDIA 官方 DLI 课程 + 工程师课程 mod-107 + CUDA 120 天挑战

### 学习资源

| 优先级 | 资源 | 说明 |
|:--:|------|------|
| ⭐ | [NVIDIA DLI: CUDA C/C++ 入门](https://learn.nvidia.com/) | 官方 8h 课程，含 GPU 实验环境。加入 Developer Program 免费领 |
| ⭐ | [An Even Easier Introduction to CUDA](https://developer.nvidia.com/blog/even-easier-introduction-cuda/) | 官方 1h 快速入门，免费 |
| ⭐ | 工程师课程 [mod-107 GPU Computing](D:/study/ai-infra-engineer-learning/lessons/mod-107-gpu-computing/) | 8 课 + 练习 + 实验 |
| 📖 | 《PMMP》Ch1-7 | 参考书，核心章节 |
| 🔧 | [CUDA-Learn-Notes](https://github.com/DefTruth/CUDA-Learn-Notes) | 200+ kernel 对照 |
| 🧩 | [GPU Puzzles](https://github.com/srush/gpu-puzzles) | 交互式学习，浏览器跑 CUDA |
| 📅 | [CUDA 120-Day Challenge](https://github.com/AdepojuJeremy/CUDA-120-DAYS--CHALLENGE) | 每日任务 + 6 个 capstone 项目 |
| 💬 | CUDA-MODE Discord | 最活跃的 CUDA 学习社区 |

### 学习路线

| 阶段 | 内容 | 资源 | 验收 |
|------|------|------|------|
| 1 | GPU 架构 + 线程模型 | NVIDIA DLI 1h 入门 + PMPP Ch1-2 | 能讲清 Grid/Block/Thread/Warp |
| 2 | 内存层次 + Shared Memory | PMPP Ch3-5 + 飞书 CUDA Ch3 | 能解释 bank conflict + 写出 shared memory kernel |
| 3 | vecAdd → Reduction → GEMM naive | CUDA-Learn-Notes + GPU Puzzles | 白板写出 GEMM naive |
| 4 | GEMM 优化链（coalescing → shared memory → Tensor Core） | how-to-optim-algorithm-in-cuda | 性能对比数据 |
| 5 | Profiling（Nsight Compute/Systems） | 工程师课程 mod-107 实验 | Roofline 分析 |
| 6 | FlashAttention | FlashAttention-PyTorch-Triton | 白板写出 FA forward |

---

## 初级工程师课程（每天 90min）

> M001-M003（Python/Linux/Git）CS 科班已掌握 ⏭️。M004 开始正课。
> 
> 项目与模块穿插进行，学完对应模块立即做项目巩固。

| 模块 | 主题 | 学时 | 状态 |
|------|------|:--:|:--:|
| M004 | ML 基础（PyTorch/TensorFlow + LLM + GPU） | 20h | 🟡 进行中 |
| M005 | Docker 容器化 | 15h | ⬜ |
| M006 | Kubernetes 入门 | 20h | ⬜ |
| M007 | API 与 Web 服务（FastAPI/Flask） | 15h | ⬜ |
| M008 | 数据库与 SQL | 15h | ⬜ |
| M009 | 监控与日志（Prometheus/Grafana） | 15h | ⬜ |
| M010 | 云平台（AWS/GCP + Terraform） | 20h | ⬜ |

### 项目穿插节奏

| 项目 | 内容 | 学时 | 前置模块 |
|------|------|:--:|------|
| P1 | 简单模型 API 部署 | 60h | M004-M005 |
| P2 | Kubernetes 模型服务 | 80h | P1 + M006 |
| P3 | ML 流水线与实验追踪 | 100h | P1-P2 + M007-M008 |
| P4 | 监控告警系统 | 80h | P1-P3 + M009 |
| P5 | 生产级 ML 系统（Capstone） | 120h | 全部 |

---

## 算法（每天 30min）

> 代码随想录 → Hot 100 → 面试经典 150 → 灵神题单。每道 Python + C++ 双版本。

| 章节 | 进度 |
|------|------|
| 01-array 核心 5 题 | ✅ |
| 01-array 拓展 | ⏸️ |
| 02-linked-list 核心 7 题 | 🟡 已到 206，下一个 24 |
| 03-hash-table → 12-graph | ⬜ |

---

## 每日时间

| 块 | 内容 | 时间 |
|----|------|:--:|
| 1 | CUDA/GPU | 45min |
| 2 | 初级课程（模块学习 + 项目） | 90min |
| 3 | 算法 | 30min |
| 4 | Andrew Ng ML/DL | 25min |

> 每日总计 ~190min。Andrew Ng 课程作为 ML/DL 理论基石，配合初级课程 M004。

---

## 核心资源速查

| 资源 | 用途 |
|------|------|
| [Andrew Ng ML 笔记](D:/study/Coursera-ML-AndrewNg-Notes/) | 机器学习理论基石 |
| [Andrew Ng DL 笔记](D:/study/deeplearning_ai_books/) | 深度学习理论基石 |
| [NVIDIA DLI CUDA C/C++](https://learn.nvidia.com/) | CUDA 官方课程 |
| [GPU Puzzles](https://github.com/srush/gpu-puzzles) | CUDA 交互练习 |
| [飞书 CUDA 课程](https://tvle9mq8jh.feishu.cn/docx/BnqMdyaJ9oyXb1xwktgc7esMn4c) | CUDA 中文教材 |
| [CUDA-Learn-Notes](https://github.com/DefTruth/CUDA-Learn-Notes) | kernel 参考 |
| [初级工程师课程](D:/study/ai-infra-junior-engineer-learning/) | 主线课程 |
| [AIInfraGuide](https://caomaolufei.github.io/AIInfraGuide/) | 面试宝典 |

---

*开始：2026-06-09 | 每天推进。*
