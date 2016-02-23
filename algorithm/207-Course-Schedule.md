题目链接：[207. Course Schedule][1]

思路：将输入转换为Graph，然后执行拓扑排序，若排序成功则说明不存在环，反之则相反。

# BFS法1(264ms)
```cpp
class Solution {
public:
    typedef vector<vector<int>> Graph;

    bool canFinish(int numCourses, vector<pair<int, int>>& prerequisites) {
       Graph graph = make_graph(numCourses, prerequisites);
       vector<int> degrees = calc_indegrees(graph);
       
       for (int i = 0; i < numCourses; ++ i) {
           int j = 0;
           for (; j < numCourses; ++ j) {
               if (0 == degrees[j]) {
                   break;
               }
           }
           // 无0度点，说明有环
           if (j == numCourses) return false;
           // 重用了degrees数组
           degrees[j] = -1;
           for (int neigh : graph[j]) {
               -- degrees[neigh];
           }
       }
       
       return true;
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
# BFS法2(244ms)
上面方法中每轮迭代都搜索0度点，比较缓慢，可以用队列保存0度点：
```cpp
class Solution {
public:
    typedef vector<vector<int>> Graph;

    bool canFinish(int numCourses, vector<pair<int, int>>& prerequisites) {
       Graph graph = make_graph(numCourses, prerequisites);
       vector<int> degrees = calc_indegrees(graph);
       
       queue<int> zeros;
        for (int i = 0; i < degrees.size(); ++ i) {
            if (degrees[i] == 0) {
                zeros.push(i);
            }
        }
        
        while (!zeros.empty()) {
            int node = zeros.front();
            zeros.pop();

            for (int neigh : graph[node]) {
                if ((--degrees[neigh]) == 0) {
                    zeros.push(neigh);
                }
            }

            -- numCourses;
        }
       
        return 0 == numCourses;
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

# DFS法(252ms)
下面的代码中使用了两个数组记录各个node的状态，实际是可以缩为一个的，一共有三种状态：
1. node从来没有被访问过
2. node已经被访问
3. node在栈上，正在接受访问

```cpp
class Solution {
public:
    typedef vector<vector<int>> Graph;

    bool canFinish(int numCourses, vector<pair<int, int>>& prerequisites) {
        Graph graph = make_graph(numCourses, prerequisites);
        vector<bool> vis(graph.size(), false), on_path(graph.size(), false);
        
        for (int i = 0; i < numCourses; ++ i) {
            if (!vis[i] && has_cycle(graph, i, vis, on_path)) {
                return false;
            }
        }
        return true;
    }
    
private:
    Graph make_graph(int numCourses, vector<pair<int, int>>& prerequisites) {
        Graph graph(numCourses);
        for (auto p : prerequisites) {
            graph[p.second].push_back(p.first);
        }
        return graph;
    }
    
    bool has_cycle(const Graph &graph, int node, vector<bool> &vis, vector<bool> &on_path) {
        if (vis[node]) return false;
        vis[node] = on_path[node] = true;
        for (int neigh : graph[node]) {
            // 务必先检查on_path再检查vis
            if (on_path[neigh] || has_cycle(graph, neigh, vis, on_path)) {
                return true;
            }
        }
        return on_path[node] = false;
    }
};
```

[1]: https://leetcode.com/problems/course-schedule/