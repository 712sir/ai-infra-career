# 练习 03：创建可复用的 ML 实用函数和模块（Creating Reusable ML Utility Functions and Modules）

## 概述（Overview）

本练习教您如何设计、实现和组织用于机器学习基础设施的可复用 Python 函数和模块。您将学习创建实用工具库、实现正确的函数签名、使用类型提示、处理默认参数，以及将代码结构化为可维护的模块。

## 学习目标（Learning Objectives）

完成本练习后，您将能够：
- 使用正确的签名和文档编写干净、可复用的函数
- 使用类型提示（Type Hints）提高代码质量和 IDE 支持
- 有效地实现默认参数和关键字参数
- 为 ML 实用工具创建模块和包
- 使用 *args 和 **kwargs 实现灵活的函数接口
- 为常见的 ML 模式（计时、日志记录、缓存）实现装饰器（Decorator）
- 应用函数式编程（Functional Programming）概念（map、filter、lambda）
- 构建全面的 ML 实用工具库

## 先决条件（Prerequisites）

- 已完成练习 01：环境设置
- 已完成练习 02：数据结构
- 已完成第 1 课和第 2 课
- 理解 ML 工作流和常见操作

## 所需时间

- 预计：100-120 分钟
- 难度：中级

## 第 1 部分：函数基础与最佳实践

### 步骤 1：使用类型提示编写清晰的函数

```python
# 创建脚本: function_basics.py

from typing import List, Dict, Tuple, Optional, Union
import numpy as np

def calculate_accuracy(predictions: List[int],
                      labels: List[int]) -> float:
    """
    计算分类准确率。

    Args:
        predictions: 模型预测的类别索引
        labels: 真实标签的类别索引

    Returns:
        0 到 1 之间的浮点准确率

    Raises:
        ValueError: 如果预测值和标签的长度不同
    """
    if len(predictions) != len(labels):
        raise ValueError("Predictions and labels must have same length")

    if len(predictions) == 0:
        return 0.0

    correct = sum(p == l for p, l in zip(predictions, labels))
    accuracy = correct / len(predictions)

    return accuracy

def normalize_features(data: List[float],
                      method: str = "minmax",
                      feature_range: Tuple[float, float] = (0.0, 1.0)
                      ) -> List[float]:
    """
    归一化特征值。

    Args:
        data: 特征值列表
        method: 归一化方法（"minmax" 或 "zscore"）
        feature_range: minmax 归一化的目标范围

    Returns:
        归一化后的特征值

    Raises:
        ValueError: 如果方法不受支持
    """
    if not data:
        return []

    if method == "minmax":
        min_val = min(data)
        max_val = max(data)

        if min_val == max_val:
            # 所有值都相同
            return [feature_range[0]] * len(data)

        # 缩放到 feature_range
        range_min, range_max = feature_range
        scale = (range_max - range_min) / (max_val - min_val)

        normalized = [
            range_min + (x - min_val) * scale
            for x in data
        ]

        return normalized

    elif method == "zscore":
        mean = sum(data) / len(data)
        variance = sum((x - mean) ** 2 for x in data) / len(data)
        std_dev = variance ** 0.5

        if std_dev == 0:
            return [0.0] * len(data)

        normalized = [(x - mean) / std_dev for x in data]
        return normalized

    else:
        raise ValueError(f"Unknown normalization method: {method}")

def split_data(data: List,
               train_ratio: float = 0.7,
               val_ratio: float = 0.15,
               shuffle: bool = True,
               random_seed: Optional[int] = None
               ) -> Tuple[List, List, List]:
    """
    将数据划分为训练集、验证集和测试集。

    Args:
        data: 要划分的输入数据
        train_ratio: 用于训练的数据比例
        val_ratio: 用于验证的数据比例
        shuffle: 是否在划分前打乱数据
        random_seed: 用于可复现性的随机种子

    Returns:
        (train_data, val_data, test_data) 的元组

    Raises:
        ValueError: 如果比例总和不 <= 1.0
    """
    import random

    if train_ratio + val_ratio > 1.0:
        raise ValueError("train_ratio + val_ratio must be <= 1.0")

    data_copy = data.copy()

    if shuffle:
        if random_seed is not None:
            random.seed(random_seed)
        random.shuffle(data_copy)

    n = len(data_copy)
    train_end = int(n * train_ratio)
    val_end = train_end + int(n * val_ratio)

    train_data = data_copy[:train_end]
    val_data = data_copy[train_end:val_end]
    test_data = data_copy[val_end:]

    return train_data, val_data, test_data

# 示例用法和测试
if __name__ == "__main__":
    # 测试准确率计算
    preds = [1, 0, 1, 1, 0, 1, 0, 0]
    labels = [1, 0, 1, 0, 0, 1, 0, 1]
    acc = calculate_accuracy(preds, labels)
    print(f"Accuracy: {acc:.2%}")

    # 测试归一化
    features = [1.0, 2.0, 3.0, 4.0, 5.0]
    normalized_minmax = normalize_features(features, method="minmax")
    print(f"MinMax normalized: {normalized_minmax}")

    normalized_zscore = normalize_features(features, method="zscore")
    print(f"Z-score normalized: {[f'{x:.2f}' for x in normalized_zscore]}")

    # 测试数据划分
    dataset = list(range(100))
    train, val, test = split_data(dataset, random_seed=42)
    print(f"Split sizes - Train: {len(train)}, Val: {len(val)}, Test: {len(test)}")
```

