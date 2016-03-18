题目链接: [109.Convert Sorted List to Binary Search Tree][1]
难度: Medium

- 给定一个有序链表，生成"height balanced"二叉查找树

# 自底向上建树

https://leetcode.com/discuss/10924/share-my-code-with-o-n-time-and-o-1-space

非常机智的一个想法，本质是中序遍历，在递归的过程中移动了list指针，使其正好匹配递归时刻的根节点位置。时间复杂度确实是O(n)，但是空间复杂度应该是栈空间对应的O(log n)，作者分析错了。

另一个角度想，可以先建好二叉树的结构，然后再中序遍历此树，遍历的过程中将值填入树中。作者只不过是将这两个过程合并一块完成。

soul machine中也有此方法。

```cpp
class Solution {
public:
    ListNode *list;
    int count(ListNode *node){
        int size = 0;
        while (node) {
            ++size;
            node = node->next;
        }
        return size;
    }

    TreeNode *generate(int n){
        if (n == 0)
            return NULL;
        TreeNode *node = new TreeNode(0); // 暂时赋值为0
        node->left = generate(n / 2);
        node->val = list->val;			  // 此处再修改值
        list = list->next; 	
        node->right = generate(n - n / 2 - 1);
        return node;
    }

    TreeNode *sortedListToBST(ListNode *head) {
        this->list = head;
        return generate(count(head));
    }
};
```

# 自顶向下建树

需要找当前的根在哪，时间复杂度是O(N^2)，详见soul machine。

[1]: https://leetcode.com/problems/convert-sorted-list-to-binary-search-tree/