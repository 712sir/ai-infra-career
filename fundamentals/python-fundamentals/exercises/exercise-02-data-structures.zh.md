# 练习 02：用于 ML 数据处理的 Python 数据结构（Python Data Structures for ML Data Processing）

## 概述（Overview）

本练习教您如何有效地使用 Python 的内置数据结构（列表、字典、集合、元组）进行机器学习（Machine Learning）数据处理任务。您将处理真实的 ML 场景，包括数据集操作、特征工程、批处理和模型元数据管理。

## 学习目标（Learning Objectives）

完成本练习后，您将能够：
- 掌握用于批处理和数据管道的列表（List）操作
- 使用字典（Dictionary）进行配置管理和特征存储
- 应用集合（Set）进行去重和数据集操作
- 利用元组（Tuple）进行不可变数据和函数返回
- 实现列表推导式（List Comprehension）和字典推导式（Dict Comprehension）以实现高效的数据处理
- 理解何时在 ML 上下文中使用每种数据结构
- 处理 ML 配置中常见的嵌套数据结构

## 先决条件（Prerequisites）

- 已完成练习 01：环境设置
- 已完成第 1 课：Python 环境
- 基本的 Python 语法知识
- 理解 ML 概念（数据集、批次、特征）

## 所需时间

- 预计：90-120 分钟
- 难度：初级到中级

## 第 1 部分：用于批处理的列表

### 步骤 1：ML 数据的基本列表操作

```python
# 创建脚本: list_operations.py

# 样本数据集：用于训练的图像文件路径
training_images = [
    "img_0001.jpg",
    "img_0002.jpg",
    "img_0003.jpg",
    "img_0004.jpg",
    "img_0005.jpg"
]

# 打印数据集信息
print(f"Total training images: {len(training_images)}")
print(f"First image: {training_images[0]}")
print(f"Last image: {training_images[-1]}")

# 添加新图像
training_images.append("img_0006.jpg")
training_images.extend(["img_0007.jpg", "img_0008.jpg"])
print(f"After adding: {len(training_images)} images")

# 在特定位置插入图像
training_images.insert(0, "img_0000.jpg")
print(f"First image now: {training_images[0]}")

# 移除图像
removed = training_images.pop()  # 移除最后一个
print(f"Removed: {removed}")

training_images.remove("img_0000.jpg")  # 按值移除
print(f"Final count: {len(training_images)}")

# 检查图像是否存在
if "img_0003.jpg" in training_images:
    index = training_images.index("img_0003.jpg")
    print(f"Found img_0003.jpg at index {index}")

# 切片操作（获取批次）
batch_size = 3
batch_1 = training_images[0:batch_size]
batch_2 = training_images[batch_size:batch_size*2]
print(f"Batch 1: {batch_1}")
print(f"Batch 2: {batch_2}")

# 反转和排序
training_images_sorted = sorted(training_images)
print(f"Sorted: {training_images_sorted}")

training_images_reversed = list(reversed(training_images))
print(f"Reversed: {training_images_reversed}")
```

**预期输出（Expected Output）**：
```
Total training images: 5
First image: img_0001.jpg
Last image: img_0005.jpg
After adding: 7 images
First image now: img_0000.jpg
Removed: img_0008.jpg
Final count: 6
Found img_0003.jpg at index 2
Batch 1: ['img_0001.jpg', 'img_0002.jpg', 'img_0003.jpg']
Batch 2: ['img_0004.jpg', 'img_0005.jpg', 'img_0006.jpg']
...
```

**任务**：
1. 运行脚本并验证输出
2. 向列表中添加另外 10 张图像
3. 创建大小为 4 的批次
4. 查找名称中包含 "000" 的所有图像

### 步骤 2：用于数据处理的列表推导式

