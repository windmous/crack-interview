题目链接: [147.Insertion Sort List][1]
难度: Medium

描述：对链表排序，要求使用插入排序

据一位Google的面试官透露：
> For God's sake, don't try sorting a linked list during the interview

# 插入排序
时间复杂度：O(N^2)
空间复杂度：O(1)

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
    ListNode* insertionSortList(ListNode* head) {
        if (!head || !head->next) return head;
        ListNode dummy(INT_MIN);
        for (ListNode *p = head; p; ) {
            ListNode *pos = findLocation(&dummy, p->val);
            ListNode *tmp = p->next;
            p->next = pos->next;
            pos->next = p;
            p = tmp;
        }
        
        return dummy.next;
    }
    
    ListNode* findLocation(ListNode *head, int val) {
        ListNode *pre = NULL;
        for (ListNode *cur = head; cur && cur->val <= val; 
                pre = cur, cur = cur->next)
        ;
        
        return pre;
    }
};
```

[1]: https://leetcode.com/problems/insertion-sort-list/