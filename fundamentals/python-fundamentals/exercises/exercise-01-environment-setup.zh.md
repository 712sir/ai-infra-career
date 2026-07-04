# 练习 01：Python 环境设置与管理（Python Environment Setup and Management）

## 目标（Objective）

为一个 ML 训练项目设置完整的 Python 开发环境，包含适当的依赖管理、可复现的配置和自动化脚本。
## 学习成果（Learning Outcomes）

完成本练习后，您将能够：- 创建和管理虚拟环境
- 编写全面的 requirements 文件
- 按照最佳实践建立项目结构
- 创建环境设置的自动化脚本
- 为团队成员记录设置过程

## 先决条件（Prerequisites）

- 已安装 Python 3.11+
- 基本的命令行知识
- 文本编辑器或 IDE

## 项目场景（Project Scenario）

您正在加入一个 AI 基础设施团队。您的第一个任务是为一个名为 "sentiment-classifier" 的新机器学习训练管道项目建立一个可复现的开发环境。
## 第 1 部分：项目结构设置（15 分钟）

### 任务 1.1：创建项目目录结构

创建以下目录结构：

```
sentiment-classifier/
├── .gitignore
├── README.md
├── requirements.txt
├── requirements-dev.txt
├── setup.sh
├── .env.example
├── src/
│   ├── __init__.py
│   ├── train.py
│   ├── evaluate.py
│   └── utils/
│       ├── __init__.py
│       ├── data_loader.py
│       └── metrics.py
├── tests/
│   ├── __init__.py
│   ├── test_data_loader.py
│   └── test_metrics.py
├── data/
│   └── .gitkeep
├── models/
│   └── .gitkeep
└── configs/
    ├── training_config.yaml
    └── model_config.yaml
```

**TODO**：创建此目录结构。使用 `mkdir -p` 和 `touch` 命令，或者编写一个 Python 脚本。
**需要思考的问题：**- 为什么要包含 `__init__.py` 文件？
- `.gitkeep` 文件的作用是什么？
- 为什么要将 `src/` 和 `tests/` 分开？

### 任务 1.2：创建 .gitignore 文件

创建一个包含 Python ML 项目合适模式的 `.gitignore` 文件：
```gitignore
# TODO: 添加要忽略的模式：
# - 虚拟环境（venv, .venv, env, virtualenv）
# - Python 缓存文件（__pycache__, *.pyc, *.pyo, *.pyd）
# - IDE 文件（.vscode/, .idea/, *.swp）
# - 环境文件（.env, .env.local）
# - 模型文件（*.pt, *.pth, *.h5, *.ckpt）
# - 数据文件（data/*.csv, data/*.json，但保留 .gitkeep）
# - 日志文件（*.log, logs/）
# - 分发文件（dist/, build/, *.egg-info/）
```

**TODO**：用适当的模式完成 `.gitignore` 文件。
## 第 2 部分：虚拟环境管理（20 分钟）

### 任务 2.1：创建虚拟环境

**TODO**：使用 venv 创建虚拟环境：
```bash
# 创建虚拟环境的命令
# TODO: 完成此命令
python -m venv _____
```

**问题：**
- 虚拟环境内部创建了哪些目录？
- 当环境激活时，包被安装到哪里？

### 任务 2.2：激活脚本测试

**TODO**：
1. 激活虚拟环境
2. 通过检查 `which python`（Linux/Mac）或 `where python`（Windows）来验证激活3. 检查 Python 版本：`python --version`4. 验证 pip 位置：`which pip` 或 `where pip`
记录您的发现：
```
激活前:
  Python 位置: _____
  Pip 位置: _____

激活后:
  Python 位置: _____
  Pip 位置: _____
```

### 任务 2.3：多环境测试

创建两个独立的虚拟环境以理解隔离：
```bash
# 环境 1: 用于 Python 3.11 开发
# TODO: 创建 venv-py311

# 环境 2: 用于 Python 3.10 测试
# TODO: 创建 venv-py310（如果您安装了 Python 3.10）
```

**TODO**：在每个环境中安装不同版本的包：- venv-py311：安装 `numpy==1.24.0`
- venv-py310：安装 `numpy==1.23.0`

通过激活每个环境并运行以下命令来验证隔离：```python
import numpy
print(numpy.__version__)
```

## 第 3 部分：依赖管理（30 分钟）

### 任务 3.1：创建 requirements.txt

