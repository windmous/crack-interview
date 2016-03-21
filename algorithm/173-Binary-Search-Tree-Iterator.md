题目链接: [173.Binary Search Tree Iterator][1]
难度: Medium

描述：给定一颗二叉搜索树，设计迭代器，该迭代器以树根作为参数初始化，next和hasNext的平均时间复杂度应为:O(1)，空间复杂度应为O(h)

# 栈模拟法（中序遍历）24ms
时间复杂度：O(1)[平摊]
空间复杂度：O(H)

使用栈模拟中序遍历。

```cpp
/**
 * Definition for binary tree
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class BSTIterator {
public:
    
    BSTIterator(TreeNode *root) {
        setNext(root);
    }

    /** @return whether we have a next smallest number */
    bool hasNext() {
        return !ss.empty();
    }

    /** @return the next smallest number */
    int next() {
        TreeNode* node = ss.top();
        ss.pop();
        setNext(node->right);
        return node->val;
    }
    
private:
    stack<TreeNode*> ss;
    
    void setNext(TreeNode* root) {
        while (root) {
            ss.push(root);
            root = root->left;
        }
    }
};

/**
 * Your BSTIterator will be called like this:
 * BSTIterator i = BSTIterator(root);
 * while (i.hasNext()) cout << i.next();
 */
```

# Morris Traverse(28ms)
时间复杂度：O(1)[平摊]
空间复杂度：O(1)

使用右侧的
```cpp
class BSTIterator {
public:
    BSTIterator(TreeNode *root) {
        p = root;
    }
    
    /** @return whether we have a next smallest number */
    bool hasNext() {
        return p != NULL;
    }
    
    /** @return the next smallest number */
    int next() {
        TreeNode *tmp;
        int ret;
        while(p) {
            if (p->left == NULL) {  
                ret = p->val;
                p = p->right;
                break;
            } else {  
                tmp = p->left;  
                while (tmp->right != NULL && tmp->right != p)  
                    tmp = tmp->right;  
                if (tmp->right == NULL) {  // 首次到达
                    tmp->right = p;  
                    p = p->left;  
                } else { // 第二次到达p位置，应该访问当前节点了
                    ret = p->val;
                    tmp->right = NULL;  
                    p = p->right;
                    break;
                }  
            }  
        }
    
        return ret;
    }

private:
    TreeNode *p;
};
```

[1]: https://leetcode.com/problems/binary-search-tree-iterator/