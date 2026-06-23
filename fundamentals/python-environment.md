# Python 环境与依赖管理 — 完整实践指南

> 来源：初级工程师 M001 · 第 01 讲 + 实际踩坑经验
> 状态：✅ 已学 | 适用：Windows 10/11 + Python 3.9+

---

## 1. 为什么需要虚拟环境

### 1.1 问题本质

全局 `pip install` 把所有包装到系统 Python，所有项目共享一套依赖：

```
项目A → numpy 1.24  ←──┐
                        ├── 系统 site-packages（只能有一个版本）
项目B → numpy 2.0   ←──┘
```

装一个，另一个就炸。Python 依赖冲突是**运行时错误**而非安装时错误。

### 1.2 虚拟环境原理

每个虚拟环境是一个独立目录，包含：
```
venv/
├── Lib/site-packages/   ← pip install 装到这儿，不是系统
├── Scripts/python.exe   ← 独立的 Python 解释器副本
└── Scripts/Activate.ps1 ← 激活脚本（改 PATH）
```

激活后 `python` 和 `pip` 自动指向 `venv/` 里面，装什么都不会污染系统。

---

## 2. 虚拟环境工具选型

| 工具 | 特点 | 何时用 |
|------|------|------|
| **venv** | Python 自带，零依赖 | 简单项目，快速验证 |
| **conda** | 管理 Python 版本 + 非 Python 包（CUDA 等） | ML/DL 项目，需要 CUDA 环境 |
| **poetry** | 锁版本 + 构建 + 发布一站式 | 正式项目，团队协作 |
| **uv** | Rust 实现，极快，兼容 pip | 新项目首选（本机已装） |
| **pipenv** | Pipfile + Pipfile.lock | 已过时，不推荐 |

### 2.1 本机推荐

- **日常小项目**：`python -m venv venv`（零心智负担）
- **ML 项目需要 CUDA**：conda 管理 Python+CUDA 版本，pip 装 PyTorch
- **正式科研项目**：uv（速度碾压 pip，本机已装 `uv 0.11.15`）

### 2.2 uv 快速上手

```powershell
# 创建虚拟环境（比 venv 快 10x）
uv venv

# 激活（跟 venv 一样）
.\venv\Scripts\Activate.ps1

# 装包（比 pip 快 10-100x）
uv pip install numpy torch fastapi

# 导出锁定文件
uv pip freeze > requirements.txt

# 从 requirements.txt 装
uv pip install -r requirements.txt
```

---

## 3. 标准项目初始化

### 3.1 三步走（每次新项目必须）

```powershell
# ① 创建虚拟环境
python -m venv venv          # 或用 uv venv

# ② 激活
.\venv\Scripts\Activate.ps1  # PowerShell
# source venv/bin/activate   # Git Bash

# ③ 验证——python 和 pip 必须指向 venv 里
python -c "import sys; print(sys.executable)"
# 应该输出 ...\venv\Scripts\python.exe
```

### 3.2 标准 .gitignore

```gitignore
# Python 虚拟环境
venv/
.venv/
env/
__pycache__/
*.pyc
*.pyo

# 环境变量（含密钥）
.env
.env.local

# IDE
.vscode/
.idea/

# OS 垃圾文件
.DS_Store
Thumbs.db

# Jupyter
.ipynb_checkpoints/

# 包构建产物
dist/
build/
*.egg-info/
```

> 虚拟环境绝不提交到 git。别人拉代码后自己 `python -m venv venv` 即可。

---

## 4. 依赖管理进阶

### 4.1 requirements.txt 分层策略

```
requirements.txt          # 生产：torch、numpy、fastapi、uvicorn
requirements-dev.txt      # 开发：pytest、black、mypy、pre-commit
requirements-docs.txt     # 文档：sphinx、mkdocs
```

`requirements-dev.txt` 写法：
```
# 第一行引用生产依赖
-r requirements.txt

# 开发工具
pytest==8.1.1
black==24.2.0
mypy==1.8.0
pre-commit==3.7.0
```

### 4.2 pip freeze 的正确用法

```powershell
# ❌ 直接用 pip freeze（会把所有传递依赖倒出来，不可读）
pip freeze > requirements.txt

# ✅ 只写顶层依赖 + 锁版本
pip freeze | grep -E "^(torch|numpy|fastapi|uvicorn)" > requirements.txt

# ✅ 最佳：用 pip-tools 的 pip-compile
pip-compile requirements.in   # 自动解析依赖树 → requirements.txt（带 hashes）
```

### 4.3 日常操作速查

