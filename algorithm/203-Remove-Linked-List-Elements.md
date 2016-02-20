题目链接：[203. Remove Linked List Elements][1]

所有方法时空复杂度均为O(n)。所有方法均没有执行delete语句，届时请注意。

# 迭代, 双指针，fake head(36ms)

```cpp
class Solution {
public:
    ListNode* removeElements(ListNode* head, int val) {
        ListNode dummy(-1);
        ListNode *pre = &dummy, *cur = head;
        while (cur) {
            if (cur->val != val) {
                pre->next = cur;
                pre = cur;
            }
            
            cur = cur->next;
        }
        
        pre->next = NULL;
        return dummy.next;
    }
};
```

# 迭代，单指针，无fake head(32ms)
```cpp
class Solution {
public:
    ListNode* removeElements(ListNode* head, int val) {
        if (!head) return NULL;
        
        ListNode *cur = head;
        while (cur->next) {
            if (cur->next->val == val) {
                cur->next = cur->next->next;
            } else {
                cur = cur->next;
            }
        }
        return (head->val == val) ? head->next : head;
    }
};
```

# 迭代，单个指针的指针(36ms)
```cpp
class Solution {
public:
    ListNode* removeElements(ListNode* head, int val) {
        ListNode **cur = &head;
        while (*cur) {
            if ((*cur)->val == val) {
                // 修改的是head或者前一个node的next指针
                *cur = (*cur)->next;
            } else {
                cur = &((*cur)->next);
            }
        }
        return head;
    }
};
```

# 递归(36ms)

```cpp
class Solution {
public:
    ListNode* removeElements(ListNode* head, int val) {
       if (!head) return NULL;
       head->next = removeElements(head->next, val);
       return head->val == val? head->next : head;
    }
};
```





[1]: https://leetcode.com/problems/remove-linked-list-elements/
