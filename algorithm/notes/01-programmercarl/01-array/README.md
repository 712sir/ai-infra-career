# 01-array — 数组

> 刷题日期：2026-05-21 ～ 2026-05-26
>
> 代码随想录数组篇：**核心 5 题** + **拓展 10 题**（按技巧分组）
>
> 核心 5 题全部完成 ✅，拓展题待做。

## 核心题（必刷 5 题）

| # | 题号 | 题目 | 核心技巧 | 状态 |
|---|------|------|----------|------|
| 1 | 704 | 二分查找 | 二分法（区间不变量） | ✅ |
| 2 | 27 | 移除元素 | 双指针（快慢指针） | ✅ |
| 3 | 977 | 有序数组的平方 | 双指针（两端向中间） | ✅ |
| 4 | 209 | 长度最小的子数组 | 滑动窗口 | ✅ |
| 5 | 59 | 螺旋矩阵II | 模拟（循环不变量） | ✅ |

## 拓展题（按技巧分组）

| 分组 | 题号 | 题目 | 状态 |
|------|------|------|------|
| 二分法拓展 | 35 | 搜索插入位置 | ⬜ |
| 二分法拓展 | 34 | 在排序数组中查找元素的第一个和最后一个位置 | ⬜ |
| 二分法拓展 | 69 | x 的平方根 | ⬜ |
| 二分法拓展 | 367 | 有效的完全平方数 | ⬜ |
| 双指针拓展 | 26 | 删除排序数组中的重复项 | ⬜ |
| 双指针拓展 | 283 | 移动零 | ⬜ |
| 双指针拓展 | 844 | 比较含退格的字符串 | ⬜ |
| 滑动窗口拓展 | 904 | 水果成篮 | ⬜ |
| 滑动窗口拓展 | 76 | 最小覆盖子串 | ⬜ |
| 模拟拓展 | 54 | 螺旋矩阵 | ⬜ |

---

## 704. 二分查找

### 核心思想：区间不变量

二分查找的关键不在 `mid` 怎么算，而在**区间的定义在整个循环中保持不变**。一旦确定了区间开闭方式，`left`/`right` 的初始值、`while` 条件、收缩逻辑三者必须统一。

| | 左闭右闭 `[l, r]` | 左闭右开 `[l, r)` |
|---|---|---|
| l 初始值 | `0` | `0` |
| r 初始值 | `nums.size() - 1` | `nums.size()` |
| while 条件 | `l <= r`（可取等号） | `l < r`（不可取等号） |
| nums[mid] > target | `r = mid - 1` | `r = mid` |
| nums[mid] < target | `l = mid + 1` | `l = mid + 1` |
| 单元素时 | `l == r == 0`，进入循环 | `l == 0, r == 1`，不进入循环，需额外判断 |

**为什么左闭右闭可以取等号？** 当 `l == r` 时，区间 `[l, r]` 仍包含一个元素，需要进入循环判断。左闭右开 `[l, r)` 在 `l == r` 时区间为空，直接跳出。

### 防溢出 mid

```
mid = (r - l) / 2 + l    // 推荐，防两个 int 相加溢出
mid = (l + r) / 2         // 简洁但 l+r 可能溢出
mid = (l + r) >> 1        // 位运算，有符号数右移除法向下取整（负数不可用）
```

### C 语言版（左闭右闭）

```c
int search(int* nums, int numsSize, int target) {
    int l = 0, r = numsSize - 1;
    while (l <= r) {
        int mid = (r - l) / 2 + l;
        if (nums[mid] < target)
            l = mid + 1;
        else if (nums[mid] > target)
            r = mid - 1;
        else
            return mid;
    }
    return -1;
}
```

### C++ 版（两种区间）

```cpp
// 左闭右闭（最常用）
class Solution {
public:
    int search(vector<int>& nums, int target) {
        int l = 0, r = nums.size() - 1;
        while (l <= r) {
            int mid = (r - l) / 2 + l;
            if (nums[mid] > target)
                r = mid - 1;
            else if (nums[mid] < target)
                l = mid + 1;
            else
                return mid;
        }
        return -1;
    }
};

// 左闭右开
int search(vector<int>& nums, int target) {
    int l = 0, r = nums.size();
    while (l < r) {
        int mid = (r - l) / 2 + l;
        if (nums[mid] > target)
            r = mid;          // 右开，mid 不包含在内
        else if (nums[mid] < target)
            l = mid + 1;
        else
            return mid;
    }
    return -1;
}
```

