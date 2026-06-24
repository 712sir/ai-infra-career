# Python DevOps 运维操作 — 实践指南

> 来源：初级工程师 M001 · 第 03 讲 + 实际工程经验
> 状态：✅ 已学 | 核心：subprocess · pathlib · argparse

---

## 1. Subprocess——从 Python 调用外部命令

### 1.1 为什么不用 os.system()

```python
import os
os.system("ls -la")     # ← 返回 0/非 0，无法捕获输出，不安全
```

`subprocess.run()` 是标准答案——捕获输出、超时控制、错误检查。

### 1.2 基础四步

```python
import subprocess

# 1. 执行并等待
result = subprocess.run(["ls", "-la"])

# 2. 捕获输出
result = subprocess.run(["nvidia-smi"], capture_output=True, text=True)
print(result.stdout)

# 3. 检查成功（失败抛异常）
result = subprocess.run(["docker", "ps"], check=True, capture_output=True, text=True)

# 4. 超时保护
result = subprocess.run(["python", "train.py"], timeout=300)  # 5 分钟
```

### 1.3 实时流式输出

```python
process = subprocess.Popen(
    ["python", "train.py"],
    stdout=subprocess.PIPE,
    stderr=subprocess.STDOUT,
    text=True,
    bufsize=1
)

# 逐行输出——终端实时看到训练进度
for line in process.stdout:
    print(f"[TRAIN] {line.rstrip()}")

exit_code = process.wait()
```

### 1.4 shell=True 什么时候都不能用？

**不要用** 当参数来自用户输入：
```python
# ❌ 用户输入 `file; rm -rf /` 就完蛋了
subprocess.run(f"ls {user_input}", shell=True)

# ✅ 参数作为数据传递，不是代码
subprocess.run(["ls", user_input])
```

**可以用** 当命令是硬编码且确实需要 shell 特性（管道）——但尽量用 Python 替代：
```python
# 需要管道？用 Python 的 Popen + pipe 串起来，或直接 Python 处理
result = subprocess.run(["ps", "aux"], capture_output=True, text=True)
python_lines = [l for l in result.stdout.split('\n') if 'python' in l]
```

### 1.5 ML 场景实战

```python
# 检测 GPU
import subprocess, json

def get_gpu_info():
    try:
        r = subprocess.run(
            ["nvidia-smi", "--query-gpu=name,memory.total,memory.free",
             "--format=csv,noheader,nounits"],
            capture_output=True, text=True, check=True
        )
        gpus = []
        for line in r.stdout.strip().split('\n'):
            name, total, free = line.split(', ')
            gpus.append({"name": name, "total_mb": int(total), "free_mb": int(free)})
        return gpus
    except FileNotFoundError:
        return []  # 没有 nvidia-smi——不是 GPU 机器

# 启 Docker 训练
def run_training(image, script, gpus=1, volumes=None):
    cmd = ["docker", "run", "--gpus", str(gpus), "--rm"]
    if volumes:
        for host, cont in volumes.items():
            cmd.extend(["-v", f"{host}:{cont}"])
    cmd.extend([image, "python", script])
    return subprocess.run(cmd).returncode

# 上传模型到 S3
def upload_to_s3(local_path, s3_uri):
    subprocess.run(
        ["aws", "s3", "cp", str(local_path), s3_uri],
        check=True, capture_output=True, text=True
    )
```

---

## 2. pathlib——告别字符串路径

### 2.1 为什么不用 os.path

```python
# ❌ 字符串拼接——不同 OS 分隔符不同
import os
path = os.path.join("data", "models", "checkpoint.pt")

# ✅ pathlib——面向对象，跨平台
from pathlib import Path
path = Path("data") / "models" / "checkpoint.pt"
```

### 2.2 核心操作速查

