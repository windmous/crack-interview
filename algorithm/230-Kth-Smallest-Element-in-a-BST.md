题目链接: [230.Kth Smallest Element in a BST][1]
难度: Medium

# 递归法(20ms)
```cpp
class Solution {
public:
    int solve(TreeNode *root, int& k) {
        if (!root) return 0;
        int tmp = solve(root->left, k);
        return !k ? tmp : ((!--k) ? root->val : solve(root->right, k));
    }
    
    int kthSmallest(TreeNode* root, int k) {
        return solve(root, k);
    }
};
```

# 迭代法(20ms)
模拟中序遍历
```cpp
class Solution {
public:
    int kthSmallest(TreeNode* root, int k) {
        stack<TreeNode*> ss;
        while (true) {
            while (root) {
                ss.push(root);
                root = root->left;
            }
            
            root = ss.top();
            ss.pop();
            if (0 == --k) return root->val;
            root = root->right;
        }
        
        return -1;
    }
};
```


[1]: https://leetcode.com/problems/kth-smallest-element-in-a-bst/