**任务**：
1. 运行脚本并验证输出
2. 添加返回复杂类型的类型提示（Dict[str, float]）
3. 为所有函数实现输入验证
4. 按照 NumPy 或 Google 风格添加全面的 docstring

### 步骤 2：使用灵活参数的函数

```python
# 创建脚本: flexible_functions.py

from typing import Any, Dict, List, Optional, Tuple
import time

def log_metrics(*args, **kwargs) -> None:
    """
    记录任意数量的指标，使用灵活的参数。

    Args:
        *args: 要记录的位置参数指标
        **kwargs: 要记录的命名参数指标

    Examples:
        log_metrics(0.92, 0.15, 0.89)
        log_metrics(accuracy=0.92, loss=0.15, f1=0.89)
        log_metrics(0.92, loss=0.15, f1=0.89)
    """
    print("=== Metrics Log ===")

    if args:
        print("Positional metrics:")
        for i, value in enumerate(args):
            print(f"  Metric {i+1}: {value}")

    if kwargs:
        print("Named metrics:")
        for name, value in kwargs.items():
            print(f"  {name}: {value}")

def create_model(model_type: str,
                *layers: int,
                activation: str = "relu",
                dropout: float = 0.0,
                **config: Any) -> Dict[str, Any]:
    """
    使用灵活的层规格创建模型配置。

    Args:
        model_type: 模型类型（例如 "cnn", "mlp"）
        *layers: 可变数量的层大小
        activation: 激活函数
        dropout: Dropout 率
        **config: 额外的配置参数

    Returns:
        模型配置字典
    """
    model_config = {
        "type": model_type,
        "layers": list(layers),
        "activation": activation,
        "dropout": dropout,
    }

    # 添加任何额外的配置
    model_config.update(config)

    return model_config

def batch_process(data: List[Any],
                 processor_func: callable,
                 batch_size: int = 32,
                 *processor_args,
                 **processor_kwargs) -> List[Any]:
    """
    使用处理器函数批量处理数据。

    Args:
        data: 要处理的数据
        processor_func: 应用于每个批次的函数
        batch_size: 每个批次的大小
        *processor_args: 传递给处理器的额外位置参数
        **processor_kwargs: 传递给处理器的额外关键字参数

    Returns:
        处理结果的列表
    """
    results = []

    for i in range(0, len(data), batch_size):
        batch = data[i:i + batch_size]
        # 使用批次和额外参数调用处理器
        result = processor_func(batch, *processor_args, **processor_kwargs)
        results.append(result)

    return results

def augment_image(image: Any,
                 flip_horizontal: bool = False,
                 flip_vertical: bool = False,
                 rotate: Optional[int] = None,
                 brightness: float = 1.0,
                 **transforms: Any) -> Dict[str, Any]:
    """
    使用灵活的转换选项应用图像增强。

    Args:
        image: 输入图像
        flip_horizontal: 是否水平翻转
        flip_vertical: 是否垂直翻转
        rotate: 旋转角度（度数）
        brightness: 亮度调整因子
        **transforms: 额外的转换

    Returns:
        包含增强信息的字典
    """
    augmentations = {
        "original": image,
        "transforms_applied": []
    }

    if flip_horizontal:
        augmentations["transforms_applied"].append("flip_h")

    if flip_vertical:
        augmentations["transforms_applied"].append("flip_v")

    if rotate is not None:
        augmentations["transforms_applied"].append(f"rotate_{rotate}")

    if brightness != 1.0:
        augmentations["transforms_applied"].append(f"brightness_{brightness}")

    # 应用任何自定义转换
    for transform_name, transform_value in transforms.items():
        augmentations["transforms_applied"].append(
            f"{transform_name}_{transform_value}"
        )

    return augmentations

# 示例用法
if __name__ == "__main__":
    # 测试灵活日志记录
    print("Example 1: Flexible logging")
    log_metrics(0.92, 0.15, 0.89)
    print()
    log_metrics(accuracy=0.92, loss=0.15, f1_score=0.89)
    print()
    log_metrics(0.92, loss=0.15, f1_score=0.89, learning_rate=0.001)
    print()

    # 测试模型创建
    print("Example 2: Model creation")
    model1 = create_model("mlp", 128, 64, 32, dropout=0.3)
    print(f"Model 1: {model1}")

    model2 = create_model("cnn", 64, 128, 256, activation="relu",
                         dropout=0.5, batch_norm=True, pool_size=2)
    print(f"Model 2: {model2}")
    print()

    # 测试批处理
    print("Example 3: Batch processing")
    def simple_processor(batch, multiplier=1):
        return sum(batch) * multiplier

    data = list(range(1, 21))
    results = batch_process(data, simple_processor, batch_size=5, multiplier=2)
    print(f"Batch results: {results}")
    print()

    # 测试图像增强
    print("Example 4: Image augmentation")
    aug_result = augment_image(
        "image.jpg",
        flip_horizontal=True,
        rotate=90,
        brightness=1.2,
        contrast=1.5,
        saturation=0.8
    )
    print(f"Augmentations: {aug_result['transforms_applied']}")
```

