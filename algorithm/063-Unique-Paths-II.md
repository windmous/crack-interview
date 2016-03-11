题目链接: [63.Unique Paths II][1]
难度: Medium

在P62的基础上，grid某些地方放置了障碍物，同样求左上角到右下角的路径个数

与上一题类似，但要特别注意第一列的障碍。在上一题中，第一列全部是1，但是在这一题中不同，第一列如果某一行有障碍物，那么后面的行全为0。

# 动归 4ms

```cpp
class Solution {
public:
    int uniquePathsWithObstacles(vector<vector<int> > &obstacleGrid) {
        const int m = obstacleGrid.size();
        const int n = obstacleGrid[0].size();
        if (obstacleGrid[0][0] || obstacleGrid[m-1][n-1]) return 0;

        vector<int> f(n, 0);
        f[0] = obstacleGrid[0][0] ? 0 : 1;

        for (int i = 0; i < m; i++) {
            f[0] = f[0] == 0 ? 0 : (obstacleGrid[i][0] ? 0 : 1);
            for (int j = 1; j < n; j++)
                f[j] = obstacleGrid[i][j] ? 0 : (f[j] + f[j - 1]);
        }

        return f[n - 1];
    }
};
```

[1]: https://leetcode.com/problems/unique-paths-ii/