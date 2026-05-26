# ============================================
# 题目：59. 螺旋矩阵 II (Spiral Matrix II)
# 难度：Medium
# 链接：https://leetcode.cn/problems/spiral-matrix-ii/
# 来源：代码随想录 01-array
# ============================================

"""
思路：
    模拟顺时针填充。每圈按 上→右→下→左 四条边依次填入，
    每条边坚持「左闭右开」原则（不填最后一个点，留给下一条边起点）。
    总圈数 = n // 2，奇数 n 时中心单独填入最后一个数。

时间复杂度：O(n²)（每个格子填一次）
空间复杂度：O(n²)（结果矩阵）
"""

"""
注意事项 / 易错点：
    1. 每条边坚持左闭右开，边界统一不变
    2. 循环圈数 = n // 2（不是 n）
    3. 奇数 n 最后手工填中心点
    4. 每圈起始点 (startx, starty) 递增，offset 递增缩小边界
"""

from typing import List


class Solution:
    def generateMatrix(self, n: int) -> List[List[int]]:
        # ✅ 正确：每行独立分配（不能用 [[0]*n]*n，各行会共享引用）
        nums = [[0] * n for _ in range(n)]
        startx, starty = 0, 0    # 每圈起始点（左上角）
        loop, mid = n // 2, n // 2  # 圈数与中心坐标
        count = 1                 # 当前填入数字

        for offset in range(1, loop + 1):  # offset 控制每圈右边界收缩
            # 上边：左→右，左闭右开（不填最后一个，留给右边起点）
            for i in range(starty, n - offset):
                nums[startx][i] = count
                count += 1
            # 右边：上→下，左闭右开
            for i in range(startx, n - offset):
                nums[i][n - offset] = count
                count += 1
            # 下边：右→左，左闭右开
            for i in range(n - offset, starty, -1):
                nums[n - offset][i] = count
                count += 1
            # 左边：下→上，左闭右开
            for i in range(n - offset, startx, -1):
                nums[i][starty] = count
                count += 1
            # 收缩进入内圈
            startx += 1
            starty += 1

        # 奇数 n：四条边填不到中心，单独处理
        if n % 2 != 0:
            nums[mid][mid] = count
        return nums
