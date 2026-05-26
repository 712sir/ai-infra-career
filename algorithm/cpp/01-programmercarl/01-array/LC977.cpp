/*
 * ============================================
 * 题目：977. 有序数组的平方 (Squares of a Sorted Array)
 * 难度：Easy
 * 链接：https://leetcode.cn/problems/squares-of-a-sorted-array/
 * 来源：代码随想录 01-array
 * ============================================
 */

/*
 * 思路：
 *   数组本身有序，但负数平方后可能变大。平方后的最大值一定出现在
 *   数组两端（最左或最右），不可能是中间。用双指针 i 从头、j 从尾
 *   向中间靠拢，每次取平方较大者放入结果数组末尾（k 指针倒序填充）。
 *
 * 时间复杂度：O(n)
 * 空间复杂度：O(n)（结果数组）
 */

/*
 * 注意事项 / 易错点：
 *   1. 循环条件是 i <= j（不是 i < j），漏掉中间元素
 *   2. k 从末尾向前填充，因为先确定的是最大值
 *   3. 相等时取哪边都行，取左边（即走 else 分支）
 */

#include <vector>
using namespace std;

class Solution {
public:
    vector<int> sortedSquares(vector<int>& nums) {
        int k = nums.size() - 1;                   // 结果数组的尾部指针（倒序填充）
        vector<int> res(nums.size(), 0);           // 预分配结果数组
        // i 指向左端（负数区），j 指向右端（正数区），向中间收缩
        for (int i = 0, j = nums.size() - 1; i <= j;) {
            if (nums[i] * nums[i] < nums[j] * nums[j]) {
                res[k] = nums[j] * nums[j];  // 右端平方更大，放末尾
                k--;
                j--;                          // 右指针左移
            } else {
                res[k] = nums[i] * nums[i];  // 左端平方更大，放末尾
                k--;
                i++;                          // 左指针右移
            }
        }
        return res;
    }
};
