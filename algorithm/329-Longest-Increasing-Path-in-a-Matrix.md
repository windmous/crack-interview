题目链接: [329.Longest Increasing Path in a Matrix][1]
难度: Medium

# DFS + DP (59ms, 77.71%)
时间复杂度：O(MN)
空间复杂度：O(MN)

水题，由于要求严格递增，所以直接暴力搜索即可。

```cpp
class Solution {
public:
    int longestIncreasingPath(vector<vector<int>>& matrix) {
        if (matrix.empty()) return 0;
        const int N = matrix.size(), M = matrix[0].size();
        
        vector<vector<int>> cache(N, vector<int>(M, 0));
        int ans = 1;
        for (int i = 0; i < N; ++ i) {
            for (int j = 0; j < M; ++ j) {
                ans = max(solve(matrix, cache, i, j), ans);
            }
        }
        return ans;
    }
    
    int solve(vector<vector<int>> &matrix, vector<vector<int>> &cache, int y, int x) {
        if (cache[y][x] > 0) return cache[y][x];
        
        static const int deltas[] = {0, -1, 0, 1, 0};
        const int N = matrix.size(), M = matrix[0].size();
        
        for (int d = 0; d < 4; ++ d) {
            int new_y = y + deltas[d];
            int new_x = x + deltas[d+1];
            if (new_y >= 0 && new_y < N && new_x >= 0 && new_x < M && matrix[new_y][new_x] > matrix[y][x]) {
                cache[y][x] = max(cache[y][x], solve(matrix, cache, new_y, new_x));
            }
        }
        
        return ++ cache[y][x];
    }
};
```

[1]: https://leetcode.com/problems/longest-increasing-path-in-a-matrix/