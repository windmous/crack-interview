题目链接: [104.Maximum Depth of Binary Tree][1]
难度: Easy

返回树的高度

# 递归

```cpp
class Solution {
public:
    int maxDepth(TreeNode* root) {
        if (root == nullptr) return 0;
        return 1 + max(maxDepth(root->left), maxDepth(root->right));
    }
};
```

[1]: https://leetcode.com/problems/maximum-depth-of-binary-tree/