题目链接: [113.Path Sum II][1]
难度: Medium

树的节点附带一个值，找到树从根到叶子的所有路径，使得各个节点和为目标值。

# dfs

https://leetcode.com/discuss/45131/12ms-11-lines-c-solution

```cpp
class Solution {
public:
    vector<vector<int>> pathSum(TreeNode* root, int sum) {
        vector<vector<int> > paths;
        vector<int> path;
        findPaths(root, sum, path, paths);
        return paths;  
    }
private:
    void findPaths(TreeNode* node, int sum, vector<int>& path, vector<vector<int> >& paths) {
        if (!node) return;
        path.push_back(node -> val);
        if (!(node -> left) && !(node -> right) && sum == node -> val)
            paths.push_back(path);
        findPaths(node -> left, sum - node -> val, path, paths);
        findPaths(node -> right, sum - node -> val, path, paths);
        path.pop_back();
    }
};
```

[1]: https://leetcode.com/problems/path-sum-ii/