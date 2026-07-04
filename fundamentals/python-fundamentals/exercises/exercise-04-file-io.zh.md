# 练习04：ML 数据文件的读取与写入

## 概述

本练习学习如何高效读写 ML 工作流中常用的文件格式：CSV、JSON、YAML、pickle 和配置文件。你将掌握正确的文件处理、错误管理以及 ML 应用中数据持久化的最佳实践。
## 学习目标

完成本练习后，你将能够：- 使用上下文管理器熟练进行文件 I/O 操作
- 读写用于数据集存储的 CSV 文件
- 处理 JSON 格式的模型元数据和配置
- 使用 YAML 编写可读配置文件
- 使用 pickle 序列化 Python 对象
- 实现带有错误处理的安全文件操作
- 使用流式处理高效处理大文件
- 跨不同操作系统管理文件路径

## 前置条件

- 已完成练习 01-03
- 理解 Python 数据结构
- 文件系统基础知识

## 预计用时

- 预计：90-120 分钟
- Difficulty: 中级

## 第 1: CSV Files for Datasets

### 步骤 1: Reading CSV Files

```python
# 创建脚本： csv_operations.py

import csv
from typing import List, Dict, Tuple

def read_csv_basic(filepath: str) -> List[List[str]]:
    """读取 CSV 文件，返回行列表"""
    with open(filepath, 'r', encoding='utf-8') as file:
        reader = csv.reader(file)
        rows = list(reader)
    return rows

def read_csv_with_headers(filepath: str) -> Tuple[List[str], List[List[str]]]:
    """读取 CSV，表头和数据分开返回"""
    with open(filepath, 'r', encoding='utf-8') as file:
        reader = csv.reader(file)
        headers = next(reader)  # 第一行作为表头
        data = list(reader)
    return headers, data

def read_csv_as_dicts(filepath: str) -> List[Dict[str, str]]:
    """读取 CSV，返回字典列表"""
    with open(filepath, 'r', encoding='utf-8') as file:
        reader = csv.DictReader(file)
        data = list(reader)
    return data

def read_csv_filtered(filepath: str, condition: callable) -> List[Dict]:
    """读取 CSV，带过滤功能"""
    results = []
    with open(filepath, 'r', encoding='utf-8') as file:
        reader = csv.DictReader(file)
        for row in reader:
            if condition(row):
                results.append(row)
    return results

# 示例： Create sample dataset
def create_sample_dataset(filepath: str):
    """创建 ML 样本数据集"""
    with open(filepath, 'w', newline='', encoding='utf-8') as file:
        writer = csv.writer(file)

        # 写表头
        writer.writerow(['id', 'feature1', 'feature2', 'feature3', 'label'])

        # 写数据
        for i in range(100):
            writer.writerow([
                i,
                round(i * 0.5, 2),
                round(i * 1.2, 2),
                round(i * 0.8, 2),
                i % 2  # Binary label
            ])

    print(f"Created dataset: {filepath}")

# 使用示例
if __name__ == "__main__":
    # Create sample data
    create_sample_dataset("training_data.csv")

    # Read different ways
    print("=== Basic Read ===")
    rows = read_csv_basic("training_data.csv")
    print(f"Total rows: {len(rows)}")
    print(f"First 3 rows: {rows[:3]}")

    print("\n=== Read with Headers ===")
    headers, data = read_csv_with_headers("training_data.csv")
    print(f"Headers: {headers}")
    print(f"First data row: {data[0]}")

    print("\n=== Read as Dicts ===")
    dict_data = read_csv_as_dicts("training_data.csv")
    print(f"First record: {dict_data[0]}")

    print("\n=== Filtered Read ===")
    # 仅筛选正标签
    positive_samples = read_csv_filtered(
        "training_data.csv",
        lambda row: row['label'] == '1'
    )
    print(f"Positive samples: {len(positive_samples)}")
```

### 步骤 2: Writing CSV Files

