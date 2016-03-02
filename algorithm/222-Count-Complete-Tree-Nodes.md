题目链接: [222.Count Complete Tree Nodes][1]
难度: Medium

# 二分法(124ms)
时间复杂度：O((logN)^2)
```cpp
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    int getLeftHeight(TreeNode *root) {
        int height = 0;
        while (root) {
            height ++;
            root = root->left;
        }
        return height;
    }
    
    int countNodes(TreeNode* root) {
        if (!root) return 0;
        int leftHeight = getLeftHeight(root->left);
        int rightHeight = getLeftHeight(root->right);
        
        if (leftHeight == rightHeight) {
            return (1<<leftHeight) + countNodes(root->right);
        } else {
            return (1<<rightHeight) + countNodes(root->left);
        }
    }
};
```

# 二分法2(180ms)
时间复杂度：O((logN)^2)

```cpp
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
  int countNodes(TreeNode* root) {
        if (!root) return 0;
        int leftHeight = 0, rightHeight = 0;
        for (TreeNode *p = root; p; ++leftHeight, p = p->left) ;
        for (TreeNode *p = root; p; ++rightHeight, p = p->right) ;
        if (leftHeight == rightHeight) {
            return (1 << leftHeight) - 1;
        } else {
            return 1 + countNodes(root->left) + countNodes(root->right);
        }
    }
};
```

[1]: https://leetcode.com/problems/count-complete-tree-nodes/