```python
# 创建脚本: list_comprehensions.py

# 样本数据：模型训练损失
losses = [2.5, 2.1, 1.8, 1.5, 1.3, 1.2, 1.1, 1.05, 1.02, 1.01]

# 对所有损失求平方
squared_losses = [loss ** 2 for loss in losses]
print(f"Squared losses: {squared_losses}")

# 过滤低于阈值的损失
low_losses = [loss for loss in losses if loss < 1.5]
print(f"Losses below 1.5: {low_losses}")

# 转换并过滤
normalized_losses = [(loss - min(losses)) / (max(losses) - min(losses))
                     for loss in losses if loss < 2.0]
print(f"Normalized losses: {normalized_losses}")

# 嵌套列表推导式：创建批次
data_points = list(range(1, 21))  # 20 个数据点
batch_size = 5
batches = [data_points[i:i+batch_size]
           for i in range(0, len(data_points), batch_size)]
print(f"Batches: {batches}")

# 处理图像尺寸
image_sizes = [(224, 224), (256, 256), (512, 512), (1024, 1024)]
total_pixels = [width * height for width, height in image_sizes]
print(f"Total pixels: {total_pixels}")

# 创建独热编码（one-hot encoding）
classes = ["cat", "dog", "bird", "fish"]
target_class = "dog"
one_hot = [1 if cls == target_class else 0 for cls in classes]
print(f"One-hot for '{target_class}': {one_hot}")

# 解析模型文件名
model_files = [
    "model_v1_acc_0.85.h5",
    "model_v2_acc_0.92.h5",
    "model_v3_acc_0.88.h5"
]

# 提取准确率
accuracies = [float(f.split("_acc_")[1].replace(".h5", ""))
              for f in model_files]
print(f"Accuracies: {accuracies}")

# 找到最佳模型
best_idx = accuracies.index(max(accuracies))
best_model = model_files[best_idx]
print(f"Best model: {best_model} (acc: {max(accuracies)})")

# 条件列表构建
training_config = {
    "epochs": 100,
    "batch_size": 32,
    "learning_rate": 0.001,
    "use_gpu": True,
    "augmentation": True
}

enabled_features = [key for key, value in training_config.items()
                   if isinstance(value, bool) and value]
print(f"Enabled features: {enabled_features}")
```

**任务**：
1. 创建一个列表推导式，过滤出准确率 > 0.90 的模型
2. 生成具有重叠窗口的批次（步长 < batch_size）
3. 创建一个按准确率排序的 (filename, accuracy) 元组列表
4. 使用嵌套推导式展平一个 2D 特征列表

### 步骤 3：真实世界的批处理

```python
# 创建脚本: batch_processor.py

import random
from typing import List, Tuple

class DataBatchProcessor:
    """处理 ML 训练的数据批次"""

    def __init__(self, data: List, batch_size: int, shuffle: bool = True):
        self.data = data.copy()
        self.batch_size = batch_size
        self.shuffle = shuffle

    def get_batches(self) -> List[List]:
        """从数据中生成批次"""
        if self.shuffle:
            random.shuffle(self.data)

        batches = []
        for i in range(0, len(self.data), self.batch_size):
            batch = self.data[i:i + self.batch_size]
            batches.append(batch)

        return batches

    def get_batch_statistics(self) -> dict:
        """计算批次统计信息"""
        num_batches = (len(self.data) + self.batch_size - 1) // self.batch_size
        last_batch_size = len(self.data) % self.batch_size or self.batch_size

        return {
            "total_samples": len(self.data),
            "batch_size": self.batch_size,
            "num_batches": num_batches,
            "last_batch_size": last_batch_size
        }

# 示例用法
sample_ids = list(range(1, 101))  # 100 个样本

processor = DataBatchProcessor(sample_ids, batch_size=16)
batches = processor.get_batches()

print(f"Generated {len(batches)} batches")
print(f"First batch: {batches[0]}")
print(f"Last batch size: {len(batches[-1])}")

stats = processor.get_batch_statistics()
print(f"Statistics: {stats}")

# TODO: 扩展此类以支持：
# 1. 分类的分层抽样（Stratified sampling）
# 2. 加权抽样（Weighted sampling）
# 3. 不均匀批次的自定义填充
```

