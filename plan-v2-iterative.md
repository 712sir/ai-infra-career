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

| 优先级 | 线路 | 每天 |
|:--:|------|:--:|
| 🥇 | B1 CUDA | 45min |
| 🥇 | B2 C++ | 25min |
| 🥇 | B2 Python | 25min |
| 🥇 | D2L 李沐 | 25min |
| 🥈 | A 算法 | 30min |
| 🥉 | C llm.c | 35min |
| ⏸️ | D cs224n | 0 |
| ⏸️ | E vLLM | 0 |

---

## 反馈节奏

| 频率 | 内容 | 时长 |
|------|------|:--:|
| 每天 | 做了什么？卡了什么？明天做什么？ | 5min |
| 每周日 | 回顾本周 + 排下周 + 2 道面试题 | 30min |
| 每月末 | 对标准则 + 排下月 | 1h |

---

## 第 1 迭代（6/9 – 7/6，4 周）

**本月目标**：能白板写出 GEMM naive kernel，理解 GPU 线程/内存模型

### Week 1（6/9 – 6/15）

| 天 | 行动 | 验收 |
|----|------|------|
| 1-2 | CUDA 环境安装 + vecAdd | ✅ 已完成 |
| 3-4 | Grid/Block/Thread 模型 + 飞书 CUDA 课程 Ch2 | 🟡 |
| 5-6 | A 算法：链表核心题（203→707→206→24） | 🟡 已到 206 |
| 7 | 复盘 + 面试题 2 道 | ⬜ |
| 每日 | C++ 手撕 + Python 手撕 + D2L 继续 | 🟡 D2L 第 1 集 ✅ |

### Week 2（6/16 – 6/22）

| 天 | 行动 | 验收 |
|----|------|------|
| 1-3 | Shared Memory + Bank Conflict | 能解释 + padding 解法 |
| 4-5 | MatMul naive kernel（临摹→白板） | 闭卷写出 |
| 6 | A 算法：链表核心题收尾（19, 160, 142） | |
| 7 | 复盘 + 面试题 2 道 | |
| 每日 | C++（move 语义+模板）+ Python（生成器+协程）+ D2L 1 集 | |

### Week 3（6/23 – 6/29）

| 天 | 行动 | 验收 |
|----|------|------|
| 1-3 | Reduction kernel（7 版优化链） | shared memory reduction |
| 4-5 | C++ 智能指针 | 手写简化版 |
| 6 | A 算法：哈希表核心题 | |
| 7 | 复盘 + 面试题 2 道 | |
| 每日 | C++ + Python + D2L 1 集 | |

### Week 4（6/30 – 7/6）：缓冲 + 决策

- 前 3 周 CUDA 学进去了吗？能白板写 kernel 吗？
- A 算法刷了 9 道吗？面试题看了 6 道吗？
- 对比 [ai-infra-performance-learning](https://github.com/ai-infra-curriculum/ai-infra-performance-learning) Module 2（CUDA），检查自己覆盖了哪些、漏了哪些
- 基于实际进度排下个 4 周

---

## 第 2 迭代预告（7/7 开始，根据第 1 迭代结果调整）

| 状态 | 下个迭代方向 |
|------|------|
| 能白板写 GEMM naive + Reduction | GEMM 优化链：tiling → double buffering → Tensor Core → MMA PTX |
| CUDA 吃力 | 降速，重看飞书课程，临摹模式 |
| 算法稳定推进 | 保持 1 题/天 |
| 连续 2 周几乎没动 | 回重置面板重新回答 12 问 |

---

## 第 3-4 迭代预告

| 迭代 | 主题 | 核心产出 |
|------|------|------|
| 3 | FlashAttention | FA forward kernel |
| 4 | CUTLASS 基础 | CUTLASS GEMM |
| 5 | vLLM 源码 + MiniInfer v0 | CPU 推理 |
| 6 | MiniInfer v1 | GPU + KV Cache |
| 7 | MiniInfer v2 | PagedAttention + Continuous Batching |

> 迭代结束后根据实际进度重新排。

---

## 资源速查

| 资源 | 用在哪 |
|------|------|
| [AIInfraGuide](https://caomaolufei.github.io/AIInfraGuide/) | 每周面试题 |
| [ai-infra-performance-learning](https://github.com/ai-infra-curriculum/ai-infra-performance-learning) | 迭代末对标准则 |
| [ZOMI AI-Infra](https://github.com/Aaaqiu1/AI-Infra) | 分布式/推理 |
| [how-to-optim-algorithm-in-cuda](https://github.com/BBuf/how-to-optim-algorithm-in-cuda) | W3 Reduction |
| [CUDA-Learn-Notes](https://github.com/DefTruth/CUDA-Learn-Notes) | W2-3 GEMM/Reduction |
| [cuda_hgemm](https://github.com/Bruce-Lee-LY/cuda_hgemm) | 第2迭代 GEMM 进阶 |
| [FlashAttention-PyTorch-Triton](https://github.com/nguyenhuykhang/FlashAttention-PyTorch-Triton) | 第3迭代 FA |
| [cutlass-learning](https://github.com/shizhengLi/cutlass-learning) | 第4迭代 CUTLASS |
| [KuiperInfer](https://github.com/zjhellofss/KuiperInfer) | MiniInfer 主参考 |
| [yalm](https://github.com/andrewkchan/yalm) | MiniInfer 第二参考 |
| [Nano-vLLM](https://github.com) | vLLM 前置 |
| [tiny-vllm](https://github.com/jmaczan/tiny-vllm) | PagedAttention |
| [llama.cpp-tutorials](https://github.com/bobozi-org/llama.cpp-tutorials) | CUDA 推理参考 |
| [zimei11/ai-infra-notes](https://github.com/zimei11/ai-infra-notes) | 架构图+博客 |

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