该项目需要以下生产依赖：
**TODO**：创建带有固定版本的 `requirements.txt`：
```txt
# 核心 ML 框架
# TODO: 添加 torch 2.1.0
# TODO: 添加 torchvision 0.16.0
# TODO: 添加 transformers 4.35.0

# 数据处理
# TODO: 添加 pandas 2.1.0
# TODO: 添加 numpy 1.24.0
# TODO: 添加 scikit-learn 1.3.0

# 配置和工具
# TODO: 添加 pyyaml 6.0.1
# TODO: 添加 python-dotenv 1.0.0
# TODO: 添加 tqdm 4.66.1

# API 和服务（用于后续模块）
# TODO: 添加 fastapi 0.104.1
# TODO: 添加 uvicorn 0.24.0

# 日志记录和监控
# TODO: 添加 loguru 0.7.2
```

**问题：**
- 为什么要精确固定版本（==），而不是使用 >= 或 ~=？
- 如果不固定版本会发生什么？

### 任务 3.2：创建 requirements-dev.txt

**TODO**：创建带有开发工具的 `requirements-dev.txt`：
```txt
# 包含生产依赖
-r requirements.txt

# 测试
# TODO: 添加 pytest 7.4.3
# TODO: 添加 pytest-cov 4.1.0
# TODO: 添加 pytest-mock 3.12.0

# 代码质量
# TODO: 添加 black 23.11.0
# TODO: 添加 flake8 6.1.0
# TODO: 添加 mypy 1.7.0
# TODO: 添加 isort 5.12.0

# 开发工具
# TODO: 添加 ipython 8.17.0
# TODO: 添加 jupyter 1.0.0
```

### 任务 3.3：安装依赖

**TODO**：
1. 激活您的虚拟环境2. 升级 pip：`python -m pip install --upgrade pip`3. 安装开发依赖：`pip install -r requirements-dev.txt`4. 验证安装：`pip list`
**预期结果**：requirements.txt 和 requirements-dev.txt 中的所有包都应被安装。
### 任务 3.4：冻结当前环境

**TODO**：生成完整的依赖冻结文件：
```bash
pip freeze > requirements-frozen.txt
```

**比较**：
- 打开 `requirements.txt` 和 `requirements-frozen.txt`
- 每个文件中有多少个包？
- 有什么区别？

**回答以下问题：**- 为什么 `requirements-frozen.txt` 中有更多的包？
- 什么是传递依赖（transitive dependencies）？
- 什么时候应该使用冻结的需求文件，什么时候应该使用未冻结的？

## 第 4 部分：环境变量和配置（25 分钟）

### 任务 4.1：创建 .env.example 模板

**TODO**：创建包含配置模板的 `.env.example`：
```bash
# .env.example
# 将其复制为 .env 并填写实际值

# 模型配置
MODEL_NAME=bert-base-uncased
MODEL_CACHE_DIR=/path/to/model/cache
MAX_SEQUENCE_LENGTH=512

# 训练配置
BATCH_SIZE=32
LEARNING_RATE=0.001
NUM_EPOCHS=10
DEVICE=cuda
# 或者: cpu

# 数据配置
DATA_DIR=/path/to/data
TRAIN_FILE=train.csv
VAL_FILE=val.csv
TEST_FILE=test.csv

# 日志记录
LOG_LEVEL=INFO
# 选项: DEBUG, INFO, WARNING, ERROR, CRITICAL
LOG_FILE=training.log

# Weights & Biases（可选）
WANDB_API_KEY=your-wandb-api-key-here
WANDB_PROJECT=sentiment-classifier
WANDB_ENTITY=your-username

# 数据库（供将来使用）
DB_HOST=localhost
DB_PORT=5432
DB_NAME=ml_experiments
DB_USER=mluser
DB_PASSWORD=changeme
```

### 任务 4.2：创建实际的 .env 文件

**TODO**：
1. 将 `.env.example` 复制为 `.env`2. 为您的本地开发填写合理的值3. 验证 `.env` 在 `.gitignore` 中
**重要（CRITICAL）**：永远不要将 `.env` 提交到 git！
### 任务 4.3：测试环境变量加载

