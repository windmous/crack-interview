题目链接: [235.Lowest Common Ancestor of a Binary Search Tree][1]
难度: Easy

描述：给定一颗二叉搜索树，求两个节点的最近公共祖先。

# 迭代(40ms)
时间复杂度：O(logN)
空间复杂度：O(1)
```cpp
class Solution { 
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        TreeNode* cur = root;
        while (true) {
            if (p -> val < cur -> val && q -> val < cur -> val)
                cur = cur -> left;
            else if (p -> val > cur -> val && q -> val > cur -> val)
                cur = cur -> right;
            else return cur; 
        }
    }
};
```

# 递归(40ms)
时间复杂度：O(logN)
空间复杂度：O(logN)

```cpp
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (p -> val < root -> val && q -> val < root -> val)
            return lowestCommonAncestor(root -> left, p, q);
        if (p -> val > root -> val && q -> val > root -> val)
            return lowestCommonAncestor(root -> right, p, q);
        return root;
    }
};
```

[1]: https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-search-tree/