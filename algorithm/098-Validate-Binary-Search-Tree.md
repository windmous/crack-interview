题目链接: [98.Validate Binary Search Tree][1]
难度: Medium

判断二叉搜索树是否合法

# 递归

写法很显然。有人认为用INT_MIN和INT_MAX是有bug的，leetcode官方给出的测试样例也补上了INT_MAX的测试样本，说明官方是不支持直接用INT_MIN和INT_MAX作为默认上下界的。此处我改为long long来存虽然能通过case，但是治标不治本。
```cpp
class Solution {
public:
    bool isValidBST(TreeNode* root) {
        return isValidBST(root, LLONG_MIN, LLONG_MAX); // 改为long long 是因为测试样例出现了INT_MIN或INT_MAX
    }
    
private:
    bool isValidBST(TreeNode* root, long long minval, long long maxval) {
        if (root == nullptr) return true;
        if (root->val >= maxval || root->val <= minval) return false;
        return isValidBST(root->left, minval, root->val) && isValidBST(root->right, root->val, maxval);
    }
};
```

# 中序遍历

合格的二叉查找树的中序遍历序列应该是单调递增的。

```cpp
class Solution {
public:
    bool isValidBST(TreeNode* root) {
        TreeNode* prev = NULL;  // prev的含义是中序遍历中“上一个访问的元素”
        return validate(root, prev);
    }
    bool validate(TreeNode* node, TreeNode* &prev) { // 注意prev是引用，下面何时更新prev较为tricky
		// 以下三行的顺序很重要：
		// 1. node不能为nullptr
		// 2. node左子树是有效的（此时prev指向左子树中序遍历末尾元素），
		// 3. 当前元素大于左子树中序遍历末尾元素
        if (node == NULL) return true;
        if (!validate(node->left, prev)) return false;
        if (prev != NULL && prev->val >= node->val) return false;
        prev = node;
        return validate(node->right, prev);
    }
};
```

[1]: https://leetcode.com/problems/validate-binary-search-tree/