**挑战任务**：
1. 实现分层批次处理，确保每个批次包含平衡的类别
2. 添加一个删除最后一个不完整批次的方法
3. 创建一个返回批次索引而非批次数据的方法
4. 实现一个用于无限训练循环的循环批次生成器

## 第 2 部分：用于配置和元数据的字典

### 步骤 4：ML 配置的字典操作

```python
# 创建脚本: dict_operations.py

# 模型配置
model_config = {
    "name": "ResNet50",
    "version": "1.0.0",
    "input_shape": (224, 224, 3),
    "num_classes": 1000,
    "pretrained": True,
    "freeze_layers": 10
}

# 访问值
print(f"Model: {model_config['name']}")
print(f"Version: {model_config['version']}")

# 使用 get() 安全访问
optimizer = model_config.get("optimizer", "adam")  # 默认为 adam
print(f"Optimizer: {optimizer}")

# 更新配置
model_config["learning_rate"] = 0.001
model_config.update({
    "optimizer": "adam",
    "weight_decay": 0.0001
})

print(f"Updated config: {model_config}")

# 检查键是否存在
if "dropout" not in model_config:
    model_config["dropout"] = 0.5
    print("Added dropout configuration")

# 遍历配置
print("\nConfiguration summary:")
for key, value in model_config.items():
    print(f"  {key}: {value}")

# 获取所有键和值
config_keys = list(model_config.keys())
config_values = list(model_config.values())
print(f"\nConfig keys: {config_keys}")

# 移除键
removed_value = model_config.pop("freeze_layers", None)
print(f"Removed freeze_layers: {removed_value}")

# 清除特定键
temp_config = model_config.copy()
temp_config.clear()
print(f"Cleared config: {temp_config}")
print(f"Original still intact: {len(model_config)} keys")
```

### 步骤 5：字典推导式和嵌套结构

```python
# 创建脚本: dict_comprehensions.py

# 从列表创建指标字典
metric_names = ["accuracy", "precision", "recall", "f1_score"]
metric_values = [0.92, 0.89, 0.94, 0.91]

metrics = {name: value for name, value in zip(metric_names, metric_values)}
print(f"Metrics: {metrics}")

# 过滤高于阈值的指标
high_metrics = {k: v for k, v in metrics.items() if v > 0.90}
print(f"High metrics (>0.90): {high_metrics}")

# 转换值
metrics_percentage = {k: f"{v*100:.1f}%" for k, v in metrics.items()}
print(f"Metrics as %: {metrics_percentage}")

# 嵌套字典：实验结果
experiments = {
    "exp_001": {
        "model": "resnet50",
        "accuracy": 0.92,
        "loss": 0.15,
        "epoch": 50,
        "status": "completed"
    },
    "exp_002": {
        "model": "vgg16",
        "accuracy": 0.88,
        "loss": 0.22,
        "epoch": 45,
        "status": "completed"
    },
    "exp_003": {
        "model": "mobilenet",
        "accuracy": 0.85,
        "loss": 0.28,
        "epoch": 30,
        "status": "failed"
    }
}

# 按准确率查找最佳实验
completed_exps = {k: v for k, v in experiments.items()
                  if v["status"] == "completed"}
best_exp = max(completed_exps.items(), key=lambda x: x["accuracy"])
print(f"Best experiment: {best_exp[0]} with accuracy {best_exp[1]['accuracy']}")

# 从所有实验中提取特定字段
accuracies = {exp_id: data["accuracy"]
              for exp_id, data in experiments.items()
              if data["status"] == "completed"}
print(f"All accuracies: {accuracies}")

# 按模型分组实验
by_model = {}
for exp_id, data in experiments.items():
    model = data["model"]
    if model not in by_model:
        by_model[model] = []
    by_model[model].append(exp_id)

print(f"Experiments by model: {by_model}")

# 创建摘要统计
summary = {
    "total_experiments": len(experiments),
    "completed": sum(1 for v in experiments.values() if v["status"] == "completed"),
    "failed": sum(1 for v in experiments.values() if v["status"] == "failed"),
    "avg_accuracy": sum(v["accuracy"] for v in experiments.values()
                       if v["status"] == "completed") / len(completed_exps)
}
print(f"Summary: {summary}")
```

