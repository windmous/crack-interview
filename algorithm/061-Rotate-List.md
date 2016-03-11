题目链接: [61.Rotate List][1]
难度: Medium

- 先遍历一遍，得出链表长度len，注意k可能大于len，因此令k %=  len。将尾节点next指针指向首节点，形成一个环，接着往后跑len-k步，从这里断开，就是要求的结果了。

```cpp
class Solution {
public:
    ListNode *rotateRight(ListNode *head, int k) {
        if (head == nullptr || k == 0) return head;

        int len = 1;
        ListNode* p = head;
        while (p->next) { // 求长度
            len++;
            p = p->next;
        }
        k = len - k % len;

        p->next = head; // 首尾相连
        for(int step = 0; step < k; step++) {
            p = p->next;  //接着往后跑
        }
        head = p->next; // 新的首节点
        p->next = nullptr; // 断开环
        return head;
    }
};
```

[1]: https://leetcode.com/problems/rotate-list/