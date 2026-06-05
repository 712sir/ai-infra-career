/**
 * C++ Smart Pointer Demo
 *
 * 手撕代码练习：unique_ptr / shared_ptr / weak_ptr 的核心用法
 * 每个函数对应一个面试高频考点
 */

#include <iostream>
#include <memory>
#include <string>
#include <cassert>

/* ===========================================================
 * 1. unique_ptr 基础：独占所有权、不可拷贝、可移动
 * =========================================================== */
void demo_unique_ptr() {
    std::cout << "=== unique_ptr ===\n";

    // 创建（推荐 make_unique）
    auto p1 = std::make_unique<int>(42);
    std::cout << "*p1 = " << *p1 << "\n";

    // 所有权转移（移动，不可拷贝）
    auto p2 = std::move(p1);
    std::cout << "p1 is " << (p1 ? "not null" : "null") << "\n";  // → null
    std::cout << "*p2 = " << *p2 << "\n";                          // → 42

    // 自定义 deleter（如：管理 FILE*）
    auto file_deleter = [](FILE* f) {
        if (f) fclose(f);
    };
    // std::unique_ptr<FILE, decltype(file_deleter)> fp(fopen("test.txt", "r"), file_deleter);

    std::cout << "unique_ptr demo passed\n\n";
}

/* ===========================================================
 * 2. shared_ptr + weak_ptr：解决循环引用
 *    → 这是面试最常考的场景！
 * =========================================================== */
struct Node {
    std::string name;
    std::shared_ptr<Node> next;
    std::weak_ptr<Node>   prev;  // ← 关键：用 weak_ptr 打破循环引用

    Node(const std::string& n) : name(n) {
        std::cout << "  Node(" << name << ") created\n";
    }
    ~Node() {
        std::cout << "  Node(" << name << ") destroyed\n";
    }
};

void demo_cyclic_reference() {
    std::cout << "=== shared_ptr + weak_ptr (cycle breaking) ===\n";

    {
        auto n1 = std::make_shared<Node>("A");
        auto n2 = std::make_shared<Node>("B");

        n1->next = n2;   // n1 → n2 (shared_ptr)
        n2->prev = n1;   // n1 ← n2 (weak_ptr, 不增加引用计数)

        // use_count: n1=1 (仅 n1 自身), n2=2 (n2 + n1->next)
        std::cout << "  n1 use_count: " << n1.use_count() << "\n";
        std::cout << "  n2 use_count: " << n2.use_count() << "\n";
    }
    // 离开作用域：n1 和 n2 都正确销毁（如果都用 shared_ptr 会泄漏！）
    std::cout << "  Both nodes properly destroyed!\n\n";
}

/* ===========================================================
 * 3. enable_shared_from_this
 *    → 从 this 安全地获取 shared_ptr
 * =========================================================== */
class Widget : public std::enable_shared_from_this<Widget> {
public:
    std::shared_ptr<Widget> getShared() {
        return shared_from_this();  // ✓ 安全：返回已有的控制块
    }

    // ❌ 错误做法（会导致 double free！）
    // std::shared_ptr<Widget> getSharedBad() {
    //     return std::shared_ptr<Widget>(this);  // 创建新的控制块！
    // }
};

void demo_enable_shared_from_this() {
    std::cout << "=== enable_shared_from_this ===\n";

    auto sp1 = std::make_shared<Widget>();
    auto sp2 = sp1->getShared();

    std::cout << "  sp1 use_count: " << sp1.use_count() << "\n";  // → 2
    std::cout << "  sp2 use_count: " << sp2.use_count() << "\n";  // → 2
    std::cout << "  Same control block: OK\n\n";
}

/* ===========================================================
 * 4. make_shared vs new + shared_ptr
 * =========================================================== */
void demo_make_shared() {
    std::cout << "=== make_shared advantage ===\n";

    // make_shared：一次堆分配（对象 + 控制块紧邻）
    auto sp1 = std::make_shared<int>(42);

    // new + shared_ptr：两次堆分配（对象 + 控制块分离）
    std::shared_ptr<int> sp2(new int(42));

    std::cout << "  make_shared: object + control block in one allocation\n";
    std::cout << "  new + shared_ptr: two separate allocations\n\n";
}

/* ===========================================================
 * Main
 * =========================================================== */
int main() {
    demo_unique_ptr();
    demo_cyclic_reference();
    demo_enable_shared_from_this();
    demo_make_shared();

    std::cout << "All demos passed!\n";
    return 0;
}
