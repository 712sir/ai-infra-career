/*
 * ============================================
 * 题目：59. 螺旋矩阵 II (Spiral Matrix II)
 * 难度：Medium
 * 链接：https://leetcode.cn/problems/spiral-matrix-ii/
 * 来源：代码随想录 01-array
 * ============================================
 */

/*
 * 思路：
 *   模拟顺时针填充。每圈按 上→右→下→左 四条边依次填入，
 *   每条边坚持「左闭右开」原则（不填最后一个点，留给下一条边起点）。
 *   总圈数 = n/2，奇数 n 时中心单独填入最后一个数。
 *
 * 时间复杂度：O(n²)（每个格子填一次）
 * 空间复杂度：O(n²)（结果矩阵）
 */

/*
 * 注意事项 / 易错点：
 *   1. 每条边坚持左闭右开，边界一致避免混乱
 *   2. 循环圈数 = n / 2（不是 n）
 *   3. 奇数 n 最后手工填中心点
 *   4. 每圈起始点 (startx, starty) 递增，offset 递增缩小边界
 */

#include <vector>
using namespace std;

class Solution {
public:
    vector<vector<int>> generateMatrix(int n) {
        vector<vector<int>> res(n, vector<int>(n, 0));  // n×n 全零矩阵
        int startx = 0, starty = 0;   // 每圈起始点（左上角）
        int loop = n / 2;              // 总圈数（n 为偶数恰好填满，奇数剩中心）
        int mid = n / 2;               // 奇数 n 的中心坐标
        int count = 1;                 // 当前填入数字
        int offset = 1;                // 每圈右边界收缩量
        int i, j;
        while (loop--) {
            i = startx, j = starty;
            // 上边：左→右，左闭右开（不填最后一个）
            for (; j < n - offset; j++) res[i][j] = count++;
            // 右边：上→下，左闭右开
            for (; i < n - offset; i++) res[i][j] = count++;
            // 下边：右→左，左闭右开
            for (; j > starty; j--)    res[i][j] = count++;
            // 左边：下→上，左闭右开
            for (; i > startx; i--)    res[i][j] = count++;
            // 收缩进入内圈
            startx++; starty++;
            offset++;
        }
        // 奇数 n：四条边填不到中心，单独处理
        if (n % 2) {
            res[mid][mid] = count;
        }
        return res;
    }
};
