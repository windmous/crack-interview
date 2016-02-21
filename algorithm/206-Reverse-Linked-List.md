题目链接：[206. Reverse Linked List][1]

所有方法时间复杂度均为O(n)

# 迭代法(8ms)

```cpp
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        ListNode *pre = NULL, *next;
        while (head) {
            next = head->next;
            head->next = pre;
            pre = head;
            head = next;
        }
        return pre;
    }
};
```

# 递归法(8ms)
```cpp
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
         if (!head || !head->next) {
            return head;
        }
        
        ListNode* new_head = reverseList(head->next);
        head->next->next = head;
        head->next = NULL;
        return new_head;
    }
};
```

[1]: https://leetcode.com/problems/reverse-linked-list/