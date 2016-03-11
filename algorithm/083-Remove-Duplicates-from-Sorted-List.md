题目链接: [83.Remove Duplicates from Sorted List][1]
难度: Easy

- 将有序链表中的重复元素删除（重复元素只保留一个）

以下解特意不使用delete 指针：
Note about freeing memory. We need to free memory when we delete a node. But don't use delete node; construct on an interview without discussing it with the interviewer. A list node can be allocated in many different ways and we can use delete node; only if we are sure that the nodes were allocated with new TreeNode(...);.

# 递归
```cpp
class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        if (head == NULL || head->next == NULL) return head;
        head->next = deleteDuplicates(head->next);
        return (head->val == head->next->val) ? head->next : head;
    }
};
```

# 迭代

```cpp
class Solution {
public:
    ListNode *deleteDuplicates(ListNode *head) {
        ListNode* cur = head;
        while (cur) {
            while (cur->next && cur->val == cur->next->val)
                cur->next = cur->next->next;
            cur = cur->next;
        }
        return head;
    }
};
```


[1]: https://leetcode.com/problems/remove-duplicates-from-sorted-list/