```python
from pathlib import Path

# === 创建 ===
models = Path("/tmp/ml-project/models")
models.mkdir(parents=True, exist_ok=True)  # 递归创建，存在不报错

# === 读写 ===
config_file = Path("config.yaml")
config_file.write_text("batch_size: 32")   # 写
content = config_file.read_text()           # 读（小文件）

with open(config_file, 'r') as f:          # 读（大文件，逐行）
    for line in f: ...

# === 检查 ===
if path.exists(): ...
if path.is_file(): ...
if path.is_dir(): ...

# === 遍历 ===
for f in Path("models").iterdir(): ...      # 当前目录
for f in Path("models").glob("*.pt"): ...   # 按模式匹配
for f in Path("models").glob("**/*.pt"): ... # 递归搜索所有子目录

# === 信息 ===
size_mb = path.stat().st_size / (1024 * 1024)
import datetime
mtime = datetime.datetime.fromtimestamp(path.stat().st_mtime)

# === 删除 ===
path.unlink()        # 删除文件
path.rmdir()         # 删除空目录
import shutil
shutil.rmtree(path)  # 删除非空目录
```

### 2.3 ML 场景实战

```python
# 清理旧模型检查点——只保留最近 5 个且 30 天内的
def cleanup_checkpoints(ckpt_dir: Path, keep_recent=5, max_age_days=30):
    ckpts = sorted(ckpt_dir.glob("checkpoint-*.pt"),
                   key=lambda p: p.stat().st_mtime, reverse=True)
    now = time.time()
    for ckpt in ckpts[keep_recent:]:
        if (now - ckpt.stat().st_mtime) / 86400 > max_age_days:
            ckpt.unlink()

# 验证数据完整性——对比 SHA256
import hashlib

def file_hash(path: Path) -> str:
    sha = hashlib.sha256()
    with open(path, 'rb') as f:
        for chunk in iter(lambda: f.read(4096), b""):
            sha.update(chunk)
    return sha.hexdigest()

def verify_dataset(data_dir: Path, manifest: Path) -> bool:
    """检查数据目录中所有文件的 SHA256 是否匹配清单"""
    with open(manifest) as f:
        expected = dict(line.strip().split() for line in f)
    for filename, expected_hash in expected.items():
        actual = file_hash(data_dir / filename)
        if actual != expected_hash:
            print(f"CORRUPTED: {filename}")
            return False
    return True
```

---

## 3. argparse——构建专业的 CLI 工具

### 3.1 为什么用 argparse

不用 argparse 的结果：每个人用不同的方式传参数，脚本之间交互靠猜。

```bash
# ❌ 各种野路子
python train.py config.yaml epochs=20
python train.py --epochs 20 config.yaml
```

argparse 标准化：
```bash
python train.py config.yaml --epochs 20 --batch-size 64
```

### 3.2 标准模板

```python
import argparse

def main():
    parser = argparse.ArgumentParser(description="ML 模型训练脚本")

    # 位置参数（必传）
    parser.add_argument("config", type=Path, help="配置文件路径")

    # 可选参数
    parser.add_argument("--epochs", type=int, default=10, help="训练轮数")
    parser.add_argument("--batch-size", type=int, default=32)
    parser.add_argument("--lr", type=float, default=0.001, help="学习率")
    parser.add_argument("--gpu", type=int, default=0, help="GPU 设备编号")

    # 开关
    parser.add_argument("--verbose", action="store_true", help="详细日志")

    args = parser.parse_args()

    # 使用
    if args.verbose:
        logging.getLogger().setLevel(logging.DEBUG)

    print(f"配置文件: {args.config}")
    print(f"训练轮数: {args.epochs}, 批次大小: {args.batch_size}")

if __name__ == "__main__":
    main()
```

### 3.3 子命令——像 git 一样的 CLI