| 场景 | 命令 |
|------|------|
| 新项目创建环境 | `python -m venv venv` |
| 激活 | `.\venv\Scripts\Activate.ps1`（PS）/ `source venv/bin/activate`（Bash）|
| 装包 | `pip install <pkg>` |
| 装指定版本 | `pip install numpy==1.24.3` |
| 装后锁定 | `pip freeze > requirements.txt` |
| 查看已装包 | `pip list` |
| 查看某包信息 | `pip show numpy` |
| 卸载 | `pip uninstall <pkg>` |
| 复现环境 | `pip install -r requirements.txt` |
| 升级包 | `pip install --upgrade <pkg>` |
| 退出虚拟环境 | `deactivate` |
| 删除虚拟环境 | 直接删 `venv/` 文件夹 |

---

## 5. conda 环境（ML/DL 项目专用）

### 5.1 为什么 ML 项目需要 conda

venv 只能隔离 Python 包，隔离不了：
- Python 版本本身
- CUDA Toolkit 版本
- cuDNN 版本
- 非 Python 系统库（如 libstdc++）

conda 同时管理 Python 版本 + 系统级依赖。

### 5.2 常用 conda 命令

```powershell
# 创建指定 Python 版本的环境
conda create -n myproject python=3.11

# 激活
conda activate myproject

# 装 PyTorch（conda 自动匹配 CUDA 版本）
conda install pytorch torchvision torchaudio pytorch-cuda=12.1 -c pytorch -c nvidia

# 导出环境（跨平台）
conda env export --no-builds > environment.yml

# 复现
conda env create -f environment.yml

# 列出所有环境
conda env list
```

### 5.3 conda + pip 混合使用

原则：**先用 conda 装能用 conda 装的，剩下的用 pip。**

```powershell
conda install pytorch numpy pandas   # conda 管这些
pip install transformers datasets     # pip 管这些
```

> ⚠️ 不要在 conda 环境里 `pip install` 已有 conda 版本的包，顺序反了会冲突。

---

## 6. .env 环境变量管理

### 6.1 核心原则

代码里绝对不写死路径和密钥：

```python
# ❌ 硬编码——换了机器就炸，提交 git 就泄露
model_path = "D:/data/model.pt"
api_key = "sk-12345678"
db_url = "postgresql://admin:pass123@localhost/db"

# ✅ 用环境变量
import os
from dotenv import load_dotenv

load_dotenv()  # 自动读项目根目录的 .env 文件

model_path = os.getenv("MODEL_PATH", "/default/path")
api_key = os.getenv("API_KEY")
db_url = os.getenv("DATABASE_URL")
```

### 6.2 .env 文件规范

```bash
# .env（不提交到 git）
# 开发环境变量
MODEL_PATH=D:/data/models/resnet50.pt
API_KEY=sk-proj-abc123def456
DATABASE_URL=postgresql://user:pass@localhost:5432/mldb
CUDA_VISIBLE_DEVICES=0
LOG_LEVEL=DEBUG
```

### 6.3 .env.example 模板

```bash
# .env.example（提交到 git，作为模板）
# 复制此文件为 .env，填写实际值
MODEL_PATH=/path/to/model.pt
API_KEY=your-api-key-here
DATABASE_URL=postgresql://user:password@host:port/dbname
CUDA_VISIBLE_DEVICES=0
LOG_LEVEL=INFO
```

> ⚠️ `.env` 含密钥，必须加入 `.gitignore`。`.env.example` 是模板，提交到 git。

### 6.4 多环境配置

```python
# config.py
import os
from dotenv import load_dotenv

# 根据环境变量选择对应的 .env 文件
env = os.getenv("APP_ENV", "development")
load_dotenv(f".env.{env}")

class Config:
    MODEL_PATH = os.getenv("MODEL_PATH", "./models/default.pt")
    API_KEY = os.getenv("API_KEY")
    DATABASE_URL = os.getenv("DATABASE_URL")
    LOG_LEVEL = os.getenv("LOG_LEVEL", "INFO")
    DEBUG = os.getenv("DEBUG", "false").lower() == "true"

# 使用
# APP_ENV=production python main.py → 加载 .env.production
# python main.py → 默认加载 .env.development
```

---

## 7. Python 导入路径与项目结构

### 7.1 PYTHONPATH 与 sys.path

```python
import sys
print(sys.path)  # Python 查找模块的路径列表

# 当 import 报 ModuleNotFoundError：
# 1. 确认包装了没：pip list | grep <pkg>
# 2. 确认虚拟环境激活了没：which python
# 3. 确认 PYTHONPATH 包含项目根目录
```

### 7.2 标准 ML 项目结构

