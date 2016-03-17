题目链接: [116.Populating Next Right Pointers in Each Node][1]
难度: Medium

树的节点多了一个next指针，任务是将每个节点的next指针指向其右边的节点，每层最右节点的next设为null。要求只用常数额外空间。

P116树保证是完全二叉树。P117取消此条件。

```
Given the following perfect binary tree,
         1
       /  \
      2    3
     / \  / \
    4  5  6  7
After calling your function, the tree should look like:
         1 -> NULL
       /  \
      2 -> 3 -> NULL
     / \  / \
    4->5->6->7 -> NULL
```

# 用next指针直接层次遍历

https://leetcode.com/discuss/7327/a-simple-accepted-solution

```cpp
void connect(TreeLinkNode *root) {
    if (root == NULL) return;
    TreeLinkNode *pre = root;
    TreeLinkNode *cur = NULL;
    while(pre->left) {
        cur = pre;
        while(cur) {
            cur->left->next = cur->right;
            if(cur->next) cur->right->next = cur->next->left;
            cur = cur->next;
        }
        pre = pre->left;
    }
}
```

[1]: https://leetcode.com/problems/populating-next-right-pointers-in-each-node/