### Python 版

```python
class Solution:
    # 左闭右闭
    def search(self, nums: List[int], target: int) -> int:
        l, r = 0, len(nums) - 1
        while l <= r:
            mid = (r - l) // 2 + l
            if nums[mid] > target:
                r = mid - 1
            elif nums[mid] < target:
                l = mid + 1
            else:
                return mid
        return -1

    # 左闭右开
    def search2(self, nums: List[int], target: int) -> int:
        l, r = 0, len(nums)
        while l < r:
            mid = (r - l) // 2 + l
            if nums[mid] > target:
                r = mid
            elif nums[mid] < target:
                l = mid + 1
            else:
                return mid
        return -1
```

### 特殊情况

- **数组中有相同元素**：三个分支（`>` / `<` / `==`）缺一不可，不能合并成两个
- **返回 bool**：可以直接 `return nums[mid] == target`
- **单元素数组**：左闭右闭可以正确处理；左闭右开需先判断 `len(nums) == 0`

---

## 27. 移除元素

### 核心思想：快慢指针

- **快指针** `fast`：遍历数组，寻找"要保留"的元素（`nums[fast] != val`）
- **慢指针** `slow`：指向下一个要写入的位置，也代表最终新数组的长度

一层循环完成"删除 + 前移"两层工作。

### C 语言版

```c
int removeElement(int* nums, int numsSize, int val) {
    int f = 0, s = 0;
    for (; f < numsSize; f++)
        if (nums[f] != val) {
            nums[s] = nums[f];
            s++;
        }
    return s;
}
```

### C++ 版

```cpp
class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        int slow = 0;
        for (int fast = 0; fast < nums.size(); fast++) {
            if (val != nums[fast]) {
                nums[slow++] = nums[fast];
            }
        }
        return slow;
    }
};
```

### Python 版

```python
class Solution:
    def removeElement(self, nums: List[int], val: int) -> int:
        slow, fast, size = 0, 0, len(nums)
        while fast < size:
            if val != nums[fast]:
                nums[slow] = nums[fast]
                slow += 1
            fast += 1
        return slow
```

> Python 没有 `++` / `--`，用 `+= 1` 替代。

---

## 额外技巧：滑动窗口模板

### 最小滑窗

求满足条件的**最短**子数组。关键：`while` 满足条件时**拼命压缩**左边界。

```
while j < len(nums):
    将 nums[j] 加入窗口
    while 窗口满足条件:
        更新结果（在 while 内！）
        i += 1   // 尽可能压缩左边界
    j += 1
```

### 最大滑窗

求满足条件的**最长**子数组。关键：`while` 不满足时才压缩，**一旦满足就停**。

```
while j < len(nums):
    将 nums[j] 加入窗口
    while 窗口不满足条件:
        i += 1   // 保守压缩，满足就停
    更新结果（在 while 外！）
    j += 1
```

---

## 语言陷阱速查

| 场景 | C | C++ | Java | Python |
|------|---|-----|------|--------|
| 数组长度 | `sizeof(arr)/sizeof(arr[0])` | `v.size()` | `arr.length` | `len(arr)` |
| 字符串长度 | `strlen(s)` | `s.size()` | `s.length()` | `len(s)` |
| 字符串比较 | `strcmp(a,b)==0` | `a == b` | `a.equals(b)` | `a == b` |
| 字符串结尾 | `'\0'` | `'\0'`（兼容C） | 无，用 `length()` | 无，用 `len()` |
| 自增 | `i++` / `++i` | `i++` / `++i` | `i++` / `++i` | 无，用 `i += 1` |
| 字符串可变 | `char[]` 可改 | `string` 可改 | `String` 不可变 → 用 `StringBuilder` | `str` 不可变 → 转 `list` |
| 遍历字符串 | `for(int i=0; s[i]!='\0'; i++)` | `for(char ch : s)` | `for(char c : s.toCharArray())` | `for ch in s` |

### Java 特别注意

- `String` 不可变，用 `StringBuilder` 动态构建：`append()` 增、`deleteCharAt(i)` 删、`toString()` 输出
- `charAt()` 返回 `char` 值，不能作为左值赋值
- 不要用 `'\0'` 判断字符串结束，用索引 `< s.length()`

---

