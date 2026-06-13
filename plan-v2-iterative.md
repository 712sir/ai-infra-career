# 迭代执行计划

> 日期：2026-06-12 | 状态：🟡 进行中

---

## 目标拆解

| 层级 | 时间 | 目标 |
|------|------|------|
| 3 年 | 毕业 | AI Infra 工程师（推理引擎 / 训练框架） |
| 1 年 | 研一 | 初级工程师阶段完成 + 第一段实习 |
| 本月 | 6/12-7/6 | CUDA 线程模型 + 链表核心题收尾 + 初级 M004-M005 |

---

## 线路优先级

| 优先级 | 线路 | 每天 | 核心资源 |
|:--:|------|:--:|------|
| 🥇 | 初级课程 | 90min | 初级工程师课程 M004 起 + 项目穿插 |
| 🥇 | CUDA/GPU | 45min | NVIDIA DLI + 工程师 mod-107 + PMPP |
| 🥈 | 算法 | 30min | 代码随想录 |

---

## 第 1 迭代（6/12 – 7/6）

**本月目标**：初级 M004 ML 基础 + M005 Docker 起步 + CUDA Grid/Block/Thread/vecAdd 能白板写 + 链表核心 7 题收尾

| 周 | CUDA | 初级课程 | 算法 |
|------|------|------|------|
| 6/12-6/15 | 线程模型 + vecAdd | M004 PyTorch 基础 + exercise-01/02 | 24 19 |
| 6/16-6/22 | Shared Memory + Bank Conflict | M004 LLM 基础 + GPU Fundamentals | 160 142 |
| 6/23-6/29 | MatMul naive | M005 Docker 容器操作 | 哈希核心题 |
| 6/30-7/6 | 缓冲周 + 查漏补缺 | M005 Docker Compose + 镜像构建 | 哈希收尾 |

---

## 第 2 迭代（7/7 – 8/3）

**目标**：初级 M005 完成 + M006 K8s + P1 项目启动 + CUDA GEMM naive

| 周 | CUDA | 初级课程 | 算法 |
|------|------|------|------|
| 7/7-7/13 | GEMM naive → shared memory | M006 K8s 架构 + 部署 | 栈核心题 |
| 7/14-7/20 | GEMM optimization | M006 Helm + P1 项目启动 | 队列核心题 |
| 7/21-7/27 | CUDA 复习 + 小测 | P1 Model API 开发 | 二叉树核心题 |
| 7/28-8/3 | Profiling 入门 | P1 Docker 容器化 + 云部署 | 二叉树收尾 |

---

## 反馈节奏

| 频率 | 内容 |
|------|------|
| 每天 5min | 做了什么？卡了什么？明天？ |
| 每周日 30min | 复盘 + 排下周 + 2 道 AIInfraGuide 面试题 |
| 每月末 1h | 对标准则 + 排下月 |

---

## 资源速查

| 资源 | 用在哪 |
|------|------|
| [NVIDIA DLI CUDA C/C++](https://learn.nvidia.com/) | CUDA 官方入门 |
| [GPU Puzzles](https://github.com/srush/gpu-puzzles) | CUDA 交互练习 |
| [CUDA-Learn-Notes](https://github.com/DefTruth/CUDA-Learn-Notes) | kernel 对照 |
| [初级工程师课程](D:/study/ai-infra-junior-engineer-learning/) | 主线课程 |
| [AIInfraGuide](https://caomaolufei.github.io/AIInfraGuide/) | 每周面试题 |
