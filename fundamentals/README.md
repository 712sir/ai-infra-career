# 板块2：核心技术栈

## 子目录

| 目录 | 内容 | 优先级 |
|------|------|--------|
| `cuda/` | CUDA kernel 代码 + 笔记 | 🔴 最高 |
| `cpp/` | C++ 专题复习笔记 | 🔴 最高 |
| `python/` | Python 深入（PyTorch 源码 / Triton / pybind11） | 🔴 最高 |
| `gpu-arch/` | GPU 架构知识 | 🟡 高 |
| `distributed/` | 分布式训练/推理笔记 | 🟡 高 |

## 学习顺序

```
cuda/ ──→ gpu-arch/ ──→ cpp/ ──→ distributed/
  │         │              │
  │         └── python/ ───┘ (与其他并行)
  └── 三条线同步推进 ──────┘
```

## Python 学习重点

| 主题 | 产出 |
|------|------|
| PyTorch autograd 源码 | `python/pytorch-autograd.md` |
| Triton DSL kernel 实践 | `python/triton-kernels/` |
| pybind11 C++ 扩展 | `python/pybind11-demo/` |
| Python 性能与 GIL | `python/python-perf.md` |
