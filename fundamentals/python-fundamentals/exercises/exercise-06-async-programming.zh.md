# 练习06：面向并发 ML 操作的异步编程

## 概述

本练习学习如何使用 Python asyncio 在 ML 工作流中实现并发操作。你将掌握同时处理多个任务、提升 I/O 密集型操作性能以及构建能并发处理数据的高效 ML 管线。
## 学习目标

完成本练习后，你将能够：- 理解 async/await 语法和协程
- 为 I/O 密集型任务编写异步函数
- 使用 asyncio.gather() 实现并发执行
- 实现异步文件操作和 API 调用
- 构建异步数据加载器和预处理器
- 处理异步代码中的错误
- 理解何时使用 async、threading 或 multiprocessing
- 监控和优化异步 ML 工作流

## 前置条件

- 已完成练习 01-05
- 理解同步与异步执行的差异
- 并发编程概念基础

## 预计用时

- 预计：90-120 分钟
- 难度：中高级

## 第 1 部分：Async 基础

### 步骤 1：理解协程

```python
# 创建脚本： async_basics.py

import asyncio
import time
from typing import List

async def download_model(model_name: str) -> dict:
    """Simulate async model download"""
    print(f"Starting download: {model_name}")
    await asyncio.sleep(2)  # Simulate network delay
    print(f"Completed download: {model_name}")
    return {"name": model_name, "size": 100, "status": "downloaded"}

async def load_dataset(dataset_name: str) -> dict:
    """Simulate async dataset loading"""
    print(f"Loading dataset: {dataset_name}")
    await asyncio.sleep(1)  # Simulate I/O
    print(f"Loaded dataset: {dataset_name}")
    return {"name": dataset_name, "samples": 1000}

async def preprocess_data(data: dict) -> dict:
    """Simulate async preprocessing"""
    print(f"Preprocessing: {data['name']}")
    await asyncio.sleep(1.5)
    print(f"Preprocessed: {data['name']}")
    return {**data, "preprocessed": True}

# 顺序执行 vs 并发执行
async def sequential_execution():
    """顺序执行任务"""
    print("=== Sequential Execution ===")
    start = time.time()

    model = await download_model("resnet50")
    data = await load_dataset("imagenet")
    processed = await preprocess_data(data)

    elapsed = time.time() - start
    print(f"Sequential time: {elapsed:.2f}s\n")

async def concurrent_execution():
    """并发执行任务"""
    print("=== Concurrent Execution ===")
    start = time.time()

    # 并发运行任务
    model_task = download_model("resnet50")
    data_task = load_dataset("imagenet")

    model, data = await asyncio.gather(model_task, data_task)
    processed = await preprocess_data(data)

    elapsed = time.time() - start
    print(f"Concurrent time: {elapsed:.2f}s\n")

# 使用示例
if __name__ == "__main__":
    # 运行顺序版
    asyncio.run(sequential_execution())

    # 运行并发版
    asyncio.run(concurrent_execution())
```

### 步骤 2：多任务 Async

```python
# 创建脚本： async_multiple.py

import asyncio
import random
from typing import List, Dict

async def process_sample(sample_id: int) -> dict:
    """异步处理单个样本"""
    # 模拟可变的处理时间
    delay = random.uniform(0.1, 0.5)
    await asyncio.sleep(delay)

    return {
        "sample_id": sample_id,
        "processed": True,
        "time": delay
    }

async def process_batch_async(batch: List[int]) -> List[dict]:
    """并发处理整个批次"""
    tasks = [process_sample(sample_id) for sample_id in batch]
    results = await asyncio.gather(*tasks)
    return results

async def download_multiple_models(model_names: List[str]) -> Dict[str, dict]:
    """并发下载多个模型"""
    async def download(name: str) -> tuple:
        await asyncio.sleep(random.uniform(0.5, 2.0))
        return name, {"name": name, "downloaded": True}

    tasks = [download(name) for name in model_names]
    results = await asyncio.gather(*tasks)

    return dict(results)

# 使用示例
async def main():
    print("=== Processing Batch Async ===")
    batch = list(range(10))

    start = asyncio.get_event_loop().time()
    results = await process_batch_async(batch)
    elapsed = asyncio.get_event_loop().time() - start

    print(f"Processed {len(results)} samples in {elapsed:.2f}s")
    print(f"Average time per sample: {elapsed/len(results):.2f}s\n")

    print("=== Downloading Multiple Models ===")
    models = ["resnet50", "vgg16", "mobilenet", "efficientnet"]

    start = asyncio.get_event_loop().time()
    downloaded = await download_multiple_models(models)
    elapsed = asyncio.get_event_loop().time() - start

    print(f"Downloaded {len(downloaded)} models in {elapsed:.2f}s")
    print(f"Models: {list(downloaded.keys())}")

if __name__ == "__main__":
    asyncio.run(main())
```

