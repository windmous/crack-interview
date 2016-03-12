题目链接: [94.Binary Tree Inorder Traversal][1]
难度: Medium

- 非递归的中序遍历

# stack 0ms

前序遍历(P144)
```cpp
vector<int> preorderTraversal(TreeNode* root) {
	vector<int> result;
	stack<TreeNode*> s;
	TreeNode *cur = root;
	
	while (!s.empty() || cur != nullptr) {
		if (cur != nullptr) {
			result.push_back(cur->val);
			if (cur->right != nullptr) 
				s.push(cur->right);
			cur = cur->left;
		} else {
			cur = s.top(); s.pop();
		}
	}
	return result;
}
```

中序遍历
```cpp
vector<int> inorderTraversal(TreeNode* root) {
	vector<int> result;
	stack<TreeNode*> s;
	TreeNode *cur = root;
	while (!s.empty() || cur != nullptr) {
		if (cur != nullptr) {
			s.push(cur);
			cur = cur->left;
		} else {
			TreeNode *p = s.top(); s.pop();
			cur = p->right;
			result.push_back(p->val);
		}
	}
	return result;
}
```

后序遍历（P145）
```cpp
vector<int> postorderTraversal(TreeNode* root) {
	vector<int> result;
	TreeNode* cur = root, *lastVisitedNode = nullptr;
	stack<TreeNode*> s;
	
	while (!s.empty() || cur != nullptr) {
		if (cur != nullptr) {
			s.push(cur);
			cur = cur->left;
		} else {
			TreeNode* peekNode = s.top();
    		// if right child exists and traversing node
			// from left child, then move right
			if (peekNode->right != nullptr && lastVisitedNode != peekNode->right) {
				cur = peekNode->right;                    
			} else {
				result.push_back(peekNode->val);
				lastVisitedNode = peekNode;
				s.pop();
			}
		}
	}
	return result;
}
```

# Morris traverse

前序遍历
```cpp
class Solution {
public:
    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> result;
        TreeNode* cur = root, *prev = nullptr;
        
        while (cur != nullptr) {
            if (cur->left == nullptr) {
                result.push_back(cur->val);
                prev = cur;  /* cur 刚被访问过*/
                cur = cur->right;
            } else {
                // 查找前驱
                TreeNode* node = cur->left;
                while (node->right != nullptr && node->right != cur) 
                    node = node->right;
                
                if (node->right == nullptr) { // 还没线索化，则建立线索
                    result.push_back(cur->val);  // 仅这一行的位置与中序不同
                    node->right = cur;
                    prev = cur; // cur 刚刚被访问过
                    cur = cur->left;
                } else {  // 已经线索化，则删除线索
                    node->right = nullptr;
                    cur = cur->right;
                }
            }
        }
        return result;
    }
};
```

中序遍历
```cpp
// Morris中序遍历，时间复杂度O(n)，空间复杂度O(1)
class Solution {
public:
    vector<int> inorderTraversal(TreeNode *root) {
        vector<int> result;
        TreeNode *cur = root, *prev = nullptr;

        while (cur != nullptr) {
            if (cur->left == nullptr) {
                result.push_back(cur->val);
                prev = cur;
                cur = cur->right;
            } else {
                /* 查找前驱 */
                TreeNode *node = cur->left;
                while (node->right != nullptr && node->right != cur)
                    node = node->right;

                if (node->right == nullptr) { /* 还没线索化，则建立线索 */
                    node->right = cur;
                    /* prev = cur; 不能有这句，cur还没有被访问 */
                    cur = cur->left;
                } else {    /* 已经线索化，则访问节点，并删除线索  */
                    result.push_back(cur->val);
                    node->right = nullptr;
                    prev = cur;
                    cur = cur->right;
                }
            }
        }
        return result;
    }
};
```
[1]: https://leetcode.com/problems/binary-tree-inorder-traversal/