```python
# 创建脚本： csv_writer.py

import csv
from typing import List, Dict

def write_csv_from_lists(filepath: str,
                        headers: List[str],
                        data: List[List]) -> None:
    """从列表的列表写入 CSV"""
    with open(filepath, 'w', newline='', encoding='utf-8') as file:
        writer = csv.writer(file)
        writer.writerow(headers)
        writer.writerows(data)

def write_csv_from_dicts(filepath: str,
                        data: List[Dict],
                        fieldnames: List[str] = None) -> None:
    """从字典列表写入 CSV"""
    if not data:
        return

    if fieldnames is None:
        fieldnames = list(data[0].keys())

    with open(filepath, 'w', newline='', encoding='utf-8') as file:
        writer = csv.DictWriter(file, fieldnames=fieldnames)
        writer.writeheader()
        writer.writerows(data)

def append_to_csv(filepath: str, row: Dict) -> None:
    """向已有 CSV 追加一行"""
    # 检查文件是否存在，决定是否需要写表头
    import os
    file_exists = os.path.isfile(filepath)

    with open(filepath, 'a', newline='', encoding='utf-8') as file:
        writer = csv.DictWriter(file, fieldnames=row.keys())
        if not file_exists:
            writer.writeheader()
        writer.writerow(row)

def write_predictions(filepath: str,
                     sample_ids: List[int],
                     predictions: List[float],
                     labels: List[int] = None) -> None:
    """将模型预测写入 CSV"""
    with open(filepath, 'w', newline='', encoding='utf-8') as file:
        headers = ['sample_id', 'prediction']
        if labels is not None:
            headers.append('true_label')

        writer = csv.writer(file)
        writer.writerow(headers)

        for i, (sid, pred) in enumerate(zip(sample_ids, predictions)):
            row = [sid, pred]
            if labels is not None:
                row.append(labels[i])
            writer.writerow(row)

# 使用示例
if __name__ == "__main__":
    # Write from lists
    headers = ['epoch', 'train_loss', 'val_loss', 'accuracy']
    training_history = [
        [1, 0.45, 0.52, 0.85],
        [2, 0.32, 0.38, 0.88],
        [3, 0.25, 0.30, 0.91],
    ]

    write_csv_from_lists("training_history.csv", headers, training_history)
    print("✓ Written training_history.csv")

    # Write from dicts
    experiments = [
        {'exp_id': 'exp001', 'model': 'resnet', 'accuracy': 0.92, 'runtime': 3600},
        {'exp_id': 'exp002', 'model': 'vgg', 'accuracy': 0.88, 'runtime': 4200},
        {'exp_id': 'exp003', 'model': 'mobilenet', 'accuracy': 0.85, 'runtime': 1800},
    ]

    write_csv_from_dicts("experiments.csv", experiments)
    print("✓ Written experiments.csv")

    # Append new experiment
    new_exp = {'exp_id': 'exp004', 'model': 'efficientnet', 'accuracy': 0.94, 'runtime': 2400}
    append_to_csv("experiments.csv", new_exp)
    print("✓ Appended to experiments.csv")

    # Write predictions
    write_predictions(
        "predictions.csv",
        sample_ids=[1, 2, 3, 4, 5],
        predictions=[0.92, 0.15, 0.88, 0.65, 0.95],
        labels=[1, 0, 1, 1, 1]
    )
    print("✓ Written predictions.csv")
```

## 第 2: JSON for Configuration and Metadata

### 步骤 3: Working with JSON