## 第 2 部分：异步文件操作

### 步骤 3：异步文件 I/O

```python
# 创建脚本： async_file_io.py

import asyncio
import aiofiles
from pathlib import Path
from typing import List, Dict

async def read_file_async(filepath: str) -> str:
    """异步读取文件"""
    async with aiofiles.open(filepath, 'r') as f:
        content = await f.read()
    return content

async def write_file_async(filepath: str, content: str) -> None:
    """异步写入文件"""
    async with aiofiles.open(filepath, 'w') as f:
        await f.write(content)

async def read_multiple_files(filepaths: List[str]) -> Dict[str, str]:
    """并发读取多个文件"""
    async def read_one(path: str) -> tuple:
        content = await read_file_async(path)
        return path, content

    tasks = [read_one(path) for path in filepaths]
    results = await asyncio.gather(*tasks, return_exceptions=True)

    # 过滤异常结果
    successful = {}
    for result in results:
        if isinstance(result, tuple):
            path, content = result
            successful[path] = content

    return successful

async def process_csv_async(filepath: str) -> List[Dict]:
    """异步处理 CSV 文件"""
    import csv

    async with aiofiles.open(filepath, 'r') as f:
        content = await f.read()

    # Parse CSV
    lines = content.strip().split('\n')
    if not lines:
        return []

    import io
    reader = csv.DictReader(io.StringIO(content))
    return list(reader)

async def save_predictions_async(filepath: str,
                                 predictions: List[Dict]) -> None:
    """异步保存预测结果"""
    import csv
    import io

    # Convert to CSV string
    if not predictions:
        return

    output = io.StringIO()
    writer = csv.DictWriter(output, fieldnames=predictions[0].keys())
    writer.writeheader()
    writer.writerows(predictions)

    # Write asynchronously
    async with aiofiles.open(filepath, 'w') as f:
        await f.write(output.getvalue())

# 使用示例
async def main():
    # 创建样本文件
    print("=== Creating Sample Files ===")
    for i in range(5):
        await write_file_async(f"data_{i}.txt", f"Content of file {i}\n" * 10)
    print("✓ Created 5 sample files\n")

    # 读取多个文件
    print("=== Reading Multiple Files ===")
    filepaths = [f"data_{i}.txt" for i in range(5)]

    start = asyncio.get_event_loop().time()
    contents = await read_multiple_files(filepaths)
    elapsed = asyncio.get_event_loop().time() - start

    print(f"Read {len(contents)} files in {elapsed:.2f}s")

    # 保存预测结果
    predictions = [
        {"sample_id": i, "prediction": 0.9, "label": 1}
        for i in range(100)
    ]

    await save_predictions_async("predictions.csv", predictions)
    print("✓ Saved predictions")

if __name__ == "__main__":
    asyncio.run(main())
```

## 第 3 部分：异步 API 调用

### 步骤 4：并发 API 请求

