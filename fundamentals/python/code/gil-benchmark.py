"""
GIL 性能对比：threading vs multiprocessing vs asyncio

GIL (Global Interpreter Lock) 是 CPython 的核心机制：
- 同一时刻只有一个线程执行 Python 字节码
- CPU 密集型：GIL 导致多线程反而更慢（线程切换 + GIL 竞争）
- IO 密集型：线程在 IO 等待时释放 GIL，多线程有效
- multiprocessing：绕过 GIL，每个进程有独立的 Python 解释器
- asyncio：单线程协程，IO 密集场景最优

运行：python gil-benchmark.py
"""

import time
import threading
import multiprocessing
import asyncio
from concurrent.futures import ThreadPoolExecutor, ProcessPoolExecutor
from typing import List, Callable


# ═══════════════════════════════════════════════════════════════════
# 工作函数
# ═══════════════════════════════════════════════════════════════════

def cpu_bound_task(n: int = 40) -> int:
    """CPU 密集型：计算 Fibonacci（大量纯 Python 运算）"""
    if n <= 1:
        return n
    return cpu_bound_task(n - 1) + cpu_bound_task(n - 2)


def cpu_bound_iterative(n: int = 10_000_000) -> int:
    """CPU 密集型：循环计数（循环 hold 住 GIL）"""
    total = 0
    for i in range(n):
        total += i
    return total


def io_bound_task(seconds: float = 0.1) -> None:
    """IO 密集型：模拟网络/磁盘等待（sleep 时释放 GIL）"""
    time.sleep(seconds)


# ═══════════════════════════════════════════════════════════════════
# 测量工具
# ═══════════════════════════════════════════════════════════════════

def measure(label: str, fn: Callable) -> float:
    """测量函数执行时间（秒）"""
    t0 = time.perf_counter()
    fn()
    elapsed = time.perf_counter() - t0
    print(f"  {label:<40} {elapsed:>7.3f}s")
    return elapsed


# ═══════════════════════════════════════════════════════════════════
# Test 1: CPU 密集型 —— 单线程 vs 多线程 vs 多进程
# ═══════════════════════════════════════════════════════════════════

def test_cpu_bound(num_tasks: int = 8, fib_n: int = 35):
    """CPU 密集型对比：证明 GIL 让多线程反而更慢"""
    print("=" * 65)
    print(f"Test 1: CPU-bound (fib({fib_n}) x {num_tasks} tasks)")
    print("=" * 65)

    # 1a: 串行执行
    def serial():
        for _ in range(num_tasks):
            cpu_bound_task(fib_n)
    baseline = measure("Serial (single-thread)", serial)

    # 1b: 多线程（GIL 下会更慢！）
    def threaded():
        threads = []
        for _ in range(num_tasks):
            t = threading.Thread(target=cpu_bound_task, args=(fib_n,))
            threads.append(t)
            t.start()
        for t in threads:
            t.join()
    t_time = measure("Threading (GIL hurts!)", threaded)

    # 1c: ThreadPoolExecutor
    def thread_pool():
        with ThreadPoolExecutor(max_workers=num_tasks) as executor:
            futures = [executor.submit(cpu_bound_task, fib_n) for _ in range(num_tasks)]
            for f in futures:
                f.result()
    tp_time = measure("ThreadPoolExecutor (GIL hurts!)", thread_pool)

    # 1d: 多进程（真正并行，绕过 GIL）
    def multiproc():
        with ProcessPoolExecutor(max_workers=num_tasks) as executor:
            futures = [executor.submit(cpu_bound_task, fib_n) for _ in range(num_tasks)]
            for f in futures:
                f.result()
    mp_time = measure("Multiprocessing (no GIL)", multiproc)

    print()
    print(f"  [BAD] Threading slowdown:    {t_time / baseline:.2f}x (expect > 1.0)")
    print(f"  [GOOD] Multiproc speedup:     {baseline / mp_time:.2f}x (expect > 1.0)")
    print(f"  [INFO] GIL causes thread contention, multiprocessing bypasses it\n")


# ═══════════════════════════════════════════════════════════════════
# Test 2: IO 密集型 —— 多线程 vs asyncio
# ═══════════════════════════════════════════════════════════════════

