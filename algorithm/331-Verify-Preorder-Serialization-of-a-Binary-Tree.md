题目链接: [331.Verify Preorder Serialization of a Binary Tree][1]
难度: Medium

# 基于度统计(12ms)
时间复杂度：O(N)
空间复杂度：O(N)

Some used stack. Some used the depth of a stack. Here I use a different perspective. In a binary tree, if we consider null as leaves, then

* all non-null node provides 2 outdegree and 1 indegree (2 children and 1 parent), except root
* all null node provides 0 outdegree and 1 indegree (0 child and 1 parent).

Suppose we try to build this tree. During building, we record the difference between out degree and in degree `diff = outdegree - indegree`. When the next node comes, we then decrease `diff` by 1, because the node provides an in degree. If the node is not `null`, we increase `diff` by 2, because it provides two out degrees. If a serialization is correct, diff should never be negative and diff will be zero when finished.

```cpp
class Solution {
public:
    vector<string> split(const string &preorder) {
        stringstream ss(preorder);
        string sep;
        vector<string> result;
        while (getline(ss, sep, ',')) {
            result.push_back(sep);
        }
        return result;
    }
    
    bool isValidSerialization(string preorder) {
        auto seps = split(preorder);
        int diff = 1;
        for (const string &s : seps) {
        	# diff < 0通常是因为已经形成了完整的tree，但还有额外的节点。
            if (--diff < 0) return false;
            if (s != "#") diff += 2;
        }
        return 0 == diff;
    }
};
```

# 栈模拟法(12ms)
时间复杂度：O(N)
空间复杂度：O(1)

遇到非null节点就将深度+1， 否则将深度-1。中间深度值不能过高
```cpp
class Solution {
public:
    vector<string> split(const string &preorder) {
        stringstream ss(preorder);
        string sep;
        vector<string> result;
        while (getline(ss, sep, ',')) {
            result.push_back(sep);
        }
        return result;
    }
    
    bool isValidSerialization(string preorder) {
        auto seps = split(preorder);
        int depth = 0;
        for (int i = 0; i + 1 < seps.size(); ++ i) {
            if (seps[i] == "#") {
                if (-- depth < 0) return false;
            } else {
                ++ depth;
            }
        }
        
        return depth == 0 && seps.back() == "#";
    }
};
```

[1]: https://leetcode.com/problems/verify-preorder-serialization-of-a-binary-tree/