### 步骤 6：特征字典管理

```python
# 创建脚本: feature_manager.py

from typing import Dict, List, Any
import json

class FeatureManager:
    """管理 ML 特征及其元数据"""

    def __init__(self):
        self.features: Dict[str, Dict[str, Any]] = {}

    def add_feature(self, name: str, dtype: str,
                   importance: float = 0.0, description: str = ""):
        """添加带有元数据的特征"""
        self.features[name] = {
            "dtype": dtype,
            "importance": importance,
            "description": description,
            "used_count": 0
        }

    def get_feature(self, name: str) -> Dict[str, Any]:
        """获取特征元数据"""
        return self.features.get(name, {})

    def update_importance(self, name: str, importance: float):
        """更新特征重要性"""
        if name in self.features:
            self.features[name]["importance"] = importance

    def increment_usage(self, name: str):
        """跟踪特征使用情况"""
        if name in self.features:
            self.features[name]["used_count"] += 1

    def get_top_features(self, n: int = 5) -> List[tuple]:
        """按重要性获取前 N 个特征"""
        sorted_features = sorted(
            self.features.items(),
            key=lambda x: x[1]["importance"],
            reverse=True
        )
        return sorted_features[:n]

    def filter_by_dtype(self, dtype: str) -> Dict[str, Dict]:
        """获取所有特定数据类型的特征"""
        return {
            name: meta for name, meta in self.features.items()
            if meta["dtype"] == dtype
        }

    def export_config(self, filepath: str):
        """将特征导出为 JSON"""
        with open(filepath, 'w') as f:
            json.dump(self.features, f, indent=2)

    def import_config(self, filepath: str):
        """从 JSON 导入特征"""
        with open(filepath, 'r') as f:
            self.features = json.load(f)

# 示例用法
manager = FeatureManager()

# 添加特征
manager.add_feature("age", "int", 0.85, "User age in years")
manager.add_feature("income", "float", 0.92, "Annual income")
manager.add_feature("location", "str", 0.65, "City name")
manager.add_feature("clicks", "int", 0.78, "Number of clicks")
manager.add_feature("conversion", "bool", 0.95, "Converted or not")

# 更新和使用特征
manager.update_importance("age", 0.88)
manager.increment_usage("age")
manager.increment_usage("income")

# 获取前几个特征
top_features = manager.get_top_features(3)
print("Top 3 features:")
for name, meta in top_features:
    print(f"  {name}: importance={meta['importance']}")

# 按类型过滤
numeric_features = manager.filter_by_dtype("int")
print(f"\nNumeric features: {list(numeric_features.keys())}")

# 导出/导入
manager.export_config("features.json")
print("Features exported to features.json")

# TODO: 扩展此类以支持：
# 1. 特征工程转换
# 2. 特征版本跟踪
# 3. 特征验证规则
# 4. 特征相关性分析
```

## 第 3 部分：用于去重和操作的集合

### 步骤 7：数据集管理的集合操作

