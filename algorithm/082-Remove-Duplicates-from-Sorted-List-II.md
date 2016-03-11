题目链接: [82.Remove Duplicates from Sorted List II][1]
难度: Medium

- 将有序链表中的出现次数超过1次的元素都删除


https://leetcode.com/discuss/12724/my-accepted-java-code
```cpp
class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        if (head == NULL || head->next == NULL) return head;
        ListNode dummy(0);
        dummy.next = head;
        ListNode *pre = &dummy, *cur = head;
        while (cur) {
            while (cur->next != NULL && cur->val == cur->next->val) 
                cur = cur->next;
            if (pre->next == cur) // 此处巧妙，判断cur是否移动过来判重
                pre = pre->next;
            else 
                pre->next = cur->next;
            cur = cur->next;
        }
        return dummy.next;
    }
};
```

[1]: https://leetcode.com/problems/remove-duplicates-from-sorted-list-ii/