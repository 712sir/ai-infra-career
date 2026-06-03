# NVIDIA

> 🥇 第一优先级 | AI Infra 方向最顶级的雇主

## 面试特点
- **CUDA 深度要求最高**：面试官本身就是 CUDA 专家，会对 kernel 细节追问到底
- **GPU 架构理解**：SM 微架构、Tensor Core、内存层次的深入理解
- **全英文环境**：文档/代码 review/日常沟通以英文为主，英语口语是硬门槛
- **算法难度高**：LeetCode Hard 题常见，注重代码质量和优化意识

## 核心团队

| 团队 | 方向 | 地点 |
|------|------|------|
| **TensorRT-LLM** | 大模型推理引擎、Graph Optimization、Kernel Auto-Tuning | 上海/北京 |
| **CUDA Toolkit** | CUDA 编译器、cuBLAS/cuDNN/cuSPARSE 等库 | 上海 |
| **DevTech** | 与客户合作优化 AI 模型的 GPU 性能 | 北京/上海 |
| **NVIDIA Research** | 前沿 GPU 算法研究（FlashAttention 作者所在团队） | 远程/美国 |

## 高频考点
- CUDA kernel 优化全链（naive → shared memory → tensor core → 异步拷贝）
- GPU 架构（SM、Warp Scheduler、Register File、L1/L2 Cache）
- Roofline Model 分析 kernel 瓶颈
- C++ 模板元编程、PTX/SASS 基础
- 系统设计（如何设计一个推理引擎）
- LeetCode Hard（DP/图论/设计题）

## 面试流程
1. 简历筛选（非常看重 CUDA/C++ 项目经验）
2. 电话面试（1 轮，算法 + CUDA 基础）
3. On-site（4-5 轮）：
   - 算法手撕（2 轮）
   - CUDA/C++ 深度（1-2 轮）
   - 系统设计（1 轮）
   - Manager 面（1 轮）

## 准备重点
- GEMM 优化链必须能手写（naive → shared memory tiled → Tensor Core）
- FlashAttention forward/backward 完整推导和实现
- 至少一个完整项目的端到端性能优化经验
- 能用 `ncu`/`nsys` 做 profiling 并解读结果

## 真题收集
> 待补充

## 相关资源
- [NVIDIA CUDA Programming Guide](https://docs.nvidia.com/cuda/cuda-c-programming-guide/)
- [NVIDIA TensorRT-LLM](https://github.com/NVIDIA/TensorRT-LLM)
- [NVIDIA CUTLASS](https://github.com/NVIDIA/cutlass)
- [NVIDIA DevBlog](https://developer.nvidia.com/blog/)
