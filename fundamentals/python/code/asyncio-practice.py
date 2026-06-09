"""
asyncio 实战练习

对应 W3 B2 Python：event loop / coroutine / await / gather / create_task
C++ 标准：Python 3.8+

核心概念：
  1. coroutine:  async def 定义的函数，调用返回 coroutine 对象，不立即执行
  2. await:      挂起当前协程，等待另一个协程完成
  3. Task:       把 coroutine 包装成 Task 提交给 event loop
  4. gather:     并发运行多个 coroutine，等全部完成
  5. Queue:      异步生产者-消费者（对比 C++ BoundedBlockingQueue）

运行：python asyncio-practice.py
"""

import asyncio
import time
import random
from typing import List


# ═══════════════════════════════════════════════════════════════════
# 1. 基础：coroutine 和 await
# ═══════════════════════════════════════════════════════════════════

async def fetch_data(source: str, delay: float) -> str:
    """模拟异步 IO：从某个数据源获取数据"""
    print(f"  [{source}] start fetching (delay={delay}s)...")
    await asyncio.sleep(delay)  # 模拟网络 IO，释放控制权给 event loop
    print(f"  [{source}] done!")
    return f"data_from_{source}"


async def demo_basic():
    print("--- 1. Basic coroutine & await ---")

    # 串行：总时间 = 0.2 + 0.3 + 0.1 = 0.6s
    t0 = time.perf_counter()
    r1 = await fetch_data("A", 0.2)
    r2 = await fetch_data("B", 0.3)
    r3 = await fetch_data("C", 0.1)
    t1 = time.perf_counter()
    print(f"  Serial:  {t1 - t0:.3f}s | results: {r1}, {r2}, {r3}")

    # 并行：总时间 ≈ max(0.2, 0.3, 0.1) = 0.3s
    t0 = time.perf_counter()
    results = await asyncio.gather(
        fetch_data("X", 0.2),
        fetch_data("Y", 0.3),
        fetch_data("Z", 0.1),
    )
    t1 = time.perf_counter()
    print(f"  Parallel: {t1 - t0:.3f}s | results: {results}")
    print(f"  Speedup:  {(0.6) / (t1 - t0):.1f}x\n")


# ═══════════════════════════════════════════════════════════════════
# 2. create_task：不等待结果，安排后台任务
# ═══════════════════════════════════════════════════════════════════

async def background_worker(name: str, count: int):
    """后台 worker，周期性做某事"""
    for i in range(count):
        await asyncio.sleep(0.1)
        print(f"  [Worker {name}] tick {i + 1}/{count}")


async def demo_create_task():
    print("--- 2. create_task (fire-and-forget-ish) ---")

    # 创建 Task 后立即返回，不阻塞
    task1 = asyncio.create_task(background_worker("W1", 3))
    task2 = asyncio.create_task(background_worker("W2", 3))

    print("  Main: tasks created, doing other work...")
    await asyncio.sleep(0.15)  # 主协程可以做别的事
    print("  Main: still running alongside workers...")

    # 等待所有后台任务完成
    await task1
    await task2
    print("  Main: all workers done\n")


# ═══════════════════════════════════════════════════════════════════
# 3. asyncio.Queue：异步生产者-消费者
# ═══════════════════════════════════════════════════════════════════
# 对比 C++ BoundedBlockingQueue：asyncio 版本无需显式 mutex/condvar
# 单线程协作式调度天然线程安全

async def producer(q: asyncio.Queue, name: str, n_items: int):
    """异步生产者"""
    for i in range(n_items):
        item = f"{name}-{i}"
        await asyncio.sleep(random.uniform(0.05, 0.15))  # 模拟生产耗时
        await q.put(item)
        print(f"  [Producer {name}] put {item}  (qsize={q.qsize()})")
    print(f"  [Producer {name}] done")


async def consumer(q: asyncio.Queue, name: str):
    """异步消费者"""
    while True:
        item = await q.get()
        if item is None:  # 毒丸信号：停止
            q.task_done()
            break
        print(f"  [Consumer {name}] got {item}  (qsize={q.qsize()})")
        await asyncio.sleep(random.uniform(0.1, 0.2))  # 模拟消费耗时
        q.task_done()
    print(f"  [Consumer {name}] done")


async def demo_queue():
    print("--- 3. asyncio.Queue (async producer-consumer) ---")

    q = asyncio.Queue(maxsize=3)  # 有界队列，maxsize=3

    # 2 个生产者，各生产 4 个
    p1 = asyncio.create_task(producer(q, "P1", 4))
    p2 = asyncio.create_task(producer(q, "P2", 4))

    # 2 个消费者
    c1 = asyncio.create_task(consumer(q, "C1"))
    c2 = asyncio.create_task(consumer(q, "C2"))

    # 等生产者完成
    await p1
    await p2

    # 发送毒丸信号给两个消费者
    await q.put(None)
    await q.put(None)

    # 等消费者完成
    await c1
    await c2

    print("  Queue size: {}\n".format(q.qsize()))


