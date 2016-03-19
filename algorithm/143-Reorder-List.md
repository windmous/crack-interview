题目链接: [143.Reorder List][1]
难度: Medium

Given a singly linked list L: L0→L1→…→Ln-1→Ln,
reorder it to: L0→Ln→L1→Ln-1→L2→Ln-2→…

# 模拟法(68ms)
分为三个步骤：
1. 将链表分成前后两个半段，前半段至多比后半段多1个元素。
2. 将后半段逆序
3. 连接链表

```cpp
class Solution {
public:
    void reorderList(ListNode *head) {
        if (!head || !head->next) return ;
        // 第1步：切割链表
        ListNode *slow = head, *fast = head->next;
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
        }

        // 第2步：逆序后半段
        ListNode *head2 = reverse(slow->next);
        slow->next = NULL;
        
        // 第3步：连接链表。每轮迭代仅链接一个元素
        for (auto p1 = head, p2 = head2; p1; ) {
            auto t = p1->next;
            p1 = p1->next = p2;
            p2 = t;
        }
    }
    
    ListNode* reverse(ListNode* head) {
        ListNode *pre = NULL, *cur = head;
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

# 递归解(64ms)
时间复杂度：O(N)
空间复杂度：O(N)

```cpp
class Solution {
public:
    bool reorderList(ListNode *&head, ListNode *tail)
    {
        if (!head) return false;

        if (!tail->next) {
            if (head==tail || head->next==tail) return false;
            ListNode *thead = head->next;
            head->next=tail;
            head=thead;
            return true;
        }

        // 前半段从该函数处返回false
        if (!reorderList(head,tail->next)) return false;

        if (head == tail || head->next == tail) {
            tail->next->next=head;
            tail->next=NULL;
            return false;
        }

        ListNode *thead = head->next;
        head->next=tail;
        tail->next->next=head;
        head=thead;

        return true;
    }

    void reorderList(ListNode *head) {
        reorderList(head,head);
    }
};
```

[1]: https://leetcode.com/problems/reorder-list/