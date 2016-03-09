题目链接: [52.N-Queens II][1]
难度: Hard

- 输出n queen的解的个数
- 和P51没有本质区别

```cpp
class Solution {
public:
    int totalNQueens(int n) {
        int res = 0;
		// 注意flag_45和flag_135的作用。此处flag值为1表示可以放皇后
        vector<int> flag_col(n, 1), flag_45(2 * n - 1, 1), flag_135(2 * n - 1, 1);
        solveNQueens(res, flag_col, flag_45, flag_135, 0, n);
        return res;
    }
private:
    void solveNQueens(int &res, vector<int> &flag_col, vector<int> &flag_45, vector<int> &flag_135, int row, int &n) {
        if (row == n) {
            ++res;
            return;
        }
        for (int col = 0; col != n; ++col)
            if (flag_col[col] && flag_45[row + col] && flag_135[n - 1 + col - row]) {
                flag_col[col] = flag_45[row + col] = flag_135[n - 1 + col - row] = 0; // 占用
                solveNQueens(res, flag_col, flag_45, flag_135, row + 1, n);
                flag_col[col] = flag_45[row + col] = flag_135[n - 1 + col - row] = 1; // 释放
            }
    }
};
```

[1]: https://leetcode.com/problems/n-queens-ii/