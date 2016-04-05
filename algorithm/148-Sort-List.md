题目链接: [148.Sort List][1]
难度: Medium

# Merge Sort(60ms)
时间复杂度：O(NlogN)
空间复杂度：O(logN)



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
    ListNode* sortList(ListNode* head) {
        if (!head || !head->next) return head;
        ListNode *slow, *fast;
        slow = fast = head;
        while (fast->next && fast->next->next) {
            slow = slow->next;
            fast = fast->next->next;
        }
        
        ListNode *headB = slow->next;
        slow->next = NULL;
        return mergeTwo(sortList(head), sortList(headB));
    }
    
    ListNode *mergeTwo(ListNode *h1, ListNode *h2) {
        ListNode dummy(-1);
        ListNode *pre = &dummy;
        
        while (h1 && h2) {
            if (h1->val <= h2->val)  {
                pre->next = h1;
                h1 = h1->next;
            } else {
                pre->next = h2;
                h2 = h2->next;
            }
            
            pre = pre->next;
        }
        
        pre->next = h1 ? h1 : h2;
        return dummy.next;
    }
};
```
# 迭代解法 Bottom-up
比较复杂，参考[这里][2]

# 快速排序(56ms)
时间复杂度：O(NlogN)(最坏)
空间复杂度：O(logN)

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
    void sort_helper(ListNode *head, ListNode *tail) {
        if (head->next == tail) 
            return ;
            
        ListNode *pre = head, *pivot = head->next, *cur = head->next;
        while (cur->next != tail) {
            if (cur->next->val < pivot->val) {
                ListNode *temp = cur->next;
                cur->next = temp->next;
                temp->next = pre->next;
                pre->next = temp;
            } else {
                cur = cur->next;
            }
        }
        sort_helper(head, pivot);
        while (pivot->next != tail && pivot->next->val == pivot->val) {
            pivot = pivot->next;
        }
        sort_helper(pivot, tail);
    }
    ListNode* sortList(ListNode* head) {
        ListNode dummy(-1);
        dummy.next = head;
        ListNode *new_head = &dummy;
        sort_helper(new_head, nullptr);
        return dummy.next;
    }
};
```

[1]: https://leetcode.com/problems/sort-list/
[2]: https://leetcode.com/discuss/28594/bottom-recurring-with-space-complextity-time-complextity
[3]: https://leetcode.com/discuss/37816/56ms-c-solutions-using-quicksort-with-explanations