def test_io_bound(num_tasks: int = 20):
    """IO 密集型对比：证明多线程在 IO 场景有效，asyncio 最优"""
    print("=" * 65)
    print(f"Test 2: IO-bound (sleep 0.1s x {num_tasks} tasks)")
    print("=" * 65)

    # 2a: 串行
    def serial():
        for _ in range(num_tasks):
            io_bound_task(0.1)
    baseline = measure("Serial (single-thread)", serial)

    # 2b: 多线程（IO 时释放 GIL，有效并行）
    def threaded():
        threads = []
        for _ in range(num_tasks):
            t = threading.Thread(target=io_bound_task, args=(0.1,))
            threads.append(t)
            t.start()
        for t in threads:
            t.join()
    t_time = measure("Threading (GIL released on IO)", threaded)

    # 2c: ThreadPoolExecutor
    def thread_pool():
        with ThreadPoolExecutor(max_workers=num_tasks) as executor:
            futures = [executor.submit(io_bound_task, 0.1) for _ in range(num_tasks)]
            for f in futures:
                f.result()
    tp_time = measure("ThreadPoolExecutor", thread_pool)

    # 2d: asyncio（最优方案）
    async def async_task():
        await asyncio.sleep(0.1)

    async def async_main():
        tasks = [async_task() for _ in range(num_tasks)]
        await asyncio.gather(*tasks)

    def run_async():
        asyncio.run(async_main())
    a_time = measure("Asyncio (best for IO)", run_async)

    print()
    print(f"  [GOOD] Threading speedup:     {baseline / t_time:.2f}x (expect >> 1)")
    print(f"  [GOOD] Asyncio speedup:       {baseline / a_time:.2f}x (expect >> 1)")
    print(f"  [INFO] For IO-bound, threading works. Asyncio is cleanest.\n")


# ═══════════════════════════════════════════════════════════════════
# Test 3: 混合负载 —— 展示 asyncio + ThreadPool 协同
# ═══════════════════════════════════════════════════════════════════

def test_mixed_workload():
    """混合负载：CPU 任务放进进程池，IO 任务用 asyncio"""
    print("=" * 65)
    print("Test 3: Mixed — async IO + ProcessPool for CPU")
    print("=" * 65)

    async def mixed_workload():
        loop = asyncio.get_running_loop()

        # CPU 部分：丢给进程池（绕过 GIL）
        cpu_tasks = [
            loop.run_in_executor(None, cpu_bound_iterative, 5_000_000)
            for _ in range(3)
        ]

        # IO 部分：asyncio 原生处理
        io_tasks = [asyncio.sleep(0.1) for _ in range(10)]

        all_tasks = cpu_tasks + io_tasks
        results = await asyncio.gather(*all_tasks)
        return results

    t0 = time.perf_counter()
    asyncio.run(mixed_workload())
    elapsed = time.perf_counter() - t0
    print(f"  Mixed workload: {elapsed:.3f}s")
    print(f"  [INFO] Default executor = ThreadPool, use ProcessPool for CPU tasks\n")


# ═══════════════════════════════════════════════════════════════════
# Test 4: GIL 的可视化证据 —— 多线程 CPU 比单线程更慢
# ═══════════════════════════════════════════════════════════════════

def test_gil_overhead():
    """定量展示 GIL 争用的开销"""
    print("=" * 65)
    print("Test 4: GIL contention overhead (counter increment)")
    print("=" * 65)

    COUNTER = 0
    ITERATIONS = 5_000_000

    # 4a: 单线程
    def single_thread_count():
        n = 0
        for _ in range(ITERATIONS):
            n += 1
        return n

    measure("Single thread counter", single_thread_count)

    # 4b: 2 线程竞争同一个计数器（不加锁）
    counter = [0]
    def thread_count_no_lock(_idx):
        for _ in range(ITERATIONS // 2):
            counter[0] += 1  # 非原子操作，GIL 不保护这个！

    def two_threads_race():
        t1 = threading.Thread(target=thread_count_no_lock, args=(0,))
        t2 = threading.Thread(target=thread_count_no_lock, args=(1,))
        t1.start(); t2.start()
        t1.join(); t2.join()
        return counter[0]

    def run_race():
        result = two_threads_race()
        return result

    measure("2 threads (race condition!)", run_race)
    print(f"    [WARN]  Expected {ITERATIONS}, got {counter[0]} (race condition!)\n")

    # 4c: 线程切换开销——两个线程各自独立计数
    def thread_independent(idx, results):
        n = 0
        for _ in range(ITERATIONS):
            n += 1
        results[idx] = n

    def two_threads_independent():
        results = [0, 0]
        t1 = threading.Thread(target=thread_independent, args=(0, results))
        t2 = threading.Thread(target=thread_independent, args=(1, results))
        t1.start(); t2.start()
        t1.join(); t2.join()
        return sum(results)

    measure("2 threads (independent)", two_threads_independent)
    print(f"    Each thread does its own counting — still slower than 1 thread")
    print(f"    [INFO] GIL serializes them, plus adds context-switch overhead\n")


# ═══════════════════════════════════════════════════════════════════
# Main
# ═══════════════════════════════════════════════════════════════════

if __name__ == "__main__":
    # Windows 下 multiprocessing 需要 freeze_support
    multiprocessing.freeze_support()

    print("Python GIL Benchmark\n")
    print(f"CPU cores: {multiprocessing.cpu_count()}")
    print(f"Threading active count: {threading.active_count()}\n")

    test_cpu_bound(num_tasks=8, fib_n=35)
    test_io_bound(num_tasks=20)
    test_mixed_workload()
    test_gil_overhead()
