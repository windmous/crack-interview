题目链接: [86.Partition List][1]
难度: Medium

- 将一个链表按照给定元素的值进行partition，小于该值的元素在链表头，大于等于的在链表尾，相对顺序不变
For example,
Given 1->4->3->2->5->2 and x = 3,
return 1->2->2->4->3->5.


# 分为两个链表
https://leetcode.com/discuss/21032/very-concise-one-pass-solution

The fundamental principles are to separate the list into 2 distinct lists and link them afterwards.
```cpp
class Solution {
public:
    ListNode* partition(ListNode* head, int x) {
        ListNode left_dummy(-1); // 头结点
        ListNode right_dummy(-1); // 头结点

        auto left_cur = &left_dummy;
        auto right_cur = &right_dummy;

        for (ListNode *cur = head; cur; cur = cur->next) {
            if (cur->val < x) {
                left_cur->next = cur;
                left_cur = cur;
            } else {
                right_cur->next = cur;
                right_cur = cur;
            }
        }

        left_cur->next = right_dummy.next;
        right_cur->next = nullptr;

        return left_dummy.next;
    }
};
```

[1]: https://leetcode.com/problems/partition-list/