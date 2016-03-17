题目链接: [111.Minimum Depth of Binary Tree][1]
难度: Easy

如题。

```cpp
class Solution {
public:
    int minDepth(TreeNode *root) {
        if(!root) return 0;
        if(!root->left) return 1 + minDepth(root->right); //注意虽然root->left是null，但是可能root->right不是null，因此root可能不是一个叶子节点
        if(!root->right) return 1 + minDepth(root->left);
        return 1+min(minDepth(root->left),minDepth(root->right));
    }
};
```

[1]: https://leetcode.com/problems/minimum-depth-of-binary-tree/