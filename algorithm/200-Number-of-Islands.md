题目链接：[199. Binary Tree Right Side View][1]
# DFS(14ms)
时间复杂度：O(n)
空间复杂度：O(n)

下列代码使用单个队列完成遍历
```cpp
class Solution {
public:
    void dfs(vector<vector<char>>& grid, int i, int j) {
        if (i < 0 || i >= grid.size() || j < 0 || j >= grid[0].size() || grid[i][j] != '1') {
            return ;
        }
        
        grid[i][j] = '0';
        
        // 此处换为数组也可以
        dfs(grid, i+1, j);
        dfs(grid, i-1, j);
        dfs(grid, i, j+1);
        dfs(grid, i, j-1);
    }
    
    int numIslands(vector<vector<char>>& grid) {
        int ans = 0;
        
        for (int i = 0; i < grid.size(); ++ i) {
            for (int j = 0; j < grid[0].size(); ++ j){
                if (grid[i][j] != '0') {
                    ans ++;
                    dfs(grid, i, j);
                }
            }
        }
        
        return ans;
    }
};
```

# BFS(12ms)
```cpp
class Solution {
public:
    void bfs(vector<vector<char>>& grid, int i, int j) {
        // 由于在JAVA中没有方法简单地表示二元组，可能要将二维坐标折叠为一维
        queue<pair<int,int>> q;
        q.push({i, j});
        grid[i][j] = '0';
        
        static int dy[] = {1, 0, -1, 0};
        static int dx[] = {0, -1, 0, 1};
        
        while (!q.empty()) {
            int cur_y = q.front().first;
            int cur_x = q.front().second;
            q.pop();

            for (int d = 0; d < 4; ++ d) {
                int new_y = cur_y + dy[d];
                int new_x = cur_x + dx[d];
                
                if (new_y >= 0 && new_y < grid.size() && new_x >= 0 && new_x < grid[0].size() && grid[new_y][new_x] == '1') {
                    grid[new_y][new_x] = '0';
                    q.push({new_y, new_x});
                }
            }
        }
    }
    
    int numIslands(vector<vector<char>>& grid) {
        int ans = 0;
        
        for (int i = 0; i < grid.size(); ++ i) {
            for (int j = 0; j < grid[0].size(); ++ j){
                if (grid[i][j] != '0') {
                    ans ++;
                    bfs(grid, i, j);
                }
            }
        }
        
        return ans;
    }
};
```

# 并查集(8ms)
我们将图中临近的'1'合并，最后统计并查集中集合的个数。
时间复杂度：并查集的查找操作复杂度接近O(nlogn)

```cpp
class UFSet {
public:
    UFSet(int size) : _count(size), _par(new int[size]) {
        for (int i = 0; i < size; ++ i) {
            _par[i] = i;
        }
    }
    
    ~UFSet() {
        delete []_par;
    }
    
    int find(int x) const {
        return _par[x] == x ? x : _par[x] = find(_par[x]);
    }
    
    void merge(int n1, int n2) {
        int s1 = find(n1);
        int s2 = find(n2);
        
        if (s1 != s2) {
            -- _count;
            _par[s1] = s2;
        }
    }
    
    bool connected(int n1, int n2) const {
        return find(n1) == find(n2);
    }
    
    int get_count() const {
        return _count;
    }
    
private:
    int *_par;
    int _count;
};

class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        if (grid.size() == 0) return 0;
        
        const int nr = grid.size(), nc = grid[0].size();
        // 统计零元素个数
        int zeros = 0;
        UFSet ss(nr * nc);
        
        for (int i = 0; i < nr; ++ i) {
            for (int j = 0; j < nc; ++ j) {
                if (grid[i][j] == '1') {
                    if (i < nr - 1 && grid[i+1][j] != '0') 
                        ss.merge(i*nc+j, (i+1)*nc+j);
                        
                    if (j < nc - 1 && grid[i][j+1] != '0')
                        ss.merge(i*nc+j, i*nc+j+1);
                } else {
                    zeros ++;
                }
            }
        }
        
        // 最终并查集中每个'0'都是一个set，所以需要扣去零元素的个数。
        return ss.get_count() - zeros;
    }
};
```

[1]: https://leetcode.com/problems/number-of-islands/