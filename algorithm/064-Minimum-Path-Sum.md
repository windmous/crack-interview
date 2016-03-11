题目链接: [64.Minimum Path Sum][1]
难度: Medium

给定m*n的grid，每个单元都是非负数，求从左上角到右下角的一条路径，使得元素和最小，只能往右往下走，返回和即可

# 动归 
f[i][j]=min(f[i-1][j], f[i][j-1])+grid[i][j]

```cpp
class Solution {
public:
    int minPathSum(vector<vector<int> > &grid) {
        const int m = grid.size();
        const int n = grid[0].size();

        int f[n];
        fill(f, f+n, INT_MAX); // 初始值是 INT_MAX，因为后面用了min函数。
        f[0] = 0;

        for (int i = 0; i < m; i++) {
            f[0] += grid[i][0];
            for (int j = 1; j < n; j++) {
                // 左边的f[j]，表示更新后的f[j]，与公式中的f[i[[j]对应
                // 右边的f[j]，表示老的f[j]，与公式中的f[i-1][j]对应
                f[j] = min(f[j - 1], f[j]) + grid[i][j];
            }
        }
        return f[n - 1];
    }
};
```

[1]: https://leetcode.com/problems/minimum-path-sum/