```python
# 创建脚本: set_operations.py

# 训练和验证数据集 ID
train_ids = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}
val_ids = {9, 10, 11, 12, 13}
test_ids = {13, 14, 15, 16, 17}

print(f"Training samples: {len(train_ids)}")
print(f"Validation samples: {len(val_ids)}")
print(f"Test samples: {len(test_ids)}")

# 查找重叠样本（数据泄露检查）
train_val_overlap = train_ids & val_ids  # 交集（Intersection）
print(f"Train-Val overlap: {train_val_overlap}")

train_test_overlap = train_ids & test_ids
print(f"Train-Test overlap: {train_test_overlap}")

val_test_overlap = val_ids & test_ids
print(f"Val-Test overlap: {val_test_overlap}")

# 并集：所有唯一样本
all_samples = train_ids | val_ids | test_ids
print(f"Total unique samples: {len(all_samples)}")
print(f"All sample IDs: {sorted(all_samples)}")

# 差集：仅在训练集中的样本
train_only = train_ids - val_ids - test_ids
print(f"Samples only in training: {train_only}")

# 对称差集：在任一集合中但不在两者都存在的样本
train_val_exclusive = train_ids ^ val_ids
print(f"Exclusive to train or val: {train_val_exclusive}")

# 检查集合是否不相交（没有重叠）
is_clean_split = train_ids.isdisjoint(test_ids)
print(f"Clean train-test split: {is_clean_split}")

# 添加和移除样本
new_samples = {18, 19, 20}
test_ids_updated = test_ids | new_samples  # 并集
print(f"Updated test set: {test_ids_updated}")

# 移除异常值
outliers = {5, 10}
train_cleaned = train_ids - outliers
print(f"Training after removing outliers: {train_cleaned}")

# 子集检查
small_set = {1, 2, 3}
is_subset = small_set.issubset(train_ids)
print(f"Is {small_set} subset of training? {is_subset}")

is_superset = train_ids.issuperset(small_set)
print(f"Is training superset of {small_set}? {is_superset}")
```

### 步骤 8：去重和数据清洗

```python
# 创建脚本: deduplication.py

from typing import List, Set, Dict

def remove_duplicate_samples(sample_ids: List[int]) -> List[int]:
    """移除重复样本，同时保持顺序"""
    seen = set()
    unique_samples = []

    for sample_id in sample_ids:
        if sample_id not in seen:
            seen.add(sample_id)
            unique_samples.append(sample_id)

    return unique_samples

def find_duplicate_files(filepaths: List[str]) -> Dict[str, List[str]]:
    """按基名查找重复文件"""
    from collections import defaultdict
    import os

    basename_map = defaultdict(list)

    for filepath in filepaths:
        basename = os.path.basename(filepath)
        basename_map[basename].append(filepath)

    # 仅返回重复项
    duplicates = {k: v for k, v in basename_map.items() if len(v) > 1}
    return duplicates

def validate_unique_classes(dataset: List[tuple]) -> bool:
    """验证每个样本的所有类别标签都是唯一的"""
    sample_ids = [item[0] for item in dataset]
    unique_ids = set(sample_ids)

    if len(sample_ids) != len(unique_ids):
        print(f"Warning: {len(sample_ids) - len(unique_ids)} duplicate sample IDs found")
        return False
    return True

# 示例：具有重复项的数据集
raw_dataset = [
    (1, "cat", "img1.jpg"),
    (2, "dog", "img2.jpg"),
    (3, "cat", "img3.jpg"),
    (1, "cat", "img1_copy.jpg"),  # 重复 ID
    (4, "bird", "img4.jpg"),
    (2, "dog", "img2_v2.jpg"),    # 重复 ID
]

print("Original dataset size:", len(raw_dataset))

# 提取唯一 ID
sample_ids = [item[0] for item in raw_dataset]
unique_ids = list(set(sample_ids))
print(f"Unique sample IDs: {len(unique_ids)} (from {len(sample_ids)} total)")

# 保留首次出现的重复项
cleaned_ids = remove_duplicate_samples(sample_ids)
print(f"Cleaned IDs: {cleaned_ids}")

# 查找重复条目
seen_ids = set()
duplicates = []
for item in raw_dataset:
    if item[0] in seen_ids:
        duplicates.append(item)
    seen_ids.add(item[0])

print(f"Duplicate entries: {duplicates}")

# 验证唯一性
is_valid = validate_unique_classes(raw_dataset)
print(f"Dataset has unique IDs: {is_valid}")

# 示例：查找重复文件名
image_files = [
    "/data/train/img001.jpg",
    "/data/train/img002.jpg",
    "/data/val/img001.jpg",      # 相同基名
    "/data/test/img002.jpg",     # 相同基名
    "/data/train/img003.jpg"
]

duplicate_files = find_duplicate_files(image_files)
print(f"\nDuplicate filenames: {duplicate_files}")

# 用于类别分布的集合操作
class_labels = ["cat", "dog", "cat", "bird", "dog", "cat", "fish", "dog"]
unique_classes = set(class_labels)
print(f"\nUnique classes: {unique_classes}")
print(f"Number of classes: {len(unique_classes)}")

# 计数出现次数
from collections import Counter
class_counts = Counter(class_labels)
print(f"Class distribution: {dict(class_counts)}")
```

