# Python 环境与依赖管理

> 来源：初级工程师 M001 · 第 01 讲 | 状态：✅ 已学

---

## 1. 当前问题

你现在是全局 `pip install` — 所有项目共用一套包。这会出问题：

```
项目A 需要 numpy==1.24
项目B 需要 numpy==2.0
→ 装一个，另一个就炸
```

解决：每个项目一个**虚拟环境**，就像每个项目有自己的 Python。

---

## 2. 从今天开始做的事

### 每个项目必须三步走

```powershell
# ① 创建虚拟环境（只做一次）
python -m venv venv

# ② 激活
.\venv\Scripts\Activate.ps1

# ③ 确认——which python 应该指向 venv 里面
```

提示符前面出现 `(venv)` 说明激活成功。用 `deactivate` 退出。

### .gitignore 必须加

```
venv/
.env
__pycache__/
```

虚拟环境绝不提交到 git——别人拉代码后自己 `python -m venv venv` 就行。

---

## 3. 依赖管理

### 装完包后立即冻结

```powershell
pip freeze > requirements.txt
```

`requirements.txt` 就是项目的"购物清单"，锁死版本号：

```txt
numpy==1.24.3
torch==2.1.0
```

别人拿到项目后：

```powershell
pip install -r requirements.txt
```

就得到跟你完全一样的环境。

### 生产 vs 开发分离

```
requirements.txt          # 生产：torch、numpy、fastapi
requirements-dev.txt      # 开发：pytest、black、mypy
```

`requirements-dev.txt` 第一行写 `-r requirements.txt`，装开发依赖自动带上生产依赖。

---

## 4. .env 环境变量

代码里不要写死路径和密钥：

```python
# ❌ 不好的做法
model_path = "D:/data/model.pt"
api_key = "sk-12345678"

# ✅ 用 .env
import os
from dotenv import load_dotenv
load_dotenv()

model_path = os.getenv("MODEL_PATH", "/default/path")
api_key = os.getenv("API_KEY")
```

```
# .env（不提交到 git）
MODEL_PATH=D:/data/model.pt
API_KEY=sk-12345678
```

提供一个 `.env.example` 模板（提交到 git），别人 copy 成 `.env` 填自己的值就行。

---

## 5. Docker（当前了解，M005 重点学）

虚拟环境只隔离 Python 包，隔离不了 CUDA、系统库、OS 差异。

Docker 把整个系统环境打包，真正做到"我这能跑，你那也能跑"。

```
Dockerfile（一张菜谱）
      ↓ docker build
   Image（一个做好的菜）
      ↓ docker run
   Container（正在运行的实例）
```

后面学到 M005 再深入。

---

## 6. 每日习惯

| 操作 | 命令 |
|------|------|
| 新项目第一步 | `python -m venv venv` |
| 激活环境 | `.\venv\Scripts\Activate.ps1` |
| 装包后立即 | `pip freeze > requirements.txt` |
| 复现环境 | `pip install -r requirements.txt` |
| 配置放 | `.env` 文件，用 `python-dotenv` 读 |

---

## 7. 给 ai-infra-career 项目补上

现在就做——给 `D:\study\ai-infra-career\` 加上 `requirements.txt` 和 `.env.example`：

```powershell
cd D:\study\ai-infra-career
python -m venv venv
.\venv\Scripts\Activate.ps1
pip install python-dotenv numpy torch
pip freeze > requirements.txt
```