```
my-ml-project/
├── .gitignore
├── .env.example
├── requirements.txt
├── requirements-dev.txt
├── README.md
├── src/
│   ├── __init__.py
│   ├── config.py          # 配置管理
│   ├── data/
│   │   ├── __init__.py
│   │   └── dataset.py     # 数据加载
│   ├── models/
│   │   ├── __init__.py
│   │   └── model.py       # 模型定义
│   └── utils/
│       ├── __init__.py
│       └── helpers.py
├── tests/
│   ├── __init__.py
│   ├── test_model.py
│   └── test_data.py
├── notebooks/             # Jupyter 实验（不影响 src）
├── docker/
│   ├── Dockerfile
│   └── docker-compose.yml
├── scripts/               # 一次性脚本
└── data/                  # 数据（不提交 git）
```

---

## 8. 常见问题排查

### 8.1 激活虚拟环境失败（PowerShell）

```
报错：无法加载文件 Activate.ps1，因为在此系统上禁止运行脚本

解决（管理员 PowerShell）：
Set-ExecutionPolicy -ExecutionPolicy RemoteSigned -Scope CurrentUser
```

### 8.2 pip 安装报 SSL 错误

```powershell
# 临时解决
pip install <pkg> --trusted-host pypi.org --trusted-host files.pythonhosted.org

# 永久解决：用清华镜像
pip config set global.index-url https://pypi.tuna.tsinghua.edu.cn/simple
pip config set global.trusted-host pypi.tuna.tsinghua.edu.cn
```

### 8.3 虚拟环境指向错误的 Python

```powershell
# 删除 venv 重建
rm -r venv
python -m venv venv --clear

# 指定 Python 版本
C:\Python311\python.exe -m venv venv
```

### 8.4 "module not found" 但我明明 pip install 了

```powershell
# 1. 确认虚拟环境已激活
# 2. 确认 pip 是 venv 里的
pip --version   # 路径应该包含 venv
# 3. 确认包真的装了
pip list | grep <pkg>
# 4. 检查 PYTHONPATH
python -c "import sys; print(sys.path)"
```

### 8.5 装了多个 Python 版本

```powershell
# 查看所有 Python 位置
where python

# 指定用哪个 Python 创建 venv
C:\Users\21716\AppData\Local\Programs\Python\Python311\python.exe -m venv venv
```

---

## 9. Docker 预览（M005 深入）

虚拟环境隔离 Python 包，但隔离不了：CUDA 版本、OS 差异、系统库版本。

Docker 把整个运行时环境打包——从操作系统到 Python 到 CUDA 到你的代码：

```dockerfile
# Dockerfile — 环境的"菜谱"
FROM python:3.11-slim

WORKDIR /app
COPY requirements.txt .
RUN pip install -r requirements.txt
COPY src/ src/

CMD ["python", "src/main.py"]
```

```yaml
# docker-compose.yml — 多服务编排
services:
  app:
    build: .
    ports:
      - "8000:8000"
    environment:
      - MODEL_PATH=/models/model.pt
    volumes:
      - ./models:/models
```

---

## 10. 日常习惯检查清单

| 习惯 | 频率 |
|------|:--:|
| 新项目第一步：创建虚拟环境 | 每个项目 |
| 装包后用 `pip freeze` 锁定 | 每次改依赖 |
| `.env` 含密钥绝不提交 | 每次提交前 |
| `.env.example` 保持更新 | 每次加新配置 |
| 服务器用 Docker 部署 | 每个生产项目 |
| `pip list --outdated` 检查过期包 | 每月 |
| 虚拟环境 `rm -r venv` 然后重建测试复现 | 关键版本发布前 |

---

## 11. 快速参考

```powershell
# === 虚拟环境 ===
python -m venv venv                    # 创建
.\venv\Scripts\Activate.ps1           # 激活 (PS)
source venv/bin/activate              # 激活 (Bash)
deactivate                            # 退出

# === pip 核心命令 ===
pip install numpy                     # 安装
pip install numpy==1.24.3             # 安装指定版本
pip install -r requirements.txt       # 批量安装
pip freeze > requirements.txt         # 导出锁定
pip list                              # 查看已装
pip show numpy                        # 包详情
pip uninstall numpy                   # 卸载
pip install --upgrade pip             # 升级 pip 自身

# === uv 加速版 ===
uv venv                               # 创建虚拟环境
uv pip install numpy                  # 装包
uv pip install -r requirements.txt    # 批量装
uv pip freeze > requirements.txt      # 导出

# === conda ===
conda create -n myenv python=3.11     # 创建环境
conda activate myenv                  # 激活
conda env list                        # 列出所有环境
conda env export > environment.yml    # 导出
```

---

*来源：初级工程师 M001 第 01 讲 + 实践补充*
*补充日期：2026-06-19*
