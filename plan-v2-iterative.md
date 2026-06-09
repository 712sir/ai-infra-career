# 迭代执行计划

> 日期：2026-06-09 | 状态：🟡 进行中

---

## 目标拆解

| 层级 | 时间 | 目标 |
|------|------|------|
| 3年 | 毕业 | AI Infra 工程师（推理引擎 / 训练框架），年薪百万 |
| 1年 | 研一 | vLLM Contributor + MiniInfer 开源 + 第一段实习 offer |
| 本月 | 6/9-7/6 | CUDA kernel 入门：能白板写出 GEMM naive + 理解 GPU 线程模型 |

---

## 线路优先级

| 优先级 | 线路 | 每天 | 说明 |
|:--:|------|:--:|------|
| 🥇 | B 技栈（CUDA/C++） | 1-2h | AI Infra 面试考 kernel，这是硬通货 |
| 🥈 | A 算法 | 30min-1h | 面试敲门砖，每天 2 题 |
| 🥉 | C llm.c | 随 B 线 | 学 CUDA 时对照 llm.c 的 kernel 实现 |
| ⏸️ | D cs224n | 0 | 理论课，等 CUDA 入门后再开 |
| ⏸️ | E vLLM | 0 | 需要先看懂 CUDA 源码，W8 再启动 |

---

## 反馈节奏

| 频率 | 内容 | 时长 |
|------|------|:--:|
| 每天 | 今天做了什么？什么卡住了？明天做什么？ | 5min |
| 每周日 | 回顾本周 + 排下周 + 看 2 道 AIInfraGuide 面试题 | 30min |
| 每月末 | 对标准则 + 排下月 | 1h |