**任务**：
1. 实现一个同时接受 *args 和 **kwargs 的函数
2. 创建一个合并默认配置和自定义配置的配置合并器
3. 构建一个处理可变指标类型的指标聚合器
4. 实现一个带有可自定义预处理的灵活数据加载器

## 第 2 部分：常见 ML 模式的装饰器

### 步骤 3：计时和日志记录装饰器

```python
# 创建脚本: decorators.py

import time
import functools
from typing import Any, Callable
import logging

# 设置日志记录
logging.basicConfig(
    level=logging.INFO,
    format='%(asctime)s - %(name)s - %(levelname)s - %(message)s'
)
logger = logging.getLogger(__name__)

def timing_decorator(func: Callable) -> Callable:
    """测量函数执行时间的装饰器"""
    @functools.wraps(func)
    def wrapper(*args, **kwargs):
        start_time = time.time()
        result = func(*args, **kwargs)
        end_time = time.time()

        execution_time = end_time - start_time
        logger.info(f"{func.__name__} took {execution_time:.4f} seconds")

        return result
    return wrapper

def log_calls(func: Callable) -> Callable:
    """记录函数调用及参数的装饰器"""
    @functools.wraps(func)
    def wrapper(*args, **kwargs):
        args_repr = [repr(a) for a in args]
        kwargs_repr = [f"{k}={v!r}" for k, v in kwargs.items()]
        signature = ", ".join(args_repr + kwargs_repr)

        logger.info(f"Calling {func.__name__}({signature})")

        result = func(*args, **kwargs)

        logger.info(f"{func.__name__} returned {result!r}")

        return result
    return wrapper

def retry(max_attempts: int = 3, delay: float = 1.0):
    """
    失败时重试函数的装饰器。

    Args:
        max_attempts: 最大重试次数
        delay: 重试之间的延迟（秒）
    """
    def decorator(func: Callable) -> Callable:
        @functools.wraps(func)
        def wrapper(*args, **kwargs):
            attempts = 0

            while attempts < max_attempts:
                try:
                    return func(*args, **kwargs)
                except Exception as e:
                    attempts += 1
                    if attempts >= max_attempts:
                        logger.error(
                            f"{func.__name__} failed after {max_attempts} attempts"
                        )
                        raise

                    logger.warning(
                        f"{func.__name__} failed (attempt {attempts}/{max_attempts}). "
                        f"Retrying in {delay}s... Error: {e}"
                    )
                    time.sleep(delay)

        return wrapper
    return decorator

def cache_results(func: Callable) -> Callable:
    """缓存函数结果的装饰器（记忆化/memoization）"""
    cache = {}

    @functools.wraps(func)
    def wrapper(*args, **kwargs):
        # 从 args 和 kwargs 创建缓存键
        cache_key = str(args) + str(sorted(kwargs.items()))

        if cache_key in cache:
            logger.info(f"Cache hit for {func.__name__}")
            return cache[cache_key]

        logger.info(f"Cache miss for {func.__name__}, computing...")
        result = func(*args, **kwargs)
        cache[cache_key] = result

        return result

    return wrapper

def validate_inputs(**validators):
    """
    验证函数输入的装饰器。

    Example:
        @validate_inputs(x=lambda x: x > 0, y=lambda y: isinstance(y, str))
        def my_func(x, y):
            pass
    """
    def decorator(func: Callable) -> Callable:
        @functools.wraps(func)
        def wrapper(*args, **kwargs):
            # 获取函数签名
            import inspect
            sig = inspect.signature(func)
            bound_args = sig.bind(*args, **kwargs)
            bound_args.apply_defaults()

            # 验证每个参数
            for param_name, validator in validators.items():
                if param_name in bound_args.arguments:
                    value = bound_args.arguments[param_name]
                    if not validator(value):
                        raise ValueError(
                            f"Validation failed for parameter '{param_name}' "
                            f"with value {value}"
                        )

            return func(*args, **kwargs)

        return wrapper
    return decorator

# 示例用法
@timing_decorator
@log_calls
def train_model(epochs: int, batch_size: int) -> float:
    """模拟模型训练"""
    time.sleep(0.5)  # 模拟训练时间
    return 0.92

@retry(max_attempts=3, delay=0.5)
def load_model_from_storage(model_path: str) -> str:
    """模拟从存储加载模型（可能会失败）"""
    import random

    if random.random() < 0.5:
        raise IOError(f"Failed to load model from {model_path}")

    return f"Model loaded from {model_path}"

@cache_results
@timing_decorator
def compute_expensive_metric(data_size: int) -> float:
    """模拟昂贵的计算"""
    time.sleep(1.0)
    return data_size * 0.001

@validate_inputs(
    learning_rate=lambda x: 0 < x < 1,
    batch_size=lambda x: isinstance(x, int) and x > 0
)
def configure_training(learning_rate: float, batch_size: int) -> dict:
    """使用验证配置训练"""
    return {
        "learning_rate": learning_rate,
        "batch_size": batch_size
    }

if __name__ == "__main__":
    # 测试计时和日志记录
    print("=== Testing timing and logging ===")
    accuracy = train_model(epochs=10, batch_size=32)
    print(f"Training accuracy: {accuracy}\n")

    # 测试重试
    print("=== Testing retry ===")
    try:
        model = load_model_from_storage("/models/resnet50.h5")
        print(f"Success: {model}\n")
    except IOError as e:
        print(f"Failed: {e}\n")

    # 测试缓存
    print("=== Testing caching ===")
    result1 = compute_expensive_metric(1000)  # 缓存未命中
    result2 = compute_expensive_metric(1000)  # 缓存命中
    result3 = compute_expensive_metric(2000)  # 缓存未命中
    print(f"Results: {result1}, {result2}, {result3}\n")

    # 测试验证
    print("=== Testing validation ===")
    try:
        config1 = configure_training(learning_rate=0.001, batch_size=32)
        print(f"Valid config: {config1}")

        config2 = configure_training(learning_rate=1.5, batch_size=32)
        print(f"Invalid config: {config2}")
    except ValueError as e:
        print(f"Validation error: {e}")
```

