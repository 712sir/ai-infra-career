# C++ 模板深入（Templates）

> 来源：《C++ Templates: The Complete Guide》Part 1
> 状态：🟡 笔记整理中
> 面试权重：⭐⭐（AI Infra：CUTLASS 用大量模板元编程做 GEMM 优化）

---

## 基础概念

### 函数模板

```cpp
// 不用模板：每种类型写一遍
int max_int(int a, int b)      { return a > b ? a : b; }
float max_float(float a, float b) { return a > b ? a : b; }

// 用模板：一个定义，适用所有类型
template<typename T>
T max(T a, T b) { return a > b ? a : b; }

max(1, 2);        // T = int
max(1.5, 2.5);    // T = double
max('a', 'b');    // T = char
```

### 类模板

```cpp
template<typename T, size_t N>
class Array {
    T data_[N];
public:
    size_t size() const { return N; }
    T& operator[](size_t i) { return data_[i]; }
};

Array<int, 10>    a;  // 编译期固定大小的 int 数组
Array<float, 100> b;  // float 数组
```

---

## 模板特化

### 全特化

```cpp
// 通用模板
template<typename T>
struct TypeInfo {
    static const char* name() { return "unknown"; }
};

// 全特化：特定类型有特定实现
template<>
struct TypeInfo<int> {
    static const char* name() { return "int"; }
};

template<>
struct TypeInfo<double> {
    static const char* name() { return "double"; }
};

TypeInfo<int>::name();    // → "int"
TypeInfo<float>::name();  // → "unknown"（用通用模板）
```

### 偏特化（Partial Specialization）

```cpp
// 通用模板
template<typename T, typename U>
struct is_same { static constexpr bool value = false; };

// 偏特化：两个类型相同时
template<typename T>
struct is_same<T, T> { static constexpr bool value = true; };

is_same<int, int>::value;    // → true
is_same<int, float>::value;  // → false
```

---

## SFINAE（Substitution Failure Is Not An Error）

```cpp
// 面试高频概念！C++ 模板的核心机制

// 场景：只想对"有 size() 方法的类型"生效
template<typename T>
auto len(const T& t) -> decltype(t.size()) {  // 如果 T 没有 size()，
    return t.size();                           // 这行编译失败 → 不报错，
}                                              // 而是尝试其他重载

// 对没有 size() 的类型
size_t len(...) { return 0; }  // fallback

std::vector<int> v = {1,2,3};
len(v);  // → 3  (匹配第一个)

int x = 5;
len(x);  // → 0  (第一个 SFINAE 失败，匹配第二个)
```

---

## 非类型模板参数（NTTP）

```cpp
// 编译期常量作为模板参数
template<typename T, int Size>
class FixedArray {
    T data_[Size];  // 栈上分配，大小在编译期确定
};

FixedArray<float, 256> buffer;  // Size = 256 在编译期已知

// C++17+：auto 非类型参数
template<auto Value>
struct Constant {
    static constexpr auto value = Value;
};

Constant<42> c1;       // Value = 42 (int)
Constant<'a'> c2;      // Value = 'a' (char)
```

---

## CUDA/AI Infra 中的模板应用

### CUTLASS 风格：模板参数驱动 GEMM 优化

```cpp
// CUTLASS 用模板参数在编译期确定 tile 大小和数据类型
// 这样编译器可以做更激进的优化（如循环展开、寄存器分配）

template<
    typename ElementA,       // A 矩阵数据类型 (half/float/int8)
    typename ElementB,       // B 矩阵数据类型
    typename ElementC,       // C 矩阵数据类型
    int TileM,               // M 方向 tile 大小 (64/128/256)
    int TileN,               // N 方向 tile 大小
    int TileK,               // K 方向 tile 大小
    int WarpTileM,           // 每个 warp 处理的 M 大小
    int WarpTileN            // 每个 warp 处理的 N 大小
>
struct GemmKernel {
    // 编译期就能计算出 shared memory 大小、寄存器数量等
    static constexpr int smem_size = TileM * TileK + TileN * TileK;

    __device__ void operator()(/*...*/) {
        // 所有 tile 大小在编译期已知 → 循环可以被完全展开
        // 编译器将循环体展开为寄存器操作序列
    }
};

// 使用：编译器为每种配置生成专门的 CUDA kernel
using Kernel_128x128_FP16 = GemmKernel<half, half, float,
                                       128, 128, 32, 64, 64>;
```

### pybind11 中的模板

```cpp
// pybind11 大量使用模板来推断 C++ 类型和 Python 类型的映射
py::class_<MyCppClass>(m, "MyCppClass")     // 类模板
    .def("method", &MyCppClass::method)      // 成员函数模板
    .def_property("name",                    // 属性模板
        &MyCppClass::getName,
        &MyCppClass::setName);
```

---

## 面试速查表

| 问题 | 答案 |
|------|------|
| 模板特化 vs 偏特化？ | 全特化：所有参数都确定；偏特化：部分参数确定 |
| SFINAE 是什么？ | 模板替换失败时不报错，继续尝试其他候选 |
| 为什么 CUTLASS 用那么多模板？ | 编译期确定 tile/类型/布局 → 编译器生成最优指令 |
| `typename` vs `class` 在模板参数？ | 99% 场景完全等价，用 `typename` 更语义准确 |
| 模板代码为什么放头文件？ | 模板在实例化点才编译，定义必须对编译器可见 |