```python
# 创建脚本： json_operations.py

import json
from typing import Dict, Any, List
from pathlib import Path

def save_model_metadata(filepath: str, metadata: Dict[str, Any]) -> None:
    """保存模型元数据到 JSON 文件"""
    with open(filepath, 'w', encoding='utf-8') as file:
        json.dump(metadata, file, indent=2)

def load_model_metadata(filepath: str) -> Dict[str, Any]:
    """从 JSON 文件加载模型元数据"""
    with open(filepath, 'r', encoding='utf-8') as file:
        metadata = json.load(file)
    return metadata

def save_training_config(filepath: str, config: Dict) -> None:
    """保存训练配置"""
    with open(filepath, 'w', encoding='utf-8') as file:
        json.dump(config, file, indent=2, sort_keys=True)
    print(f"✓ Saved config to {filepath}")

def load_training_config(filepath: str) -> Dict:
    """加载训练配置"""
    try:
        with open(filepath, 'r', encoding='utf-8') as file:
            config = json.load(file)
        return config
    except FileNotFoundError:
        print(f"Config file not found: {filepath}")
        return {}
    except json.JSONDecodeError as e:
        print(f"Invalid JSON in {filepath}: {e}")
        return {}

def update_experiment_log(filepath: str, experiment: Dict) -> None:
    """向实验日志追加新记录"""
    # 加载已有日志
    if Path(filepath).exists():
        with open(filepath, 'r', encoding='utf-8') as file:
            log = json.load(file)
    else:
        log = {'experiments': []}

    # 添加新实验
    log['experiments'].append(experiment)

    # 保存更新后的日志
    with open(filepath, 'w', encoding='utf-8') as file:
        json.dump(log, file, indent=2)

def save_metrics_history(filepath: str, history: Dict[str, List[float]]) -> None:
    """保存训练指标历史"""
    with open(filepath, 'w', encoding='utf-8') as file:
        json.dump(history, file, indent=2)

# 使用示例
if __name__ == "__main__":
    # Model metadata
    metadata = {
        "model_name": "ResNet50",
        "version": "1.0.0",
        "framework": "pytorch",
        "input_shape": [3, 224, 224],
        "num_classes": 1000,
        "accuracy": 0.92,
        "trained_on": "2024-10-18",
        "hyperparameters": {
            "learning_rate": 0.001,
            "batch_size": 32,
            "epochs": 100
        }
    }

    save_model_metadata("model_metadata.json", metadata)
    print("✓ Saved model metadata")

    loaded_metadata = load_model_metadata("model_metadata.json")
    print(f"Loaded accuracy: {loaded_metadata['accuracy']}")

    # Training config
    config = {
        "model": {
            "type": "resnet50",
            "pretrained": True
        },
        "training": {
            "epochs": 100,
            "batch_size": 32,
            "learning_rate": 0.001,
            "optimizer": "adam"
        },
        "data": {
            "train_path": "/data/train",
            "val_path": "/data/val",
            "augmentation": True
        }
    }

    save_training_config("config.json", config)

    # Experiment logging
    experiment = {
        "id": "exp001",
        "timestamp": "2024-10-18T10:30:00",
        "model": "resnet50",
        "accuracy": 0.92,
        "loss": 0.15
    }

    update_experiment_log("experiments.json", experiment)
    print("✓ Logged experiment")

    # Metrics history
    history = {
        "epoch": [1, 2, 3, 4, 5],
        "train_loss": [0.45, 0.32, 0.25, 0.20, 0.18],
        "val_loss": [0.52, 0.38, 0.30, 0.28, 0.26],
        "accuracy": [0.85, 0.88, 0.91, 0.92, 0.93]
    }

    save_metrics_history("metrics_history.json", history)
    print("✓ Saved metrics history")
```

## 第 3: YAML for Human-Readable Configs

### 步骤 4: Working with YAML

```python
# 创建脚本： yaml_operations.py

import yaml
from typing import Dict, Any
from pathlib import Path

def save_yaml_config(filepath: str, config: Dict[str, Any]) -> None:
    """保存配置到 YAML 文件"""
    with open(filepath, 'w', encoding='utf-8') as file:
        yaml.dump(config, file, default_flow_style=False, sort_keys=False)

def load_yaml_config(filepath: str) -> Dict[str, Any]:
    """从 YAML 加载配置"""
    with open(filepath, 'r', encoding='utf-8') as file:
        config = yaml.safe_load(file)
    return config

def merge_configs(default_config: Dict, user_config: Dict) -> Dict:
    """将用户配置与默认配置合并"""
    merged = default_config.copy()
    merged.update(user_config)
    return merged

# 使用示例
if __name__ == "__main__":
    # Create ML pipeline config
    pipeline_config = {
        'model': {
            'name': 'ResNet50',
            'pretrained': True,
            'freeze_layers': 10
        },
        'training': {
            'epochs': 100,
            'batch_size': 32,
            'learning_rate': 0.001,
            'optimizer': {
                'type': 'adam',
                'betas': [0.9, 0.999],
                'weight_decay': 0.0001
            }
        },
        'data': {
            'train_path': '/data/train',
            'val_path': '/data/val',
            'test_path': '/data/test',
            'augmentation': {
                'horizontal_flip': True,
                'rotation': 15,
                'brightness': 0.2
            }
        },
        'logging': {
            'level': 'INFO',
            'save_dir': './logs',
            'tensorboard': True
        }
    }

    save_yaml_config("pipeline_config.yaml", pipeline_config)
    print("✓ Saved YAML config")

    loaded_config = load_yaml_config("pipeline_config.yaml")
    print(f"Loaded model: {loaded_config['model']['name']}")
    print(f"Batch size: {loaded_config['training']['batch_size']}")
```

## 第 4: Pickle for Python Objects

### 步骤 5: Serializing Python Objects