**任务**：
1. 创建一个记录 GPU 内存使用情况的装饰器
2. 实现一个将函数结果保存到磁盘检查点的装饰器
3. 构建一个将指标发送到监控服务的装饰器
4. 创建一个实现 API 调用速率限制的装饰器

## 第 3 部分：构建可复用模块

### 步骤 4：创建指标模块

```python
# 创建文件: ml_utils/metrics.py
# 目录结构:
# ml_utils/
#   __init__.py
#   metrics.py
#   preprocessing.py
#   visualization.py

"""
机器学习指标模块

提供分类和回归任务的常见评估指标。
"""

from typing import List, Dict, Tuple
import math

def accuracy(predictions: List[int], labels: List[int]) -> float:
    """计算分类准确率"""
    if len(predictions) != len(labels):
        raise ValueError("Predictions and labels must have same length")

    if not predictions:
        return 0.0

    correct = sum(p == l for p, l in zip(predictions, labels))
    return correct / len(predictions)

def precision(predictions: List[int],
             labels: List[int],
             positive_class: int = 1) -> float:
    """计算二分类的精确率"""
    true_positives = sum(
        1 for p, l in zip(predictions, labels)
        if p == positive_class and l == positive_class
    )

    predicted_positives = sum(1 for p in predictions if p == positive_class)

    if predicted_positives == 0:
        return 0.0

    return true_positives / predicted_positives

def recall(predictions: List[int],
          labels: List[int],
          positive_class: int = 1) -> float:
    """计算二分类的召回率"""
    true_positives = sum(
        1 for p, l in zip(predictions, labels)
        if p == positive_class and l == positive_class
    )

    actual_positives = sum(1 for l in labels if l == positive_class)

    if actual_positives == 0:
        return 0.0

    return true_positives / actual_positives

def f1_score(predictions: List[int],
            labels: List[int],
            positive_class: int = 1) -> float:
    """计算 F1 分数"""
    prec = precision(predictions, labels, positive_class)
    rec = recall(predictions, labels, positive_class)

    if prec + rec == 0:
        return 0.0

    return 2 * (prec * rec) / (prec + rec)

def confusion_matrix(predictions: List[int],
                    labels: List[int],
                    num_classes: int) -> List[List[int]]:
    """
    计算混淆矩阵。

    Returns:
        矩阵，其中元素 [i][j] 表示真实标签为 i、预测标签为 j 的样本
    """
    matrix = [[0] * num_classes for _ in range(num_classes)]

    for pred, label in zip(predictions, labels):
        matrix[label][pred] += 1

    return matrix

def classification_report(predictions: List[int],
                         labels: List[int],
                         class_names: List[str] = None) -> Dict[str, Dict]:
    """
    生成全面的分类报告。

    Returns:
        包含每个类别指标的字典
    """
    num_classes = max(max(predictions), max(labels)) + 1

    if class_names is None:
        class_names = [f"class_{i}" for i in range(num_classes)]

    report = {}

    for class_id, class_name in enumerate(class_names):
        report[class_name] = {
            "precision": precision(predictions, labels, class_id),
            "recall": recall(predictions, labels, class_id),
            "f1_score": f1_score(predictions, labels, class_id)
        }

    # 添加整体准确率
    report["accuracy"] = accuracy(predictions, labels)

    return report

def mean_squared_error(predictions: List[float],
                      labels: List[float]) -> float:
    """计算回归的均方误差（MSE）"""
    if len(predictions) != len(labels):
        raise ValueError("Predictions and labels must have same length")

    if not predictions:
        return 0.0

    squared_errors = [(p - l) ** 2 for p, l in zip(predictions, labels)]
    return sum(squared_errors) / len(squared_errors)

def mean_absolute_error(predictions: List[float],
                       labels: List[float]) -> float:
    """计算回归的平均绝对误差（MAE）"""
    if len(predictions) != len(labels):
        raise ValueError("Predictions and labels must have same length")

    if not predictions:
        return 0.0

    absolute_errors = [abs(p - l) for p, l in zip(predictions, labels)]
    return sum(absolute_errors) / len(absolute_errors)

def r_squared(predictions: List[float],
             labels: List[float]) -> float:
    """计算回归的 R² 分数"""
    if len(predictions) != len(labels):
        raise ValueError("Predictions and labels must have same length")

    if not predictions:
        return 0.0

    # 计算标签的均值
    mean_label = sum(labels) / len(labels)

    # 总平方和
    ss_tot = sum((l - mean_label) ** 2 for l in labels)

    # 残差平方和
    ss_res = sum((l - p) ** 2 for l, p in zip(labels, predictions))

    if ss_tot == 0:
        return 0.0

    return 1 - (ss_res / ss_tot)

# 创建 ml_utils/__init__.py
"""
ML 实用工具包

为机器学习工作流提供可复用的实用工具。
"""

from . import metrics
from . import preprocessing

__version__ = "0.1.0"
__all__ = ["metrics", "preprocessing"]
```

