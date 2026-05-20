# C++ 题解目录

每道题一个 `.cpp` 文件，文件内包含完整的解题记录。

## 文件命名规则

```
按题单分类存放，文件名为题号：
cpp/01-programmercarl/01-array/LC704.cpp
cpp/02-hot100/01-hash/LC1.cpp
cpp/03-top150/01-array-string/LC88.cpp
```

> 同一道题出现在多个题单时，放在首次遇到的那个题单目录下，其他位置用注释记录交叉引用。

## 每道题必须包含以下内容

```cpp
/*
 * ============================================
 * 题目：1. 两数之和 (Two Sum)
 * 难度：Easy
 * 链接：https://leetcode.cn/problems/two-sum/
 * 来源：Hot 100
 * ============================================
 */

/*
 * 思路：
 *   一句话说清核心思路。例如：用哈希表存储已遍历元素，
 *   每次检查 target - nums[i] 是否在表中。
 *
 * 时间复杂度：O(n)
 * 空间复杂度：O(n)
 */

/*
 * 注意事项 / 易错点：
 *   1. 不能重复使用同一个元素，先查表再插入
 *   2. 返回的是下标，不是值
 *   3. unordered_map 的 find() 返回迭代器
 */

#include <vector>
#include <unordered_map>
using namespace std;

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        // 你的代码
    }
};
```

## 文件模板

```cpp
/*
 * ============================================
 * 题目：<题号>. <题目名>
 * 难度：<Easy / Medium / Hard>
 * 链接：<LeetCode URL>
 * 来源：<代码随想录 / Hot 100 / 面试经典150题 / 灵神题单>
 * ============================================
 */

/*
 * 思路：
 *   <核心思路，1-3句话>
 *
 * 时间复杂度：O(x)
 * 空间复杂度：O(x)
 */

/*
 * 注意事项 / 易错点：
 *   1. ...
 *   2. ...
 */

class Solution {
public:
    // 你的实现
};
```

## 目录结构

```
cpp/
├── README.md                 ← 本文件
├── 01-programmercarl/        ← 代码随想录
│   ├── 01-array/
│   ├── 02-linked-list/
│   ├── 03-hash-table/
│   ├── 04-string/
│   ├── 05-two-pointers/
│   ├── 06-stack-queue/
│   ├── 07-monotonic-stack/
│   ├── 08-binary-tree/
│   ├── 09-backtracking/
│   ├── 10-greedy/
│   ├── 11-dynamic-programming/
│   ├── 12-graph/
│   └── 14-extra/
├── 02-hot100/                ← Hot 100（按16章分类）
├── 03-top150/                ← 面试经典150题（按23章分类）
└── 04-lingshen/              ← 灵神题单（按专题分类）
```
