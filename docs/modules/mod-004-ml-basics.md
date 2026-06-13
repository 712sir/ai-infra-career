# 模块 004 — 机器学习基础

> **时长**: 20 小时 | **难度**: 入门 | **前置知识**: Python 编程基础（模块 001 推荐）

---

## 模块概述

作为 AI 基础设施工程师，理解机器学习模型的生命周期是核心能力之一。本模块从 ML 的基本概念出发，覆盖两大主流框架 PyTorch 和 TensorFlow/Keras 的使用，并重点讲解如何为生产部署准备和优化模型。你不必成为数据科学家，但需要能够操作、转换和部署训练好的模型。

---

## 主题分解

### 1. 机器学习概述（4小时）

- **监督学习与无监督学习**: 分类、回归、聚类、降维的基本概念与典型算法简介，何时使用哪种学习类型
- **训练 / 验证 / 测试集**: 数据划分的策略与目的，交叉验证（k-fold cross-validation），数据泄露（data leakage）的识别与防范
- **ML 工作流**: 数据收集 -> 数据预处理 -> 特征工程 -> 模型训练 -> 模型评估 -> 模型部署的完整链条，各阶段的输入输出与关键决策点
- **模型评估指标**: 分类指标（准确率、精确率、召回率、F1-score、ROC-AUC），回归指标（MSE、RMSE、MAE、R-squared），如何根据业务需求选择合适的评估指标

### 2. PyTorch 基础（6小时）

- **张量与操作**: Tensor 的创建（torch.tensor、torch.zeros、torch.randn）、属性（shape / dtype / device），张量运算（矩阵乘法、广播机制），GPU 加速（.to('cuda') / .cuda()）
- **神经网络构建**: torch.nn.Module 的子类化，常用层（Linear / Conv2d / ReLU / Dropout / BatchNorm），参数初始化策略，模型的参数统计与可视化
- **训练循环**: 前向传播、损失函数（CrossEntropyLoss / MSELoss / BCELoss），优化器（SGD / Adam / AdamW），反向传播与梯度更新，训练/验证循环的模板化编写
- **模型保存与加载**: state_dict 的状态保存与恢复，torch.save / torch.load 的使用，检查点（checkpoint）的保存策略，跨设备加载模型

### 3. TensorFlow/Keras 基础（6小时）

- **TF 核心概念**: TensorFlow 的计算图模型（静态图 vs 动态图），tf.Tensor 与 tf.Variable，Eager Execution 模式，tf.function 的图优化加速
- **Keras API**: Sequential API 与 Functional API 的对比与使用，Model Subclassing 方式，自定义层、损失函数与评估指标
- **模型训练与评估**: model.compile() 的配置（优化器、损失、指标），model.fit() 的训练流程，回调函数（EarlyStopping、ModelCheckpoint、TensorBoard）
- **模型序列化**: SavedModel 格式与 HDF5 格式的差异，model.save() 与 tf.saved_model.save()，模型加载与推理（model.predict()）

### 4. 模型部署准备（4小时）

- **模型格式转换**: ONNX（Open Neural Network Exchange）开放格式的导出与验证（torch.onnx.export / tf2onnx），TorchScript（torch.jit.script / torch.jit.trace）的追踪与脚本化，TF SavedModel 的生产级导出
- **模型优化基础**: 量化（quantization）——动态量化与静态量化的原理与精度影响，剪枝（pruning）——结构化与非结构化剪枝，知识蒸馏（knowledge distillation）的概念及其作用
- **I/O 处理**: 模型推理中的输入预处理（归一化、resize、tokenization），输出后处理（softmax、阈值过滤、NMS），批处理（batching）与吞吐优化
- **版本管理**: 模型版本号策略（语义化版本），MLflow / DVC 的模型实验追踪，模型注册中心（Model Registry）的概念

---

## 学习目标

完成本模块后，你应当能够：

1. 理解机器学习模型从训练到部署的完整生命周期
2. 使用 PyTorch 和 TensorFlow/Keras 加载、操作和微调模型
3. 将训练好的模型转换为 ONNX、TorchScript、SavedModel 等生产级格式
4. 为模型部署准备输入预处理和输出后处理管道
5. 对模型进行基础的优化（量化、剪枝）
6. 管理模型版本并追踪实验

---

## 文件清单

| 文件名 | 类型 | 说明 |
|--------|------|------|
| `README.md` | 文档 | 模块总览、学习路线图与使用指南 |
| `lecture-notes/01-ml-overview.md` | 讲义 | 机器学习概述（监督/无监督、数据集划分、评估指标） |
| `lecture-notes/02-pytorch-basics.md` | 讲义 | PyTorch 基础（张量、神经网络、训练循环） |
| `lecture-notes/03-tensorflow-keras-basics.md` | 讲义 | TensorFlow/Keras 基础（核心概念、Keras API、序列化） |
| `lecture-notes/04-model-deployment-preparation.md` | 讲义 | 模型部署准备（ONNX/TorchScript/SavedModel、优化、版本管理） |
| `exercises/01-ml-fundamentals.md` | 练习 | ML 基础概念练习 |
| `exercises/02-pytorch-tensors.md` | 练习 | PyTorch 张量操作练习 |
| `exercises/03-pytorch-training.md` | 练习 | PyTorch 模型训练练习 |
| `exercises/04-tensorflow-keras.md` | 练习 | TensorFlow/Keras 模型构建与训练练习 |
| `exercises/05-model-export-optimization.md` | 练习 | 模型格式转换与优化练习 |
| `quizzes/quiz-01-ml-basics.md` | 测验 | 模块 004 知识检测测验 |
| `resources.md` | 资源 | 推荐阅读、教程链接与延伸学习资料 |

---

## 关联模块

- **前序**: [模块 001 — Python 基础设施编程基础](./mod-001-python-fundamentals.md)
- **后续**: [模块 005 — Docker 容器化技术](./mod-005-docker-containers.md)、[模块 007 — API 与 Web 服务开发](./mod-007-apis-web-services.md)
