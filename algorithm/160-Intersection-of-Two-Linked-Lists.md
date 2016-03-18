题目链接: [160.Intersection of Two Linked Lists][1]
难度: Easy

给定两个链表，若它们相交则返回交点，否则返回null。

# 循环法(56ms)
时间复杂度：O(N)
空间复杂度：O(1)

```cpp
class Solution {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        ListNode *ptr1 = headA, *ptr2 = headB;
        //不相交时，最终ptr1和ptr2都为nullptr。相交时指向交点。
        while (ptr1 != ptr2) { 
            ptr1 = ptr1 ? ptr1->next : headB;
            ptr2 = ptr2 ? ptr2->next : headA;
        }
        
        return ptr1;
    }
};
```

设链表A比较短，那么ptr1到底重新指向B时，落后ptr2 len(A)位。ptr2达到链尾时，ptr1向前前进了len(B)-len(A)位，所以ptr2重新指向链表A时，一起前进即可到达相交位（相交），或者一起到达链表尾（不相交）


[1]: https://leetcode.com/problems/intersection-of-two-linked-lists/