## 相关题目

[844. 比较含退格的字符串](https://leetcode.cn/problems/backspace-string-compare/) — 栈模拟 / 双指针

> 双指针反向遍历，用退格计数器跳过被删除的字符，可将空间从 O(n) 优化到 O(1)。本文暂记栈写法：

```cpp
class Solution {
public:
    bool backspaceCompare(string s, string t) {
        return build(s) == build(t);
    }
private:
    string build(string str) {
        string ret;
        for (char ch : str) {
            if (ch != '#')
                ret.push_back(ch);
            else if (!ret.empty())
                ret.pop_back();
        }
        return ret;
    }
};
```

```java
class Solution {
    public boolean backspaceCompare(String s, String t) {
        StringBuilder sbS = new StringBuilder();
        StringBuilder sbT = new StringBuilder();

        for (char c : s.toCharArray()) {
            if (c != '#') sbS.append(c);
            else if (sbS.length() > 0) sbS.deleteCharAt(sbS.length() - 1);
        }
        for (char c : t.toCharArray()) {
            if (c != '#') sbT.append(c);
            else if (sbT.length() > 0) sbT.deleteCharAt(sbT.length() - 1);
        }
        return sbS.toString().equals(sbT.toString());
    }
}
```

---

## 977. 有序数组的平方

### 核心思想：两端双指针

数组本身是非递减有序的，但包含负数。负数平方后可能变得很大，导致**平方后的最大值只可能出现在数组两端**（最左负数平方 or 最右正数平方），不可能在中间。

于是用两个指针 `l`（左端）、`r`（右端）向中间收缩，每次比较平方值，大的放入结果数组的**末尾**（`k` 指针倒序填充）。

```
原数组: [-4, -1, 0, 3, 10]
平方后: [16, 1, 0, 9, 100]
               ↑           ↑
               l           r         100 最大 → 放末尾
               l        r             16 次大 → 放倒数第二
                   l    r              9 ...
```

### C++ 版

```cpp
class Solution {
public:
    vector<int> sortedSquares(vector<int>& nums) {
        int k = nums.size() - 1;
        vector<int> res(nums.size(), 0);
        for (int i = 0, j = nums.size() - 1; i <= j;) {
            if (nums[i] * nums[i] < nums[j] * nums[j]) {
                res[k--] = nums[j] * nums[j];
                j--;
            } else {
                res[k--] = nums[i] * nums[i];
                i++;
            }
        }
        return res;
    }
};
```

### Python 版

```python
class Solution:
    def sortedSquares(self, nums: List[int]) -> List[int]:
        l, r, k = 0, len(nums) - 1, len(nums) - 1
        res = [0] * len(nums)   # 预分配固定大小
        while l <= r:
            if nums[l] ** 2 < nums[r] ** 2:
                res[k] = nums[r] ** 2
                r -= 1
            else:
                res[k] = nums[l] ** 2
                l += 1
            k -= 1
        return res
```

---

## 209. 长度最小的子数组

### 核心思想：滑动窗口

**关键认知**：只用一个 `for` 循环时，循环变量表示**窗口的终止位置**而不是起始位置（否则退回暴力解法）。

```
窗口 = 满足 sum >= target 的最短连续子数组
右边界 j → for 循环自动扩张
左边界 i → while 满足条件时持续收缩
```

**滑动窗口三要素**：

| 要素 | 本题答案 |
|------|---------|
| 窗口是什么 | 满足 `sum >= target` 的最短连续子数组 |
| 起始位置如何移动 | `sum >= target` 时缩小（`i++`） |
| 结束位置如何移动 | 遍历数组 `j++` |

### 复杂度分析

虽然 `for` 里套了 `while`，但**时间复杂度是 O(n) 而非 O(n²)**。

原因：每个元素在滑动窗口生命周期中被操作**恰好两次**——进窗口一次（`sum += nums[j]`），出窗口一次（`sum -= nums[i]`）。总操作次数 = 2n。

```
外层 for j=0..n-1     → 每个元素进窗口 1 次
内层 while sum>=target → 每个元素出窗口最多 1 次
总数：2n = O(n)
```

### C++ 版

```cpp
class Solution {
public:
    int minSubArrayLen(int target, vector<int>& nums) {
        int res = INT32_MAX;
        int sum = 0, i = 0, subL = 0;
        for (int j = 0; j < nums.size(); j++) {
            sum += nums[j];
            while (sum >= target) {
                subL = j - i + 1;
                res = min(res, subL);
                sum -= nums[i++];
            }
        }
        return res == INT32_MAX ? 0 : res;
    }
};
```

### Python 版

```python
class Solution:
    def minSubArrayLen(self, target: int, nums: List[int]) -> int:
        left, cur_sum, min_len = 0, 0, float('inf')
        for right in range(len(nums)):
            cur_sum += nums[right]
            while cur_sum >= target:
                min_len = min(min_len, right - left + 1)
                cur_sum -= nums[left]
                left += 1
        return min_len if min_len != float('inf') else 0
```

---

## 59. 螺旋矩阵 II

### 核心思想：模拟 + 循环不变量

模拟顺时针填充过程，每圈分 上→右→下→左 四条边。关键原则：**每条边坚持「左闭右开」**，即每条边不填最后一个点，留给下一条边的起点。

```
n=3 时，只有 1 圈：
  上边: (0,0)→(0,1)   填 1,2
  右边: (0,2)→(1,2)   填 3,4
  下边: (2,2)→(2,1)   填 5,6
  左边: (2,0)→(1,0)   填 7,8
  中心: (1,1)         填 9
```

### C++ 版

```cpp
class Solution {
public:
    vector<vector<int>> generateMatrix(int n) {
        vector<vector<int>> res(n, vector<int>(n, 0));
        int startx = 0, starty = 0;
        int loop = n / 2, mid = n / 2, count = 1, offset = 1;
        int i, j;
        while (loop--) {
            i = startx, j = starty;
            for (; j < n - offset; j++) res[i][j] = count++;
            for (; i < n - offset; i++) res[i][j] = count++;
            for (; j > starty; j--)    res[i][j] = count++;
            for (; i > startx; i--)    res[i][j] = count++;
            startx++; starty++; offset++;
        }
        if (n % 2) res[mid][mid] = count;
        return res;
    }
};
```

### Python 版

```python
class Solution:
    def generateMatrix(self, n: int) -> List[List[int]]:
        nums = [[0] * n for _ in range(n)]   # 关键：每行独立
        startx, starty = 0, 0
        loop, mid, count = n // 2, n // 2, 1

        for offset in range(1, loop + 1):
            for i in range(starty, n - offset):
                nums[startx][i] = count; count += 1
            for i in range(startx, n - offset):
                nums[i][n - offset] = count; count += 1
            for i in range(n - offset, starty, -1):
                nums[n - offset][i] = count; count += 1
            for i in range(n - offset, startx, -1):
                nums[i][starty] = count; count += 1
            startx += 1; starty += 1

        if n % 2 != 0:
            nums[mid][mid] = count
        return nums
```

---

## Python 列表赋值陷阱

### `[0] * n` 适用于一维，不适用于二维

```python
# ✅ 一维列表：[0]*n 没问题，n 个 0 是独立的不可变 int
res = [0] * 5       # [0, 0, 0, 0, 0]  ← 每个都是独立的 0

# ❌ 二维列表：[[0]*n] * n 有坑！
nums = [[0] * 3] * 3
# 看起来: [[0,0,0], [0,0,0], [0,0,0]]
# 实际上: 三行指向同一行对象！
nums[0][1] = 99
# 结果: [[0,99,0], [0,99,0], [0,99,0]]  ← 三行全变了！
```

**原因**：`[[0]*3]` 先创建了一个行 `[0,0,0]`，外层 `*3` 把这一行的**引用**复制了 3 次。三行指向同一个 `list` 对象，改一行全部跟着变。

### ✅ 正确写法

```python
# 列表推导式：每次循环重新创建一个新行
nums = [[0] * n for _ in range(n)]    # 每行独立
nums[0][1] = 99
# 结果: [[0,99,0], [0,0,0], [0,0,0]]  ← 只变了第一行
```

### `[float('inf')] * n` 是否安全？

```python
# ✅ 安全：float('inf') 是不可变类型
res = [float('inf')] * 5   # 5 个独立的哨兵值
res[0] = 10                # 只改第一个
# 结果: [10, inf, inf, inf, inf]  没问题
```

**判断规则**：`[x] * n` 中 `x` 是**不可变类型**（int / float / str / tuple）则安全；是**可变类型**（list / dict / set）则有引用共享问题，必须用列表推导式。
