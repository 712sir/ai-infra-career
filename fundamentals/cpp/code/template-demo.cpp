/**
 * C++ Templates Demo
 *
 * 对应 W2 B2 C++ 模板深入练习。
 * 内容：
 *   1. Array<T, N> — 编译期固定大小数组
 *   2. is_same<T, U> — type trait 实现
 *   3. 模板特化（全特化 vs 偏特化）
 *   4. SFINAE 入门：用 enable_if 控制重载
 *   5. 变参模板（Variadic Templates）—— C++17 fold expression
 *
 * 编译：g++ -std=c++17 -O2 template-demo.cpp -o template-demo.exe
 */

#include <iostream>
#include <type_traits>
#include <string>
#include <cassert>
#include <cstdint>

// ═══════════════════════════════════════════════════════════════════
// 1. Array<T, N> — 编译期固定大小数组
// ═══════════════════════════════════════════════════════════════════
// 非类型模板参数 N 在编译期确定，数组分配在栈上（无堆分配）
// 对标 std::array<T, N>

template <typename T, size_t N>
class Array {
public:
    // ── 类型别名（STL 惯例） ──
    using value_type      = T;
    using size_type       = size_t;
    using pointer         = T*;
    using const_pointer   = const T*;
    using reference       = T&;
    using const_reference = const T&;

    // ── 元素访问 ──
    constexpr T& operator[](size_t i) {
        return data_[i];
    }
    constexpr const T& operator[](size_t i) const {
        return data_[i];
    }

    // ── 迭代器 ──
    constexpr T* begin() { return data_; }
    constexpr T* end()   { return data_ + N; }
    constexpr const T* begin() const { return data_; }
    constexpr const T* end()   const { return data_ + N; }

    // ── 容量 ──
    static constexpr size_t size()     { return N; }
    static constexpr bool   empty()    { return N == 0; }

    // ── 边界检查访问 ──
    T& at(size_t i) {
        if (i >= N) throw std::out_of_range("Array::at: index out of range");
        return data_[i];
    }

    // ── 填充 ──
    void fill(const T& value) {
        for (size_t i = 0; i < N; i++) data_[i] = value;
    }

    // ── 直接访问底层数组 ──
    constexpr T*       data()       { return data_; }
    constexpr const T* data() const { return data_; }

private:
    T data_[N];  // 编译期大小，栈上分配
};

// 偏特化：Array<T, 0>（空数组）
template <typename T>
class Array<T, 0> {
public:
    static constexpr size_t size()  { return 0; }
    static constexpr bool   empty() { return true; }
    constexpr T* begin() { return nullptr; }
    constexpr T* end()   { return nullptr; }
};


// ═══════════════════════════════════════════════════════════════════
// 2. is_same<T, U> — 手写 type trait
// ═══════════════════════════════════════════════════════════════════
// 原理：主模板假设 T 和 U 不同，继承 false_type
//       特化版本当 T == U 时继承 true_type

template <typename T, typename U>
struct my_is_same : std::false_type {};

template <typename T>
struct my_is_same<T, T> : std::true_type {};

// 便捷变量模板（C++14 style）
template <typename T, typename U>
inline constexpr bool my_is_same_v = my_is_same<T, U>::value;


// ═══════════════════════════════════════════════════════════════════
// 3. 全特化 vs 偏特化
// ═══════════════════════════════════════════════════════════════════

// 主模板
template <typename T>
struct TypeName {
    static const char* get() { return "unknown"; }
};

// 全特化：针对 int
template <>
struct TypeName<int> {
    static const char* get() { return "int"; }
};

// 全特化：针对 double
template <>
struct TypeName<double> {
    static const char* get() { return "double"; }
};

// 偏特化：针对所有指针类型
template <typename T>
struct TypeName<T*> {
    static const char* get() { return "pointer"; }
};

// 偏特化：针对所有 const 类型
template <typename T>
struct TypeName<const T> {
    static const char* get() { return "const"; }
};


// ═══════════════════════════════════════════════════════════════════
// 4. SFINAE 入门：用 enable_if 控制重载
// ═══════════════════════════════════════════════════════════════════
// "Substitution Failure Is Not An Error"
// 模板替换失败不报错，只是从重载候选集中移除

// 手写 enable_if（理解原理）
template <bool B, typename T = void>
struct my_enable_if {};

template <typename T>
struct my_enable_if<true, T> {
    using type = T;
};

