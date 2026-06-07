# Python GIL 与并发模型

> 来源：《Fluent Python》Ch18-19 + David Beazley "Understanding the Python GIL"
> 状态：🟡 笔记整理中
> 面试权重：⭐⭐⭐（Python 岗位必问，AI Infra 中推理服务怎么处理高并发）

---

## GIL 是什么

**Global Interpreter Lock** — 全局解释器锁。

```
┌─────────────────────────────────────┐
│         CPython 进程                 │
│  ┌──────┐ ┌──────┐ ┌──────┐        │
│  │Thread│ │Thread│ │Thread│        │
│  │  1   │ │  2   │ │  3   │        │
│  └──┬───┘ └──┬───┘ └──┬───┘        │
│     │        │        │             │
│     └────────┼────────┘             │
│              │                      │
│         ╔════╧════╗                 │
│         ║  GIL   ║  ← 同一时刻      │
│         ╚════╤════╝    只有一个线程  │
│              │        能执行 Python  │
│         ┌────┴────┐    字节码        │
│         │ Interp  │                 │
│         └─────────┘                 │
└─────────────────────────────────────┘
```

**一句话**：同一时刻只有一个线程能执行 Python 代码。

---

## GIL 的影响

### CPU 密集型 → 多线程反而慢

```python
import time, threading

def cpu_bound(n):
    """计算密集型任务——多线程比单线程更慢！"""
    total = 0
    for i in range(n):
        total += i
    return total

# 单线程
t0 = time.time()
cpu_bound(10**7)
cpu_bound(10**7)
print(f"Serial: {time.time()-t0:.2f}s")

# 多线程（线程切换 + GIL 竞争 → 反而更慢）
t0 = time.time()
t1 = threading.Thread(target=cpu_bound, args=(10**7,))
t2 = threading.Thread(target=cpu_bound, args=(10**7,))
t1.start(); t2.start()
t1.join(); t2.join()
print(f"Threaded: {time.time()-t0:.2f}s")  # 通常是 Serial 的 1.5x-2x
```

### IO 密集型 → 多线程有效

```python
import requests, threading

# IO 等待时 GIL 释放 → 多线程有优势
def fetch_url(url):
    resp = requests.get(url)   # 网络 IO → GIL 释放
    return len(resp.text)      # Python 计算 → GIL 重新获取

# 多线程并发请求 → 快!
threads = [threading.Thread(target=fetch_url, args=(url,))
           for url in urls]
```

---

## 绕过 GIL 的三种方式

### 方式 1：multiprocessing（CPU 密集首选）

```python
from multiprocessing import Pool

# 每个进程有自己独立的 Python 解释器 + GIL
# CPU 密集型任务：用多进程！
def heavy_compute(n):
    return sum(i*i for i in range(n))

with Pool(processes=4) as pool:
    results = pool.map(heavy_compute, [10**7] * 4)
```

### 方式 2：asyncio（IO 密集首选）

```python
import asyncio
import aiohttp

# 单线程 + 事件循环 → 不涉及 GIL 竞争
async def fetch(url):
    async with aiohttp.ClientSession() as session:
        async with session.get(url) as resp:
            return await resp.text()

async def main():
    tasks = [fetch(url) for url in urls]
    return await asyncio.gather(*tasks)

asyncio.run(main())  # 所有请求并发，单线程搞定
```

### 方式 3：C 扩展释放 GIL

```cpp
// CUDA / C++ 扩展中释放 GIL，让 Python 线程真正并行
Py_BEGIN_ALLOW_THREADS
    // 这里的 C/C++ 代码不受 GIL 限制
    cudaMemcpy(dst, src, size, cudaMemcpyHostToDevice);
    kernel<<<grid, block>>>(...);
Py_END_ALLOW_THREADS
```

---

## AI Infra 中的实际场景

### 推理服务的高并发处理

```python
# vLLM 推理服务架构的核心思路：
# Python 层做调度（asyncio 事件循环）
# C++/CUDA 层做计算（GIL 释放，GPU 真正并行）

# 简化版推理服务器
import asyncio
from concurrent.futures import ThreadPoolExecutor

# 假设 model 是一个 C 扩展对象（内部用 Py_BEGIN_ALLOW_THREADS 释放 GIL）
# 如果 model 是纯 Python 对象，请改用 ProcessPoolExecutor
from transformers import AutoTokenizer

tokenizer = AutoTokenizer.from_pretrained("gpt2")
model = load_cpp_inference_engine("model.bin")  # C++ 推理引擎

executor = ThreadPoolExecutor(max_workers=4)

async def handle_client(reader, writer):
    """asyncio.start_server 要求的回调签名"""
    data = await reader.read(4096)
    prompt = data.decode('utf-8')

    # tokenize 在 Python 中（轻量）
    tokens = tokenizer.encode(prompt)

    # 推理在 C++/CUDA 中（重量，GIL 释放 → 可真正并行）
    loop = asyncio.get_event_loop()
    result = await loop.run_in_executor(executor, model.generate, tokens)

    # detokenize 在 Python 中
    response = tokenizer.decode(result)
    writer.write(response.encode('utf-8'))
    await writer.drain()
    writer.close()
    await writer.wait_closed()

# 启动服务
async def main():
    server = await asyncio.start_server(handle_client, '0.0.0.0', 8080)
    async with server:
        await server.serve_forever()

asyncio.run(main())
```

### 为什么推理引擎用 C++ 写而不是纯 Python？

```
纯 Python：
  模型推理 ← GIL 阻止多线程同时用 GPU → GPU 利用率低

C++/CUDA 引擎 + Python 前端（vLLM/SGLang 的做法）：
  Python 做请求调度/预处理 → asyncio，不争 GIL
  C++ 做模型推理 → Py_BEGIN_ALLOW_THREADS，GIL 释放
  GPU 做计算 → 完全不受 GIL 影响
  
  → 多请求并发，GPU 利用率高
```

---

## 面试高频问题

| 问题 | 答案 |
|------|------|
| GIL 是什么？ | CPython 的全局锁，同一时刻只有一个线程执行 Python 字节码 |
| 为什么有 GIL？ | 简化 CPython 内存管理（引用计数），避免竞态条件 |
| CPU 密集怎么破？ | multiprocessing，每个进程独立 GIL |
| IO 密集怎么破？ | threading（IO 时 GIL 释放）或 asyncio（单线程事件循环） |
| C 扩展能绕 GIL 吗？ | 能，`Py_BEGIN_ALLOW_THREADS` 释放，`Py_END_ALLOW_THREADS` 重新获取 |
| 多线程到底有没有用？ | IO 密集：有用；CPU 密集：没用甚至更慢 |
| subprocess vs multiprocessing？ | subprocess 运行任何可执行文件；multiprocessing 只 fork Python 函数 |
