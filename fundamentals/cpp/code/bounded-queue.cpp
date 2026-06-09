/**
 * BoundedBlockingQueue<T> — 线程安全有界阻塞队列
 *
 * 对应 W3 B2 C++ 多线程练习
 * C++ 标准：C++17
 *
 * 编译：g++ -std=c++17 -pthread bounded-queue.cpp -o bounded-queue.exe
 *
 * 核心知识点：
 *   1. std::mutex + std::condition_variable 实现生产者-消费者
 *   2. std::unique_lock 的灵活性（可手动 unlock，可配合 condition_variable）
 *   3. RAII 锁管理（lock_guard vs unique_lock）
 *   4. 两个条件变量分别通知 not_full 和 not_empty（避免惊群）
 */

#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <string>
#include <chrono>
#include <vector>
#include <cassert>
#include <atomic>
#include <sstream>

// ═══════════════════════════════════════════════════════════════════
// 1. BoundedBlockingQueue<T> — 有界阻塞队列
// ═══════════════════════════════════════════════════════════════════
// 生产者-消费者模型的经典实现：
//   - enqueue: 队列满时阻塞等待 not_full 信号
//   - dequeue: 队列空时阻塞等待 not_empty 信号
//   - 两个条件变量分别处理"满"和"空"，避免无效唤醒

template <typename T>
class BoundedBlockingQueue {
public:
    explicit BoundedBlockingQueue(size_t capacity)
        : capacity_(capacity) {}

    // ── 生产者：入队 ──
    // 队列满时阻塞，直到有消费者取走元素
    void enqueue(T item) {
        std::unique_lock<std::mutex> lock(mutex_);
        // 用 while 而非 if：防止虚假唤醒（spurious wakeup）
        not_full_.wait(lock, [this] { return queue_.size() < capacity_; });

        queue_.push(std::move(item));

        // 通知一个等待的消费者
        not_empty_.notify_one();
        // lock 析构时自动解锁（unique_lock RAII）
    }

    // ── 消费者：出队 ──
    // 队列空时阻塞，直到有生产者放入元素
    T dequeue() {
        std::unique_lock<std::mutex> lock(mutex_);
        not_empty_.wait(lock, [this] { return !queue_.empty(); });

        T item = std::move(queue_.front());
        queue_.pop();

        // 通知一个等待的生产者
        not_full_.notify_one();
        return item;
    }

    // ── 非阻塞尝试 ──
    bool try_enqueue(T item) {
        std::lock_guard<std::mutex> lock(mutex_);
        if (queue_.size() >= capacity_) return false;
        queue_.push(std::move(item));
        not_empty_.notify_one();
        return true;
    }

    bool try_dequeue(T& item) {
        std::lock_guard<std::mutex> lock(mutex_);
        if (queue_.empty()) return false;
        item = std::move(queue_.front());
        queue_.pop();
        not_full_.notify_one();
        return true;
    }

    // ── 状态查询 ──
    size_t size() const {
        std::lock_guard<std::mutex> lock(mutex_);
        return queue_.size();
    }

    bool empty() const {
        std::lock_guard<std::mutex> lock(mutex_);
        return queue_.empty();
    }

private:
    mutable std::mutex mutex_;
    std::condition_variable not_full_;
    std::condition_variable not_empty_;
    std::queue<T> queue_;
    size_t capacity_;
};


// ═══════════════════════════════════════════════════════════════════
// 2. LockFreeCounter — std::atomic 无锁计数器
// ═══════════════════════════════════════════════════════════════════
// 演示 memory_order 的四种常用级别

class LockFreeCounter {
public:
    LockFreeCounter() : count_(0) {}

    // relaxed：只保证原子性，不保证顺序（适合纯计数）
    void increment_relaxed() {
        count_.fetch_add(1, std::memory_order_relaxed);
    }

    // release：之前的写操作对后续 acquire 可见（生产者侧）
    void increment_release() {
        count_.fetch_add(1, std::memory_order_release);
    }

    // acquire：能看到之前 release 的写（消费者侧）
    int load_acquire() const {
        return count_.load(std::memory_order_acquire);
    }

    // seq_cst（默认）：全局顺序一致性，最安全但最慢
    int load_seq_cst() const {
        return count_.load(std::memory_order_seq_cst);
    }

    int get() const { return count_.load(); }

private:
    mutable std::atomic<int> count_;
};


// ═══════════════════════════════════════════════════════════════════
// 3. SpinLock — 用 std::atomic_flag 实现自旋锁
// ═══════════════════════════════════════════════════════════════════
// 适用场景：临界区极短（几行代码），等待开销 < 上下文切换开销

