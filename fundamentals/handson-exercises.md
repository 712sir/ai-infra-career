# 🔨 B 线手撕代码练习

> 原则：🥇 白板手搓（关笔记，从零写） | 🥈 临摹手搓（看完笔记，用自己的风格重写）
>
> 每个练习给出了**需求描述和验收标准**，不给你代码。参考答案在后方，写完再对照。

---

## 练习 1：unique_ptr 的所有权转移 🥇 白板

**需求**：实现一个函数，展示 `unique_ptr` 的所有权转移过程。

```
要求：
1. 创建一个 unique_ptr<string>，内容为 "hello"
2. 写一个函数 void takeOwnership(unique_ptr<string> p)，
   接收端打印 "*p = ..." 和 "p is null? ..."
3. 在主函数中先后调用：
   - takeOwnership(std::move(p1)) ← 转移所有权
   - takeOwnership(move(p1))     ← p1 已为空，验证
4. 确保 p1 在 move 后为 nullptr
```

**验收**：
- [ ] 编译运行，输出显示第一次调用有值，第二次调用为空
- [ ] 能口头解释为什么第 3 步会输出 null

**参考答案**：`fundamentals/cpp/code/smart-ptr-demo.cpp` → `demo_unique_ptr()`

---

## 练习 2：shared_ptr + weak_ptr 打破循环引用 🥇 白板 

**需求**：实现一个双向链表节点，用 `weak_ptr` 打破循环引用。

```
要求：
1. 定义 struct Node { string name; shared_ptr<Node> next; weak_ptr<Node> prev; }
2. 在析构函数中打印 "~Node(name)"
3. 创建两个节点 A 和 B，互相引用：
   - A.next = B  (shared_ptr)
   - B.prev = A  (weak_ptr)
4. 打印 A 和 B 的 use_count
5. 离开作用域，验证两个节点都被正确销毁（析构函数都被调用）
```

**验收**：
- [ ] 输出显示 A.use_count == 1, B.use_count == 2
- [ ] 离开作用域后两个节点都打印了 "~Node(...)"
- [ ] 能解释：如果 `B.prev` 也用 `shared_ptr`，会发生什么？

**参考答案**：`fundamentals/cpp/code/smart-ptr-demo.cpp` → `demo_cyclic_reference()`

---

## 练习 3：手写 @timer 装饰器 🥇 白板

**需求**：实现一个计时装饰器。

```
要求：
1. 用 functools.wraps 保留原函数元信息
2. 装饰器名为 @timer
3. 被装饰的函数调用后，打印 "func_name took X.XXXXXXs"
4. 测试用例：
   @timer
   def slow_add(n):
       return sum(range(n))
   
   result = slow_add(10**7)
   # 应输出：slow_add took 0.xxxxxxs
```

**验收**：
- [ ] 能正确打印函数名和执行时间
- [ ] `slow_add.__name__` 仍然是 `"slow_add"`（不是 `"wrapper"`）
- [ ] 返回值正确

**参考答案**：`fundamentals/python/decorators.md` → 「实用装饰器示例」→ `@timer`

---

## 练习 4：手写 @retry 装饰器（带参数） 🥈 临摹

**需求**：实现一个可配置重试次数的装饰器。

```
要求：
1. 使用三层嵌套结构（参数 → 装饰器 → wrapper）
2. 参数：times（重试次数）、delay（间隔秒数）
3. 被装饰函数抛异常时，重试 times 次，每次间隔 delay 秒
4. 用完所有重试次数后仍失败，抛出最后一次的异常

测试：
@retry(times=3, delay=0.5)
def flaky_api():
    import random
    if random.random() < 0.7:
        raise RuntimeError("fail")
    return "success"
```

**验收**：
- [ ] 70% 概率失败时，大概率会重试并最终成功
- [ ] 能解释三层嵌套每层的作用

**参考答案**：`fundamentals/python/decorators.md` → 「带参数的装饰器」→ `@retry`

---

## 练习 5：生成器实现惰性文件读取 🥇 白板

**需求**：用生成器实现大文件逐行读取（不一次加载到内存）。

```
要求：
1. 定义 read_large_file(filepath) 生成器函数
2. 逐行 yield，每行去掉尾部换行符
3. 写一个简单测试（或脑测）：计算文件总行数

# 测试
count = 0
for line in read_large_file("big_file.txt"):
    count += 1
print(f"Total lines: {count}")
```

**验收**：
- [ ] 内存占用 O(1)（不是 O(文件大小)）
- [ ] 能正确 yield 每一行

**参考答案**：`fundamentals/python/generators.md` → 「生成器 vs 列表」→ `read_large_file`

---

## 练习 6：手写简单的 Array<T, N> 类模板 🥇 白板

**需求**：实现编译期固定大小的数组模板类。

```
要求：
1. template<typename T, size_t N>
2. 数据存在栈上：T data_[N]
3. 实现：size() 返回 N，operator[] 读写元素
4. 实现：begin() / end() 返回指针（支持 range-for）
5. 测试：
   Array<int, 5> arr;
   arr[0] = 10; arr[1] = 20;
   for (auto x : arr) cout << x << " ";  // 10 20 0 0 0
```

**验收**：
- [ ] 编译通过，支持 range-for 遍历
- [ ] operator[] 能读写
- [ ] size() 在编译期确定

---

## 参考答案索引

| 练习 | 答案位置 |
|------|------|
| 1-2 | [smart-ptr-demo.cpp](ai-infra-career/fundamentals/cpp/code/smart-ptr-demo.cpp) |
| 3-4 | [decorators.md](ai-infra-career/fundamentals/python/decorators.md) |
| 5 | [generators.md](ai-infra-career/fundamentals/python/generators.md) |
| 6 | [templates.md](ai-infra-career/fundamentals/cpp/templates.md) |
