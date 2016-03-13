题目链接: [103.Binary Tree Zigzag Level Order Traversal][1]
难度: Medium

zigzag层次遍历树，若root为第0层，则奇数层从左往右，偶数层从右往左遍历。返回类型为`vector<vector<int>>`，所以即使实现不是层次遍历也无所谓，结果正确即可。


# 递归 6ms

https://leetcode.com/discuss/11328/my-accepted-java-solution

遍历时加上level信息，偶数层的遍历值插在开头。注意下面这个方法是DFS，真正访问元素的顺序并不是层次访问的，而是前序遍历。虽然如此，存在res中的最终结果是zigzag层次遍历的结果。
```cpp
class Solution {
public:
    void travel(TreeNode* cur, vector<vector<int>> &res, int level) {
        if (cur == NULL)    return;

        if (res.size() <= level) {
            res.push_back(vector<int>());
        }

        if (level % 2 == 0)
            res[level].push_back(cur->val);
        else
            res[level].insert(res[level].begin(), cur->val);

        travel(cur->left, res, level+1);
        travel(cur->right, res, level+1);
    }

    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        vector<vector<int>> res;
        travel(root, res, 0);
        return res;
    }
};
```

# 迭代 

https://leetcode.com/discuss/50994/clear-iterative-solution-with-deque-no-reverse

用到了deque来避免vector需要的reverse操作。
```cpp
vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
    vector<vector<int>> res;
    if(!root) return res;
    std::deque<TreeNode*> deq;
    deq.push_back(root);
    int iszig=1;
    while(!deq.empty()) {
        int sz=deq.size();
        iszig=iszig^1;
        vector<int> row;
        while(sz--) {
            if(iszig) { // pop_front, push_back, right then left
                root=deq.front();deq.pop_front();
                row.push_back(root->val);
                if(root->right) deq.push_back(root->right);
                if(root->left) deq.push_back(root->left);
            }
            else { // pop_back, push_front, left then right
                root=deq.back();deq.pop_back();
                row.push_back(root->val);
                if(root->left) deq.push_front(root->left);
                if(root->right) deq.push_front(root->right);
            }
        }
        res.push_back(row);
    }
    return res;
}
```

[1]: https://leetcode.com/problems/binary-tree-zigzag-level-order-traversal/