创建 `test_env.py`：
```python
# test_env.py
import os
from dotenv import load_dotenv

# TODO: 加载 .env 文件
# 提示: 使用 load_dotenv()

# TODO: 读取并打印环境变量
model_name = os.getenv("MODEL_NAME")
batch_size = os.getenv("BATCH_SIZE")
device = os.getenv("DEVICE")

print(f"Model: {model_name}")
print(f"Batch Size: {batch_size}")
print(f"Device: {device}")

# TODO: 处理缺失的变量
db_password = os.getenv("DB_PASSWORD")
if db_password == "changeme":
    print("WARNING: Using default database password. Change in production!")

# TODO: 类型转换
batch_size_int = int(os.getenv("BATCH_SIZE", "32"))
print(f"Batch size as integer: {batch_size_int}")
```

**运行并验证**：`python test_env.py`
## 第 5 部分：自动化脚本（30 分钟）

### 任务 5.1：创建 setup.sh 脚本

**TODO**：创建 `setup.sh` 来自动化环境设置：
```bash
#!/bin/bash
# setup.sh - 自动化环境设置脚本

set -e  # 遇到错误时退出

echo "========================================="
echo "Setting up Sentiment Classifier Project"
echo "========================================="

# TODO: 检查 Python 版本
echo "Checking Python version..."
# 提示: 使用 python --version

# TODO: 检查虚拟环境是否存在
if [ -d "venv" ]; then
    echo "Virtual environment already exists."
    read -p "Recreate it? (y/n) " -n 1 -r
    echo
    if [[ $REPLY =~ ^[Yy]$ ]]; then
        echo "Removing existing virtual environment..."
        rm -rf venv
    fi
fi

# TODO: 创建虚拟环境
if [ ! -d "venv" ]; then
    echo "Creating virtual environment..."
    # 提示: python -m venv venv
fi

# TODO: 激活虚拟环境
echo "Activating virtual environment..."
# 提示: source venv/bin/activate

# TODO: 升级 pip
echo "Upgrading pip..."
# 提示: python -m pip install --upgrade pip

# TODO: 安装依赖
echo "Installing dependencies..."
# 提示: pip install -r requirements-dev.txt

# TODO: 如果 .env 不存在，从模板创建
if [ ! -f ".env" ]; then
    echo "Creating .env from template..."
    cp .env.example .env
    echo "WARNING: .env created from template. Please update with actual values!"
fi

# TODO: 运行验证
echo ""
echo "========================================="
echo "Setup complete!"
echo "========================================="
echo ""
echo "Next steps:"
echo "1. Activate environment: source venv/bin/activate"
echo "2. Update .env with your configuration"
echo "3. Run tests: pytest tests/"
echo ""
```

**TODO**：
1. 完成 setup.sh 中的 TODO2. 使其可执行：`chmod +x setup.sh`3. 测试它：`./setup.sh`
### 任务 5.2：创建 verify_setup.py 脚本

**TODO**：创建 `verify_setup.py` 以验证设置：
```python
#!/usr/bin/env python3
"""
verify_setup.py - 验证开发环境设置
"""

import sys
import subprocess
from pathlib import Path

def check_python_version():
    """验证 Python 版本为 3.11+"""
    # TODO: 检查 sys.version_info
    # 应至少为 3.11
    pass

def check_virtual_environment():
    """验证是否在虚拟环境中运行"""
    # TODO: 检查 sys.prefix != sys.base_prefix
    # 这表示虚拟环境已激活
    pass

def check_required_packages():
    """验证所有必需的包已安装"""
    required_packages = [
        "torch",
        "transformers",
        "pandas",
        "pytest",
        "black",
        "mypy"
    ]

    # TODO: 尝试导入每个包
    # 报告哪些缺失
    pass

def check_project_structure():
    """验证项目目录是否存在"""
    required_dirs = [
        "src",
        "tests",
        "data",
        "models",
        "configs"
    ]

    required_files = [
        "requirements.txt",
        "requirements-dev.txt",
        ".gitignore",
        ".env.example"
    ]

    # TODO: 检查每个目录和文件是否存在
    # 报告任何缺失
    pass

def check_git_setup():
    """验证 git 配置"""
    # TODO: 检查 .git 目录是否存在
    # 验证 .gitignore 包含 venv/
    pass

def main():
    print("Verifying Development Environment Setup")
    print("=" * 50)

    checks = [
        ("Python Version", check_python_version),
        ("Virtual Environment", check_virtual_environment),
        ("Required Packages", check_required_packages),
        ("Project Structure", check_project_structure),
        ("Git Configuration", check_git_setup)
    ]

    all_passed = True

    for check_name, check_func in checks:
        try:
            check_func()
            print(f"✓ {check_name}")
        except Exception as e:
            print(f"✗ {check_name}: {e}")
            all_passed = False

    print("=" * 50)

    if all_passed:
        print("All checks passed! Environment is ready.")
        return 0
    else:
        print("Some checks failed. Please fix issues above.")
        return 1

if __name__ == "__main__":
    sys.exit(main())
```

