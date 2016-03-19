题目链接: [141.Linked List Cycle][1]
难度: Medium

描述：检测链表中是否有环

# Floyd’s cycle finding algorithm(16ms)
时间复杂度：O(N)
空间复杂度：O(1)

```cpp
class Solution {
public:
    bool hasCycle(ListNode *head) {
        ListNode *slow = head, *fast = head;
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
            if (slow == fast) return true;
        }
        
        return false;
    }
};
```

# 反转链表法(12ms)
时间复杂度：O(N)
空间复杂度：O(1)

我们可以将链表reverse，如果一个链表中有环，那么逆序完成，新的逆序链表的head节点跟源链表的head节点是相同的。

本方法的缺陷是会修改原始链表

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
    bool hasCycle(ListNode *head) {
        ListNode *rlist_head = reverse_list(head);
        // 如果只有一个元素，rlist_head == head时
        // 1. 空链表，无环
        // 2. 只有一个元素的链表：必须要改元素next指向自己时才判有环，否则判无环
        // 3. >=2个元素：直接判有环
        // 下面的head->next用来处理第2、3个条件
        if (head && head->next && rlist_head == head) {
            return true;
        }
        return false;
    }
    
    ListNode *reverse_list(ListNode *head) {
        ListNode *pre = nullptr, *cur = head;
        while (cur) {
            ListNode *tmp = cur->next;
            cur->next = pre;
            pre = cur;
            cur = tmp;
        }
        
        return pre;
    }
};
```

[1]: https://leetcode.com/problems/linked-list-cycle/