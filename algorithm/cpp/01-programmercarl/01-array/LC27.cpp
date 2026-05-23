/*
 * ============================================
 * 题目：27. 移除元素 (Remove Element)
 * 难度：Easy
 * 链接：https://leetcode.cn/problems/remove-element/
 * 来源：代码随想录 01-array
 * ============================================
 */

/*
 * 思路：
 *   快慢指针。快指针 fast 遍历数组，遇到不等于 val 的元素就拷贝到
 *   慢指针 slow 的位置，slow 前进。最终 slow 即新数组长度。
 *
 * 时间复杂度：O(n)
 * 空间复杂度：O(1)
 */

/*
 * 注意事项 / 易错点：
 *   1. slow 只在写入时才前进，fast 每轮都前进
 *   2. 返回的是 slow（不是 slow+1），因为 slow 在写完后才自增
 *   3. 不需要管 slow 之后的内容
 */

#include <vector>
#include <iostream>
using namespace std;

class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        int slow = 0;
        for (int fast = 0; fast < static_cast<int>(nums.size()); fast++) {
            if (nums[fast] != val) {
                nums[slow] = nums[fast];
                slow++;
            }
        }
        return slow;
    }
};

int main() {
    Solution s;
    vector<int> nums = {3, 2, 2, 3};
    int len = s.removeElement(nums, 3);
    cout << "len=" << len << " -> ";
    for (int i = 0; i < len; i++) cout << nums[i] << " ";
    cout << endl;
    return 0;
}
