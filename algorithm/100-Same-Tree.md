题目链接: [100.Same Tree][1]
难度: Easy

判断两颗树是否相同

# 递归


https://leetcode.com/discuss/18433/heres-a-c-recursion-solution-in-minimal-lines-of-code

```cpp
//
// Algorithm for the recursion:
// 1)
// If one of the node is NULL then return the equality result of p an q.
// This boils down to if both are NULL then return true, 
// but if one of them is NULL but not the other one then return false
// 2)
// At this point both root nodes represent valid pointers.
// Return true if the root nodes have same value and 
// the left tree of the roots are same (recursion)
// and the right tree of the roots are same (recursion). 
// Otherwise return false. 
//

bool isSameTree(TreeNode *p, TreeNode *q) {
    if (p == NULL || q == NULL) return (p == q);
    return (p->val == q->val && isSameTree(p->left, q->left) && isSameTree(p->right, q->right));
}
```


# 迭代

前序迭代，soul machine

```cpp
class Solution {
public:
    bool isSameTree(TreeNode *p, TreeNode *q) {
        stack<TreeNode*> s;
        s.push(p);
        s.push(q);

        while(!s.empty()) {
            p = s.top(); s.pop();
            q = s.top(); s.pop();

            if (!p && !q) continue;
            if (!p || !q) return false;
            if (p->val != q->val) return false;

			s.push(p->right);
            s.push(q->right);
            
			s.push(p->left);
            s.push(q->left);
        }
        return true;
    }
};
```

[1]: https://leetcode.com/problems/same-tree/