class SpinLock {
public:
    void lock() {
        while (flag_.test_and_set(std::memory_order_acquire)) {
            // 自旋等待（生产代码可能加 _mm_pause() / yield）
        }
    }

    void unlock() {
        flag_.clear(std::memory_order_release);
    }

private:
    std::atomic_flag flag_ = ATOMIC_FLAG_INIT;
};


// ═══════════════════════════════════════════════════════════════════
// 测试
// ═══════════════════════════════════════════════════════════════════

// 线程安全的日志输出
std::mutex print_mutex;
void safe_print(const std::string& msg) {
    std::lock_guard<std::mutex> lock(print_mutex);
    std::cout << msg << std::endl;
}

void test_bounded_queue() {
    std::cout << "--- Test 1: BoundedBlockingQueue ---\n";

    BoundedBlockingQueue<int> q(3);  // 容量 3

    // 统计计数器（无锁）
    std::atomic<int> produced{0};
    std::atomic<int> consumed{0};
    const int total_items = 20;

    // 生产者线程
    auto producer = [&](int id) {
        for (int i = 0; i < total_items / 2; i++) {
            int item = id * 1000 + i;
            q.enqueue(item);
            produced.fetch_add(1);
            std::ostringstream oss;
            oss << "  Producer " << id << " enqueued " << item;
            safe_print(oss.str());
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
    };

    // 消费者线程
    auto consumer = [&](int id) {
        for (int i = 0; i < total_items / 2; i++) {
            int item = q.dequeue();
            consumed.fetch_add(1);
            std::ostringstream oss;
            oss << "  Consumer " << id << " dequeued " << item;
            safe_print(oss.str());
            std::this_thread::sleep_for(std::chrono::milliseconds(20));
        }
    };

    std::thread p1(producer, 1);
    std::thread p2(producer, 2);
    std::thread c1(consumer, 1);
    std::thread c2(consumer, 2);

    p1.join(); p2.join(); c1.join(); c2.join();

    std::cout << "  Produced: " << produced << ", Consumed: " << consumed
              << " " << (produced == consumed ? "PASS" : "FAIL") << "\n\n";
}

void test_lockfree_counter() {
    std::cout << "--- Test 2: LockFreeCounter (std::atomic) ---\n";

    LockFreeCounter counter;
    const int num_threads = 4;
    const int per_thread = 100000;
    std::vector<std::thread> threads;

    for (int t = 0; t < num_threads; t++) {
        threads.emplace_back([&counter, per_thread]() {
            for (int i = 0; i < per_thread; i++) {
                counter.increment_relaxed();
            }
        });
    }

    for (auto& t : threads) t.join();

    int expected = num_threads * per_thread;
    int actual = counter.get();
    std::cout << "  Expected: " << expected << ", Actual: " << actual
              << " " << (expected == actual ? "PASS" : "FAIL") << "\n\n";
}

void test_try_operations() {
    std::cout << "--- Test 3: try_enqueue / try_dequeue ---\n";

    BoundedBlockingQueue<std::string> q(2);

    std::cout << "  try_enqueue(\"A\"): " << q.try_enqueue("A") << "\n";
    std::cout << "  try_enqueue(\"B\"): " << q.try_enqueue("B") << "\n";
    std::cout << "  try_enqueue(\"C\"): " << q.try_enqueue("C") << " (expect 0, queue full)\n";

    std::string item;
    std::cout << "  try_dequeue: " << q.try_dequeue(item) << ", item = " << item << "\n";
    std::cout << "  try_dequeue: " << q.try_dequeue(item) << ", item = " << item << "\n";
    std::cout << "  try_dequeue: " << q.try_dequeue(item) << " (expect 0, queue empty)\n\n";
}

int main() {
    std::cout << "=== C++ Multithreading Demo ===\n\n";

    test_bounded_queue();
    test_lockfree_counter();
    test_try_operations();

    // ── 知识点总结 ──
    std::cout << "=== Key Takeaways ===\n";
    std::cout << "  lock_guard:   最简单的 RAII 锁，不能手动 unlock\n";
    std::cout << "  unique_lock:  可手动 lock/unlock，配合 condition_variable\n";
    std::cout << "  condition_variable::wait: 用 while + lambda，防止虚假唤醒\n";
    std::cout << "  atomic memory_order:\n";
    std::cout << "    relaxed: 只保原子性，计数器够用\n";
    std::cout << "    acquire/release: 配对使用，保序不保全\n";
    std::cout << "    seq_cst: 全局顺序一致，最安全也最慢\n";
    std::cout << "  SpinLock: 临界区 < 1us 时可能比 mutex 快\n";

    return 0;
}
