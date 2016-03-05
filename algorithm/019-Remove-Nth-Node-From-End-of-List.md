题目链接: [19.Remove Nth Node From End of List][1]
难度: Easy

- 删除链表从后往前数第n个数，保证存在这个数
- 特殊情况：删除头结点

```cpp
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode *h1 = head, *h2 = head;
        for (int i = 0; i < n; ++i)
            h2 = h2->next;
        
        if (h2 == NULL) { // delete the head
            head = h1->next;
            delete h1;
            return head;
        } else {
            h2 = h2->next;
        }
        
        while (h2 != NULL) {
            h1 = h1->next;
            h2 = h2->next;
        }
        
        ListNode *toDel = h1->next; // 删除h1.next指向的那个node
        h1->next = h1->next->next;
        delete toDel;
        return head;
    }
};
```

[1]: https://leetcode.com/problems/remove-nth-node-from-end-of-list/