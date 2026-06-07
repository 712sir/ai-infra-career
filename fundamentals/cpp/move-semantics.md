# C++ Move 语义与完美转发

> 来源：《Effective Modern C++》Item 23–29
> 状态：🟡 笔记整理中
> 面试权重：⭐⭐⭐

---

## 基础概念

### 左值 vs 右值（直觉版）

```cpp
int a = 42;          // a 是左值：有名字、有地址、可被赋值
int b = a;           // a 作为左值使用

int c = a + b;       // (a+b) 是右值：临时值、无地址、用完即销毁

int&& r = std::move(a);  // r 是右值引用，绑定到 a（a 仍然有效）
int&& r2 = 42;           // 右值引用绑定到字面量
```

| 概念 | 口语表达 | 识别方法 |
|------|----------|----------|
| 左值 (lvalue) | "有名有姓的" | 可以取地址 `&x` |
| 右值 (xvalue + prvalue) | "临时的/无名无姓的" | 不能取地址 |
| 右值引用 (`T&&`) | "我绑定到右值" | 用于 move 语义 |
| 万能引用 (`T&&` + 模板) | "我可能绑定到任何东西" | 需要 `std::forward` |

---

## Move 语义

### 为什么需要 Move

```cpp
// Copy：昂贵的深拷贝
std::vector<int> v2 = v1;  // 拷贝所有元素 → 可能几 GB

// Move：廉价的指针交换
std::vector<int> v3 = std::move(v1);  // 只交换内部指针 → O(1)
// v1 变为空（处于"有效但未指定"状态）
```

```cpp
// Move 的底层原理：转交资源所有权
template<typename T>
class vector {
    T* data_;       // 指向堆内存
    size_t size_;
    size_t capacity_;
public:
    // 拷贝构造：复制所有元素（昂贵）
    vector(const vector& other)
        : data_(new T[other.capacity_])
        , size_(other.size_)
        , capacity_(other.capacity_) {
        std::copy(other.data_, other.data_ + size_, data_);  // O(N)
    }

    // 移动构造：交换指针（廉价）
    vector(vector&& other) noexcept
        : data_(other.data_)      // "偷"走指针
        , size_(other.size_)
        , capacity_(other.capacity_) {
        other.data_ = nullptr;     // 源对象置空（避免 double free）
        other.size_ = 0;
        other.capacity_ = 0;
    }                              // O(1)！
};
```

### Move 的关键规则

```cpp
// 规则 1：move 后，源对象处于"有效但未指定"状态
std::string s1 = "hello";
std::string s2 = std::move(s1);
// s1 现在是什么？不知道。但它可以安全地：
s1.clear();         // ✓ 重置状态
s1 = "world";       // ✓ 赋值新值
// std::cout << s1; // 可以，但不知道输出什么

// 规则 2：移动构造函数标记 noexcept 很重要！
std::vector<MyType> v;
v.push_back(MyType());  // vector 扩容时，如果移动构造是 noexcept 的
                        // 就用移动，否则用拷贝！所以：
class MyType {
public:
    MyType(MyType&&) noexcept = default;  // ← 一定要加 noexcept！
};

// 规则 3：不要对 const 对象 move
const std::string s3 = "hello";
std::string s4 = std::move(s3);  // 调用的是拷贝构造！因为 const T&& 不能绑定到 T&&
                                  // （无法丢弃 const），回退匹配 const T& → 拷贝构造
```

---

## std::forward 与万能引用

### 万能引用 (Universal/Forwarding Reference)

```cpp
// 什么样的 T&& 是万能引用？
template<typename T>
void f(T&& param);      // ✓ 万能引用（有类型推导）

void g(Widget&& param); // ✗ 右值引用（无类型推导）

template<typename T>
class Widget {
    void h(T&& param);  // ✗ 右值引用（T 是类模板参数，已在类实例化时确定）
};

// push_back 的两种重载
template<typename T>
class vector {
    void push_back(const T& value);  // 左值版本
    void push_back(T&& value);       // 右值引用（T 已确定）

    template<typename... Args>
    void emplace_back(Args&&... args);  // 万能引用！
};
```

### Move vs Forward

```cpp
// 口诀：
// std::move  = 无条件转换为右值（"我不管你是啥，给我转"）
// std::forward = 有条件转发（"左值保持左值，右值变成右值"）

// 典型用法：转发函数
template<typename T, typename Arg>
std::shared_ptr<T> factory(Arg&& arg) {
    // forward 保留了 arg 的原始类型属性
    return std::make_shared<T>(std::forward<Arg>(arg));
}

std::string s = "hello";
auto p1 = factory<Widget>(s);             // arg 是左值 → 拷贝
auto p2 = factory<Widget>(std::string());  // arg 是右值 → 移动
```

### 引用折叠规则

```cpp
// 引用的引用在以下 4 种场景中发生：
// 1. 模板实例化   2. auto 推导   3. typedef/using   4. decltype

// 折叠规则（只有一种结果产生右值引用）：
// T&  &   → T&
// T&  &&  → T&
// T&& &   → T&
// T&& &&  → T&&   ← 只有右值引用的右值引用保持右值！

// 这就是 std::forward 的核心机制：
template<typename T>
T&& forward(typename std::remove_reference<T>::type& param) {
    return static_cast<T&&>(param);
}
// 当 T = Widget&  → 返回 Widget&  (左值)
// 当 T = Widget   → 返回 Widget&& (右值)
```

---

## 面试高频问题

### Q1: move 和 forward 的区别？

```cpp
// std::move: 总是返回右值引用。"我要移动这个对象"
// std::forward: 条件地返回右值引用。"我把参数原样转发"

// 记忆方式：
// move  = unconditional cast to rvalue
// forward = conditional cast to rvalue (preserves lvalueness)
```

### Q2: 编译器生成的默认移动操作？

```cpp
class Widget {
    // 编译器生成移动构造/赋值的条件（缺一不可）：
    // 1. 没有声明拷贝构造
    // 2. 没有声明拷贝赋值
    // 3. 没有声明移动赋值
    // 4. 没有声明析构函数
    // → 五法则：声明了其中任意一个，就手动声明全部五个
};
```

### Q3: 什么时候用拷贝什么时候用移动？

```cpp
// 口诀：有 move 用 move，没有则用 copy
// 但注意：move 仅对"拥有堆资源"的类型有意义

// 对 vector/string/unique_ptr → move 是 O(1)，copy 是 O(N) → 巨大差异
// 对 int/char/array<int,100> → move == copy → 没区别
```

---

## AI Infra 中的实际场景

```cpp
// CUDA buffer 的移动语义（在实际项目中大量使用）
class CudaBuffer {
    float* data_;
    size_t size_;
public:
    CudaBuffer(size_t n) : size_(n) { cudaMalloc(&data_, n * sizeof(float)); }
    ~CudaBuffer() { if (data_) cudaFree(data_); }

    // 移动：转移 GPU 内存所有权
    CudaBuffer(CudaBuffer&& other) noexcept
        : data_(other.data_), size_(other.size_) {
        other.data_ = nullptr;  // 防止析构时 double-free
        other.size_ = 0;
    }

    // 禁止拷贝（GPU 内存拷贝很贵，应该显式处理）
    CudaBuffer(const CudaBuffer&) = delete;
    CudaBuffer& operator=(const CudaBuffer&) = delete;
};
```
