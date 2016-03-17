题目链接: [114.Flatten Binary Tree to Linked List][1]
难度: Medium

Given a binary tree, flatten it to a linked list in-place.
```
Given

         1
        / \
       2   5
      / \   \
     3   4   6
The flattened tree should look like:
   1
    \
     2
      \
       3
        \
         4
          \
           5
            \
             6
```


Hints:
If you notice carefully in the flattened tree, each node's right child points to the next node of a pre-order traversal.


# 递归

https://leetcode.com/discuss/30719/my-short-post-order-traversal-java-solution-for-share

这个解法很妙，先扁平化右子树，再扁平化左子树，同时保持一个prev指针指向已经扁平化的链表头部。

可以想象链表生成的过程，从最底下开始不断向上生成，并且prev始终在链表头部。

```cpp
class Solution {
    TreeNode* prev = nullptr;
public:
    void flatten(TreeNode* root) {
        if (root == nullptr) return;
        flatten(root->right);
        flatten(root->left);
        root->right = prev;
        root->left = nullptr;
        prev = root;
    }
};
```

# 非递归

https://leetcode.com/discuss/13054/share-my-simple-non-recursive-solution-o-1-space-complexity

借鉴了Morris traversal的思想，非常巧妙的想法。

```cpp
class Solution {
public:
    void flatten(TreeNode *root) {
        TreeNode*now = root;
        while (now)
        {
            if(now->left)
            {
                //Find current node's prenode that links to current node's right subtree
                TreeNode* pre = now->left;
                while(pre->right)
                {
                    pre = pre->right;
                }
                pre->right = now->right;
                //Use current node's left subtree to replace its right subtree(original right 
                //subtree is already linked by current node's prenode
                now->right = now->left;
                now->left = NULL;
            }
            now = now->right;
        }
    }
};
```

# 递归（比较好想的方法）

https://leetcode.com/discuss/27643/straightforward-java-solution

下面是java代码，这种想法比较朴素

```java
public void flatten(TreeNode root) {
        if (root == null) return;

        TreeNode left = root.left;
        TreeNode right = root.right;

        root.left = null;

        flatten(left);
        flatten(right);

        root.right = left;
        TreeNode cur = root;
        while (cur.right != null) cur = cur.right;
        cur.right = right;
    }
```

[1]: https://leetcode.com/problems/flatten-binary-tree-to-linked-list/