```python
# 创建脚本： pickle_operations.py

import pickle
from typing import Any, Dict, List

def save_object(filepath: str, obj: Any) -> None:
    """保存 Python 对象到 pickle 文件"""
    with open(filepath, 'wb') as file:
        pickle.dump(obj, file)

def load_object(filepath: str) -> Any:
    """从 pickle 文件加载 Python 对象"""
    with open(filepath, 'rb') as file:
        obj = pickle.load(file)
    return obj

class ModelCheckpoint:
    """模型检查点示例类"""

    def __init__(self, model_state: Dict, optimizer_state: Dict,
                 epoch: int, metrics: Dict):
        self.model_state = model_state
        self.optimizer_state = optimizer_state
        self.epoch = epoch
        self.metrics = metrics
        self.timestamp = "2024-10-18"

    def __repr__(self):
        return f"Checkpoint(epoch={self.epoch}, metrics={self.metrics})"

# 使用示例
if __name__ == "__main__":
    # Save simple objects
    data = {'accuracy': 0.92, 'loss': 0.15}
    save_object("metrics.pkl", data)
    print("✓ Saved metrics pickle")

    loaded_data = load_object("metrics.pkl")
    print(f"Loaded: {loaded_data}")

    # Save complex object
    checkpoint = ModelCheckpoint(
        model_state={'layer1.weight': [0.1, 0.2, 0.3]},
        optimizer_state={'lr': 0.001},
        epoch=50,
        metrics={'accuracy': 0.92, 'loss': 0.15}
    )

    save_object("checkpoint.pkl", checkpoint)
    print("✓ Saved checkpoint")

    loaded_checkpoint = load_object("checkpoint.pkl")
    print(f"Loaded: {loaded_checkpoint}")
```

## 第 5: Large File Processing

### 步骤 6: Streaming Large Files

```python
# 创建脚本： large_file_processing.py

from typing import Iterator, List, Dict
import csv

def read_csv_chunks(filepath: str,
                   chunk_size: int = 1000) -> Iterator[List[Dict]]:
    """分块读取大 CSV 文件"""
    with open(filepath, 'r', encoding='utf-8') as file:
        reader = csv.DictReader(file)

        chunk = []
        for row in reader:
            chunk.append(row)

            if len(chunk) >= chunk_size:
                yield chunk
                chunk = []

        # 返回剩余行
        if chunk:
            yield chunk

def process_large_dataset(filepath: str) -> Dict[str, float]:
    """分块处理大数据集"""
    total_samples = 0
    total_positive = 0

    for chunk in read_csv_chunks(filepath, chunk_size=100):
        total_samples += len(chunk)
        total_positive += sum(1 for row in chunk if row['label'] == '1')

    return {
        'total_samples': total_samples,
        'positive_ratio': total_positive / total_samples if total_samples > 0 else 0
    }

def read_file_lines(filepath: str) -> Iterator[str]:
    """逐行读取文件（内存友好）"""
    with open(filepath, 'r', encoding='utf-8') as file:
        for line in file:
            yield line.strip()

# 使用示例
if __name__ == "__main__":
    # 分块处理
    stats = process_large_dataset("training_data.csv")
    print(f"Dataset stats: {stats}")
```

## 第 6: Comprehensive File Manager

### 步骤 7: Build a Complete File Manager