**TODO**：
1. 完成每个检查函数的实现2. 运行：`python verify_setup.py`3. 修复报告的任何问题
## 第 6 部分：文档（20 分钟）

### 任务 6.1：创建全面的 README.md

**TODO**：创建包含设置说明的 `README.md`：
```markdown
# Sentiment Classifier

用于情感分类的 ML 训练管道，使用 transformer 模型。

## 先决条件（Prerequisites）

- Python 3.11+
- Git
- 8GB+ 内存
- （可选）支持 CUDA 11.8+ 的 NVIDIA GPU

## 快速设置（Quick Setup）

# TODO: 添加逐步设置说明
# 包括:
# 1. 克隆仓库
# 2. 运行设置脚本
# 3. 配置 .env
# 4. 验证设置

## 开发（Development）

# TODO: 添加常见开发任务
# - 运行训练
# - 运行测试
# - 代码格式化
# - 类型检查

## 项目结构（Project Structure）

# TODO: 记录目录结构
# 解释每个目录的用途

## 配置（Configuration）

# TODO: 解释配置系统
# - 环境变量
# - 配置文件
# - 优先级顺序

## 故障排除（Troubleshooting）

# TODO: 添加常见问题和解决方案
```

### 任务 6.2：记录您的学习心得

创建 `SETUP_NOTES.md` 记录：- 您遇到的挑战
- 如何解决这些挑战
- 给团队成员的提示
- 常见错误和修复方法

## 验证检查清单

提交前，请验证：

- [ ] 虚拟环境已创建并可正常工作
- [ ] 所有依赖都已成功安装
- [ ] `requirements.txt` 包含所有带有固定版本的生产依赖
- [ ] `requirements-dev.txt` 包含所有开发工具
- [ ] `.env.example` 已创建并包含所有配置选项
- [ ] `.env` 已创建（但没有提交到 git！）
- [ ] `.gitignore` 正确排除了敏感文件和生成文件
- [ ] `setup.sh` 成功自动化了完整设置
- [ ] `verify_setup.py` 通过了所有检查
- [ ] `README.md` 有清晰的设置说明
- [ ] 项目结构符合规范
- [ ] 可以激活 venv 并成功运行 `python`
- [ ] 可以运行 `pip list` 并看到所有包
- [ ] 可以导入核心包：`import torch`、`import transformers`

## 提交（Submission）

创建一个文档回答以下问题：
1. **环境隔离**：解释虚拟环境如何提供隔离。在一个 venv 中安装包与全局安装有什么不同？
2. **依赖版本固定**：为什么在生产环境中精确固定版本，而在开发期间可能使用 `>=`？
3. **传递依赖**：它们是什么？`pip freeze` 与您原始的 requirements.txt 有什么不同？
4. **配置策略**：为什么要将 `.env.example`（提交）与 `.env`（不提交）分开？
5. **自动化**：`setup.sh` 相比手动设置说明有什么好处？
6. **挑战**：本练习中最具挑战性的部分是什么？您是如何克服的？
## 扩展挑战（可选）

额外练习：

1. **多环境**：为 Python 3.10、3.11 和 3.12 创建单独的环境。测试包兼容性。
2. **Pip-tools 集成**：安装 `pip-tools` 并创建 `requirements.in` 而不是 `requirements.txt`。使用 `pip-compile` 生成锁定的需求文件。
3. **Docker 集成**：创建一个在容器中设置此环境的 `Dockerfile`。
4. **Pre-commit Hooks**：设置 pre-commit hooks 以在提交前运行 `black`、`flake8` 和 `mypy`。
5. **CI/CD 配置**：创建一个 GitHub Actions 工作流来设置环境并运行测试。
## 资源（Resources）

- [Python venv 文档](https://docs.python.org/3/library/venv.html)
- [pip 文档](https://pip.pypa.io/)
- [pip-tools](https://github.com/jazzband/pip-tools)
- [python-dotenv](https://github.com/theskumar/python-dotenv)

---

**练习版本**：1.0**预计时间**：2-3 小时**难度**：初级
