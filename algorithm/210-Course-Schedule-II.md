题目链接：[207. Course Schedule][1]

思路：将输入转换为Graph，然后执行拓扑排序，若排序成功则说明不存在环，反之则相反。

# BFS法(452ms)
```cpp
class Solution {
public:
    typedef vector<vector<int>> Graph;
    vector<int> findOrder(int N, vector<pair<int, int>>& prerequisites) {
       Graph graph = make_graph(N, prerequisites);
       vector<int> degrees = calc_indegrees(graph);
       vector<int> ans;
       
       for (int i = 0; i < N; ++ i) {
           int j = 0;
           for (; j < N; ++ j) {
               if (0 == degrees[j]) {
                   break;
               }
           }
           // 无0度点，说明有环
           if (j == N) return vector<int>();
           ans.push_back(j);
           
           // 重用了degrees数组
           degrees[j] = -1;
           for (int neigh : graph[j]) {
               -- degrees[neigh];
           }
       }
       
       return ans;
    }
private:
    Graph make_graph(int numCourses, vector<pair<int, int>>& prerequisites) {
        Graph graph(numCourses);
        for (auto p : prerequisites) {
            graph[p.second].push_back(p.first);
        }
        return graph;
    }
    
    vector<int> calc_indegrees(const Graph &graph) {
        vector<int> degrees(graph.size());
        for (const auto &neighbors : graph) {
            for (int neigh : neighbors) {
                degrees[neigh] ++;
            }
        }
        return degrees;
    }
};
```

# BFS法2(496ms)
上面方法中每轮迭代都搜索0度点，比较缓慢，可以用队列保存0度点：
```cpp
class Solution {
public:
    typedef vector<vector<int>> Graph;
    vector<int> findOrder(int N, vector<pair<int, int>>& prerequisites) {
       Graph graph = make_graph(N, prerequisites);
       vector<int> degrees = calc_indegrees(graph);
       queue<int> zeros;
        for (int i = 0; i < degrees.size(); ++ i) {
            if (degrees[i] == 0) {
                zeros.push(i);
            }
        }
        
        vector<int> ans;
        for (int i = 0; i < N; ++ i) {
            if (zeros.empty()) return {};
            int node = zeros.front();
            zeros.pop();
            ans.push_back(node);

            for (int neigh : graph[node]) {
                if ((--degrees[neigh]) == 0) {
                    zeros.push(neigh);
                }
            }
        }
       
        return ans;
    }
    
private:
    Graph make_graph(int numCourses, vector<pair<int, int>>& prerequisites) {
        Graph graph(numCourses);
        for (auto p : prerequisites) {
            graph[p.second].push_back(p.first);
        }
        return graph;
    }
    
    vector<int> calc_indegrees(const Graph &graph) {
        vector<int> degrees(graph.size());
        for (const auto &neighbors : graph) {
            for (int neigh : neighbors) {
                degrees[neigh] ++;
            }
        }
        return degrees;
    }
};

```

# DFS法(484ms)
```cpp
class Solution {
public:
    typedef vector<vector<int>> Graph;
    vector<int> findOrder(int N, vector<pair<int, int>>& prerequisites) {
        Graph graph = make_graph(N, prerequisites);
        vector<bool> vis(graph.size(), false), on_path(graph.size(), false);
        vector<int> order;
        
        for (int i = 0; i < N; ++ i) {
            if (!vis[i] && has_cycle(graph, i, vis, on_path, order)) {
                return {};
            }
        }
        
        reverse(order.begin(), order.end());
        return order;
    }
    
private:
    Graph make_graph(int numCourses, vector<pair<int, int>>& prerequisites) {
        Graph graph(numCourses);
        for (auto p : prerequisites) {
            graph[p.second].push_back(p.first);
        }
        return graph;
    }
    
    bool has_cycle(const Graph &graph, int node, vector<bool> &vis, vector<bool> &on_path, vector<int> &order) {
        if (vis[node]) return false;
        vis[node] = on_path[node] = true;
        for (int neigh : graph[node]) {
            // 务必先检查on_path再检查vis
            if (on_path[neigh] || has_cycle(graph, neigh, vis, on_path, order)) {
                return true;
            }
        }

        // 注意，不可将该代码提前，本质是后序遍历
        order.push_back(node);
        return on_path[node] = false;
    }
};
```

[1]: https://leetcode.com/problems/course-schedule-ii/