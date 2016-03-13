题目链接: [102.Binary Tree Level Order Traversal][1]
难度: Easy

层次遍历，要求按层放入`vector<vector<int>>`中。

# 递归

带depth的前序遍历

https://leetcode.com/discuss/15521/one-of-c-solutions-preorder

```cpp
vector<vector<int>> ret;

void buildVector(TreeNode *root, int depth)
{
    if(root == NULL) return;
    if(ret.size() == depth)
        ret.push_back(vector<int>());

    ret[depth].push_back(root->val);
    buildVector(root->left, depth + 1);
    buildVector(root->right, depth + 1);
}

vector<vector<int> > levelOrder(TreeNode *root) {
    buildVector(root, 0);
    return ret;
}
```

# 非递归

https://leetcode.com/discuss/28762/c-solution-using-only-one-queue-use-a-marker-null

```cpp
class Solution {
public:
    vector<vector<int> > levelOrder(TreeNode *root) {
        vector<vector<int> >  result;
        if (!root) return result;
        queue<TreeNode*> q;
        q.push(root);
        q.push(NULL);
        vector<int> cur_vec;
        while(!q.empty()) {
            TreeNode* t = q.front();
            q.pop();
            if (t==NULL) {
                result.push_back(cur_vec);
                cur_vec.resize(0);
                if (q.size() > 0) {
                    q.push(NULL);
                }
            } else {
                cur_vec.push_back(t->val);
                if (t->left) q.push(t->left);
                if (t->right) q.push(t->right);
            }
        }
        return result;
    }
};
```

[1]: https://leetcode.com/problems/binary-tree-level-order-traversal/