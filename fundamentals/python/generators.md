# Python 生成器与迭代器（Generators & Iterators）

> 来源：《Fluent Python》Ch14: Iterables, Iterators, and Generators
> 状态：🟡 笔记整理中
> 面试权重：⭐⭐（AI Infra 场景：流式推理输出、大数据集 lazy 加载）

---

## 迭代器协议

### 基础

```python
# 可迭代对象 (Iterable)：实现了 __iter__，返回迭代器
# 迭代器 (Iterator)：实现了 __iter__ + __next__

# for 循环的幕后：
for item in obj:
    do_something(item)

# 等价于：
it = iter(obj)        # obj.__iter__() → 返回迭代器
while True:
    try:
        item = next(it)  # it.__next__() → 返回下一个元素
        do_something(item)
    except StopIteration:
        break
```

### 手写迭代器

```python
class CountDown:
    """从 n 倒数到 1 的迭代器"""
    def __init__(self, start):
        self.current = start

    def __iter__(self):
        return self  # 迭代器返回自身

    def __next__(self):
        if self.current <= 0:
            raise StopIteration
        self.current -= 1
        return self.current + 1

for n in CountDown(3):
    print(n)  # → 3, 2, 1

# 注意：迭代器只能用一次！
cd = CountDown(3)
list(cd)  # → [3, 2, 1]
list(cd)  # → [] （已经耗尽了！）
```

---

## 生成器函数

### yield 核心

```python
# 生成器 = 有 yield 的函数
def countdown(n):
    while n > 0:
        yield n    # "产出"值并暂停，状态保留
        n -= 1

g = countdown(3)
next(g)  # → 3
next(g)  # → 2
next(g)  # → 1
next(g)  # → StopIteration

# 生成器自动实现了迭代器协议
for num in countdown(3):
    print(num)  # → 3, 2, 1
```

### 生成器 vs 列表（内存优势）

```python
# 场景：读大文件（可能 100GB）
def read_large_file(filepath):
    """逐行读取，内存占用 O(1)"""
    with open(filepath) as f:
        for line in f:
            yield line.strip()

# 对比：
# lines = open(filepath).readlines()  # ← 100GB 文件直接 OOM
# for line in read_large_file(path):  # ← 一次只持有一行，安全
```

### 生成器表达式

```python
# 列表推导 → 一次性创建（占内存）
squares_list = [x**2 for x in range(10**6)]  # 1M 个 int 在内存中

# 生成器表达式 → 惰性计算（省内存）
squares_gen = (x**2 for x in range(10**6))   # 几乎不占内存

sum(squares_gen)  # 逐个计算，逐个累加
```

---

## yield from

```python
# yield from = 委托给子生成器
def chain(*iterables):
    """将多个可迭代对象串起来"""
    for it in iterables:
        yield from it

list(chain('AB', 'CD', 'EF'))  # → ['A','B','C','D','E','F']

# 等价于（但更简洁高效）：
def chain_manual(*iterables):
    for it in iterables:
        for item in it:
            yield item
```

---

## AI Infra 中的实际用途

### 1. 流式 Token 生成

```python
def generate_stream(model, prompt, max_tokens=100):
    """推理引擎流式输出：每生成一个 token 就 yield"""
    tokens = model.encode(prompt)
    for _ in range(max_tokens):
        logits = model(tokens[-model.context_len:])  # __call__ 而非 forward()（触发 hooks）
        next_token = sample(logits)          # 采样
        yield model.decode([next_token])     # 产出文本片段
        tokens.append(next_token)
        if next_token == model.config.eos_token_id:
            break

# 使用：打字机效果
for chunk in generate_stream(model, "Once upon a time"):
    print(chunk, end='', flush=True)
```

### 2. 惰性数据集加载

```python
import numpy as np
import glob

def load_sharded_dataset(pattern, batch_size):
    """分片加载训练数据——不用全读到内存"""
    for shard_path in sorted(glob.glob(pattern)):
        shard = np.load(shard_path)          # 只加载当前分片
        for i in range(0, len(shard), batch_size):
            yield shard[i:i + batch_size]    # 按 batch 产出

# 内存友好：可以处理 TB 级数据集
for batch in load_sharded_dataset("data/train_*.npy", 32):
    model.train_step(batch)
```

---

## 面试高频问题

| 问题 | 答案 |
|------|------|
| 迭代器 vs 可迭代对象？ | Iterable 有 `__iter__`；Iterator 有 `__iter__` + `__next__` |
| yield 做了什么？ | 暂停函数执行、保留局部状态、返回调用方 |
| 生成器能用几次？ | 一次（耗尽后 StopIteration） |
| list vs generator 内存？ | list O(N)，generator O(1) |
| `yield from` 干什么？ | 委托给子生成器，简化嵌套迭代 |
| 生成器的 send/throw/close？ | send 传入值、throw 抛异常、close 终止 |
