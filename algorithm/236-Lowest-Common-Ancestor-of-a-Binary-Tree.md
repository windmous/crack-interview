题目链接: [236.Lowest Common Ancestor of a Binary Tree][1]
难度: Medium

描述：给定一颗二叉树以及树上的两个节点，求两个节点的最近公共祖先。注意本题中节点是没有父指针的，若提供父指针则问题转换为相交链表求交点问题。

# 递归(24ms)
时间复杂度：O(N)
空间复杂度：O(H)

下面的代码虽然只用一个函数就写成了，但最好拆出一个helper函数。如果递归时调用lowestCommonAncestor，则意味着我们解决一个更小的子问题，即在一颗更小的树上搜索最近公共祖先。然而从实际计算情况看，lowestCommonAncestor变成了搜索子树上是否有p或q或p&q的公共祖先。

```cpp
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if( root == p || root == q || root == NULL)
            return root;
        TreeNode * parent1 = lowestCommonAncestor(root->left, p, q);
        TreeNode * parent2 = lowestCommonAncestor(root->right, p, q);

        if( parent1 && parent2)
            return root;
        else
            return parent1 ? parent1 : parent2;
    }
};
```

# 迭代法(27ms)
时间复杂度：O(N)
空间复杂度：O(H)

迭代法使用后序搜索遍历整个二叉树，一旦遇到了p或者q，就将路径记录下来。最后我们比较p和q的路径即可。

```cpp
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        //iterative, path comparing
        if(!root || root==p || root==q) return root;
        vector<TreeNode*> pathp, pathq, temp;
        temp.push_back(root);
        TreeNode* prev=NULL;
        
        while(pathp.empty() || pathq.empty()){
            root=temp.back();
            if(root==p) pathp=temp;
            if(root==q) pathq=temp;
            if(!root->left && !root->right || !root->right && prev==root->left || root->right && prev==root->right){
                temp.pop_back();
                prev=root;
            }
            else{
                if(!root->left || prev==root->left) temp.push_back(root->right);
                else temp.push_back(root->left);
            }
        }
        
        if (pathp.size() > pathq.size()) pathp.swap(pathq);
        auto pans = mismatch(pathp.begin(), pathp.end(), pathq.begin());
        return pans.first == pathp.end() ? pathp.back() : *(pans.first-1);
    }
};
```
# 迭代法2(52ms)
时间复杂度：O(N)
空间复杂度：O(H)
下面的方法是递归法的迭代版本，模拟了递归调用时栈上的行为。

```cpp
class Solution {
	// 实际上应该称为 带父结点指针+子树搜索结果的TreeNode
    struct Frame {
        TreeNode* node; // 当前节点
        Frame* parent; // 当前节点的父节点
        vector<TreeNode*> subs; // 子树搜索p、q的结果
    };
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        Frame answer;
        stack<Frame> stack;
        stack.push({root, &answer});
        while (stack.size()) {
            Frame *top = &stack.top(), *parent = top->parent;
            TreeNode *node = top->node;
            if (!node || node == p || node == q) {
            	// 注意这里有一个剪枝，如果当前节点是p或者q，我们不再搜索其子树
            	// 能这样做的条件是p、q一定在树中。
                parent->subs.push_back(node);
                stack.pop();
            } else if (top->subs.empty()) {
            	// 该条件意味着还没有搜索过该节点的子树，否则至少有2个NULL在top->subs中
                stack.push({node->right, top});
                stack.push({node->left, top});
            } else {
            	// 已经搜索完子树了
                TreeNode *left = top->subs[0], *right = top->subs[1];
                parent->subs.push_back(!left ? right : !right ? left : node);
                stack.pop();
            }
        }
        return answer.subs[0];
    }
};
```

[1]: https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-tree/