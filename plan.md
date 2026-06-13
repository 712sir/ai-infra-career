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

## C++（每天 25min）

> 目标：系统编程能力，能读懂和贡献推理引擎（vLLM/TensorRT-LLM 全是 C++）

### 学习资源

| 优先级 | 资源 | 说明 |
|:--:|------|------|
| ⭐ | 《Effective Modern C++》 | 智能指针、move 语义、模板 |
| ⭐ | [现代 C++ 编程实战（极客时间）](https://time.geekbang.org/column/intro/100040501) | 前 Intel 架构师讲 RAII/coroutine/PMR |
| 📖 | 《CSAPP》 | 内存层次、机器级表示、缓存 |
| 🔗 | [zimei11/ai-infra-notes](https://github.com/zimei11/ai-infra-notes) | AI Infra 学习笔记 + 架构图 |
| 🔗 | [现代 C++ 教程](https://github.com/changkun/modern-cpp-tutorial) | 免费在线 C++11/14/17/20 |

### 学习路线

| 阶段 | 内容 | 验收 |
|------|------|------|
| 1 | 智能指针（unique/shared/weak）+ move 语义 | 手写简化版 shared_ptr |
| 2 | 多线程（thread/mutex/atomic/condition_variable） | 手写有界阻塞队列 |
| 3 | 内存池 + lock-free queue | 手写简化版内存池 |
| 4 | CMake + pybind11 + GDB | 给 CUDA kernel 绑定 Python 接口 |
| 5 | 源码阅读：vLLM Scheduler / BlockManager | 模块级架构图笔记 |

---

## Python（每天 25min）

> 目标：PyTorch 内部原理 + Triton DSL + Python/C++ 绑定

### 学习资源

| 优先级 | 资源 | 说明 |
|:--:|------|------|
| ⭐ | 《Fluent Python》 | 装饰器、生成器、协程、GIL |
| ⭐ | [D2L 李沐 B站 171 集](https://b23.tv/IjnkTRm) | 每天 1 集基石 |
| 🔧 | PyTorch 源码 | autograd 引擎、nn.Module、Tensor 内存布局 |
| 🔧 | [Triton 官方教程](https://triton-lang.org/) | GPU kernel 原型验证 |
| 🔧 | [pybind11 文档](https://pybind11.readthedocs.io/) | Python ↔ C++ 绑定 |

### 学习路线

| 阶段 | 内容 | 验收 |
|------|------|------|
| 1 | 装饰器 + 生成器 + 协程 | 手写 @timer/@retry + 惰性文件读取 |
| 2 | GIL / 多进程 / asyncio | 手写异步推理服务雏形 |
| 3 | PyTorch autograd 源码 | 能讲清计算图构建 + backward 流程 |
| 4 | Triton DSL 写 GEMM / Attention | 性能对比 PyTorch 原生 |
| 5 | pybind11 暴露 C++ kernel 给 Python | 跑通编译 + import |

---

## 算法（不变 · 每天 30min）

> 代码随想录 → Hot 100 → 面试经典 150 → 灵神题单。每道 Python + C++ 双版本。

| 章节 | 进度 |
|------|------|
| 01-array 核心 5 题 | ✅ |
| 01-array 拓展 | ⏸️ |
| 02-linked-list 核心 7 题 | 🟡 已到 206，下一个 24 |
| 03-hash-table → 12-graph | ⬜ |

---

## 初级工程师课程（每天 35min）

> M001-M003（Python/Linux/Git）⏭️。M004 开始正课。

| 模块 | 进度 |
|------|------|
| M004 ML 基础 + GPU Fundamentals | 🟡 |
| M005 Docker | ⬜ |
| M006 K8s | ⬜ |
| M007 APIs | ⬜ |
| M008 数据库 ⏭️ M009 监控 | ⬜ |
| M010 云平台 | ⬜ |

---

## llm.c（每天 35min）

| 周 | 状态 |
|------|:--:|
| Week 1 训练跑通 | ✅ |
| Week 2 model.py 精读 | ✅ |
| Week 3 自测 | 🟡 待做 |
| Week 4 llm.c 主循环 | ⬜ |

---

## 每日时间

| 块 | 内容 | 时间 |
|----|------|:--:|
| 1 | CUDA/GPU | 45min |
| 2 | C++ | 25min |
| 3 | Python | 25min |
| 4 | D2L 李沐 | 25min |
| 5 | 算法 | 30min |
| 6 | 初级课程 | 35min |
| 7 | llm.c | 35min |

---

## 核心资源速查

| 资源 | 用途 |
|------|------|
| [NVIDIA DLI CUDA C/C++](https://learn.nvidia.com/) | CUDA 官方课程 |
| [GPU Puzzles](https://github.com/srush/gpu-puzzles) | CUDA 交互练习 |
| [现代 C++ 教程](https://github.com/changkun/modern-cpp-tutorial) | C++11-20 系统学习 |
| [zimei11/ai-infra-notes](https://github.com/zimei11/ai-infra-notes) | AI Infra 全景图 |
| [Triton 官方教程](https://triton-lang.org/) | GPU kernel Python 原型 |
| [pybind11 文档](https://pybind11.readthedocs.io/) | Python ↔ C++ |
| [飞书 CUDA 课程](https://tvle9mq8jh.feishu.cn/docx/BnqMdyaJ9oyXb1xwktgc7esMn4c) | CUDA 中文教材 |
| [D2L 李沐](https://b23.tv/IjnkTRm) | 深度学习基石 |
| [CUDA-Learn-Notes](https://github.com/DefTruth/CUDA-Learn-Notes) | kernel 参考 |
| [AIInfraGuide](https://caomaolufei.github.io/AIInfraGuide/) | 面试宝典 |

---

*开始：2026-06-09 | 每天推进。*