### 步骤 5：创建预处理模块

```python
# 创建文件: ml_utils/preprocessing.py

"""
数据预处理模块

提供数据清洗和预处理的实用工具。
"""

from typing import List, Tuple, Optional, Dict, Any
import statistics

def normalize_minmax(data: List[float],
                    feature_range: Tuple[float, float] = (0.0, 1.0)
                    ) -> List[float]:
    """将数据归一化到指定范围"""
    if not data:
        return []

    min_val = min(data)
    max_val = max(data)

    if min_val == max_val:
        return [feature_range[0]] * len(data)

    range_min, range_max = feature_range
    scale = (range_max - range_min) / (max_val - min_val)

    return [range_min + (x - min_val) * scale for x in data]

def normalize_zscore(data: List[float]) -> List[float]:
    """使用 z-score 标准化对数据进行归一化"""
    if not data:
        return []

    mean = statistics.mean(data)
    std_dev = statistics.stdev(data) if len(data) > 1 else 0

    if std_dev == 0:
        return [0.0] * len(data)

    return [(x - mean) / std_dev for x in data]

def remove_outliers(data: List[float],
                   method: str = "iqr",
                   threshold: float = 1.5) -> List[float]:
    """
    从数据中移除异常值。

    Args:
        data: 输入数据
        method: 使用的方法（"iqr" 或 "zscore"）
        threshold: 异常值检测的阈值

    Returns:
        移除异常值后的数据
    """
    if not data or len(data) < 4:
        return data

    if method == "iqr":
        sorted_data = sorted(data)
        q1_idx = len(sorted_data) // 4
        q3_idx = 3 * len(sorted_data) // 4

        q1 = sorted_data[q1_idx]
        q3 = sorted_data[q3_idx]
        iqr = q3 - q1

        lower_bound = q1 - threshold * iqr
        upper_bound = q3 + threshold * iqr

        return [x for x in data if lower_bound <= x <= upper_bound]

    elif method == "zscore":
        mean = statistics.mean(data)
        std_dev = statistics.stdev(data)

        z_scores = [abs((x - mean) / std_dev) for x in data]
        return [x for x, z in zip(data, z_scores) if z <= threshold]

    else:
        raise ValueError(f"Unknown method: {method}")

def fill_missing_values(data: List[Optional[float]],
                       strategy: str = "mean") -> List[float]:
    """
    填充数据中的缺失值。

    Args:
        data: 可能包含 None 值的输入数据
        strategy: 使用的策略（"mean"、"median"、"mode"、"forward"、"backward"）

    Returns:
        缺失值已被填充的数据
    """
    if not data:
        return []

    # 获取非缺失值
    valid_values = [x for x in data if x is not None]

    if not valid_values:
        return [0.0] * len(data)

    if strategy == "mean":
        fill_value = statistics.mean(valid_values)
        return [x if x is not None else fill_value for x in data]

    elif strategy == "median":
        fill_value = statistics.median(valid_values)
        return [x if x is not None else fill_value for x in data]

    elif strategy == "mode":
        fill_value = statistics.mode(valid_values)
        return [x if x is not None else fill_value for x in data]

    elif strategy == "forward":
        result = []
        last_valid = valid_values[0]
        for x in data:
            if x is not None:
                last_valid = x
                result.append(x)
            else:
                result.append(last_valid)
        return result

    elif strategy == "backward":
        result = []
        data_reversed = list(reversed(data))
        valid_reversed = [x for x in data_reversed if x is not None]
        last_valid = valid_reversed[0]

        for x in data_reversed:
            if x is not None:
                last_valid = x
                result.append(x)
            else:
                result.append(last_valid)

        return list(reversed(result))

    else:
        raise ValueError(f"Unknown strategy: {strategy}")

def one_hot_encode(labels: List[int], num_classes: int) -> List[List[int]]:
    """将类别标签转换为独热编码"""
    encoded = []

    for label in labels:
        one_hot = [0] * num_classes
        if 0 <= label < num_classes:
            one_hot[label] = 1
        encoded.append(one_hot)

    return encoded

def train_test_split(data: List[Any],
                    test_size: float = 0.2,
                    shuffle: bool = True,
                    random_seed: Optional[int] = None
                    ) -> Tuple[List[Any], List[Any]]:
    """将数据划分为训练集和测试集"""
    import random

    if not 0 < test_size < 1:
        raise ValueError("test_size must be between 0 and 1")

    data_copy = data.copy()

    if shuffle:
        if random_seed is not None:
            random.seed(random_seed)
        random.shuffle(data_copy)

    split_idx = int(len(data_copy) * (1 - test_size))
    train_data = data_copy[:split_idx]
    test_data = data_copy[split_idx:]

    return train_data, test_data
```