## 第 4 部分：用于不可变数据的元组

### 步骤 9：使用元组处理固定数据

```python
# 创建脚本: tuple_operations.py

# 模型元数据（不可变）
model_metadata = ("ResNet50", "1.0.0", "2024-10-18", 0.92)
model_name, version, date, accuracy = model_metadata  # 解包

print(f"Model: {model_name}")
print(f"Version: {version}")
print(f"Released: {date}")
print(f"Accuracy: {accuracy}")

# 元组的元组：训练历史
training_history = (
    (1, 0.85, 0.45),   # (epoch, accuracy, loss)
    (2, 0.88, 0.32),
    (3, 0.91, 0.25),
    (4, 0.92, 0.20),
    (5, 0.93, 0.18)
)

print("\nTraining History:")
for epoch, acc, loss in training_history:
    print(f"Epoch {epoch}: Accuracy={acc:.2f}, Loss={loss:.2f}")

# 找到最佳 epoch
best_epoch = max(training_history, key=lambda x: x[1])
print(f"Best epoch: {best_epoch[0]} with accuracy {best_epoch[1]}")

# 命名元组提高可读性
from collections import namedtuple

ModelConfig = namedtuple('ModelConfig',
                        ['name', 'layers', 'params', 'memory_mb'])

resnet_config = ModelConfig('ResNet50', 50, 25_500_000, 98)
vgg_config = ModelConfig('VGG16', 16, 138_000_000, 528)

print(f"\n{resnet_config.name}: {resnet_config.params:,} parameters")
print(f"{vgg_config.name}: {vgg_config.params:,} parameters")

# 比较内存
if resnet_config.memory_mb < vgg_config.memory_mb:
    print(f"{resnet_config.name} is more memory efficient")

# 元组作为字典键（不可变）
model_performance = {
    ('ResNet50', 'ImageNet'): 0.92,
    ('VGG16', 'ImageNet'): 0.88,
    ('ResNet50', 'CIFAR10'): 0.95,
}

key = ('ResNet50', 'ImageNet')
accuracy = model_performance[key]
print(f"\n{key[0]} on {key[1]}: {accuracy}")

# 从函数返回多个值
def train_model(epochs: int) -> tuple:
    """模拟训练，返回多个指标"""
    final_accuracy = 0.92
    final_loss = 0.15
    training_time = 3600  # 秒
    num_params = 25_500_000

    return final_accuracy, final_loss, training_time, num_params

# 解包返回值
acc, loss, time, params = train_model(50)
print(f"\nTraining complete:")
print(f"  Accuracy: {acc}")
print(f"  Loss: {loss}")
print(f"  Time: {time}s")
print(f"  Parameters: {params:,}")
```

## 第 5 部分：综合数据结构挑战

### 步骤 10：构建数据集管理器

