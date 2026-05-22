/*
 * ============================================
 * 题目：704. 二分查找 (Binary Search)
 * 难度：Easy
 * 链接：https://leetcode.cn/problems/binary-search/
 * 来源：代码随想录 01-array
 * ============================================
 */

/*
 * 思路：
 *   经典二分查找。左闭右闭区间 [left, right]，每次取 mid 与 target 比较，
 *   相等返回 mid，target 更小则收缩右边界，更大则收缩左边界。
 *
 * 时间复杂度：O(log n)
 * 空间复杂度：O(1)
 */

/*
 * 注意事项 / 易错点：
 *   1. while 条件是 left <= right（左闭右闭，left==right 时区间仍有一个元素）
 *   2. mid 用 left + (right - left) / 2 防溢出
 *   3. 收缩时 left = mid + 1 / right = mid - 1（mid 已排除）
 */

#include <vector>
using namespace std;

class Solution {
public:
    int search(vector<int>& nums, int target) {
        int left = 0, right = nums.size() - 1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (nums[mid] == target) {
                return mid;
            } else if (nums[mid] < target) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        return -1;
    }
};
