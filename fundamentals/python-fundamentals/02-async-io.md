# Python 异步编程

> 来源：初级工程师 M001 · 第 04 讲 | 状态：✅ 已学

---

## 1. 什么时候用异步

| 场景 | 用 async | 原因 |
|------|:--:|------|
| HTTP API 调用 | ✅ | I/O 等待，不占 CPU |
| 读写数据库 | ✅ | 同上 |
| 文件读写 | ✅ | 同上 |
| 多个模型端点健康检查并发 | ✅ | 经典场景 |
| 数据处理/训练 | ❌ | CPU 密集，用 `multiprocessing` |
| 简单脚本无并发 | ❌ | 没必要 |

---

## 2. 基本语法

```python
import asyncio

async def fetch(url: str) -> dict:
    await asyncio.sleep(1)      # 模拟 I/O 等待
    return {"url": url}

async def main():
    result = await fetch("https://api.example.com")
    print(result)

asyncio.run(main())              # 入口点
```

---

## 3. 并发执行 — asyncio.gather

5 个请求并发：0.5s；逐个执行：2.5s。

```python
async def check_all(endpoints: list) -> list:
    tasks = [check_one(ep) for ep in endpoints]
    return await asyncio.gather(*tasks)
```

每个请求出错不影响其他的写法：

```python
results = await asyncio.gather(*tasks, return_exceptions=True)
```

---

## 4. 异步 HTTP — httpx

```python
import httpx

async def check_health(url: str) -> dict:
    async with httpx.AsyncClient(timeout=5.0) as client:
        resp = await client.get(f"{url}/health")
        return {"url": url, "status": resp.status_code}
```

---

## 5. 重试 + 指数退避

```python
async def fetch_with_retry(url: str, retries: int = 3) -> dict | None:
    for n in range(retries):
        try:
            async with httpx.AsyncClient() as c:
                r = await c.get(url, timeout=10.0)
                r.raise_for_status()
                return r.json()
        except httpx.TimeoutException:
            if n < retries - 1:
                await asyncio.sleep(2 ** n)   # 1s, 2s, 4s
    return None
```

---

## 6. 异步上下文管理器

连接 → 用 → 自动关闭，跟 `with open()` 一样，只是异步版。

```python
class AsyncModelClient:
    async def __aenter__(self):
        self.client = httpx.AsyncClient()
        return self

    async def __aexit__(self, *args):
        await self.client.aclose()

    async def predict(self, data: dict) -> dict:
        r = await self.client.post("/predict", json=data)
        return r.json()

# 用
async with AsyncModelClient() as cli:
    result = await cli.predict({"x": [1,2,3]})
```

---

## 7. 异步生成器 — 流式输出

```python
async def stream_logs(job_id: str):
    for i in range(10):
        await asyncio.sleep(0.5)
        yield f"[{job_id}] Epoch {i+1}/10 loss={1.0/(i+1):.4f}"

async for line in stream_logs("job-123"):
    print(line)
```

---

## 8. 常见场景速查

| 场景 | 模式 |
|------|------|
| 并发检查多个模型健康状态 | `asyncio.gather(*[check_health(ep) for ep in endpoints])` |
| 批量推理（I/O 密集） | `asyncio.gather(*[infer(data) for data in batch])` |
| 数据管线（拉→处理→存） | `await fetch()` → `await asyncio.gather(*process_tasks)` → `await save()` |
| 错误隔离 | `asyncio.gather(*tasks, return_exceptions=True)` |
