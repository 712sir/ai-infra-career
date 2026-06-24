# 高级 Python：类型提示、日志与配置 — 实践指南

> 来源：初级工程师 M001 · 第 02 讲 + 实际工程经验
> 状态：✅ 已学 | 三大支柱：Type Hints → Logging → Config

---

## 1. 为什么需要类型提示

### 1.1 问题场景

```python
# 不看代码根本不知道参数和返回值是什么类型
def train_model(data, config, epochs):
    # data 是 DataFrame？List？numpy array？
    # config 是 dict？object？路径字符串？
    pass
```

维护别人的代码时这种情况极其痛苦——必须通读全部源码才能知道怎么调用。

### 1.2 加了类型提示之后

```python
import pandas as pd
from typing import Dict, Any

def train_model(
    data: pd.DataFrame,
    config: Dict[str, Any],
    epochs: int
) -> Dict[str, float]:
    """训练 ML 模型，返回训练/验证损失"""
    pass
```

一眼看清：`data` 是 DataFrame，`config` 是字典，返回指标字典。IDE 还能自动补全。

---

## 2. 类型提示速查

### 2.1 基础类型

```python
name: str = "model-v1"
version: int = 42
lr: float = 0.001
is_train: bool = True

def get_batch_size(training: bool) -> int:
    return 32 if training else 64
```

### 2.2 集合类型

```python
from typing import List, Dict, Set, Tuple, Optional, Union

model_names: List[str] = ["bert", "gpt"]
layer_sizes: Dict[str, int] = {"input": 768, "hidden": 1024}
seen_ids: Set[int] = {1, 2, 3}
dimensions: Tuple[int, int, int] = (224, 224, 3)

# 可以为 None
def load_checkpoint(path: Optional[str] = None) -> Dict[str, Any]: ...

# 多种类型（Python 3.10+）
def process(data: str | bytes | List[str]) -> str: ...
```

### 2.3 实用模式

```python
from typing import Callable, Literal, TypeVar, Generic

# 函数类型
Processor = Callable[[str], str]

# 限定值范围
ModelType = Literal["bert", "gpt", "t5"]
def load_model(mtype: ModelType): ...

# 泛型——任何类型都适用
T = TypeVar('T')
class DataLoader(Generic[T]):
    def __init__(self, data: List[T]): ...
    def get_batch(self, size: int) -> List[T]: ...
```

### 2.4 类型别名——提升可读性

```python
ModelPath = str
Hyperparams = Dict[str, Any]
Metrics = Dict[str, float]

def train(model: ModelPath, hp: Hyperparams) -> Metrics: ...
```

---

## 3. 生产环境日志

### 3.1 为什么 print() 不够用

| | print() | logging |
|------|:--:|:--:|
| 级别控制（DEBUG/INFO/WARNING/ERROR）| ❌ | ✅ |
| 输出到文件+控制台 | ❌ | ✅ |
| 自动带时间戳 | ❌ | ✅ |
| 生产环境关闭 DEBUG | ❌ | ✅ |
| 结构化 JSON 输出 | ❌ | ✅ |

### 3.2 标准配置（复制即用）

```python
import logging

logging.basicConfig(
    level=logging.INFO,
    format='%(asctime)s | %(levelname)-8s | %(name)s | %(message)s',
    datefmt='%Y-%m-%d %H:%M:%S'
)

logger = logging.getLogger(__name__)
logger.info("服务启动")
logger.warning("配置文件缺失，使用默认配置")
logger.error("模型加载失败", exc_info=True)
```

**日志级别使用原则**：

| 级别 | 什么时候用 | 例子 |
|------|------|------|
| DEBUG | 本地调试的详细信息 | 变量值、中间步骤 |
| INFO | 正常业务流程节点 | "训练开始" "模型保存" |
| WARNING | 异常但能自动处理 | "GPU 不可用，降级到 CPU" |
| ERROR | 功能失败需人工介入 | "数据库连接失败" |
| CRITICAL | 系统级崩溃 | "内存耗尽无法恢复" |

### 3.3 生产级配置——控制台+文件双输出

```python
import logging
from logging.handlers import RotatingFileHandler

logger = logging.getLogger("ml_pipeline")
logger.setLevel(logging.DEBUG)

# 控制台输出 INFO 及以上
console = logging.StreamHandler()
console.setLevel(logging.INFO)
console.setFormatter(logging.Formatter('%(asctime)s | %(levelname)s | %(message)s'))
logger.addHandler(console)

# 文件输出 DEBUG 及以上，自动轮转（10MB × 5 个备份）
file_handler = RotatingFileHandler('pipeline.log', maxBytes=10*1024*1024, backupCount=5)
file_handler.setLevel(logging.DEBUG)
file_handler.setFormatter(logging.Formatter(
    '%(asctime)s | %(levelname)s | %(filename)s:%(lineno)d | %(message)s'
))
logger.addHandler(file_handler)
```

