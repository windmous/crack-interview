题目链接: [142.Linked List Cycle II][1]
难度: Medium

描述：给一个链表，检测器是否有环，若有环则返回环的起点

# Floyd’s cycle finding algorithm
时间复杂度：O(N)
空间复杂度：O(1)

证明参考[这里][2]。

```cpp
class Solution {
public:
    ListNode *detectCycle(ListNode *head) {
        if (head == NULL || head->next == NULL)
            return NULL;
    
        ListNode *slow = head, *fast = head;
    
        while (fast->next && fast->next->next) {
            slow = slow->next;
            fast = fast->next->next;
            if (slow == fast) {                      // there is a cycle
            	ListNode *entry = head;
                while(slow != entry) {               // found the entry location
                    slow  = slow->next;
                    entry = entry->next;
                }
                return entry;
            }
        }
        return nullptr;                                 // there has no cycle
    }
};
```

[1]: https://leetcode.com/problems/linked-list-cycle-ii/
[2]: https://leetcode.com/discuss/16567/concise-solution-using-with-detailed-alogrithm-description