template <bool B, typename T = void>
using my_enable_if_t = typename my_enable_if<B, T>::type;

// 用法：仅当 T 是整数类型时启用这个重载
template <typename T>
my_enable_if_t<std::is_integral_v<T>, std::string>
describe_number(T x) {
    return "integer: " + std::to_string(x);
}

// 仅当 T 是浮点类型时启用
template <typename T>
my_enable_if_t<std::is_floating_point_v<T>, std::string>
describe_number(T x) {
    return "floating-point: " + std::to_string(x);
}


// ═══════════════════════════════════════════════════════════════════
// 5. 变参模板 + C++17 fold expression
// ═══════════════════════════════════════════════════════════════════

// 递归终止
template <typename T>
T sum_all(T v) {
    return v;
}

// 变参模板（递归展开）
template <typename T, typename... Args>
T sum_all(T first, Args... rest) {
    return first + sum_all(rest...);
}

// C++17 fold expression 写法（更简洁）
template <typename... Args>
auto sum_fold(Args... args) {
    return (... + args);  // 一元左折叠
}

// 打印所有参数
template <typename... Args>
void print_all(Args... args) {
    ((std::cout << args << " "), ...);  // 逗号折叠
    std::cout << "\n";
}


// ═══════════════════════════════════════════════════════════════════
// Tests
// ═══════════════════════════════════════════════════════════════════

int main() {
    std::cout << "=== C++ Templates Demo ===\n\n";

    // ── Test 1: Array<T, N> ──
    std::cout << "--- 1. Array<T, N> ---\n";
    Array<int, 5> arr;
    for (size_t i = 0; i < arr.size(); i++) {
        arr[i] = static_cast<int>(i * i);
    }
    std::cout << "arr = [";
    for (auto v : arr) std::cout << v << " ";
    std::cout << "]\n";
    std::cout << "arr.size() = " << arr.size() << " (compile-time constant)\n";
    std::cout << "sizeof(Array<int,5>) = " << sizeof(arr)
              << " bytes (== 5 * sizeof(int) = 20)\n";

    // 偏特化：空数组
    std::cout << "Array<int,0>::size() = " << Array<int, 0>::size()
              << ", empty = " << Array<int, 0>::empty() << "\n\n";

    // ── Test 2: is_same ──
    std::cout << "--- 2. my_is_same<T, U> ---\n";
    std::cout << std::boolalpha;
    std::cout << "my_is_same<int, int>::value     = " << my_is_same<int, int>::value << "\n";
    std::cout << "my_is_same<int, float>::value   = " << my_is_same<int, float>::value << "\n";
    std::cout << "my_is_same_v<int, const int>    = " << my_is_same_v<int, const int> << "\n";
    std::cout << "my_is_same_v<int, int32_t>      = " << my_is_same_v<int, int32_t>
              << "  (same on this platform)\n\n";

    // ── Test 3: 全特化 vs 偏特化 ──
    std::cout << "--- 3. Template Specialization ---\n";
    std::cout << "TypeName<int>::get()        = " << TypeName<int>::get() << "\n";
    std::cout << "TypeName<double>::get()     = " << TypeName<double>::get() << "\n";
    std::cout << "TypeName<int*>::get()       = " << TypeName<int*>::get() << "\n";
    std::cout << "TypeName<const int>::get()  = " << TypeName<const int>::get() << "\n";
    std::cout << "TypeName<std::string>::get()= " << TypeName<std::string>::get() << "\n\n";

    // ── Test 4: SFINAE ──
    std::cout << "--- 4. SFINAE (enable_if) ---\n";
    std::cout << "describe_number(42)     = " << describe_number(42) << "\n";
    std::cout << "describe_number(3.14f)  = " << describe_number(3.14f) << "\n";
    std::cout << "describe_number(2.718)  = " << describe_number(2.718) << "\n\n";

    // ── Test 5: Variadic Templates + Fold ──
    std::cout << "--- 5. Variadic Templates ---\n";
    std::cout << "sum_all(1,2,3,4,5)   = " << sum_all(1, 2, 3, 4, 5) << "\n";
    std::cout << "sum_fold(1,2,3,4,5)  = " << sum_fold(1, 2, 3, 4, 5) << "\n";
    std::cout << "print_all: ";
    print_all("hello", 42, 3.14, "world");

    std::cout << "\n=== All tests done ===\n";
    return 0;
}
