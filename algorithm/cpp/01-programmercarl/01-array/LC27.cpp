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
 *   快慢指针。快指针 fast 遍历数组寻找"要保留"的元素（nums[fast] != val），
 *   慢指针 slow 指向下一个要写入的位置，即新数组的尾部。
 *   一层循环完成"删除 + 前移"两层工作，空间 O(1)。
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
        int slow = 0;  // 慢指针：下一个要写入的位置，也是最终新数组长度
        for (int fast = 0; fast < static_cast<int>(nums.size()); fast++) {
            if (nums[fast] != val) {       // 找到了要保留的元素
                nums[slow] = nums[fast];    // 拷贝到 slow 位置
                slow++;                     // slow 前进
            }
            // 等于 val 时 slow 不动，相当于跳过（删除）
        }
        return slow;  // slow 即新数组长度
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
