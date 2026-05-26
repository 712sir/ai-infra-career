# ============================================
# 题目：977. 有序数组的平方 (Squares of a Sorted Array)
# 难度：Easy
# 链接：https://leetcode.cn/problems/squares-of-a-sorted-array/
# 来源：代码随想录 01-array
# ============================================

"""
思路：
    数组本身有序，但负数平方后可能变大。平方后的最大值一定出现在
    数组两端（最左或最右），不可能是中间。用双指针 l 从开头、r 从结尾
    向中间靠拢，每次取平方较大者放入结果数组末尾（k 指针倒序填充）。

时间复杂度：O(n)
空间复杂度：O(n)（结果数组）
"""

"""
注意事项 / 易错点：
    1. 循环条件是 l <= r（不是 l < r），漏掉中间元素
    2. k 从末尾向前填充，因为先确定的是最大值
    3. res 预分配后通过下标赋值，不要用 append
"""

from typing import List


class Solution:
    def sortedSquares(self, nums: List[int]) -> List[int]:
        l, r, k = 0, len(nums) - 1, len(nums) - 1
        res = [0] * len(nums)  # 预分配结果数组，通过下标赋值
        # l 指向左端（负数区），r 指向右端（正数区），向中间收缩
        while l <= r:
            if nums[l] ** 2 < nums[r] ** 2:
                res[k] = nums[r] ** 2  # 右端平方更大，放末尾
                r -= 1                  # 右指针左移
            else:
                res[k] = nums[l] ** 2  # 左端平方更大，放末尾
                l += 1                  # 左指针右移
            k -= 1                      # 填充指针前移
        return res
