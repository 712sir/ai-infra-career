# AI Infra 工程师求职路线图

> 目标：AI Infra 工程师 | 路径：初级工程师 → 工程师 | 出师标准：工程师阶段全部完成
>
> 状态：🟡 初级工程师阶段

---

## 仓库结构

```
ai-infra-career/
├── README.md              ← 本文件
├── plan.md                ← 学习计划（初级→工程师）
├── plan-v2-iterative.md   ← 迭代执行计划
├── algorithm/             ← 手撕算法
│   ├── cpp/ / python/     ← 双版本题解
│   └── notes/             ← 算法专题笔记
├── fundamentals/          ← 核心技术栈
│   ├── cuda/ / cpp/ / python/
│   ├── gpu-arch/ / distributed/
│   └── handson-exercises.md
├── projects.md            ← 项目索引
├── references.md          ← 资源索引
├── resources/             ← 学习资料
└── interview/             ← 求职备战：八股/简历/面经
```

---

## 学习路径

> 主线跟随初级工程师 → 工程师课程。CUDA/GPU、算法、C++/Python、D2L 作为每日并行线。

### 阶段一：初级工程师（440h）

| 模块 | 主题 | 预估 | 策略 |
|------|------|:--:|------|
| 001-003 | Python / Linux / Git | 40h | CS 科班 ⏭️ |
| 004 | ML 基础（PyTorch + GPU + LLM） | 20h | 🟡 重点 |
| 005 | Docker 容器 | 15h | 必学 |
| 006 | Kubernetes 入门 | 20h | 必学，Infra 核心 |
| 007 | API 与 Web 服务（Flask/FastAPI） | 15h | 必学 |
| 008 | 数据库与 SQL | 15h | 快速复习 ⏭️ |
| 009 | 监控与日志（Prometheus/Grafana） | 15h | 必学 |
| 010 | 云平台（AWS/GCP + Terraform） | 20h | 必学 |
| P1-P5 | 5 个项目：Model API → K8s Serving → ML Pipeline → 监控 → Capstone | 290h | 穿插进行 |

### 阶段二：工程师（500+h）

> 初级完成后启动。GPU Computing / MLOps / LLM 基础设施 / 分布式训练推理。

### 并行线：CUDA/GPU（每天）

| 阶段 | 内容 | 状态 |
|------|------|:--:|
| Grid/Block/Thread + vecAdd | PMPP Ch1-2 + 飞书 CUDA 课程 | 🟡 |
| Shared Memory + Bank Conflict | 飞书 CUDA 课程 Ch3 | ⬜ |
| Reduction kernel（7 版优化） | how-to-optim-algorithm-in-cuda | ⬜ |
| GEMM naive → shared memory → Tensor Core | CUDA-Learn-Notes | ⬜ |
| FlashAttention | FlashAttention-PyTorch-Triton | ⬜ |

### 并行线：算法（不变）

代码随想录 → Hot 100 → 面试经典 150 → 灵神题单

每道题 Python + C++ 双版本。先核心题，再拓展题。

---

## 板块2：核心技术栈

### CUDA 内核编程

