题目链接: [417.Pacific Atlantic Water Flow][1]
难度: Medium

# BFS (82ms)
时间复杂度：O(N*M)
空间复杂度：O(N*M)

```cpp
class Solution {
public:
    vector<pair<int, int>> pacificAtlantic(vector<vector<int>>& matrix) {
        if (matrix.empty()) return {};
        vector<pair<int,int>> result;
        const int N = matrix.size(), M = matrix[0].size();
        vector<vector<int>> visit(N, vector<int>(M, 0));
        
        queue<pair<int,int>> Q;
        for (int i = 0; i < N; ++ i) {
            Q.push({i, 0});
            visit[i][0] = 1;
        }
        for (int j = 1; j < M; ++ j) {
            Q.push({0, j});
            visit[0][j] = 1;
        }
        solve(matrix, visit, result, Q, 1);
        
        for (int i = 0; i < N; ++ i) {
            Q.push({i, M-1});
            visit[i][M-1] |= 2;
        }
        for (int j = 0; j < M-1; ++ j) {
            Q.push({N-1, j});
            visit[N-1][j] |= 2;
        }
        solve(matrix, visit, result, Q, 2);
        
        return result;
    }
    
    void solve(vector<vector<int>> &matrix, vector<vector<int>> &visit, vector<pair<int,int>> &result, queue<pair<int,int>> &Q, int bit) {
        const int N = matrix.size(), M = matrix[0].size();
        static const int deltas[] = {0, -1, 0, 1, 0};
        while (!Q.empty()) {
            int y = Q.front().first, x = Q.front().second;
            Q.pop();
            
            if (visit[y][x] == 3) {
                result.push_back({y, x});
            }
            
            for (int d = 0; d < 4; ++ d) {
                int new_y = y + deltas[d];
                int new_x = x + deltas[d+1];
                if (new_y >= 0 && new_x >= 0 && new_y < N && new_x < M && matrix[y][x] <= matrix[new_y][new_x] && !(visit[new_y][new_x]&bit)) {
                    Q.push({new_y, new_x});
                    visit[new_y][new_x] |= bit;
                }
            }
        }
    }
};
```

# DFS


[1]: https://leetcode.com/problems/pacific-atlantic-water-flow
