题目链接: [257.Binary Tree Paths][1]
难度: Easy

描述：给定一颗二叉树，生成所有从根到叶子节点的路径。

# DFS法(4ms)
时间复杂度：O(N)
空间复杂度：O(H)
```cpp
class Solution {
public:
    void binaryTreePaths(vector<string>& result, TreeNode* root, string t) {
        if(!root->left && !root->right) {
            result.push_back(t);
            return;
        }
    
        if(root->left) binaryTreePaths(result, root->left, t + "->" + to_string(root->left->val));
        if(root->right) binaryTreePaths(result, root->right, t + "->" + to_string(root->right->val));
    }

    vector<string> binaryTreePaths(TreeNode* root) {
        vector<string> result;
        if(!root) return result;
    
        binaryTreePaths(result, root, to_string(root->val));
        return result;
    }
};
```

# 迭代-先序遍历
时间复杂度：O(N)
空间复杂度：O(N)

```cpp
class Solution {
public:
    vector<string> binaryTreePaths(TreeNode* root) {
        vector<string> res;
        TreeNode *curNode;
        string curPath;
        // pair第2个元素记录当前的路径
        stack<pair<TreeNode*, string>> liveNodes;
        if(root) liveNodes.push(make_pair(root, ""));
        while(!liveNodes.empty())
        {
            curNode = liveNodes.top().first;
            curPath    = liveNodes.top().second;
            liveNodes.pop();
            if(!curNode->left && !curNode->right)
            {
                res.push_back(curPath + std::to_string(curNode->val));
            }
            else
            {
                if(curNode->right) liveNodes.push(make_pair(curNode->right, curPath + std::to_string(curNode->val)+ "->"));
                if(curNode->left)  liveNodes.push(make_pair(curNode->left, curPath + std::to_string(curNode->val)+ "->"));
            }
        }
        return res;
    }
};
```
# 迭代-BFS(4ms)
时间复杂度：O(N)
空间复杂度：O(N)

```cpp
class Solution {
public:
    vector<string> binaryTreePaths(TreeNode* root) {
    	// pair第2个元素记录当前的路径
        queue<pair<TreeNode*, string>> liveNodes[2];
        int cur=0, next=1;
        TreeNode* curNode;
        string curPath;
        vector<string> res;

        if(root) liveNodes[cur].push(make_pair(root, ""));
        while(!liveNodes[cur].empty())
        {
            curNode = liveNodes[cur].front().first;
            curPath = liveNodes[cur].front().second;
            liveNodes[cur].pop();
            if(!curNode->left && !curNode->right) res.push_back(curPath + std::to_string(curNode->val));
            else{
                if(curNode->left)  liveNodes[next].push(make_pair(curNode->left,  curPath + std::to_string(curNode->val) + "->"));
                if(curNode->right) liveNodes[next].push(make_pair(curNode->right, curPath + std::to_string(curNode->val) + "->"));
            }
            if(liveNodes[cur].empty()) swap(cur, next);
        }
        return res;
    }
};
```


# 单函数DFS法(4ms)
时间复杂度：O(N)
空间复杂度：O(H)

```cpp
class Solution {
public:
    vector<string> binaryTreePaths(TreeNode* root) {
        if (root == nullptr)
            return {};
        if (root->left == nullptr && root->right == nullptr)
            return {to_string(root->val)};
    
        vector<string> left  = binaryTreePaths(root->left);
        vector<string> right = binaryTreePaths(root->right);
        left.insert(left.end(), begin(right), end(right));
        for_each(left.begin(), left.end(), [root](string& s) {s = to_string(root->val) + "->" + s;});
    
        return left;
    }
};
```

[1]: https://leetcode.com/problems/binary-tree-paths/