```python
# 创建脚本： file_manager.py

import json
import csv
import yaml
import pickle
from pathlib import Path
from typing import Any, Dict, List, Union

class MLFileManager:
    """ML 工作流的综合文件管理器"""

    def __init__(self, base_dir: str = "."):
        self.base_dir = Path(base_dir)
        self.base_dir.mkdir(parents=True, exist_ok=True)

    def save(self, data: Any, filename: str, format: str = 'auto') -> None:
        """
        Save data in specified format.

        Args:
            data: Data to save
            filename: Output filename
            format: Format ('json', 'yaml', 'csv', 'pickle', or 'auto')
        """
        filepath = self.base_dir / filename

        # 根据扩展名自动检测格式
        if format == 'auto':
            format = filepath.suffix[1:]  # Remove dot

        if format == 'json':
            self._save_json(filepath, data)
        elif format == 'yaml' or format == 'yml':
            self._save_yaml(filepath, data)
        elif format == 'csv':
            self._save_csv(filepath, data)
        elif format == 'pkl' or format == 'pickle':
            self._save_pickle(filepath, data)
        else:
            raise ValueError(f"Unsupported format: {format}")

        print(f"✓ Saved {filename}")

    def load(self, filename: str, format: str = 'auto') -> Any:
        """从文件加载数据"""
        filepath = self.base_dir / filename

        if not filepath.exists():
            raise FileNotFoundError(f"File not found: {filepath}")

        if format == 'auto':
            format = filepath.suffix[1:]

        if format == 'json':
            return self._load_json(filepath)
        elif format == 'yaml' or format == 'yml':
            return self._load_yaml(filepath)
        elif format == 'csv':
            return self._load_csv(filepath)
        elif format == 'pkl' or format == 'pickle':
            return self._load_pickle(filepath)
        else:
            raise ValueError(f"Unsupported format: {format}")

    def _save_json(self, filepath: Path, data: Any) -> None:
        with open(filepath, 'w', encoding='utf-8') as f:
            json.dump(data, f, indent=2)

    def _load_json(self, filepath: Path) -> Any:
        with open(filepath, 'r', encoding='utf-8') as f:
            return json.load(f)

    def _save_yaml(self, filepath: Path, data: Any) -> None:
        with open(filepath, 'w', encoding='utf-8') as f:
            yaml.dump(data, f, default_flow_style=False)

    def _load_yaml(self, filepath: Path) -> Any:
        with open(filepath, 'r', encoding='utf-8') as f:
            return yaml.safe_load(f)

    def _save_csv(self, filepath: Path, data: List[Dict]) -> None:
        if not data:
            return

        with open(filepath, 'w', newline='', encoding='utf-8') as f:
            writer = csv.DictWriter(f, fieldnames=data[0].keys())
            writer.writeheader()
            writer.writerows(data)

    def _load_csv(self, filepath: Path) -> List[Dict]:
        with open(filepath, 'r', encoding='utf-8') as f:
            return list(csv.DictReader(f))

    def _save_pickle(self, filepath: Path, data: Any) -> None:
        with open(filepath, 'wb') as f:
            pickle.dump(data, f)

    def _load_pickle(self, filepath: Path) -> Any:
        with open(filepath, 'rb') as f:
            return pickle.load(f)

    def list_files(self, pattern: str = '*') -> List[str]:
        """列出匹配模式的文件"""
        return [f.name for f in self.base_dir.glob(pattern)]

# 使用示例
if __name__ == "__main__":
    manager = MLFileManager(base_dir="ml_data")

    # Save different formats
    config = {'model': 'resnet', 'lr': 0.001}
    manager.save(config, 'config.json')
    manager.save(config, 'config.yaml')

    # Save CSV
    data = [
        {'id': 1, 'accuracy': 0.92, 'loss': 0.15},
        {'id': 2, 'accuracy': 0.88, 'loss': 0.22}
    ]
    manager.save(data, 'results.csv')

    # Load back
    loaded_config = manager.load('config.json')
    print(f"Loaded config: {loaded_config}")

    # List files
    files = manager.list_files('*.json')
    print(f"JSON files: {files}")
```

## 验证

```python
# 创建脚本： validate_file_io.py

def validate_exercise():
    """验证文件 I/O 练习"""
    print("=== File I/O Validation ===\n")

    # 测试 CSV
    import csv
    with open('test.csv', 'w', newline='') as f:
        writer = csv.writer(f)
        writer.writerow(['a', 'b', 'c'])

    with open('test.csv', 'r') as f:
        reader = csv.reader(f)
        rows = list(reader)

    assert rows[0] == ['a', 'b', 'c'], "CSV test failed"
    print("✓ CSV operations work")

    # 测试 JSON
    import json
    data = {'test': 123}

    with open('test.json', 'w') as f:
        json.dump(data, f)

    with open('test.json', 'r') as f:
        loaded = json.load(f)

    assert loaded == data, "JSON test failed"
    print("✓ JSON operations work")

    print("\n✓ All validations passed!")

    # Cleanup
    import os
    os.remove('test.csv')
    os.remove('test.json')

if __name__ == "__main__":
    validate_exercise()
```

## 思考题

1. 什么时候应该用 CSV 而不是 JSON 来存储数据？2. 使用 pickle 有哪些安全隐患？3. 如何在不同操作系统上处理文件操作？4. 什么时候需要分块处理文件？5. 用于配置时，YAML 相比 JSON 有哪些优势？6. 如何确保文件操作是原子性和安全的？
## 下一步

- **练习05**：文件操作的健壮错误处理
- **练习06**：并发 I/O 的异步编程
- **第03讲**：Python DevOps 集成

## 补充资源

- CSV Module: https://docs.python.org/3/library/csv.html
- JSON Module: https://docs.python.org/3/library/json.html
- PyYAML: https://pyyaml.org/wiki/PyYAMLDocumentation
- Pickle Security: https://docs.python.org/3/library/pickle.html#module-pickle

---

**恭喜！** 你已掌握 ML 工作流的文件 I/O 操作，现在可以高效地跨多种格式持久化和加载数据。