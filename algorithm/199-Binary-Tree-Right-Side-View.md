题目链接：[199. Binary Tree Right Side View][1]
# BFS
时间复杂度：O(n)
空间复杂度：O(n) in the worse case

## 单队列（4ms)
下列代码使用单个队列完成遍历
```cpp
class Solution {
public:
    vector<int> rightSideView(TreeNode *root) {
        vector<int> ans;
        queue<TreeNode*> q;
        
        if (root) q.push(root);
        while (!q.empty()) {
            ans.push_back(q.back()->val);
            
            // 逐层遍历trick:
            //  令计数器从大到小计算，可以省一个变量来记录队列大小
            for (auto i = q.size(); i > 0; -- i) {
                TreeNode *head = q.front();
                q.pop();
                if (head->left) q.push(head->left);
                if (head->right) q.push(head->right);
            }
        }
        
        return ans;
    }
};
```

## 双队列(4ms)
```cpp
class Solution {
public:
    vector<int> rightSideView(TreeNode* root) {
        vector<int> ans;
        # 记录当前层和下一层
        vector<TreeNode*> current, next;
        
        if (root) current.push_back(root);
        while (!current.empty()) {
            ans.push_back(current.back()->val);
            
            for (TreeNode *node : current) {
                if (node->left) next.push_back(node->left);
                if (node->right) next.push_back(node->right);
            }
            current.clear();
            swap(current, next);
        }
        
        return ans;
    }
};
```
# DFS
复杂度同BFS

使用mirror版本的先序遍历，即先访问本节点，再访问右侧节点，再访问左侧节点的方法遍历，遍历过程中记录下某一层中首次被访问到的node即可。

```cpp
class Solution {
public:
    void dfs(TreeNode *root, int lev, vector<int> &res) {
        if (!root) return ;
        // 若lev >= res.size()，说明root是lev是第一次被访问到的节点
        if (lev >= res.size()) res.push_back(root->val);
        
        // mirror版本的先序遍历，需要先访问右孩子
        dfs(root->right, lev+1, res);
        dfs(root->left, lev+1, res);
    }

    vector<int> rightSideView(TreeNode *root) {
        vector<int> ans;
        dfs(root, 0, ans);
        
        return ans;
    }
};
```

[1]: https://leetcode.com/problems/binary-tree-right-side-view/