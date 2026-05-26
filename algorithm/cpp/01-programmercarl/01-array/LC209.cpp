/*
 * ============================================
 * 题目：209. 长度最小的子数组 (Minimum Size Subarray Sum)
 * 难度：Medium
 * 链接：https://leetcode.cn/problems/minimum-size-subarray-sum/
 * 来源：代码随想录 01-array
 * ============================================
 */

/*
 * 思路：
 *   滑动窗口。右边界 j 扩张累加 sum，当 sum >= target 时，
 *   持续收缩左边界 i（while 循环），记录最小窗口长度，
 *   直到 sum < target 再继续扩张右边界。
 *
 * 时间复杂度：O(n)（每个元素进窗口一次、出窗口一次，共 2n）
 * 空间复杂度：O(1)
 */

/*
 * 注意事项 / 易错点：
 *   1. 收缩左边界用 while 而非 if（可能连续收缩多次）
 *   2. 窗口长度 = j - i + 1
 *   3. 返回前判断 res 是否被更新过，未更新说明无解返回 0
 *   4. 时间复杂度 O(n)：每个元素进窗口一次、出窗口一次，共 2n
 */

#include <vector>
#include <climits>
using namespace std;

class Solution {
public:
    int minSubArrayLen(int target, vector<int>& nums) {
        int res = INT32_MAX;   // 哨兵：记录最短窗口长度，初始为最大值
        int sum = 0;           // 当前窗口内元素之和
        int i = 0;             // 窗口左边界
        int subL = 0;          // 当前窗口长度
        // j 是窗口右边界（for 循环的索引表示终止位置）
        for (int j = 0; j < nums.size(); j++) {
            sum += nums[j];                    // 右边界扩张，纳入新元素
            // 窗口满足条件时，持续收缩左边界（while 而非 if！）
            while (sum >= target) {
                subL = j - i + 1;              // 当前窗口长度
                res = res < subL ? res : subL; // 更新最短长度
                sum -= nums[i];                // 左边界元素移出窗口
                i++;                           // 左边界右移，缩小窗口
            }
        }
        return res == INT32_MAX ? 0 : res;  // 无解返回 0
    }
};
