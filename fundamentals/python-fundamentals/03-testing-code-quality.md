# Python 测试与代码质量

> 来源：初级工程师 M001 · 第 05 讲 | 状态：✅ 已学

---

## 1. pytest 核心用法

### 基本测试

```python
# src/calc.py
def divide(a, b):
    if b == 0:
        raise ValueError("Cannot divide by zero")
    return a / b

# tests/test_calc.py
import pytest
from src.calc import divide

def test_divide():
    assert divide(10, 2) == 5.0

def test_divide_by_zero():
    with pytest.raises(ValueError, match="Cannot divide by zero"):
        divide(10, 0)
```

### 夹具（fixture）— 复用测试数据

```python
@pytest.fixture
def sample_config():
    return {"model_name": "test", "version": "1.0"}

def test_init(sample_config):        # 自动注入
    model = MLModel(sample_config)
    assert model.name == "test"
```

### 参数化 — 一个测函数覆盖多组数据

```python
@pytest.mark.parametrize("a,b,expected", [
    (2, 3, 5), (-5, 3, -2), (0, 0, 0)
])
def test_add(a, b, expected):
    assert add(a, b) == expected
```

### 异步测试

```python
@pytest.mark.asyncio
async def test_async_predict():
    async with AsyncModelClient() as client:
        result = await client.predict({"x": [1,2,3]})
        assert "prediction" in result
```

### Mock — 隔离外部依赖

```python
from unittest.mock import Mock, AsyncMock, patch

def test_with_mock_db():
    mock_db = Mock()
    mock_db.query.return_value = [{"id": 1}]
    store = DataStore(mock_db)
    assert len(store.get_all()) == 1
    mock_db.query.assert_called_once()

# 异步 mock
async def test_async_api():
    with patch("httpx.AsyncClient.post", AsyncMock(return_value={"ok": True})):
        client = ModelAPIClient()
        result = await client.predict({"x": [1]})
        assert result["ok"] is True
```

---

## 2. pytest 配置

```ini
# pytest.ini
[pytest]
testpaths = tests
asyncio_mode = auto          # 自动识别 @pytest.mark.asyncio

addopts = -v --tb=short --strict-markers
```

### 常用命令

```bash
pytest tests/ -v                          # 跑全部
pytest tests/test_models.py -v            # 跑单个文件
pytest tests/ -v -k "test_model_deploy"   # 按名字筛选
pytest tests/ --cov=src --cov-report=term # 覆盖率
pytest tests/ --cov=src --cov-fail-under=80  # 低于 80% 视为失败
```

---

## 3. 代码质量三件套

| 工具 | 干什么 | 命令 |
|------|--------|------|
| **Black** | 自动格式化 | `black src/ tests/` |
| **Ruff** | 代码检查（lint） | `ruff check src/ --fix` |
| **mypy** | 类型检查 | `mypy src/` |

### pyproject.toml 配置

```toml
[tool.black]
line-length = 100
target-version = ['py311']

[tool.ruff]
line-length = 100
select = ["E", "W", "F", "I", "B", "C4", "UP"]

[tool.isort]
profile = "black"
```

---

## 4. Pre-commit — 提交前自动检查

装一次，以后每次 `git commit` 自动跑。

```bash
pip install pre-commit
pre-commit install
```

`.pre-commit-config.yaml`（精简版）：

```yaml
repos:
  - repo: https://github.com/psf/black
    rev: 23.11.0
    hooks: [{id: black}]
  - repo: https://github.com/charliermarsh/ruff-pre-commit
    rev: v0.1.6
    hooks: [{id: ruff, args: [--fix]}]
  - repo: https://github.com/pre-commit/mirrors-mypy
    rev: v1.7.1
    hooks: [{id: mypy}]
```

---

## 5. 日常开发流程

```bash
black src/ tests/ && isort src/ tests/   # 格式化
ruff check src/ --fix                     # 检查
mypy src/                                 # 类型
pytest tests/ -v --cov=src                # 测试 + 覆盖率
```

或者一个 Makefile 搞定：

```makefile
quality:
	black src/ tests/ && isort src/ tests/
	ruff check src/ --fix
	mypy src/
	pytest tests/ -v --cov=src --cov-fail-under=70
```

---

## 6. 边界条件检查清单

每写一个函数，测试至少覆盖：

- 正常输入
- 空输入 / 零值
- 非法输入（抛异常）
- 边界值（最大/最小）
- 并发（如果是 async）
