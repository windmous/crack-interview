题目链接: [101.Symmetric Tree][1]
难度: Easy

判断一棵树是否左右对称，要求递归和迭代版本都实现了。

# 递归

```cpp
class Solution {
public:
    bool isSymmetric(TreeNode* root) {
        if (root == nullptr) return true;
        return isSymmetric(root->left, root->right);
    }
private:
    bool isSymmetric(TreeNode* left, TreeNode* right) {
        if (left == nullptr || right == nullptr) return left == right;
        return left->val == right->val &&
			   isSymmetric(left->left, right->right) &&
			   isSymmetric(left->right, right->left);
    }
};

```

# 迭代

https://leetcode.com/discuss/13978/my-c-accepted-code-in-16ms-with-iteration-solution

```cpp
class Solution {
public:
    bool isSymmetric(TreeNode *root) {
        TreeNode *left, *right;
        if (!root)
            return true;

        queue<TreeNode*> q1, q2;
        q1.push(root->left);
        q2.push(root->right);
        while (!q1.empty() && !q2.empty()){
            left = q1.front();
            q1.pop();
            right = q2.front();
            q2.pop();
            if (NULL == left && NULL == right)
                continue;
            if (NULL == left || NULL == right)
                return false;
            if (left->val != right->val)
                return false;
            q1.push(left->left);
            q1.push(left->right);
            q2.push(right->right);
            q2.push(right->left);
        }
        return true;
    }
};
```

[1]: https://leetcode.com/problems/symmetric-tree/