题目链接: [106.Construct Binary Tree from Inorder and Postorder Traversal][1]
难度: Medium


# 递归(36ms)

之前使用了java版本
// https://leetcode.com/discuss/10961/my-recursive-java-code-with-o-n-time-and-o-n-space


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
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        if (inorder.empty() || inorder.size() != postorder.size()) return nullptr;
        return solve(0, 0, postorder.size()-1, inorder, postorder);
    }
    
    TreeNode* solve(int in_start, int post_start, int post_end, 
        const vector<int> &inorder, const vector<int> &postorder) {
        if (post_start > post_end) {
            return nullptr;
        }
        
        TreeNode *root = new TreeNode(postorder[post_end]);
        int root_in;
        for (int i = in_start; ; ++ i) {
            if (root->val == inorder[i]) {
                root_in = i;
                break;
            }
        }
        
        const int len_left = root_in - in_start;
        root->left = solve(in_start, post_start, post_start+len_left-1, inorder, postorder);
        root->right = solve(root_in+1, post_start+len_left, post_end-1, inorder, postorder);
        return root;
    }
};
```

# 非递归

https://leetcode.com/discuss/15115/my-comprehension-of-o-n-solution-from-%40hongzhi


与P105的非递归版本思想一致，同样难以理解

```cpp
class Solution {
public:
    TreeNode *buildTree(vector<int> &inorder, vector<int> &postorder) {
        if(inorder.size() == 0)return NULL;
        TreeNode *p;
        TreeNode *root;
        stack<TreeNode *> stn;

        root = new TreeNode(postorder.back()); 
        stn.push(root); 
        postorder.pop_back(); 

        while(true)
        {
            if(inorder.back() == stn.top()->val) 
            {
                p = stn.top();
                stn.pop(); 
                inorder.pop_back(); 
                if(inorder.size() == 0) break;
                if(stn.size() && inorder.back() == stn.top()->val)
                    continue;
                p->left = new TreeNode(postorder.back()); 
                postorder.pop_back();
                stn.push(p->left);
            }
            else 
            {
                p = new TreeNode(postorder.back());
                postorder.pop_back();
                stn.top()->right = p; 
                stn.push(p); 
            }
        }
        return root;
    }
};
```

[1]: https://leetcode.com/problems/construct-binary-tree-from-inorder-and-postorder-traversal/