| 阶段 | 内容 | 资源 |
|------|------|------|
| 入门 | Grid/Block/Thread/Warp 模型 | [飞书 CUDA 课程](https://tvle9mq8jh.feishu.cn/docx/BnqMdyaJ9oyXb1xwktgc7esMn4c) + PMPP |
| 内存 | Global/Shared/Register + Bank Conflict | 飞书课程 + PMPP Ch3-5 |
| 进阶 | Warp Shuffle、Cooperative Groups | CUDA Programming Guide |
| 实战 | Tensor Core GEMM + FlashAttention | CUDA-Learn-Notes |

### C++ 强化

| 主题 | 内容 |
|------|------|
| C++11/14/17 | move 语义、lambda、template、constexpr |
| 多线程 | thread、mutex、atomic、condition_variable |
| 内存管理 | unique_ptr、shared_ptr、weak_ptr、memory pool |
| 编译工具 | CMake、GDB |
| pybind11 | Python 与 C++ 绑定 |

### Python 深入

| 主题 | 内容 |
|------|------|
| 装饰器 / 生成器 / 协程 | Fluent Python |
| GIL / 多进程 / asyncio | Python 性能与并发 |
| PyTorch autograd 源码 | 计算图、反向传播 |
| Triton DSL | GPU kernel 原型 |

### 推理优化技术

| 技术 | 说明 |
|------|------|
| Continuous Batching | 动态合并请求 |
| PagedAttention | KV Cache 按 Page 管理 |
| FlashAttention-2/3 | 高效 Attention |
| INT8/INT4 量化 | AWQ、GPTQ、TensorRT |
| Speculative Decoding | 小模型猜 + 大模型验证 |

### 分布式训练技术

| 主题 | 内容 |
|------|------|
| NCCL 原语 | AllReduce、AllGather、ReduceScatter |
| 并行策略 | DP、TP、PP、ZeRO-1/2/3 |
| 混合精度 | AMP（FP16/BF16 + loss scaling） |

---

## 板块3：项目经历

> 已有项目 + 规划项目见 [projects.md](projects.md)

| 项目 | 状态 |
|------|:--:|
| llm.c-learning | 🟡 |
| nanoGPT | ✅ |
| MiniInfer（规划） | ⬜ |
| MiniQuant（规划） | ⬜ |
| CUDA Kernel 合集（规划） | ⬜ |
| vLLM 源码笔记（规划） | ⬜ |

---

## 板块4：求职备战

### 八股文

| 文件 | 内容 |
|------|------|
| `cuda.md` | GPU 架构、内存层次、Bank Conflict、Tensor Core |
| `cpp.md` | 智能指针、多线程、STL 原理 |
| `python.md` | GIL、装饰器、生成器、asyncio |
| `inference.md` | PagedAttention、Continuous Batching、量化 |
| `training.md` | NCCL、ZeRO、TP/PP、混合精度 |
| `pytorch.md` | autograd、DDP、DataLoader |

### 厂谱

`interview/companies/` 下按大厂/独角兽/芯片厂分类，含团队、方向、面经。

---

## 时间线总览

```
Month 1-2  │ 初级 M004-M006 + CUDA Grid/Block/Thread + 算法链表/哈希
Month 3-4  │ 初级 P1-P2 + CUDA Reduction/GEMM + 算法栈/队列/二叉树
Month 5-8  │ 初级 P3-P5 + 工程师阶段 + CUDA FlashAttention/Tensor Core
Month 9-12 │ 工程师阶段深入 + 实习投递 + MiniInfer/MiniQuant
```

---

## 每日时间分配

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

## 补充资源

| 资源 | 用途 |
|------|------|
| [飞书 CUDA 编程基础](https://tvle9mq8jh.feishu.cn/docx/BnqMdyaJ9oyXb1xwktgc7esMn4c) | CUDA 主教材 |
| [D2L 李沐 B站](https://b23.tv/IjnkTRm) | 每天 1 集 |
| [CUDA-Learn-Notes](https://github.com/DefTruth/CUDA-Learn-Notes) | kernel 参考 |
| [AIInfraGuide](https://caomaolufei.github.io/AIInfraGuide/) | 面试宝典 |
| [KuiperInfer](https://github.com/zjhellofss/KuiperInfer) | 推理引擎参考 |
| [yalm](https://github.com/andrewkchan/yalm) | C++/CUDA 推理引擎 |
| [ZOMI AI-Infra](https://github.com/Aaaqiu1/AI-Infra) | 分布式/推理 |
| [vLLM 飞书课程](https://l0kzvikuq0w.feishu.cn/drive/folder/FEHnfpzWel2BVgdERTvcQ8oLnWh) | 推理部署 |
| [how-to-optim-algorithm-in-cuda](https://github.com/BBuf/how-to-optim-algorithm-in-cuda) | Reduce/Attention 优化 |
| [FlashAttention-PyTorch-Triton](https://github.com/nguyenhuykhang/FlashAttention-PyTorch-Triton) | FA 实战 |
| [Nano-vLLM](https://github.com) | vLLM 前置 |
| [tiny-vllm](https://github.com/jmaczan/tiny-vllm) | PagedAttention |
| [AIInfraGuide 面经](https://caomaolufei.github.io/AIInfraGuide/interview) | 面试题 |
