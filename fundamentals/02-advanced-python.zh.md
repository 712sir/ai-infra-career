# 第二讲：面向基础设施的高级 Python — 类型提示、日志与配置

## 目录
1. [引言](#引言)
2. [类型提示与静态类型检查](#类型提示与静态类型检查)
3. [生产环境日志策略](#生产环境日志策略)
4. [配置管理](#配置管理)
5. [使用数据格式](#使用数据格式)
6. [错误处理模式](#错误处理模式)
7. [总结与最佳实践](#总结与最佳实践)

---

## 引言

### 生产代码的挑战

写出能跑的代码很简单。但要写出以下这样的代码：

- 在生产环境中**可靠运行**
- 出问题时**可以调试**
- 能被其他工程师**维护**
- **优雅处理**意外输入
- 从开发到企业级**可伸缩**

……这些才是基础设施工程真正的挑战。

本讲涵盖生产级 Python 的三大支柱：

1. **类型提示（Type Hints）**：让代码成为自文档，在运行前就捕获错误
2. **日志（Logging）**：了解生产系统中正在发生的事情
3. **配置管理（Configuration Management）**：让同一套代码在多个环境中运行

### 为什么这些对 AI 基础设施很重要

**类型提示**：机器学习流水线涉及复杂的数据结构（张量、数据框、模型配置）。类型提示可以防止把一个 `List[Dict]` 错误地传给期望 `pd.DataFrame` 的地方。

**日志**：当凌晨 3 点模型服务端点返回了错误的预测结果，日志是你唯一能看清发生了什么的手段。

**配置**：训练超参、模型路径、API 端点——这些在开发、预发布和生产环境之间各不相同。配置管理让这一切保持可维护。

### 学习目标

通过本讲的学习，你将能够：

- 编写全面带类型提示的 Python 代码
- 使用 mypy 进行静态类型检查
- 为生产系统实现结构化日志
- 为多环境设计配置系统
- 处理不同的数据格式（JSON、YAML、TOML）
- 在基础设施代码中应用错误处理模式

---

## 类型提示与静态类型检查

### 为什么需要类型提示？

考虑下面这个函数：

```python
def train_model(data, config, epochs):
    # 这些参数分别是什么类型？
    # data: DataFrame？List？numpy array？
    # config: dict？object？string path？
    # epochs: int？string？
    pass
```

现在加上类型提示：

```python
import pandas as pd
from typing import Dict, Any

def train_model(
    data: pd.DataFrame,
    config: Dict[str, Any],
    epochs: int
) -> Dict[str, float]:
    """使用给定的数据和配置训练机器学习模型。

    返回包含训练/验证损失的指标字典。
    """
    pass
```

**一目了然**：

- `data` 必须是一个 pandas DataFrame
- `config` 是一个键为字符串的字典
- `epochs` 是一个整数
- 返回一个将指标名映射到浮点数值的字典

### 基本类型注解

#### 基本类型（Primitive Types）

```python
# 基本类型
name: str = "model-v1"
version: int = 42
learning_rate: float = 0.001
is_training: bool = True

# 函数参数和返回值
def get_batch_size(training: bool) -> int:
    return 32 if training else 64

# None 类型
def log_message(message: str) -> None:
    print(message)
```

#### 集合类型（Collection Types）

```python
from typing import List, Dict, Set, Tuple

# 字符串列表
model_names: List[str] = ["bert", "gpt", "t5"]

# 字符串到整数的字典映射
layer_sizes: Dict[str, int] = {
    "input": 768,
    "hidden": 1024,
    "output": 512
}

# 唯一标识符的集合
seen_ids: Set[int] = {1, 2, 3}

# 固定大小和类型的元组
dimensions: Tuple[int, int, int] = (224, 224, 3)

# 变长元组（所有元素类型相同）
from typing import Tuple
scores: Tuple[float, ...] = (0.9, 0.85, 0.92, 0.88)
```

#### Optional 和 Union 类型

```python
from typing import Optional, Union

# Optional 表示"可以为 None"
def load_checkpoint(path: Optional[str] = None) -> Dict[str, Any]:
    if path is None:
        return {}
    # 从路径加载

# 现代语法（Python 3.10+）
def load_checkpoint(path: str | None = None) -> Dict[str, Any]:
    pass

# 多种类型的联合
from typing import Union
def process_input(data: Union[str, bytes, List[str]]) -> str:
    if isinstance(data, str):
        return data
    elif isinstance(data, bytes):
        return data.decode()
    else:
        return " ".join(data)

# 现代 Union 语法（Python 3.10+）
def process_input(data: str | bytes | List[str]) -> str:
    pass
```

#### 复杂类型

```python
from typing import List, Dict, Any, Callable

# 嵌套结构
ModelConfig = Dict[str, Any]
TrainingConfigs = Dict[str, ModelConfig]

configs: TrainingConfigs = {
    "bert": {"layers": 12, "hidden_size": 768},
    "gpt": {"layers": 24, "hidden_size": 1024}
}

# 可调用对象（函数）类型
ProcessingFunction = Callable[[str], str]

def apply_processing(text: str, func: ProcessingFunction) -> str:
    return func(text)

# 更具体的可调用对象类型
from typing import Callable
MetricCalculator = Callable[[List[float], List[float]], float]

def evaluate(
    predictions: List[float],
    labels: List[float],
    metric_fn: MetricCalculator
) -> float:
    return metric_fn(predictions, labels)
```

### 类型别名提升可读性

```python
from typing import Dict, List, Tuple, Any

# 定义一次，到处复用
ModelPath = str
Hyperparameters = Dict[str, Any]
TrainingData = List[Tuple[str, int]]
Metrics = Dict[str, float]

def train_model(
    model_path: ModelPath,
    hyperparams: Hyperparameters,
    data: TrainingData
) -> Metrics:
    """比直接使用原始类型可读性高得多"""
    pass

# 面向机器学习基础设施
import pandas as pd
import torch

DataFrame = pd.DataFrame
Tensor = torch.Tensor
Device = torch.device

def prepare_batch(
    df: DataFrame,
    device: Device
) -> Tensor:
    pass
```

### 高级类型提示

#### 泛型类型（Generic Types）

```python
from typing import TypeVar, Generic, List

T = TypeVar('T')

class DataLoader(Generic[T]):
    """适用于任何类型的泛型数据加载器"""

    def __init__(self, data: List[T]):
        self.data = data

    def get_batch(self, size: int) -> List[T]:
        return self.data[:size]

# 使用具体类型
int_loader: DataLoader[int] = DataLoader([1, 2, 3])
str_loader: DataLoader[str] = DataLoader(["a", "b", "c"])
```

#### 协议类型（Protocol Types）——结构化子类型

```python
from typing import Protocol

class ModelProtocol(Protocol):
    """任何拥有这些方法的类就是一个"Model" """

    def train(self, data: Any) -> None: ...
    def predict(self, input: Any) -> Any: ...

def train_and_evaluate(model: ModelProtocol, data: Any) -> float:
    """接受任何拥有 train() 和 predict() 方法的对象"""
    model.train(data)
    predictions = model.predict(data)
    return evaluate(predictions)

# 两者都可以使用，无需继承！
class PyTorchModel:
    def train(self, data): pass
    def predict(self, input): pass

class TensorFlowModel:
    def train(self, data): pass
    def predict(self, input): pass
```

#### 字面量类型（Literal Types）

```python
from typing import Literal

ModelType = Literal["bert", "gpt", "t5"]

def load_model(model_type: ModelType) -> Any:
    """model_type 必须恰好是这些字符串之一"""
    if model_type == "bert":
        return BertModel()
    elif model_type == "gpt":
        return GPTModel()
    else:
        return T5Model()

# 类型检查器确保只传入合法的值
load_model("bert")     # ✓ 正确
load_model("invalid")  # ✗ 类型错误
```

### 使用 mypy 进行类型检查

安装 mypy：

```bash
pip install mypy
```

**示例代码**（`training.py`）：

```python
from typing import List, Dict

def calculate_average(numbers: List[float]) -> float:
    return sum(numbers) / len(numbers)

def main() -> None:
    scores: List[float] = [0.9, 0.85, 0.92]
    avg: str = calculate_average(scores)  # 类型错误！
    print(avg)
```

**运行 mypy**：

```bash
mypy training.py
```

**输出**：

```
training.py:8: error: Incompatible types in assignment (expression has type "float", variable has type "str")
Found 1 error in 1 file (checked 1 source file)
```

#### Mypy 配置

创建 `mypy.ini` 或添加到 `pyproject.toml` 中：

```ini
# mypy.ini
[mypy]
python_version = 3.11
warn_return_any = True
warn_unused_configs = True
disallow_untyped_defs = True  # 所有函数都必须有类型注解
disallow_incomplete_defs = True
check_untyped_defs = True
no_implicit_optional = True
warn_redundant_casts = True
warn_unused_ignores = True
warn_unreachable = True
strict_equality = True

# 按模块配置
[mypy-numpy.*]
ignore_missing_imports = True  # Numpy 没有完整的类型存根

[mypy-pandas.*]
ignore_missing_imports = True
```

**或者在 pyproject.toml 中**：

```toml
[tool.mypy]
python_version = "3.11"
disallow_untyped_defs = true
warn_return_any = true
no_implicit_optional = true
```

#### 渐进式类型标注策略

不要一次标注所有内容。从以下步骤开始：

**第一步：标注函数签名**

```python
def train_model(config: Dict, data: Any) -> Any:
    # 函数体尚未标注类型
    pass
```

**第二步：完全标注关键函数**

```python
def train_model(
    config: Dict[str, Any],
    data: pd.DataFrame
) -> Dict[str, float]:
    epochs: int = config["epochs"]
    batch_size: int = config["batch_size"]
    # ...
    return {"loss": 0.5, "accuracy": 0.95}
```

**第三步：启用严格模式**

```python
# 添加到文件顶部
# mypy: strict

# 或使用 --strict 标志
# mypy --strict training.py
```

---

## 生产环境日志策略

### 为什么日志很重要

**场景**：模型服务 API 返回了错误的预测结果。如果没有日志：

- 不知道是什么输入导致了问题
- 不知道执行了哪条代码路径
- 无法复现错误
- 看不到性能指标

**有了正确的日志**：

- 追踪到具体哪个请求失败了
- 看到模型版本、输入特征、预测结果
- 识别出是数据问题、模型问题还是代码 bug
- 测量延迟、吞吐量和错误率

### Python 的 logging 模块

```python
import logging

# 基本日志记录
logging.debug("用于调试的详细信息")
logging.info("一般的信息性消息")
logging.warning("警告：发生了意外情况")
logging.error("错误：某个功能失败了")
logging.critical("严重错误：系统不可用")
```

**日志级别**：

```
DEBUG    (10): 详细的诊断信息
INFO     (20): 确认一切正常工作的消息
WARNING  (30): 发生了意外但已被处理的情况
ERROR    (40): 严重问题，函数执行失败
CRITICAL (50): 系统级故障
```

### 配置日志

#### 基本配置

```python
import logging

# 在应用启动时配置日志
logging.basicConfig(
    level=logging.INFO,
    format='%(asctime)s - %(name)s - %(levelname)s - %(message)s',
    datefmt='%Y-%m-%d %H:%M:%S'
)

logger = logging.getLogger(__name__)

logger.info("应用已启动")
logger.warning("未找到配置文件，使用默认配置")
```

**输出**：

```
2025-10-18 10:30:45 - __main__ - INFO - 应用已启动
2025-10-18 10:30:45 - __main__ - WARNING - 未找到配置文件，使用默认配置
```

#### 日志记录器层级

```python
# 文件: ml_pipeline/training/trainer.py
logger = logging.getLogger(__name__)  # 创建: ml_pipeline.training.trainer

# 文件: ml_pipeline/data/loader.py
logger = logging.getLogger(__name__)  # 创建: ml_pipeline.data.loader

# 配置根记录器或父记录器
logging.getLogger("ml_pipeline").setLevel(logging.INFO)
logging.getLogger("ml_pipeline.training").setLevel(logging.DEBUG)  # 更详细的输出
```

### 高级日志配置

#### 多个处理器（Handler）

```python
import logging
from logging.handlers import RotatingFileHandler
import sys

def setup_logging():
    # 创建记录器
    logger = logging.getLogger("ml_pipeline")
    logger.setLevel(logging.DEBUG)

    # 控制台处理器（INFO 及以上级别）
    console_handler = logging.StreamHandler(sys.stdout)
    console_handler.setLevel(logging.INFO)
    console_format = logging.Formatter(
        '%(asctime)s - %(name)s - %(levelname)s - %(message)s'
    )
    console_handler.setFormatter(console_format)

    # 文件处理器（DEBUG 及以上级别，带轮转）
    file_handler = RotatingFileHandler(
        'ml_pipeline.log',
        maxBytes=10*1024*1024,  # 10 MB
        backupCount=5
    )
    file_handler.setLevel(logging.DEBUG)
    file_format = logging.Formatter(
        '%(asctime)s - %(name)s - %(levelname)s - %(filename)s:%(lineno)d - %(message)s'
    )
    file_handler.setFormatter(file_format)

    # 添加处理器
    logger.addHandler(console_handler)
    logger.addHandler(file_handler)

    return logger

logger = setup_logging()
logger.info("日志配置完成")
```

#### 结构化日志（JSON 格式）

适用于集中式日志系统（ELK、Datadog、CloudWatch）：

```python
import logging
import json
from datetime import datetime

class JSONFormatter(logging.Formatter):
    def format(self, record: logging.LogRecord) -> str:
        log_data = {
            "timestamp": datetime.utcnow().isoformat(),
            "level": record.levelname,
            "logger": record.name,
            "message": record.getMessage(),
            "module": record.module,
            "function": record.funcName,
            "line": record.lineno
        }

        # 如有异常信息则添加
        if record.exc_info:
            log_data["exception"] = self.formatException(record.exc_info)

        # 添加自定义字段
        if hasattr(record, "user_id"):
            log_data["user_id"] = record.user_id
        if hasattr(record, "request_id"):
            log_data["request_id"] = record.request_id

        return json.dumps(log_data)

# 设置
handler = logging.StreamHandler()
handler.setFormatter(JSONFormatter())
logger = logging.getLogger("api")
logger.addHandler(handler)
logger.setLevel(logging.INFO)

# 使用额外上下文记录日志
logger.info(
    "模型预测完成",
    extra={
        "user_id": "user123",
        "request_id": "req-456",
        "model_version": "v2.1",
        "latency_ms": 45
    }
)
```

**输出**：

```json
{
  "timestamp": "2025-10-18T10:30:45.123456",
  "level": "INFO",
  "logger": "api",
  "message": "模型预测完成",
  "module": "serving",
  "function": "predict",
  "line": 42,
  "user_id": "user123",
  "request_id": "req-456",
  "model_version": "v2.1",
  "latency_ms": 45
}
```

### 机器学习系统的日志最佳实践

#### 1. 使用恰当的级别记录日志

```python
logger = logging.getLogger(__name__)

# DEBUG: 详细的诊断信息
logger.debug(f"正在处理批次 {batch_id}，形状: {data.shape}")
logger.debug(f"模型权重: {model.state_dict().keys()}")

# INFO: 主要步骤、里程碑
logger.info("模型 v2.1 开始训练")
logger.info(f"轮次 {epoch}/{total_epochs} 完成，损失: {loss:.4f}")
logger.info("模型已保存至 /models/checkpoint-100.pt")

# WARNING: 意外但已被处理的情况
logger.warning("GPU 不可用，退回到 CPU")
logger.warning(f"验证损失上升: {prev_loss:.4f} -> {curr_loss:.4f}")

# ERROR: 操作失败
logger.error(f"加载检查点失败: {checkpoint_path}")
logger.error("模型预测失败", exc_info=True)  # 包含回溯信息

# CRITICAL: 系统故障
logger.critical("内存不足，无法继续训练")
```

#### 2. 包含上下文信息

```python
# 不好：上下文不足
logger.info("训练完成")

# 好：包含相关细节
logger.info(
    f"训练完成 - 模型: {model_name}, "
    f"轮次: {epochs}, 最终损失: {final_loss:.4f}, "
    f"耗时: {duration:.2f}s"
)

# 不好：只有错误信息
logger.error("预测失败")

# 好：包含调试所需的上下文
logger.error(
    f"对输入形状 {input_shape} 的预测失败, "
    f"模型版本: {model_version}, "
    f"错误: {str(e)}"
)
```

#### 3. 使用结构化日志

```python
import logging
import structlog

# 配置 structlog
structlog.configure(
    processors=[
        structlog.stdlib.add_log_level,
        structlog.stdlib.add_logger_name,
        structlog.processors.TimeStamper(fmt="iso"),
        structlog.processors.JSONRenderer()
    ],
    wrapper_class=structlog.stdlib.BoundLogger,
    logger_factory=structlog.stdlib.LoggerFactory(),
)

logger = structlog.get_logger()

# 使用结构化上下文记录日志
logger.info(
    "model_prediction",
    model_id="bert-v2",
    input_length=512,
    prediction_confidence=0.95,
    latency_ms=23
)
```

#### 4. 使用上下文管理器实现请求追踪

```python
import logging
from contextlib import contextmanager
import uuid

logger = logging.getLogger(__name__)

@contextmanager
def request_context(request_id: str | None = None):
    """在上下文范围内的所有日志中添加请求 ID"""
    if request_id is None:
        request_id = str(uuid.uuid4())

    # 创建添加了 request_id 的日志适配器
    adapter = logging.LoggerAdapter(
        logger,
        {"request_id": request_id}
    )

    try:
        yield adapter
    finally:
        pass

# 使用
def handle_prediction(input_data):
    with request_context() as log:
        log.info("收到预测请求")

        result = model.predict(input_data)
        log.info(f"预测完成: {result}")

        return result

# 所有日志都会自动包含 request_id！
```

---

## 配置管理

### 配置管理的挑战

同一套代码，不同的环境：

```
开发环境（Development）:
- 模型: /local/models/dev-model.pt
- 数据库: localhost:5432
- 日志级别: DEBUG
- 批次大小: 8（较小，便于快速测试）

预发布环境（Staging）:
- 模型: s3://staging-models/model-v2.pt
- 数据库: staging-db.internal:5432
- 日志级别: INFO
- 批次大小: 32

生产环境（Production）:
- 模型: s3://prod-models/model-v2.1.pt
- 数据库: prod-db-replica.internal:5432
- 日志级别: WARNING
- 批次大小: 128
- TLS: 必须启用
```

**目标**：单一代码库，由配置驱动行为。

### 配置策略

#### 1. 环境变量

```python
import os

# 从环境变量中读取
MODEL_PATH = os.getenv("MODEL_PATH", "/default/model.pt")
BATCH_SIZE = int(os.getenv("BATCH_SIZE", "32"))
DEBUG_MODE = os.getenv("DEBUG", "false").lower() == "true"

# 验证必需的环境变量
DB_HOST = os.environ["DB_HOST"]  # 如果缺失则抛出 KeyError
```

**设置环境变量**：

```bash
# 开发环境
export MODEL_PATH=/local/models/dev-model.pt
export BATCH_SIZE=8
export DEBUG=true

# 或在一行中设置
MODEL_PATH=/local/models/dev-model.pt python train.py
```

#### 2. .env 文件

安装 python-dotenv：

```bash
pip install python-dotenv
```

**`.env` 文件**：

```bash
# .env
MODEL_PATH=/local/models/model.pt
BATCH_SIZE=32
LEARNING_RATE=0.001
DB_HOST=localhost
DB_PORT=5432
DB_PASSWORD=secretpassword
```

**在 Python 中加载**：

```python
from dotenv import load_dotenv
import os

# 加载 .env 文件
load_dotenv()

# 现在从环境变量中读取
model_path = os.getenv("MODEL_PATH")
batch_size = int(os.getenv("BATCH_SIZE"))
```

**多个环境文件**：

```bash
.env                 # 默认配置
.env.development     # 开发环境覆盖
.env.staging         # 预发布环境覆盖
.env.production      # 生产环境覆盖
```

```python
from dotenv import load_dotenv
import os

# 根据环境加载对应文件
env = os.getenv("ENVIRONMENT", "development")
load_dotenv(f".env.{env}")
```

#### 3. 配置文件（YAML）

**config.yaml**：

```yaml
# config.yaml
application:
  name: ml-training-pipeline
  version: 2.1.0

model:
  path: /models/bert-base
  type: bert
  max_length: 512

training:
  batch_size: 32
  learning_rate: 0.001
  epochs: 10
  device: cuda

database:
  host: localhost
  port: 5432
  name: ml_data
  pool_size: 10

logging:
  level: INFO
  format: json
  handlers:
    - type: console
    - type: file
      path: /var/log/ml-training.log
```

**加载 YAML 配置**：

```python
import yaml
from typing import Dict, Any

def load_config(path: str) -> Dict[str, Any]:
    with open(path, 'r') as f:
        return yaml.safe_load(f)

config = load_config('config.yaml')

batch_size = config['training']['batch_size']
model_path = config['model']['path']
db_host = config['database']['host']
```

#### 4. 使用 Pydantic 进行配置验证

```python
from pydantic import BaseModel, Field, validator
from typing import Literal
import yaml

class ModelConfig(BaseModel):
    path: str
    type: Literal["bert", "gpt", "t5"]
    max_length: int = Field(gt=0, le=2048)

class TrainingConfig(BaseModel):
    batch_size: int = Field(gt=0)
    learning_rate: float = Field(gt=0, lt=1)
    epochs: int = Field(gt=0)
    device: Literal["cuda", "cpu"] = "cuda"

    @validator("batch_size")
    def validate_batch_size(cls, v):
        if v % 8 != 0:
            raise ValueError("batch_size 必须是 8 的倍数")
        return v

class DatabaseConfig(BaseModel):
    host: str
    port: int = Field(ge=1, le=65535)
    name: str
    pool_size: int = Field(default=10, ge=1)

class AppConfig(BaseModel):
    model: ModelConfig
    training: TrainingConfig
    database: DatabaseConfig

# 加载并验证
with open('config.yaml') as f:
    config_dict = yaml.safe_load(f)

config = AppConfig(**config_dict)  # 验证所有字段！

# 类型安全的访问
batch_size: int = config.training.batch_size
model_path: str = config.model.path
```

**优势**：

- 类型安全
- 自动验证
- 清晰的错误消息
- IDE 自动补全
- 通过字段描述提供文档

#### 5. 层级化配置

```python
from pathlib import Path
import yaml
from typing import Dict, Any

class Config:
    def __init__(self, environment: str = "development"):
        self.environment = environment
        self._config = self._load_config()

    def _load_config(self) -> Dict[str, Any]:
        """加载基础配置 + 环境特定的覆盖"""
        # 加载基础配置
        base_config = self._load_yaml("config.yaml")

        # 加载环境特定的覆盖
        env_config_path = f"config.{self.environment}.yaml"
        if Path(env_config_path).exists():
            env_config = self._load_yaml(env_config_path)
            base_config = self._deep_merge(base_config, env_config)

        # 用环境变量进行覆盖
        self._apply_env_overrides(base_config)

        return base_config

    def _load_yaml(self, path: str) -> Dict[str, Any]:
        with open(path) as f:
            return yaml.safe_load(f)

    def _deep_merge(
        self,
        base: Dict[str, Any],
        override: Dict[str, Any]
    ) -> Dict[str, Any]:
        """递归地将覆盖配置合并到基础配置中"""
        result = base.copy()
        for key, value in override.items():
            if key in result and isinstance(result[key], dict) and isinstance(value, dict):
                result[key] = self._deep_merge(result[key], value)
            else:
                result[key] = value
        return result

    def _apply_env_overrides(self, config: Dict[str, Any]) -> None:
        """通过环境变量覆盖配置"""
        import os

        # ML_TRAINING_BATCH_SIZE -> config['training']['batch_size']
        # ML_MODEL_PATH -> config['model']['path']
        for key, value in os.environ.items():
            if key.startswith("ML_"):
                self._set_nested(config, key[3:].lower().split('_'), value)

    def _set_nested(self, d: Dict, keys: list, value: str) -> None:
        """通过键路径设置嵌套字典的值"""
        for key in keys[:-1]:
            d = d.setdefault(key, {})
        # 尝试转换为合适的类型
        try:
            d[keys[-1]] = int(value)
        except ValueError:
            try:
                d[keys[-1]] = float(value)
            except ValueError:
                d[keys[-1]] = value

# 使用
config = Config(environment="production")
```

**配置优先级**（从高到低）：

1. 环境变量（最高优先级）
2. 环境特定的配置文件（config.production.yaml）
3. 基础配置文件（config.yaml）
4. 代码默认值（最低优先级）

---

## 使用数据格式

### JSON

```python
import json
from typing import Dict, Any

# 写入 JSON
config: Dict[str, Any] = {
    "model": "bert-base",
    "batch_size": 32,
    "learning_rate": 0.001
}

with open("config.json", "w") as f:
    json.dump(config, f, indent=2)

# 读取 JSON
with open("config.json", "r") as f:
    loaded_config = json.load(f)

# JSON 字符串
json_string = json.dumps(config)
parsed = json.loads(json_string)
```

### YAML

```python
import yaml

# 写入 YAML
config = {
    "model": {
        "name": "bert-base",
        "params": {
            "hidden_size": 768,
            "num_layers": 12
        }
    }
}

with open("config.yaml", "w") as f:
    yaml.dump(config, f, default_flow_style=False)

# 读取 YAML
with open("config.yaml", "r") as f:
    loaded = yaml.safe_load(f)  # 务必使用 safe_load！
```

### TOML

```python
import tomli  # Python 3.11+ 标准库中内置 tomllib
import tomli_w

# 写入 TOML
config = {
    "model": {
        "name": "bert-base",
        "hidden_size": 768
    },
    "training": {
        "batch_size": 32,
        "epochs": 10
    }
}

with open("config.toml", "wb") as f:
    tomli_w.dump(config, f)

# 读取 TOML
with open("config.toml", "rb") as f:
    loaded = tomli.load(f)
```

---

## 错误处理模式

### 具体的异常处理

```python
import logging
from typing import Optional

logger = logging.getLogger(__name__)

def load_model(path: str) -> Optional[Any]:
    try:
        model = torch.load(path)
        logger.info(f"模型已从 {path} 加载")
        return model
    except FileNotFoundError:
        logger.error(f"未找到模型文件: {path}")
        return None
    except torch.serialization.SerializationError:
        logger.error(f"模型文件已损坏: {path}")
        return None
    except Exception as e:
        logger.error(f"加载模型时发生意外错误: {e}", exc_info=True)
        raise
```

### 基础设施中的重试逻辑

```python
import time
import logging
from typing import Callable, TypeVar, Any

logger = logging.getLogger(__name__)
T = TypeVar('T')

def retry(
    func: Callable[..., T],
    max_attempts: int = 3,
    delay: float = 1.0,
    backoff: float = 2.0
) -> T:
    """使用指数退避重试函数"""
    attempt = 0
    current_delay = delay

    while attempt < max_attempts:
        try:
            return func()
        except Exception as e:
            attempt += 1
            if attempt >= max_attempts:
                logger.error(f"经过 {max_attempts} 次尝试后失败")
                raise

            logger.warning(
                f"第 {attempt} 次尝试失败: {e}，"
                f"将在 {current_delay}s 后重试..."
            )
            time.sleep(current_delay)
            current_delay *= backoff

# 使用
def fetch_data():
    # 可能因为网络问题而失败
    response = requests.get("https://api.example.com/data")
    response.raise_for_status()
    return response.json()

data = retry(fetch_data, max_attempts=5, delay=2.0)
```

---

## 总结与最佳实践

### 类型提示检查清单

✅ 为所有函数签名添加注解
✅ 对复杂类型使用类型别名
✅ 在 CI/CD 中启用 mypy
✅ 对可空值使用 `Optional[T]`
✅ 利用 `Protocol` 实现灵活的接口
✅ 对固定的字符串选项使用 `Literal`

### 日志检查清单

✅ 在应用启动时配置日志
✅ 使用恰当的日志级别（DEBUG、INFO、WARNING、ERROR、CRITICAL）
✅ 在日志消息中包含上下文
✅ 在生产环境中使用结构化日志（JSON 格式）
✅ 为文件处理器实现日志轮转
✅ 绝不记录敏感数据（密码、令牌）

### 配置检查清单

✅ 绝不硬编码配置
✅ 对部署相关的配置使用环境变量
✅ 在开发环境中使用 `.env` 文件
✅ 在启动时验证配置
✅ 为所有配置选项编写文档
✅ 提供合理的默认值
✅ 使用配置层级（基础配置 + 覆盖）

---

**讲义版本**：1.0
**最后更新**：2025 年 10 月
**字数**：约 4,200 字
**预计阅读时间**：50-70 分钟

**下一讲**：继续阅读 `03-python-devops.md`，学习子进程管理、文件操作和命令行开发。