### 步骤 6：使用您的自定义模块

```python
# 创建脚本: test_ml_utils.py

# 确保 ml_utils/ 在您的 Python 路径中
import sys
sys.path.insert(0, '.')

from ml_utils import metrics, preprocessing

def test_metrics():
    """测试指标模块"""
    print("=== Testing Metrics Module ===")

    # 测试数据
    predictions = [1, 0, 1, 1, 0, 1, 0, 0, 1, 1]
    labels = [1, 0, 1, 0, 0, 1, 0, 1, 1, 0]

    # 计算指标
    acc = metrics.accuracy(predictions, labels)
    prec = metrics.precision(predictions, labels)
    rec = metrics.recall(predictions, labels)
    f1 = metrics.f1_score(predictions, labels)

    print(f"Accuracy: {acc:.2%}")
    print(f"Precision: {prec:.2%}")
    print(f"Recall: {rec:.2%}")
    print(f"F1 Score: {f1:.2%}")

    # 生成报告
    report = metrics.classification_report(
        predictions, labels,
        class_names=["negative", "positive"]
    )
    print(f"\nClassification Report:")
    for class_name, metrics_dict in report.items():
        if class_name != "accuracy":
            print(f"  {class_name}: {metrics_dict}")

    print(f"  Overall Accuracy: {report['accuracy']:.2%}\n")

def test_preprocessing():
    """测试预处理模块"""
    print("=== Testing Preprocessing Module ===")

    # 测试归一化
    data = [1.0, 2.0, 3.0, 4.0, 5.0]
    normalized = preprocessing.normalize_minmax(data)
    print(f"Original: {data}")
    print(f"Normalized: {[f'{x:.2f}' for x in normalized]}")

    # 测试异常值移除
    data_with_outliers = [1, 2, 3, 4, 5, 100, 2, 3, 4, 5]
    cleaned = preprocessing.remove_outliers(data_with_outliers)
    print(f"\nWith outliers: {data_with_outliers}")
    print(f"Cleaned: {cleaned}")

    # 测试缺失值处理
    data_with_missing = [1.0, 2.0, None, 4.0, None, 6.0]
    filled = preprocessing.fill_missing_values(data_with_missing, strategy="mean")
    print(f"\nWith missing: {data_with_missing}")
    print(f"Filled (mean): {[f'{x:.2f}' for x in filled]}")

    # 测试独热编码
    labels = [0, 1, 2, 1, 0, 2]
    one_hot = preprocessing.one_hot_encode(labels, num_classes=3)
    print(f"\nLabels: {labels}")
    print(f"One-hot: {one_hot}\n")

if __name__ == "__main__":
    test_metrics()
    test_preprocessing()

    print("✓ All tests passed!")
```

