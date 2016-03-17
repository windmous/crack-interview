题目链接: [110.Balanced Binary Tree][1]
难度: Easy

判断一棵树是不是平衡二叉树

# 自底向上递归

每个节点只访问一次，O(N)

```cpp
class solution {
public:
int dfsHeight (TreeNode *root) {
        if (root == NULL) return 0;

        int leftHeight = dfsHeight (root -> left);
        if (leftHeight == -1) return -1;
        int rightHeight = dfsHeight (root -> right);
        if (rightHeight == -1) return -1;

        if (abs(leftHeight - rightHeight) > 1)  return -1;
        return max (leftHeight, rightHeight) + 1;
    }
    bool isBalanced(TreeNode *root) {
        return dfsHeight (root) != -1;
    }
};
```

注意和下面这个写法的区别，这个的复杂度是O(N^2)

```cpp
// 复杂度是O(N^2)，不可取！
class solution {
public:
    int depth (TreeNode *root) {
        if (root == NULL) return 0;
        return max (depth(root -> left), depth (root -> right)) + 1;
    }

    bool isBalanced (TreeNode *root) {
        if (root == NULL) return true;

        int left=depth(root->left);
        int right=depth(root->right);

        return abs(left - right) <= 1 && isBalanced(root->left) && isBalanced(root->right);
    }
};
```

[1]: https://leetcode.com/problems/balanced-binary-tree/