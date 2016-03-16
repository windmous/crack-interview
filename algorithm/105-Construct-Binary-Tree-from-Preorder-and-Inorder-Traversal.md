题目链接: [105.Construct Binary Tree from Preorder and Inorder Traversal][1]
难度: Medium

如题。

# 递归 40ms

https://leetcode.com/discuss/12179/my-accepted-java-solution

```cpp
class Solution {
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        return helper(0, 0, inorder.size() - 1, preorder, inorder);
    }
    
private:
    TreeNode* helper(int preStart, int inStart, int inEnd, vector<int>& preorder, vector<int>& inorder) {
        if (preStart > preorder.size() - 1 || inStart > inEnd) return nullptr;
        
        TreeNode* root = new TreeNode(preorder[preStart]);
        int inIndex = 0; 
        for (int i = inStart; i <= inEnd; ++i)
            if (inorder[i] == root->val) {
				inIndex = i;
				break;
			}
        // 上面这个for循环可以用find函数替代，但是for循环看着更清爽一点
		
        root->left = helper(preStart + 1, inStart, inIndex - 1, preorder, inorder);
        root->right = helper(preStart + inIndex - inStart + 1, inIndex + 1, inEnd, preorder, inorder);
        return root;
    }
};
```

# 迭代

https://leetcode.com/discuss/2297/the-iterative-solution-is-easier-than-you-think

感觉这个方法并不简单，思想是例如按照层次编号为1~5的完全二叉树

前序：1,2,4,5,3

中序：4,2,5,1,3

2和4顺着1的左子树走，在前序中出现的顺序是1,2,4，但是在中序中出现的顺序就反过来，是4,2,1

1) Keep pushing the nodes from the preorder into a stack (and keep making the tree by adding nodes to the left of the previous node) until the top of the stack matches the inorder.

2) At this point, pop the top of the stack until the top does not equal inorder (keep a flag to note that you have made a pop).

3) Repeat 1 and 2 until preorder is empty. The key point is that whenever the flag is set, insert a node to the right and reset the flag.

作者本人的解 16ms
```cpp
class Solution {
public:
    TreeNode *buildTree(vector<int> &preorder, vector<int> &inorder) {
        if(preorder.size()==0) return NULL;

        stack<TreeNode *> st;
        TreeNode *t,*r,*root;
        int i,j,f;
        f=i=j=0;

        root = new TreeNode(preorder[i]);
        st.push(root);
        t = root;
        i++;

        while(i < preorder.size())
        {
            if(!st.empty() && st.top()->val==inorder[j])
            {
                t = st.top(); 
                st.pop();
                f = 1;
                j++;
            }
            else
            {
                if(f==0)
                {
                    t->left = new TreeNode(preorder[i]);
                    t = t->left;
                    st.push(t);
                    i++;
                }
                else 
                {
                    f = 0;
                    t->right = new TreeNode(preorder[i]);
                    t = t -> right;
                    st.push(t);
                    i++;
                }
            }
        }

        return root;
    }
};
```


评论中的实现 
```cpp
class Solution {
public:
    TreeNode *buildTree(vector<int> &pre, vector<int> &in) {
        int i=0,j=0;
        TreeNode *root=new TreeNode(0x80000000);
        TreeNode *pp=NULL,*ptr=root;
        stack<TreeNode*> sn;sn.push(root);
        while (j<in.size()) {
            if (sn.top()->val==in[j]) {
                pp=sn.top();
                sn.pop();
                j++;
            } else if (pp) {
                ptr=new TreeNode(pre[i]);
                pp->right=ptr;pp=NULL;
                sn.push(ptr);
                i++;
            } else {
                ptr=new TreeNode(pre[i]);
                sn.top()->left=ptr;
                sn.push(ptr);
                i++;
            }
        }
        ptr=root->left;delete root;
        return ptr;
    }
}; 
```

[1]: https://leetcode.com/problems/construct-binary-tree-from-preorder-and-inorder-traversal/