## 第 4 部分：函数式编程模式

### 步骤 7：使用 map、filter 和 lambda

```python
# 创建脚本: functional_patterns.py

from typing import List, Callable, Any
from functools import reduce

# 常用操作的 Lambda 函数
square = lambda x: x ** 2
is_even = lambda x: x % 2 == 0
normalize = lambda x, min_val, max_val: (x - min_val) / (max_val - min_val)

def example_map():
    """演示 map 用于转换"""
    print("=== Map Examples ===")

    # 对所有数字求平方
    numbers = [1, 2, 3, 4, 5]
    squared = list(map(square, numbers))
    print(f"Original: {numbers}")
    print(f"Squared: {squared}")

    # 将概率转换为类别标签
    probabilities = [0.2, 0.8, 0.6, 0.3, 0.9]
    predictions = list(map(lambda p: 1 if p > 0.5 else 0, probabilities))
    print(f"Probabilities: {probabilities}")
    print(f"Predictions: {predictions}")

    # 解析文件名
    files = ["model_v1.h5", "model_v2.h5", "model_v3.h5"]
    versions = list(map(lambda f: f.split("_v")[1].split(".")[0], files))
    print(f"Files: {files}")
    print(f"Versions: {versions}\n")

def example_filter():
    """演示 filter 用于筛选"""
    print("=== Filter Examples ===")

    # 过滤偶数
    numbers = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
    evens = list(filter(is_even, numbers))
    print(f"Numbers: {numbers}")
    print(f"Evens: {evens}")

    # 过滤高准确率模型
    models = [
        {"name": "model1", "accuracy": 0.85},
        {"name": "model2", "accuracy": 0.92},
        {"name": "model3", "accuracy": 0.88},
        {"name": "model4", "accuracy": 0.95},
    ]

    high_accuracy = list(filter(lambda m: m["accuracy"] > 0.90, models))
    print(f"High accuracy models: {[m['name'] for m in high_accuracy]}")

    # 过滤已完成的实验
    experiments = [
        ("exp1", "completed"),
        ("exp2", "running"),
        ("exp3", "completed"),
        ("exp4", "failed"),
    ]

    completed = list(filter(lambda e: e[1] == "completed", experiments))
    print(f"Completed: {[e[0] for e in completed]}\n")

def example_reduce():
    """演示 reduce 用于聚合"""
    print("=== Reduce Examples ===")

    # 求和所有数字
    numbers = [1, 2, 3, 4, 5]
    total = reduce(lambda acc, x: acc + x, numbers, 0)
    print(f"Numbers: {numbers}")
    print(f"Sum: {total}")

    # 找到最大准确率
    accuracies = [0.85, 0.92, 0.88, 0.95, 0.90]
    max_acc = reduce(lambda acc, x: max(acc, x), accuracies, 0)
    print(f"Accuracies: {accuracies}")
    print(f"Max: {max_acc}")

    # 合并配置
    configs = [
        {"learning_rate": 0.001},
        {"batch_size": 32},
        {"epochs": 100},
    ]

    merged = reduce(lambda acc, d: {**acc, **d}, configs, {})
    print(f"Configs: {configs}")
    print(f"Merged: {merged}\n")

def example_composition():
    """演示函数组合"""
    print("=== Function Composition ===")

    # 组合数据处理管道
    data = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]

    # 管道：过滤偶数，求平方，求和
    result = reduce(
        lambda acc, x: acc + x,
        map(square, filter(is_even, data)),
        0
    )

    print(f"Original: {data}")
    print(f"Evens squared and summed: {result}")

    # 处理模型指标
    metrics = [
        {"model": "m1", "acc": 0.85, "loss": 0.25},
        {"model": "m2", "acc": 0.92, "loss": 0.15},
        {"model": "m3", "acc": 0.88, "loss": 0.20},
    ]

    # 过滤高准确率，提取名称
    best_models = list(map(
        lambda m: m["model"],
        filter(lambda m: m["acc"] > 0.87, metrics)
    ))

    print(f"Best models: {best_models}\n")

if __name__ == "__main__":
    example_map()
    example_filter()
    example_reduce()
    example_composition()
```

