# ============================================
# 题目：209. 长度最小的子数组 (Minimum Size Subarray Sum)
# 难度：Medium
# 链接：https://leetcode.cn/problems/minimum-size-subarray-sum/
# 来源：代码随想录 01-array
# ============================================

"""
思路：
    滑动窗口。右边界 right 扩张累加 cur_sum，当 cur_sum >= target 时，
    持续收缩左边界 left（while 循环），记录最小窗口长度，
    直到 cur_sum < target 再继续扩张右边界。

时间复杂度：O(n)（每个元素进窗口一次、出窗口一次，共 2n）
空间复杂度：O(1)
"""

"""
注意事项 / 易错点：
    1. 收缩左边界用 while 而非 if（可能连续收缩多次）
    2. 窗口长度 = right - left + 1
    3. 无解时 min_len 保持 float('inf')，返回时判断
    4. 时间复杂度 O(n)：每个元素进窗口一次、出窗口一次，共 2n
"""

from typing import List


class Solution:
    def minSubArrayLen(self, target: int, nums: List[int]) -> int:
        left = 0                         # 窗口左边界
        cur_sum = 0                      # 当前窗口元素和
        min_len = float('inf')           # 哨兵：记录最短窗口长度
        # right 是窗口右边界（for 循环的索引表示终止位置）
        for right in range(len(nums)):
            cur_sum += nums[right]       # 右边界扩张，纳入新元素
            # 窗口满足条件时，持续收缩左边界（while 而非 if！）
            while cur_sum >= target:
                min_len = min(min_len, right - left + 1)  # 更新最短长度
                cur_sum -= nums[left]    # 左边界元素移出窗口
                left += 1                # 左边界右移，缩小窗口
        return min_len if min_len != float('inf') else 0  # 无解返回 0
