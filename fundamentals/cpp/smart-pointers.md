# C++ 智能指针（Smart Pointers）

> 来源：《Effective Modern C++》Item 17–25
> 状态：🟡 笔记整理中
> 面试权重：⭐⭐⭐（AI Infra 面试必问）

---

## 为什么需要智能指针

### C++ 内存管理的痛点

```cpp
// 裸指针的问题
void bad_code() {
    Widget* w = new Widget();  // ① 分配内存
    // ...
    if (some_error)
        return;                // ② 提前返回 → w 泄漏！
    // ...
    delete w;                  // ③ 忘记 delete → 泄漏
    w->doSomething();          // ④ delete 后使用 → UB
    delete w;                  // ⑤ 重复 delete → UB
}
```

智能指针 = **RAII**（Resource Acquisition Is Initialization）：把资源生命周期绑定到对象生命周期。

---

## 三种智能指针

| 指针 | 所有权 | 引用计数 | 典型场景 |
|------|--------|:--:|------|
| `unique_ptr` | 独占 | 无（零开销） | 工厂函数、容器元素、PIMPL |
| `shared_ptr` | 共享 | 有（原子操作） | 共享对象、观察者模式、循环引用需配合 weak_ptr |
| `weak_ptr` | 观察（不拥有） | 有（不增加 use_count） | 缓存、打破循环引用、观察者 |

---

## unique_ptr

### 基本用法

```cpp
#include <memory>

// 创建（推荐 make_unique，C++14）
auto p1 = std::make_unique<Widget>();          // C++14 推荐
std::unique_ptr<Widget> p2(new Widget());       // C++11

// 所有权转移
auto p3 = std::move(p1);    // p1 变为 nullptr，p3 拥有对象
// auto p4 = p1;            // ❌ 编译错误：unique_ptr 不可拷贝

// 自定义 deleter
auto deleter = [](FILE* f) { fclose(f); };
std::unique_ptr<FILE, decltype(deleter)> fp(fopen("a.txt", "r"), deleter);
```

### 内存布局（零开销）

```
unique_ptr<Widget>
┌──────────┐
│ raw ptr  │──────→ [Widget Object]
└──────────┘
与裸指针大小完全相同（sizeof == 8 字节，64位）
```

### 关键面试点

```cpp
// Q: make_unique vs new + unique_ptr？
auto p1 = std::make_unique<Widget>(arg1, arg2);  // ✓ 推荐：异常安全
std::unique_ptr<Widget> p2(new Widget(arg1, arg2)); // ✗ 不推荐

// 异常安全场景：
process(std::unique_ptr<Widget>(new Widget), mayThrow());
//   ① new Widget           ← 先执行
//   ② unique_ptr 构造       ← 编译器可重排为 ①→③→②！
//   ③ mayThrow()           ← 如果这里抛异常，Widget 泄漏！
// → 用 make_unique 就没有这个问题
```

---

## shared_ptr

### 基本用法

```cpp
auto sp1 = std::make_shared<Widget>();  // 推荐
auto sp2 = sp1;          // sp2 和 sp1 共享同一对象，引用计数 = 2
sp2.reset();             // sp2 释放引用，计数 = 1
sp1.reset();             // sp1 释放引用，计数 = 0 → Widget 被销毁
```

### 内存布局（控制块）

```
shared_ptr<Widget>   (sp1)      控制块 (Control Block)       Widget 对象
┌──────────────┐    ┌───────┐   ┌─────────────────┐       ┌──────────┐
│ ptr → Widget │───→│       │   │ use_count  = 2  │       │ Widget   │
│ ptr → CtrlBlk│───→│       │──→│ weak_count = 0  │   ┌──→│          │
└──────────────┘    └───────┘   │ deleter         │   │   └──────────┘
                                │ allocator       │   │
shared_ptr<Widget>   (sp2)      └─────────────────┘   │
┌──────────────┐                                      │
│ ptr → Widget │──────────────────────────────────────┘
│ ptr → CtrlBlk│───→ 控制块
└──────────────┘
```

**控制块包含**：use_count、weak_count、deleter、allocator

### make_shared 的内存优势

```cpp
// 方式 1：分离分配（两次 new）
std::shared_ptr<Widget> sp(new Widget);
// new Widget → 1 次堆分配（对象）
// new ControlBlock → 1 次堆分配（控制块）
// 总计：2 次堆分配

// 方式 2：合并分配（一次 new）
auto sp = std::make_shared<Widget>();
// make_shared → 1 次堆分配（对象 + 控制块紧邻）
// 总计：1 次堆分配 + 更好的缓存局部性！
```

### 关键面试点

```cpp
// Q1: enable_shared_from_this 有什么用？
class Widget : public std::enable_shared_from_this<Widget> {
public:
    std::shared_ptr<Widget> getShared() {
        return shared_from_this();  // 安全：返回已存在的 shared_ptr
    }
    // ❌ 不能这样做：
    // std::shared_ptr<Widget> getShared() {
    //     return std::shared_ptr<Widget>(this);  // 创建新的控制块 → double free!
    // }
};

auto sp = std::make_shared<Widget>();
auto sp2 = sp->getShared();  // sp2 和 sp 共享同一个控制块 ✓

// Q2: shared_ptr 的引用计数的线程安全性？
// → use_count 的增减是原子的（atomic），但对象本身的访问需要你加锁
// → 只有控制块的引用计数是线程安全的，不是对象本身！
```

---

## weak_ptr

### 作用

```cpp
// 1. 打破循环引用（最经典场景）
struct Node {
    std::shared_ptr<Node> next;
    std::weak_ptr<Node>   prev;  // ← 用 weak_ptr 打破循环！
    ~Node() { std::cout << "Node destroyed\n"; }
};

// 2. 缓存/观察者模式
std::weak_ptr<ExpensiveData> cache;
auto sp = cache.lock();  // 尝试获取 shared_ptr
if (sp) {
    // 对象还存在，使用它
} else {
    // 对象已被销毁，重新创建
    sp = std::make_shared<ExpensiveData>(...);
    cache = sp;
}
```

### weak_ptr::lock() 原理

```cpp
// 简化实现思路
std::shared_ptr<T> lock() const {
    if (control_block->use_count == 0)
        return std::shared_ptr<T>();  // 空指针
    // 原子地递增 use_count
    return std::shared_ptr<T>(ptr, control_block);
    // ↑ 如果此时另一个线程正在析构最后一个 shared_ptr...
    // 需要原子 CAS 操作来保证正确性
}
```

---

## 面试速查表

| 问题 | 答案 |
|------|------|
| unique_ptr 大小？ | 等于裸指针（通常 8 字节），自定义 deleter 可能变大 |
| shared_ptr 大小？ | 两个裸指针大小（通常 16 字节） |
| weak_ptr 大小？ | 同 shared_ptr（16 字节） |
| make_shared 优势？ | 一次分配（对象+控制块），异常安全，更好的局部性 |
| make_shared 劣势？ | 无法自定义 deleter，weak_ptr 存在时对象内存延迟释放 |
| shared_ptr 线程安全？ | 控制块引用计数的增减是原子的，对象本身需要外部同步 |
| enable_shared_from_this 原理？ | 对象内部存储 weak_ptr，shared_from_this() 通过 lock() 返回 |
| 循环引用怎么解决？ | 一方用 weak_ptr 替代 shared_ptr |
| unique_ptr 如何转移所有权？ | std::move，不可拷贝只可移动 |
| weak_ptr 什么时候用？ | 打破循环引用、缓存、观察者模式 |
