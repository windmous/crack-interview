题目链接: [107.Binary Tree Level Order Traversal II][1]
难度: Easy

层次遍历二叉树，要求返回的`vector<vector<int>>`中，最底层的放在下标小的一方。

将P102 Binary Tree Level Order Traversal的结果reverse一下即可。

# 递归
```cpp
vector<vector<int> > res;

void DFS(TreeNode* root, int level)
{
    if (root == NULL) return;
    if (level == res.size()) // The level does not exist in output
    {
        res.push_back(vector<int>()); // Create a new level
    }

    res[level].push_back(root->val); // Add the current value to its level
    DFS(root->left, level+1); // Go to the next level
    DFS(root->right,level+1);
}

vector<vector<int> > levelOrderBottom(TreeNode *root) {
    DFS(root, 0);
    return vector<vector<int> > (res.rbegin(), res.rend());
}
```

# 迭代

在P102的return前加个reverse

[1]: https://leetcode.com/problems/binary-tree-level-order-traversal-ii/