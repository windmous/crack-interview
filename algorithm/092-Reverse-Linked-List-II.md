题目链接: [92.Reverse Linked List II][1]
难度: Medium

将链表中从第m个元素到第n个元素逆转，其余不变。保证1 ≤ m ≤ n ≤ length of list.

For example:

Given 1->2->3->4->5->NULL, m = 2 and n = 4,

return 1->4->3->2->5->NULL.


初始化结果：
```
                     mth            nth
					  v              v
[head -> ... -> pre][cur -> mov -> nth][后续元素]
```

```cpp
class Solution {  
public:
    ListNode* reverseBetween(ListNode* head, int m, int n) {
        ListNode* new_head = new ListNode(0);
        new_head -> next = head;
        ListNode* pre = new_head;
        for (int i = 0; i < m - 1; i++)
            pre = pre -> next;
        ListNode* cur = pre -> next;
        for (int i = 0; i < n - m; i++) { // 每一次进入for循环，都将cur之后的一元丢到已经反转链表的头部
            ListNode* move = cur -> next; 
            cur -> next = move -> next;
            move -> next = pre -> next;
            pre -> next = move;
        }
        return new_head -> next;
    }
}; 
```


[1]: https://leetcode.com/problems/reverse-linked-list-ii/