### 3.4 日志中要包含上下文

```python
# ❌ 上下文不足
logger.info("训练完成")

# ✅ 有关键指标
logger.info(f"训练完成 | 模型={model_name} | 轮次={epoch} | 损失={loss:.4f} | 耗时={duration:.1f}s")

# ❌ 只有错误信息
logger.error("预测失败")

# ✅ 含调试所需的全部上下文
logger.error(f"预测失败 | 输入形状={shape} | 模型={version} | 异常={e}", exc_info=True)
```

---

## 4. 配置管理

### 4.1 核心原则

> 同一套代码，不同环境用不同配置。绝不把路径和密钥写死在代码里。

### 4.2 三层配置策略

```
优先级：环境变量 > .env 文件 > 代码默认值
```

```python
import os
from dotenv import load_dotenv

load_dotenv()  # 自动加载项目根目录 .env

# 读环境变量 + 给默认值
MODEL_PATH = os.getenv("MODEL_PATH", "/default/model.pt")
BATCH_SIZE = int(os.getenv("BATCH_SIZE", "32"))
DEBUG = os.getenv("DEBUG", "false").lower() == "true"

# 必需变量——缺失直接报错，不偷偷用默认值
DB_HOST = os.environ["DB_HOST"]
```

### 4.3 YAML 配置（推荐用于复杂配置）

```yaml
# config.yaml
model:
  name: bert-base
  max_length: 512

training:
  batch_size: 32
  learning_rate: 0.001
  epochs: 10
  device: cuda

database:
  host: localhost
  port: 5432
```

```python
import yaml

with open('config.yaml') as f:
    config = yaml.safe_load(f)

batch_size = config['training']['batch_size']
db_host = config['database']['host']
```

### 4.4 Pydantic 验证（正式项目用）

```python
from pydantic import BaseModel, Field
from typing import Literal

class TrainingConfig(BaseModel):
    batch_size: int = Field(gt=0, description="批次大小，必须为正数")
    learning_rate: float = Field(gt=0, lt=1)
    epochs: int = Field(gt=0)
    device: Literal["cuda", "cpu"] = "cuda"

# 加载 + 自动验证所有字段
config = TrainingConfig(**yaml.safe_load(open('config.yaml')))
# 类型错误或值不合法会在启动时就报错，不会跑到一半才炸
```

---

## 5. 错误处理模式

### 5.1 具体的异常处理

```python
def load_model(path: str):
    try:
        return torch.load(path)
    except FileNotFoundError:
        logger.error(f"模型文件不存在: {path}")
        return None
    except torch.serialization.SerializationError:
        logger.error(f"模型文件损坏: {path}")
        return None
    except Exception as e:
        logger.error(f"未知错误: {e}", exc_info=True)
        raise  # 意料之外的错误向上抛
```

### 5.2 带指数退避的重试

```python
import time

def retry(func, max_attempts=3, delay=1.0, backoff=2.0):
    """指数退避重试：1s → 2s → 4s"""
    current_delay = delay
    for attempt in range(1, max_attempts + 1):
        try:
            return func()
        except Exception as e:
            if attempt == max_attempts:
                raise
            logger.warning(f"第 {attempt} 次失败，{current_delay}s 后重试: {e}")
            time.sleep(current_delay)
            current_delay *= backoff

# 用：网络请求失败自动重试 5 次
data = retry(lambda: requests.get("https://api.example.com/data").json(),
             max_attempts=5, delay=2.0)
```

---

## 6. 日常习惯检查清单

| 习惯 | 说明 |
|------|------|
| 新函数加类型提示 | 至少标注参数和返回值 |
| CI 里跑 mypy | 提交前自动检查类型错误 |
| 用 logger 不用 print | print 无法控制级别和输出目标 |
| DEBUG 放细节，INFO 放流程节点 | 生产环境设 INFO，出问题再开 DEBUG |
| 日志里带上下文 | 每行日志都足够独立排障 |
| 配置不硬编码 | 用环境变量 + .env + YAML |
| 异常具体捕获 | 不用裸露 `except:` 偷懒 |

---

## 7. 快速参考

```python
# === 类型提示 ===
name: str = "v1"
scores: List[float] = [0.9, 0.8]
config: Dict[str, Any] = {}
def fn(x: int) -> Optional[str]: ...

# === 日志 ===
import logging
logger = logging.getLogger(__name__)
logger.info("msg")
logger.error("msg", exc_info=True)   # 带完整堆栈

# === 配置 ===
import os
val = os.getenv("KEY", "default")
from dotenv import load_dotenv; load_dotenv()

# === 错误处理 ===
try: ...
except SpecificError: ...
except Exception as e: logger.error(...); raise
```

---

*来源：初级工程师 M001 第 02 讲 + 实践补充 | 整理日期：2026-06-23*