```python
# 创建脚本: dataset_manager.py

from typing import Dict, List, Set, Tuple
from collections import defaultdict
import random

class MLDatasetManager:
    """使用所有数据结构的综合数据集管理器"""

    def __init__(self):
        # 字典：sample_id -> 样本数据
        self.samples: Dict[int, Dict] = {}

        # 集合：跟踪数据集划分
        self.train_ids: Set[int] = set()
        self.val_ids: Set[int] = set()
        self.test_ids: Set[int] = set()

        # 列表：维护类别标签的顺序
        self.class_names: List[str] = []

        # 字典：类别 -> 样本 ID 列表
        self.class_to_samples: Dict[str, List[int]] = defaultdict(list)

    def add_sample(self, sample_id: int, filepath: str,
                   class_label: str, metadata: Dict = None):
        """向数据集添加样本"""
        if sample_id in self.samples:
            raise ValueError(f"Sample {sample_id} already exists")

        self.samples[sample_id] = {
            'filepath': filepath,
            'class': class_label,
            'metadata': metadata or {}
        }

        # 更新类别跟踪
        if class_label not in self.class_names:
            self.class_names.append(class_label)

        self.class_to_samples[class_label].append(sample_id)

    def split_dataset(self, train_ratio: float = 0.7,
                     val_ratio: float = 0.15, seed: int = 42):
        """将数据集划分为 train/val/test"""
        random.seed(seed)

        all_ids = list(self.samples.keys())
        random.shuffle(all_ids)

        n = len(all_ids)
        train_end = int(n * train_ratio)
        val_end = train_end + int(n * val_ratio)

        self.train_ids = set(all_ids[:train_end])
        self.val_ids = set(all_ids[train_end:val_end])
        self.test_ids = set(all_ids[val_end:])

    def validate_splits(self) -> Tuple[bool, List[str]]:
        """验证数据集划分没有重叠"""
        issues = []

        # 检查重叠
        train_val = self.train_ids & self.val_ids
        if train_val:
            issues.append(f"Train-Val overlap: {len(train_val)} samples")

        train_test = self.train_ids & self.test_ids
        if train_test:
            issues.append(f"Train-Test overlap: {len(train_test)} samples")

        val_test = self.val_ids & self.test_ids
        if val_test:
            issues.append(f"Val-Test overlap: {len(val_test)} samples")

        # 检查所有样本是否已分配
        all_split_ids = self.train_ids | self.val_ids | self.test_ids
        if len(all_split_ids) != len(self.samples):
            issues.append("Not all samples assigned to splits")

        return len(issues) == 0, issues

    def get_class_distribution(self, split: str = 'train') -> Dict[str, int]:
        """获取划分的类别分布"""
        if split == 'train':
            split_ids = self.train_ids
        elif split == 'val':
            split_ids = self.val_ids
        elif split == 'test':
            split_ids = self.test_ids
        else:
            raise ValueError("Split must be 'train', 'val', or 'test'")

        distribution = {}
        for class_name in self.class_names:
            class_samples = set(self.class_to_samples[class_name])
            count = len(class_samples & split_ids)
            distribution[class_name] = count

        return distribution

    def get_summary(self) -> Dict:
        """获取数据集摘要统计"""
        return {
            'total_samples': len(self.samples),
            'num_classes': len(self.class_names),
            'classes': self.class_names,
            'train_samples': len(self.train_ids),
            'val_samples': len(self.val_ids),
            'test_samples': len(self.test_ids),
            'class_distribution': {
                cls: len(samples)
                for cls, samples in self.class_to_samples.items()
            }
        }

# 示例用法
manager = MLDatasetManager()

# 添加样本
samples_data = [
    (1, "/data/cat_001.jpg", "cat"),
    (2, "/data/dog_001.jpg", "dog"),
    (3, "/data/cat_002.jpg", "cat"),
    (4, "/data/bird_001.jpg", "bird"),
    (5, "/data/dog_002.jpg", "dog"),
    (6, "/data/cat_003.jpg", "cat"),
    (7, "/data/bird_002.jpg", "bird"),
    (8, "/data/dog_003.jpg", "dog"),
    (9, "/data/cat_004.jpg", "cat"),
    (10, "/data/bird_003.jpg", "bird"),
]

for sample_id, filepath, class_label in samples_data:
    manager.add_sample(sample_id, filepath, class_label)

# 划分数据集
manager.split_dataset(train_ratio=0.6, val_ratio=0.2, seed=42)

# 验证
is_valid, issues = manager.validate_splits()
print(f"Splits valid: {is_valid}")
if issues:
    for issue in issues:
        print(f"  - {issue}")

# 获取摘要
summary = manager.get_summary()
print(f"\nDataset Summary:")
for key, value in summary.items():
    print(f"  {key}: {value}")

# 检查分布
print("\nClass Distribution per Split:")
for split in ['train', 'val', 'test']:
    dist = manager.get_class_distribution(split)
    print(f"  {split}: {dist}")
```