```python
def main():
    parser = argparse.ArgumentParser(description="ML 模型管理工具")
    subparsers = parser.add_subparsers(dest="command", required=True)

    # ml-tool train --model bert --epochs 20
    train_p = subparsers.add_parser("train")
    train_p.add_argument("--model", required=True)
    train_p.add_argument("--epochs", type=int, default=10)

    # ml-tool deploy --model bert --env prod
    deploy_p = subparsers.add_parser("deploy")
    deploy_p.add_argument("--model", required=True)
    deploy_p.add_argument("--env", choices=["dev", "staging", "prod"], required=True)

    # ml-tool list --env prod
    list_p = subparsers.add_parser("list")
    list_p.add_argument("--env", choices=["dev", "staging", "prod"])

    args = parser.parse_args()

    if args.command == "train":
        train_model(args.model, args.epochs)
    elif args.command == "deploy":
        deploy_model(args.model, args.env)
    elif args.command == "list":
        list_deployments(args.env)
```

### 3.4 CLI 设计原则

| 原则 | 说明 |
|------|------|
| 提供合理默认值 | `default=32`——让大多数场景不需要传参 |
| 描述要清晰 | `help=` 写清楚参数干什么 |
| 尽早校验 | 文件不存在或值非法在 `parse_args` 后就报错 |
| 标准退出码 | 成功 `exit(0)`，失败 `exit(1)`，Ctrl+C `exit(130)` |
| 示例写到 `epilog` | 用户看完 `--help` 知道怎么用 |

---

## 4. 环境变量与系统交互

### 4.1 读取和设置

```python
import os

# 读——给默认值
model_path = os.getenv("MODEL_PATH", "/default/model.pt")

# 读——必须存在
api_key = os.environ["API_KEY"]  # 不存在抛 KeyError

# 写——仅影响当前进程及其子进程
os.environ["CUDA_VISIBLE_DEVICES"] = "0,1"

# 启动子进程时自定义环境
import subprocess
env = os.environ.copy()
env["CUDA_VISIBLE_DEVICES"] = "2,3"
env["OMP_NUM_THREADS"] = "8"
subprocess.run(["python", "train.py"], env=env)
```

### 4.2 获取系统信息

```python
import os, platform, sys

print(f"OS: {platform.system()} {platform.platform()}")
print(f"Python: {sys.version}")
print(f"CPU 核数: {os.cpu_count()}")
print(f"当前目录: {os.getcwd()}")
print(f"当前用户: {os.getlogin()}")
```

---

## 5. 日常习惯检查清单

| 习惯 | 说明 |
|------|------|
| `subprocess.run([...])` 不用 `os.system()` | 安全 + 可控 + 能捕获输出 |
| `check=True` + `timeout` | 失败立即知道，不挂死 |
| 路径用 `Path` 不用字符串 | 跨平台 `/` 拼接，不操心分隔符 |
| 文件操作用 `with` | 自动关闭，不泄露句柄 |
| CLI 用 argparse | 标准化参数，自带 `--help` |
| 子命令拆功能 | 一个工具做一类事，像 `git` 和 `docker` |
| 环境变量放配置不写死 | 开发/测试/生产一套代码 |

---

## 6. 快速参考

```bash
# === subprocess ===
subprocess.run(["cmd", "arg"], check=True, capture_output=True, text=True)
subprocess.run(["cmd"], timeout=30)                    # 超时
subprocess.Popen(["cmd"], stdout=PIPE, text=True)       # 流式输出

# === pathlib ===
path = Path("dir") / "subdir" / "file.txt"
path.mkdir(parents=True, exist_ok=True)
path.read_text() / path.write_text("content")
path.glob("*.pt") / path.glob("**/*.pt")

# === argparse ===
parser = argparse.ArgumentParser()
parser.add_argument("config", type=Path)
parser.add_argument("--epochs", type=int, default=10)
parser.add_argument("--verbose", action="store_true")

# === 环境变量 ===
os.getenv("KEY", "default")
os.environ["KEY"]           # 必须存在
```

---

*来源：初级工程师 M001 第 03 讲 + 实践补充 | 整理日期：2026-06-23*