**每周日额外必做**：打开 [AIInfraGuide 面试宝典](https://caomaolufei.github.io/AIInfraGuide/interview)，看 2 道面经。不用全会，目的是知道"面试到底考什么"，反向校准学习重点。优先看 T3 芯片厂（英伟达/寒武纪/壁仞）和 T0 大厂（字节/阿里）。

---

## 第 1 迭代（6/9 – 7/6，4 周）

**本月目标**：能白板写出 GEMM naive kernel，理解 GPU 线程/内存模型

### Week 1（6/9 – 6/15）

| 天 | 行动 | 验收 | 参考资料 |
|----|------|------|------|
| 1-2 | CUDA Toolkit 安装 + 验证 nvcc + 跑通 vecAdd | `nvcc --version` + vecAdd PASS | [AIInfraGuide CUDA 环境搭建](https://caomaolufei.github.io/AIInfraGuide/cuda) |
| 3-4 | Grid/Block/Thread 模型 + 飞书 CUDA 课程 Ch1-2 | 能讲清楚 GPU 线程层次 | [ZOMI 课程](https://github.com/Aaaqiu1/AI-Infra) 概览了解全貌 |
| 5-6 | A 算法：数组拓展题 3 道（35, 34, 26） | C++ + Python 双版本 | |
| 7 | 复盘 + AIInfraGuide 面试题 2 道 | | |

### Week 2（6/16 – 6/22）

| 天 | 行动 | 验收 | 参考资料 |
|----|------|------|------|
| 1-3 | Shared Memory + Bank Conflict | 能解释 bank conflict 和 padding 解法 | 飞书 CUDA 课程 Ch3 |
| 4-5 | 手写 MatMul naive kernel（先临摹，再白板） | 闭卷写出 naive MatMul | 临摹用 [CUDA-Learn-Notes](https://github.com/DefTruth/CUDA-Learn-Notes) 的 GEMM 基础版 |
| 6 | A 算法：数组拓展题 3 道（283, 844, 69） | 双版本 | |
| 7 | 复盘 + 面试题 2 道 | | |

### Week 3（6/23 – 6/29）

| 天 | 行动 | 验收 | 参考资料 |
|----|------|------|------|
| 1-3 | Reduction kernel（7 版优化链） | 能写出 shared memory reduction | [how-to-optim-algorithm-in-cuda](https://github.com/BBuf/how-to-optim-algorithm-in-cuda) Reduce 章节 |
| 4-5 | C++ 智能指针（unique/shared/weak） | 能手写简化版 | |
| 6 | A 算法：滑动窗口 3 道（904, 76, 54） | 双版本 | |
| 7 | 复盘 + 面试题 2 道 | | |

### Week 4（6/30 – 7/6）：缓冲 + 决策

- 前 3 周 CUDA 学进去了吗？能白板写 kernel 吗？
- A 算法刷了 9 道吗？面试题看了 6 道吗？
- 对比 [ai-infra-performance-learning](https://github.com/ai-infra-curriculum/ai-infra-performance-learning) Module 2（CUDA），检查自己覆盖了哪些、漏了哪些
- 基于实际进度排下个 4 周

---

## 第 2 迭代预告（7/7 开始，根据第 1 迭代结果调整）

| 状态 | 下个迭代方向 | 参考资料 |
|------|------|------|
| 能白板写 GEMM naive + Reduction | GEMM 优化链：shared memory tiling → double buffering → Tensor Core WMMA → MMA PTX | [CUDA-Learn-Notes](https://github.com/DefTruth/CUDA-Learn-Notes) GEMM 全链 + [cuda_hgemm](https://github.com/Bruce-Lee-LY/cuda_hgemm) |
| CUDA 吃力 | 降速，重看飞书 CUDA 课程，只用临摹模式 | |
| 算法稳定推进 | 保持 2 题/天的频率 | |
| 连续 2 周几乎没动 | 回到重置面板重新回答 12 问 | |

---

## 第 3-4 迭代预告（CUDA 进阶 → 推理引擎）

| 迭代 | 主题 | 核心产出 | 参考资料 |
|------|------|------|------|
| 3 | FlashAttention | 白板写出 FA forward kernel | [FlashAttention-PyTorch-Triton](https://github.com/nguyenhuykhang/FlashAttention-PyTorch-Triton) 9 阶段教程 |
| 4 | CUTLASS 基础 | 会用 CUTLASS 写 GEMM | [cutlass-learning](https://github.com/shizhengLi/cutlass-learning) 中文解析 |
| 5 | vLLM 源码 + MiniInfer v0 | CPU 推理 + 源码笔记 | [Nano-vLLM](https://github.com)（前置理解）→ [KuiperInfer](https://github.com/zjhellofss/KuiperInfer)（主参考）→ [yalm](https://github.com/andrewkchan/yalm)（第二参考） |
| 6 | MiniInfer v1 | GPU 推理 + KV Cache | [tiny-vllm](https://github.com/jmaczan/tiny-vllm)（PagedAttention 参考） |
| 7 | MiniInfer v2 | PagedAttention + Continuous Batching | vLLM 源码 + [ZOMI 05 推理](https://github.com/Aaaqiu1/AI-Infra) |

> ⚠️ 第 3 迭代往后的内容只是方向标，不提前排具体周计划。每个迭代结束后，根据实际进度重新排。

---

## 资源速查（融入计划的那些）

| 资源 | 用在哪 |
|------|------|
| [AIInfraGuide](https://caomaolufei.github.io/AIInfraGuide/) | 每周 2 道面试题 + CUDA 模块当辅助教材 |
| [ai-infra-performance-learning](https://github.com/ai-infra-curriculum/ai-infra-performance-learning) | 每迭代结束时对比，检查覆盖度 |
| [ZOMI AI-Infra](https://github.com/Aaaqiu1/AI-Infra) | 学分布式训练/推理时看对应 PPT+视频 |
| [how-to-optim-algorithm-in-cuda](https://github.com/BBuf/how-to-optim-algorithm-in-cuda) | Week 3 Reduction 优化链 |
| [CUDA-Learn-Notes](https://github.com/DefTruth/CUDA-Learn-Notes) | Week 2-3 GEMM/Reduction 对照 |
| [cuda_hgemm](https://github.com/Bruce-Lee-LY/cuda_hgemm) | 第 2 迭代 GEMM 进阶 |
| [FlashAttention-PyTorch-Triton](https://github.com/nguyenhuykhang/FlashAttention-PyTorch-Triton) | 第 3 迭代 FlashAttention |
| [cutlass-learning](https://github.com/shizhengLi/cutlass-learning) | 第 4 迭代 CUTLASS |
| [KuiperInfer](https://github.com/zjhellofss/KuiperInfer) | 第 5 迭代 MiniInfer 主参考（报课内容） |
| [yalm](https://github.com/andrewkchan/yalm) | 第 5 迭代 MiniInfer 第二参考 |
| [Nano-vLLM](https://github.com) | 第 5 迭代 vLLM 前置理解 |
| [tiny-vllm](https://github.com/jmaczan/tiny-vllm) | 第 6 迭代 PagedAttention |
| [llama.cpp-tutorials](https://github.com/bobozi-org/llama.cpp-tutorials) | CUDA 推理的工业参考，随时可看 |
| [zimei11/ai-infra-notes](https://github.com/zimei11/ai-infra-notes) | 架构图 + 博客推荐，需要宏观理解时查阅 |

---

## 每周复盘模板

```markdown
## Week X 复盘

### 完成了什么
- B1:
- A:
- 面试题:  道

### 什么卡住了
-

### 下周最重要的 3 件事
1.
2.
3.
```

---

## 每日最小行动

即使当天只有 30 分钟：

| 行动 | 时长 |
|------|:--:|
| 写 1 个 CUDA kernel 或刷 1 道算法题 | 25min |
| 记一句当日反馈 | 5min |
