题目链接: [124.Binary Tree Maximum Path Sum][1]
难度: Hard

在二叉树中找到一条路径，使得和最大。路径可为空，也可不经过根节点。

# 递归

用全局变量sum记录不经过根的最大值，递归返回的是“一端是根的路径的和的最大值”。

https://leetcode.com/discuss/14190/accepted-short-solution-in-java
```cpp
class Solution { 
public:
    int maxPathSum(TreeNode* root) {
        sum = INT_MIN;
        pathSum(root);
        return sum;
    }
private:
    int sum;
    int pathSum(TreeNode* node) {
        if (!node) return 0;
        int left = max(0, pathSum(node -> left));
        int right = max(0, pathSum(node -> right));
        sum = max(sum, left + right + node -> val);
        return max(left, right) + node -> val;
    }
};
```

# 递归2

将上面解法的全局变量放在参数列表中。注意解路径肯定有一个根，所以每次调用maxToRoot只需要更新“经过当前根节点的最大路径”即可，解路径一定会被更新的。

https://leetcode.com/discuss/17214/simple-o-n-algorithm-with-one-traversal-through-the-tree

```cpp
class Solution {
    int maxToRoot(TreeNode *root, int &re) {
        if (!root) return 0;
        int l = maxToRoot(root->left, re);
        int r = maxToRoot(root->right, re);
        if (l < 0) l = 0;
        if (r < 0) r = 0;
        if (l + r + root->val > re) re = l + r + root->val;
        return root->val += max(l, r);
    }
public:
    int maxPathSum(TreeNode *root) {
        int max = -2147483648;
        maxToRoot(root, max);
        return max;
    }
};
```

[1]: https://leetcode.com/problems/binary-tree-maximum-path-sum/