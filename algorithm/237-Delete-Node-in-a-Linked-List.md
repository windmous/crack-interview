题目链接: [237.Delete Node in a Linked List][1]
难度: Easy

编写一个函数，函数参数为Node*，即一个链表的头节点地址，请删除该节点。
注意，该函数参数所指向的链表可能只是个子链表，其前方还有其它结点的。

# 法1(17ms)
时间复杂度：O(1)
空间复杂度：O(1)

1. 别忘了检查输入是否为空
2. 别忘了delete释放空间

```cpp
class Solution {
public:
    void deleteNode(ListNode* node) {
        if (!node || !node->next) return ;
        auto next = node->next;
        *node = *next;
        delete next;
    }
};
```

[1]: https://leetcode.com/problems/delete-node-in-a-linked-list/