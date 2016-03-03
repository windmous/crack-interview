题目链接: [226.Invert Binary Tree][1]
难度: Easy

本题本质是完成一次树的遍历，用先序遍历、后序遍历均可以。

# 递归法(4ms)
```cpp
class Solution {
public:
    TreeNode* invertTree(TreeNode* root) {
        if (root) {
            invertTree(root->left);
            invertTree(root->right);
            swap(root->left, root->right);
        }
        return root;
    }
};
```

# 迭代法(4ms)
使用栈来模拟先序遍历

```cpp
class Solution {
public:
    TreeNode* invertTree(TreeNode* root) {
        stack<TreeNode*> ss;
        ss.push(root);
        
        while (!ss.empty()) {
            TreeNode *cur = ss.top();
            ss.pop();
            
            if (cur) {
                swap(cur->left, cur->right);
                ss.push(cur->left);
                ss.push(cur->right);
            }
        }
        
        return root;
    }
};
```

# BFS(0ms)
```cpp
class Solution {
public:
    TreeNode* invertTree(TreeNode* root) {
        queue<TreeNode*> q;
        q.push(root);
        
        while (!q.empty()) {
            TreeNode *cur = q.front();
            q.pop();
            
            if (cur) {
                q.push(cur->left);
                q.push(cur->right);
                swap(cur->left, cur->right);
            }
        }
        
        return root;
    }
};
```

[1]: https://leetcode.com/problems/invert-binary-tree/