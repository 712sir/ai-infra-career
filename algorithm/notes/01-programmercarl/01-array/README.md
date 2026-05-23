# 01-array — 数组

> 刷题日期：2026-05-21 ～ 2026-05-23
>
> 本章共 7 题，已完成 2 题。

| # | 题号 | 题目 | 核心技巧 | 状态 |
|---|------|------|----------|------|
| 1 | 704 | 二分查找 | 二分法（区间不变量） | ✅ |
| 2 | 27 | 移除元素 | 双指针（快慢指针） | ✅ |
| 3 | 977 | 有序数组的平方 | 双指针（两端向中间） | ⬜ |
| 4 | 209 | 长度最小的子数组 | 滑动窗口 | ⬜ |
| 5 | 59 | 螺旋矩阵II | 模拟（循环不变量） | ⬜ |
| 6 | 35 | 搜索插入位置 | 二分法 | ⬜ |
| 7 | 34 | 在排序数组中查找元素的第一个和最后一个位置 | 二分边界 | ⬜ |

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
