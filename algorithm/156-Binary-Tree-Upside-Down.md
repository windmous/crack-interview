题目链接: [156.Binary Tree Upside Down][1]
难度: Medium

Given a binary tree where all the right nodes are either leaf nodes with a sibling (a left node that shares the same parent node) or empty, flip it upside down and turn it into a tree where the original right nodes turned into left leaf nodes. Return the new root.
For example:
Given a binary tree {1,2,3,4,5},
    1
   / \
  2   3
 / \
4   5
return the root of the binary tree [4,5,2,#,#,3,1].
   4
  / \
 5   2
    / \
   3   1  

思路：
1. 对于一个parent来说，加入有right node，必须得有left node。而有left node，right node可以为空。而right node必须为叶子节点。所以该树每层至多有2个节点，并且2节点有共同的parent。
2. 所以对于最底层来说，必有一个left node，而这个left node则为整个新树的根 —— 例子中的4为最底层的左节点，最后成为新树的root。
3. 原树的根节点，变为了新树的最右节点。
3. 对于子树1 2 3来说，需要在以2为根的子树2 4 5建立成新树4 5 2后，插入到新树的最右节点2下面。原树的根节点root为left child，原树root->right为新树的left nnode
递归实现：

# 递归1
```java
public TreeNode UpsideDownBinaryTree(TreeNode root) {  
    if (root == null)  
        return null;  
    TreeNode parent = root, left = root.left, right = root.right;  
    if (left != null) {  
        TreeNode ret = UpsideDownBinaryTree(left);  
        left.left = right;  
        left.right = parent;  
        return ret;  
    }  
    return root;  
}  
```

# 迭代
```java
public TreeNode UpsideDownBinaryTree(TreeNode root) {  
    TreeNode node = root, parent = null, right = null;  
    while (node != null) {  
        TreeNode left = node.left;  
        node.left = right;  
        right = node.right;  
        node.right = parent;  
        parent = node;  
        node = left;  
    }  
    return parent;  
}
```

[1]: https://leetcode.com/problems/binary-tree-upside-down/