```python
# 创建脚本： async_api_calls.py

import asyncio
import aiohttp
from typing import List, Dict, Optional

async def fetch_model_metadata(session: aiohttp.ClientSession,
                               model_id: str) -> Dict:
    """从 API 获取模型元数据"""
    url = f"https://api.example.com/models/{model_id}"

    try:
        async with session.get(url, timeout=aiohttp.ClientTimeout(total=10)) as response:
            if response.status == 200:
                data = await response.json()
                return {"model_id": model_id, "data": data, "success": True}
            else:
                return {"model_id": model_id, "error": f"Status {response.status}", "success": False}
    except asyncio.TimeoutError:
        return {"model_id": model_id, "error": "Timeout", "success": False}
    except Exception as e:
        return {"model_id": model_id, "error": str(e), "success": False}

async def fetch_multiple_models(model_ids: List[str]) -> List[Dict]:
    """并发获取多个模型的元数据"""
    async with aiohttp.ClientSession() as session:
        tasks = [fetch_model_metadata(session, model_id) for model_id in model_ids]
        results = await asyncio.gather(*tasks)
        return results

async def batch_inference_api(samples: List[Dict],
                              api_url: str,
                              batch_size: int = 10) -> List[Dict]:
    """批量发送样本到推理 API"""
    async def send_batch(session: aiohttp.ClientSession, batch: List[Dict]) -> Dict:
        try:
            async with session.post(api_url, json={"samples": batch}) as response:
                return await response.json()
        except Exception as e:
            return {"error": str(e), "success": False}

    # 拆分为批次
    batches = [samples[i:i+batch_size] for i in range(0, len(samples), batch_size)]

    async with aiohttp.ClientSession() as session:
        tasks = [send_batch(session, batch) for batch in batches]
        results = await asyncio.gather(*tasks)
        return results

# 使用示例 (with mock server)
async def main():
    print("=== Async API Calls (Mock) ===")

    # Simulate API calls
    model_ids = [f"model_{i}" for i in range(10)]

    print(f"Fetching metadata for {len(model_ids)} models...")

    # 注：真实 API 会失败，但演示了使用模式
    # 有真实 API 端点时取消注释
    # results = await fetch_multiple_models(model_ids)
    # successful = [r for r in results if r.get("success")]
    # print(f"Successfully fetched: {len(successful)}/{len(model_ids)}")

    print("✓ API call pattern demonstrated")

if __name__ == "__main__":
    asyncio.run(main())
```

## 第 4 部分：异步数据管线

### 步骤 5：构建异步 ML 管线

```python
# 创建脚本： async_ml_pipeline.py

import asyncio
from typing import List, Dict, Optional
from dataclasses import dataclass
import time

@dataclass
class Sample:
    """数据样本"""
    id: int
    data: List[float]
    processed: bool = False
    predicted: bool = False

class AsyncMLPipeline:
    """异步 ML 管线"""

    def __init__(self, batch_size: int = 32):
        self.batch_size = batch_size

    async def load_data(self, num_samples: int) -> List[Sample]:
        """异步加载数据"""
        print(f"Loading {num_samples} samples...")
        await asyncio.sleep(0.5)  # Simulate I/O

        samples = [
            Sample(id=i, data=[float(i) * 0.1] * 10)
            for i in range(num_samples)
        ]

        print(f"✓ Loaded {len(samples)} samples")
        return samples

    async def preprocess_sample(self, sample: Sample) -> Sample:
        """预处理单个样本"""
        await asyncio.sleep(0.01)  # Simulate processing
        sample.processed = True
        return sample

    async def preprocess_batch(self, samples: List[Sample]) -> List[Sample]:
        """并发预处理样本批次"""
        tasks = [self.preprocess_sample(s) for s in samples]
        return await asyncio.gather(*tasks)

    async def predict_sample(self, sample: Sample) -> Sample:
        """对单个样本运行推理"""
        await asyncio.sleep(0.02)  # Simulate inference
        sample.predicted = True
        return sample

    async def predict_batch(self, samples: List[Sample]) -> List[Sample]:
        """并发运行批次推理"""
        tasks = [self.predict_sample(s) for s in samples]
        return await asyncio.gather(*tasks)

    async def run_pipeline(self, num_samples: int) -> Dict[str, any]:
        """运行完整的异步管线"""
        start_time = time.time()

        # 加载数据
        samples = await self.load_data(num_samples)

        # 分批预处理
        print(f"Preprocessing {len(samples)} samples...")
        batches = [samples[i:i+self.batch_size]
                  for i in range(0, len(samples), self.batch_size)]

        preprocessed = []
        for batch in batches:
            batch_result = await self.preprocess_batch(batch)
            preprocessed.extend(batch_result)

        print(f"✓ Preprocessed {len(preprocessed)} samples")

        # 分批推理
        print(f"Running inference on {len(preprocessed)} samples...")
        predicted = []
        for batch in [preprocessed[i:i+self.batch_size]
                     for i in range(0, len(preprocessed), self.batch_size)]:
            batch_result = await self.predict_batch(batch)
            predicted.extend(batch_result)

        print(f"✓ Predicted {len(predicted)} samples")

        elapsed = time.time() - start_time

        return {
            "total_samples": len(predicted),
            "time_elapsed": elapsed,
            "samples_per_second": len(predicted) / elapsed
        }

# 使用示例
async def main():
    print("=== Async ML Pipeline ===\n")

    pipeline = AsyncMLPipeline(batch_size=32)
    results = await pipeline.run_pipeline(num_samples=200)

    print(f"\n=== Results ===")
    print(f"Total samples: {results['total_samples']}")
    print(f"Time elapsed: {results['time_elapsed']:.2f}s")
    print(f"Throughput: {results['samples_per_second']:.1f} samples/sec")

if __name__ == "__main__":
    asyncio.run(main())
```