## 验证与反思

```python
# 创建脚本: validate_module.py

def validate_exercise():
    """验证所有练习组件"""
    print("=== Exercise 03 Validation ===\n")

    # 检查 1：类型提示
    from ml_utils import metrics
    import inspect

    sig = inspect.signature(metrics.accuracy)
    print(f"✓ Type hints present in metrics.accuracy: {sig}")

    # 检查 2：装饰器工作正常
    from decorators import timing_decorator

    @timing_decorator
    def test_func():
        import time
        time.sleep(0.1)
        return "done"

    result = test_func()
    print(f"✓ Decorator executed: {result}")

    # 检查 3：模块导入
    try:
        from ml_utils import metrics, preprocessing
        print(f"✓ Module imports successful")
    except ImportError as e:
        print(f"✗ Module import failed: {e}")

    # 检查 4：函数工作正确
    preds = [1, 0, 1, 1]
    labels = [1, 0, 0, 1]
    acc = metrics.accuracy(preds, labels)
    expected = 0.75
    assert abs(acc - expected) < 0.01, f"Expected {expected}, got {acc}"
    print(f"✓ Metrics calculation correct: {acc}")

    print("\n✓ All validations passed!")

if __name__ == "__main__":
    validate_exercise()
```

## 反思问题

1. 何时应该在生产代码中使用类型提示？
2. 装饰器如何帮助使代码更易于维护？
3. 将代码组织到模块中有什么好处？
4. 何时应该使用 *args 和 **kwargs？
5. 函数式编程如何提高代码可读性？
6. 对于实用工具函数，应该使用什么测试策略？
7. 如何在函数设计的灵活性和简单性之间取得平衡？

## 下一步

完成本练习后：
- **练习 04**：文件 I/O - 读取和写入 ML 数据文件
- **练习 05**：错误处理 - 构建健壮的 ML 应用程序
- **第 3 课**：Python DevOps 集成

## 额外资源

- 类型提示：https://docs.python.org/3/library/typing.html
- 装饰器指南：https://realpython.com/primer-on-python-decorators/
- Python 模块：https://docs.python.org/3/tutorial/modules.html
- 函数式编程：https://docs.python.org/3/howto/functional.html

---

**恭喜！** 您已学会为 ML 基础设施创建可复用、结构良好的 Python 代码。这些模式将在您的 AI 工程职业生涯中持续为您服务。
