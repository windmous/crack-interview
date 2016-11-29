题目链接: [317.Shortest Distance from All Buildings][1]
难度: Hard

You want to build a house on an empty land which reaches all buildings in the shortest amount of distance. You can only move up, down, left and right. You are given a 2D grid of values 0, 1 or 2, where:

Each 0 marks an empty land which you can pass by freely.
Each 1 marks a building which you cannot pass through.
Each 2 marks an obstacle which you cannot pass through.
For example, given three buildings at (0,0), (0,4), (2,2), and an obstacle at (0,2):

1 - 0 - 2 - 0 - 1
|   |   |   |   |
0 - 0 - 0 - 0 - 0
|   |   |   |   |
0 - 0 - 1 - 0 - 0
The point (1,2) is an ideal empty land to build a house, as the total travel distance of 3+3+1=7 is minimal. So return 7.

# BFS
时间复杂度：O(M^2N^2)
空间复杂度：O(MN)

从各个城市出发执行BFS即可，主要必须额外统计每个城市被访问的次数

```cpp
class Solution {
public:
    int shortestDistance(vector<vector<int>>& grid) {
        if (grid.empty()) return -1;
        const int N = grid.size(), M = grid[0].size();
        vector<vector<int>> total_dist(N, vector<int>(M, 0)),
                            total_vis(N, vector<int>(M, 0));
        int n_cities = 0;
        for (int i = 0; i < N; ++ i) {
            for (int j = 0; j < M; ++ j) {
                if (grid[i][j] == 1) {
                    ++ n_cities;
                    static int deltas[] = {0, 1, 0, -1, 0};
                    vector<vector<int>> dist(N, vector<int>(M, -1));
                    dist[i][j] = 0;
                    queue<pair<int,int>> Q;
                    Q.push({i, j});
                    
                    while (!Q.empty()) {
                        int y = Q.front().first, x = Q.front().second;
                        Q.pop();
                        for (int d = 0; d < 4; ++ d) {
                            int new_y = deltas[d] + y, new_x = deltas[d+1] + x;
                            if (new_y < 0 || new_y >= N || new_x < 0 || new_x >= M || grid[new_y][new_x] != 0 || dist[new_y][new_x] >= 0)
                                continue;
                            dist[new_y][new_x] = dist[y][x] + 1;
                            total_dist[new_y][new_x] += dist[new_y][new_x];
                            Q.push({new_y, new_x});
                            ++ total_vis[new_y][new_x];
                        }
                    }
                }
            }
        }
        
        int ans = INT_MAX;
        for (int i = 0; i < N; ++ i) {
            for (int j = 0; j < M; ++ j) {
                if (total_vis[i][j] == n_cities) {
                    ans = min(ans, total_dist[i][j]);
                }
            }
        }
        return ans == INT_MAX ? -1 : ans;
    }
};
```

[1]: https://leetcode.com/problems/shortest-distance-from-all-buildings/