# ═══════════════════════════════════════════════════════════════════
# 4. run_in_executor：把阻塞 CPU 任务扔进线程池
# ═══════════════════════════════════════════════════════════════════
# 关键：asyncio 是单线程的，CPU 密集任务会阻塞整个 event loop！
# 解决：用 loop.run_in_executor() 把 CPU 任务扔进线程/进程池

def cpu_heavy(n: int) -> int:
    """纯 CPU 计算（同步函数，不是协程）"""
    total = 0
    for i in range(n):
        total += i
    return total


async def demo_run_in_executor():
    print("--- 4. run_in_executor (CPU task in thread pool) ---")

    loop = asyncio.get_running_loop()
    t0 = time.perf_counter()

    # 把 CPU 任务丢进默认线程池（不阻塞 event loop！）
    # 注意：Python GIL 下线程池对 CPU 任务没有加速效果
    # 真正的 CPU 并行需要 ProcessPoolExecutor
    cpu_task = loop.run_in_executor(None, cpu_heavy, 20_000_000)

    # 同时可以做 IO 任务
    io_tasks = asyncio.gather(
        fetch_data("io1", 0.1),
        fetch_data("io2", 0.15),
    )

    cpu_result, io_results = await asyncio.gather(cpu_task, io_tasks)

    t1 = time.perf_counter()
    print(f"  CPU result: {cpu_result}")
    print(f"  IO results: {io_results}")
    print(f"  Total: {t1 - t0:.3f}s (IO + CPU overlapped!)\n")


# ═══════════════════════════════════════════════════════════════════
# 5. 实际场景：模拟 AI Infra 中的异步模型推理请求
# ═══════════════════════════════════════════════════════════════════

class AsyncInferenceServer:
    """模拟异步推理服务器：并发处理多个推理请求"""

    def __init__(self, max_concurrent: int = 3):
        self.semaphore = asyncio.Semaphore(max_concurrent)
        self.request_count = 0

    async def infer(self, request_id: int, model_size: str) -> str:
        """单个推理请求"""
        async with self.semaphore:  # 限制并发数（模拟 GPU 显存限制）
            self.request_count += 1
            print(f"  [Infer {request_id}] start ({model_size}), "
                  f"concurrent={self.semaphore._value}")

            # 模拟推理延迟
            if model_size == "7B":
                await asyncio.sleep(0.5)
            elif model_size == "13B":
                await asyncio.sleep(0.8)
            else:
                await asyncio.sleep(0.2)

            self.request_count -= 1
            print(f"  [Infer {request_id}] done")
            return f"result_{request_id}"


async def demo_inference_server():
    print("--- 5. AsyncInferenceServer (simulated) ---")

    server = AsyncInferenceServer(max_concurrent=3)

    # 模拟 8 个并发推理请求
    requests = [
        server.infer(i, random.choice(["7B", "13B", "350M"]))
        for i in range(8)
    ]

    t0 = time.perf_counter()
    results = await asyncio.gather(*requests)
    t1 = time.perf_counter()

    print(f"  8 requests done in {t1 - t0:.3f}s")
    print(f"  Results: {results[:3]}...\n")


# ═══════════════════════════════════════════════════════════════════
# 6. 常见错误演示
# ═══════════════════════════════════════════════════════════════════

async def demo_common_mistakes():
    print("--- 6. Common Mistakes ---")

    # ❌ 错误 1：忘记 await
    print("  Mistake 1: Forgetting await")
    coro = fetch_data("X", 0.1)
    print(f"    coro without await: {coro} (not executed!)")
    result = await coro  # 必须 await 才执行
    print(f"    after await: {result}")

    # ❌ 错误 2：在 async 函数里用 time.sleep（阻塞整个 event loop！）
    print("  Mistake 2: time.sleep in async (blocks event loop!)")
    t0 = time.perf_counter()
    await asyncio.gather(
        asyncio.sleep(0.1),
        asyncio.sleep(0.1),
    )
    t1 = time.perf_counter()
    print(f"    asyncio.sleep x2: {t1 - t0:.3f}s (parallel, ~0.1s)")

    # ❌ 错误 3：CPU 密集任务直接放 async 里
    print("  Mistake 3: CPU-heavy in async (NEVER do this)")
    print("    -> use run_in_executor instead (see demo #4)\n")


# ═══════════════════════════════════════════════════════════════════
# Main
# ═══════════════════════════════════════════════════════════════════

async def main():
    await demo_basic()
    await demo_create_task()
    await demo_queue()
    await demo_run_in_executor()
    await demo_inference_server()
    await demo_common_mistakes()

    print("=== Key Takeaways ===")
    print("  async/await: 协程 = 可暂停的函数，await = 让出控制权")
    print("  gather: 并发运行，总时间 = max(各任务时间)")
    print("  create_task: 安排后台任务，不阻塞当前协程")
    print("  Queue: 单线程协作式，无需 mutex/condvar")
    print("  Semaphore: 限制并发数（如 GPU 显存限制）")
    print("  run_in_executor: CPU 任务扔进线程池，不阻塞 event loop")
    print("  time.sleep in async = 灾难！用 asyncio.sleep")


if __name__ == "__main__":
    asyncio.run(main())