## 第 5 部分：异步代码中的错误处理

### 步骤 6：异步异常处理

```python
# 创建脚本： async_error_handling.py

import asyncio
from typing import List, Dict, Optional
import logging

logging.basicConfig(level=logging.INFO)
logger = logging.getLogger(__name__)

async def risky_operation(task_id: int, failure_rate: float = 0.3) -> Dict:
    """可能失败的操作"""
    import random

    await asyncio.sleep(0.1)

    if random.random() < failure_rate:
        raise ValueError(f"Task {task_id} failed")

    return {"task_id": task_id, "result": "success"}

async def safe_risky_operation(task_id: int) -> Dict:
    """用错误处理包装风险操作"""
    try:
        result = await risky_operation(task_id)
        return result
    except ValueError as e:
        logger.warning(f"Task {task_id} failed: {e}")
        return {"task_id": task_id, "result": "failed", "error": str(e)}
    except Exception as e:
        logger.error(f"Unexpected error in task {task_id}: {e}")
        return {"task_id": task_id, "result": "error", "error": str(e)}

async def run_tasks_with_error_handling(num_tasks: int) -> Dict[str, int]:
    """用错误处理运行多个任务"""
    tasks = [safe_risky_operation(i) for i in range(num_tasks)]
    results = await asyncio.gather(*tasks)

    # 统计结果
    successful = sum(1 for r in results if r["result"] == "success")
    failed = sum(1 for r in results if r["result"] == "failed")
    errors = sum(1 for r in results if r["result"] == "error")

    return {
        "total": num_tasks,
        "successful": successful,
        "failed": failed,
        "errors": errors
    }

async def retry_async(func, *args, max_retries: int = 3, **kwargs):
    """失败时重试异步函数"""
    for attempt in range(max_retries):
        try:
            return await func(*args, **kwargs)
        except Exception as e:
            if attempt == max_retries - 1:
                raise
            logger.warning(f"Attempt {attempt + 1} failed, retrying...")
            await asyncio.sleep(0.5 * (attempt + 1))

# 使用示例
async def main():
    print("=== Async Error Handling ===\n")

    stats = await run_tasks_with_error_handling(20)

    print(f"Results:")
    print(f"  Total: {stats['total']}")
    print(f"  Successful: {stats['successful']}")
    print(f"  Failed: {stats['failed']}")
    print(f"  Errors: {stats['errors']}")

if __name__ == "__main__":
    asyncio.run(main())
```

## 第 6 部分：何时使用 Async

### 步骤 7：Async vs Threading vs Multiprocessing