## 验证与测试

```python
# 创建脚本: validate_exercise.py

def test_list_operations():
    """测试列表推导式"""
    numbers = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]

    # 测试过滤
    evens = [n for n in numbers if n % 2 == 0]
    assert evens == [2, 4, 6, 8, 10], "Even filter failed"

    # 测试转换
    squared = [n**2 for n in numbers]
    assert squared[0] == 1 and squared[-1] == 100, "Squaring failed"

    print("✓ List operations tests passed")

def test_dict_operations():
    """测试字典操作"""
    metrics = {"acc": 0.92, "loss": 0.15, "f1": 0.89}

    # 测试过滤
    high_metrics = {k: v for k, v in metrics.items() if v > 0.20}
    assert "loss" not in high_metrics, "Dict filtering failed"

    # 测试带默认值的 get
    lr = metrics.get("learning_rate", 0.001)
    assert lr == 0.001, "Dict get with default failed"

    print("✓ Dict operations tests passed")

def test_set_operations():
    """测试集合操作"""
    set_a = {1, 2, 3, 4, 5}
    set_b = {4, 5, 6, 7, 8}

    # 测试交集
    overlap = set_a & set_b
    assert overlap == {4, 5}, "Set intersection failed"

    # 测试并集
    combined = set_a | set_b
    assert len(combined) == 8, "Set union failed"

    # 测试差集
    only_a = set_a - set_b
    assert only_a == {1, 2, 3}, "Set difference failed"

    print("✓ Set operations tests passed")

def test_tuple_operations():
    """测试元组不可变性及用法"""
    config = ("model", "v1", 0.92)

    # 测试解包
    name, version, acc = config
    assert name == "model", "Tuple unpacking failed"

    # 测试不可变性
    try:
        config[0] = "new_model"
        assert False, "Tuple should be immutable"
    except TypeError:
        pass  # 预期行为

    print("✓ Tuple operations tests passed")

if __name__ == "__main__":
    test_list_operations()
    test_dict_operations()
    test_set_operations()
    test_tuple_operations()
    print("\n✓ All validation tests passed!")
```

## 反思问题

1. 何时应该使用列表而非元组来处理 ML 数据？
2. 为什么字典对存储配置很有用？
3. 集合如何帮助防止训练/测试划分中的数据泄露？
4. 列表推导式相比 for 循环有什么性能影响？
5. 如何高效处理包含数百万样本的数据集？
6. 何时应使用命名元组（named tuple）而不是字典？
7. 如何确保数据结构选择不会影响模型性能？

## 下一步

完成本练习后：
- **练习 03**：函数与模块 - 构建可复用的 ML 实用工具
- **练习 04**：文件 I/O - 读取和写入 ML 数据文件
- **第 2 课**：高级 Python 概念

## 额外资源

- Python 数据结构：https://docs.python.org/3/tutorial/datastructures.html
- 列表推导式指南：https://realpython.com/list-comprehension-python/
- Collections 模块：https://docs.python.org/3/library/collections.html
- 性能提示：https://wiki.python.org/moin/PythonSpeed/PerformanceTips

---

**恭喜！** 您已经掌握了用于 ML 数据处理的 Python 数据结构。这些技能是高效 ML 管道开发的基础。
