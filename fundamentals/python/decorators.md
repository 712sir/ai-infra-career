# Python 装饰器（Decorators）

> 来源：《Fluent Python》Ch7: Decorators and Closures
> 状态：🟡 笔记整理中
> 面试权重：⭐⭐（AI Infra 中常用于 runtime hook、profile、缓存）

---

## 基础概念

### 函数是一等公民

```python
# 在 Python 中，函数就是对象
def add(x, y):
    return x + y

f = add              # 函数赋值给变量
f(1, 2)              # → 3

def apply(func, x, y):
    return func(x, y)

apply(add, 1, 2)     # → 3  (函数作为参数)
```

### 闭包（Closure）

```python
# 闭包 = 函数 + 它捕获的外部变量
def make_multiplier(n):
    def multiplier(x):
        return x * n    # n 被"捕获"到闭包中
    return multiplier

double = make_multiplier(2)
triple = make_multiplier(3)

double(5)   # → 10
triple(5)   # → 15

# 查看闭包捕获的变量
double.__code__.co_freevars   # → ('n',)
double.__closure__[0].cell_contents  # → 2
```

---

## 装饰器原理

### 本质：语法糖

```python
@decorator
def target():
    ...

# 等价于：
def target():
    ...
target = decorator(target)  # 装饰器是一个函数，接收函数，返回函数
```

### 从简单开始

```python
# 装饰器模板
def my_decorator(func):
    import functools

    @functools.wraps(func)  # ← 保留原函数的 __name__, __doc__ 等元信息
    def wrapper(*args, **kwargs):
        # 前置操作
        print(f"Calling {func.__name__}")
        result = func(*args, **kwargs)
        # 后置操作
        print(f"Returned: {result}")
        return result
    return wrapper

@my_decorator
def greet(name):
    """Say hello to someone."""
    return f"Hello, {name}!"

greet("World")
# Calling greet
# Returned: Hello, World!
```

### 关键：`functools.wraps` 是必须的

```python
# 没有 @wraps → 元信息丢失
def bad_decorator(func):
    def wrapper(*args, **kwargs):
        return func(*args, **kwargs)
    return wrapper

@bad_decorator
def foo():
    "docstring"
    pass

foo.__name__  # → 'wrapper'   ← 错了！
foo.__doc__   # → None        ← 丢了！

# 有 @wraps → 正确
def good_decorator(func):
    @functools.wraps(func)
    def wrapper(*args, **kwargs):
        return func(*args, **kwargs)
    return wrapper

@good_decorator
def bar():
    "docstring"
    pass

bar.__name__  # → 'bar'       ← 正确！
bar.__doc__   # → 'docstring' ← 正确！
```

---

## 带参数的装饰器

```python
# 需求：@retry(times=3, delay=1) → 可配置重试次数和间隔

# 实现：三层嵌套！
def retry(times=3, delay=1.0):
    """失败后重试 times 次，每次间隔 delay 秒"""
    def decorator(func):                    # 第二层：真正的装饰器
        @functools.wraps(func)
        def wrapper(*args, **kwargs):       # 第三层：包装函数
            import time
            last_exc = None
            for attempt in range(times):
                try:
                    return func(*args, **kwargs)
                except Exception as e:
                    last_exc = e
                    print(f"Attempt {attempt+1}/{times} failed: {e}")
                    if attempt < times - 1:
                        time.sleep(delay)
            raise last_exc
        return wrapper
    return decorator                         # 第一层返回装饰器

@retry(times=3, delay=0.5)
def unstable_api():
    ...

# 拆解：
# retry(times=3, delay=0.5)  → 返回 decorator
# @decorator                 → func = decorator(func) = wrapper
```

---

## 实用装饰器示例

```python
import functools
import time

# 1. @timer: 计时（面试手写高频）
def timer(func):
    @functools.wraps(func)
    def wrapper(*args, **kwargs):
        start = time.perf_counter()
        result = func(*args, **kwargs)
        elapsed = time.perf_counter() - start
        print(f"{func.__name__} took {elapsed:.6f}s")
        return result
    return wrapper

# 2. @cache: 简单的函数结果缓存
def cache(func):
    memo = {}
    @functools.wraps(func)
    def wrapper(*args):
        if args not in memo:
            memo[args] = func(*args)
        return memo[args]
    return wrapper

# 3. @singleton: 单例模式
def singleton(cls):
    instances = {}
    @functools.wraps(cls)
    def get_instance(*args, **kwargs):
        if cls not in instances:
            instances[cls] = cls(*args, **kwargs)
        return instances[cls]
    return get_instance

# 4. @log_args: 参数日志（AI Infra 常用于 debug）
def log_args(func):
    @functools.wraps(func)
    def wrapper(*args, **kwargs):
        print(f"[LOG] {func.__name__}(args={args}, kwargs={kwargs})")
        return func(*args, **kwargs)
    return wrapper
```

---

## 面试高频问题

| 问题 | 答案 |
|------|------|
| 装饰器原理？ | 语法糖，接收函数返回新函数 |
| `functools.wraps` 作用？ | 保留原函数的 `__name__`、`__doc__` 等元信息 |
| 带参数装饰器怎么写？ | 三层嵌套：`factory(config) → decorator(func) → wrapper(*args)` |
| 闭包是什么？ | 函数捕获其外部作用域的变量，形成闭包 |
| 如何获取闭包变量？ | `func.__closure__[i].cell_contents` |
| `@staticmethod` vs `@classmethod`？ | staticmethod 无默认参数，classmethod 第一个参数是 cls |
