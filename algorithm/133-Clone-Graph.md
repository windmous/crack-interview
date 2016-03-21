题目链接: [133.Clone Graph][1]
难度: Medium

描述：复制一个给定的无向图

# 深搜(76ms)
时间复杂度：O(N)
空间复杂度：O(N)

```cpp
class Solution {
public:
    UndirectedGraphNode *cloneGraph(UndirectedGraphNode *node) {
        using NodePtr = UndirectedGraphNode *;
        // 哈希表有两个作用：1.担任vis数组 2.记录副本
        unordered_map<NodePtr, NodePtr> copied; // key是原图node指针，value是克隆图node指针
        function<NodePtr(NodePtr)> clone = [&](NodePtr node) -> NodePtr {
            if (nullptr == node) return nullptr;
            if (copied.find(node) == copied.end()) {
                auto copied_node = copied[node] = new UndirectedGraphNode(node->label);
                for (auto child : node->neighbors) {
                    copied_node->neighbors.push_back(clone(child));
                }
            }
            return copied[node];
        };
        
        return clone(node);
    }
};
```

简化版

https://leetcode.com/discuss/26440/9-line-c-dfs-solution

```cpp
class Solution {
public:
    unordered_map<UndirectedGraphNode*, UndirectedGraphNode*> hash;
    UndirectedGraphNode *cloneGraph(UndirectedGraphNode *node) {
       if (!node) return node;
       if(hash.find(node) == hash.end()) {
           hash[node] = new UndirectedGraphNode(node -> label);
           for (auto x : node -> neighbors) {
                (hash[node] -> neighbors).push_back( cloneGraph(x) );
           }
       }
       return hash[node];
    }
};
```

# 广搜(77ms)
时间复杂度：O(N)
空间复杂度：O(N)

```cpp
class Solution {
public:
    UndirectedGraphNode *cloneGraph(UndirectedGraphNode *node) {
        if (nullptr == node) return nullptr;
        using NodePtr = UndirectedGraphNode *;
        // 哈希表担任vis数组并记录副本
        unordered_map<NodePtr, NodePtr> copied;
        queue<NodePtr> q;
        q.push(node);
        copied[node] = new UndirectedGraphNode(node->label);
        
        while (!q.empty()) {
            const auto cur = q.front();
            q.pop();
            for (auto nbr : cur->neighbors) {
                if (copied.find(nbr) != copied.end()) {
                    copied[cur]->neighbors.push_back(copied[nbr]);
                } else {
                    NodePtr new_node = new UndirectedGraphNode(nbr->label);
                    copied[nbr] = new_node;
                    copied[cur]->neighbors.push_back(new_node);
                    q.push(nbr);
                }
            }
        }
        
        return copied[node];
    }
};
```

[1]: https://leetcode.com/problems/clone-graph/