```python
# 创建脚本： concurrency_comparison.py

import asyncio
import time
import threading
import multiprocessing
from typing import List

def cpu_bound_task(n: int) -> int:
    """CPU 密集型任务"""
    result = sum(i * i for i in range(n))
    return result

def io_bound_task(duration: float) -> str:
    """I/O 密集型任务（模拟）"""
    time.sleep(duration)
    return "completed"

async def io_bound_task_async(duration: float) -> str:
    """异步 I/O 密集型任务"""
    await asyncio.sleep(duration)
    return "completed"

# 同步基线
def sync_io_tasks(num_tasks: int):
    """同步运行 I/O 任务"""
    start = time.time()

    for _ in range(num_tasks):
        io_bound_task(0.1)

    return time.time() - start

# 异步版本
async def async_io_tasks(num_tasks: int):
    """异步运行 I/O 任务"""
    start = time.time()

    tasks = [io_bound_task_async(0.1) for _ in range(num_tasks)]
    await asyncio.gather(*tasks)

    return time.time() - start

# 线程版本
def threaded_io_tasks(num_tasks: int):
    """用线程运行 I/O 任务"""
    start = time.time()

    threads = []
    for _ in range(num_tasks):
        thread = threading.Thread(target=io_bound_task, args=(0.1,))
        thread.start()
        threads.append(thread)

    for thread in threads:
        thread.join()

    return time.time() - start

def compare_approaches():
    """对比不同的并发方式"""
    num_tasks = 10

    print("=== I/O-Bound Task Comparison ===")
    print(f"Number of tasks: {num_tasks}\n")

    # 同步
    sync_time = sync_io_tasks(num_tasks)
    print(f"Synchronous: {sync_time:.2f}s")

    # 异步
    async_time = asyncio.run(async_io_tasks(num_tasks))
    print(f"Async: {async_time:.2f}s")

    # 线程
    threaded_time = threaded_io_tasks(num_tasks)
    print(f"Threading: {threaded_time:.2f}s\n")

    print(f"Async speedup: {sync_time/async_time:.1f}x")
    print(f"Threading speedup: {sync_time/threaded_time:.1f}x")

if __name__ == "__main__":
    compare_approaches()

    print("\n=== 使用指南 ===")
    print("Async 适用：")
    print("  - I/O-bound tasks (file, network, database)")
    print("  - Many concurrent operations")
    print("  - API calls and web scraping")
    print("\nUse Threading for:")
    print("  - I/O-bound tasks in sync code")
    print("  - Moderate concurrency")
    print("\nUse Multiprocessing for:")
    print("  - CPU-bound tasks")
    print("  - Parallel computation")
    print("  - Training multiple models")
```

## 验证

```python
# 创建脚本： validate_async.py

async def validate_async_basics():
    """验证 async 基础"""
    async def test_func():
        await asyncio.sleep(0.1)
        return "success"

    result = await test_func()
    assert result == "success", "Async function failed"
    print("✓ Async basics work")

async def validate_gather():
    """验证 asyncio.gather()"""
    async def task(n):
        await asyncio.sleep(0.1)
        return n * 2

    results = await asyncio.gather(task(1), task(2), task(3))
    assert results == [2, 4, 6], "Gather failed"
    print("✓ asyncio.gather() works")

async def validate_error_handling():
    """验证异步错误处理"""
    async def failing_task():
        raise ValueError("Test error")

    try:
        await failing_task()
        assert False, "Should have raised error"
    except ValueError:
        print("✓ Async error handling works")

async def main():
    print("=== Async Validation ===\n")
    await validate_async_basics()
    await validate_gather()
    await validate_error_handling()
    print("\n✓ All validations passed!")

if __name__ == "__main__":
    asyncio.run(main())
```

## 思考题

1. 何时用 async，何时用 threading？2. asyncio 如何提升 I/O 密集型任务的性能？3. 异步编程有哪些局限性？4. 如何调试异步代码？5. 什么时候 multiprocessing 比 async 更好？6. 如何处理并发任务中的错误？7. 异步 ML 管线需要哪些监控？
## 下一步

- **练习07**：使用 pytest-asyncio 测试异步代码
- **模块002**：Linux 基础
- **项目01**：构建完整的异步 ML 管线

## 补充资源

- Asyncio Documentation: https://docs.python.org/3/library/asyncio.html
- Real Python Async Guide: https://realpython.com/async-io-python/
- aiohttp: https://docs.aiohttp.org/
- aiofiles: https://github.com/Tinche/aiofiles

---

**恭喜！** 你已掌握面向并发 ML 操作的异步编程。你现在可以构建高效、高性能的 ML 管线，同时处理多个任务。