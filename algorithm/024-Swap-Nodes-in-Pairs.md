题目链接: [24.Swap Nodes in Pairs][1]
难度: Medium

- 两两对调对链表中的元素

# 容易调试的4指针方案 4ms

```cpp
class Solution {
public:
    ListNode *swapPairs(ListNode *head) {
        ListNode pseudoHead(-1);
        pseudoHead.next = head;
        ListNode *p1 = &pseudoHead, *p2=NULL, *p3=NULL, *p4=NULL;
        while (p1 != NULL && p1->next != NULL && p1->next->next != NULL){
            p2 = p1->next;
            p3 = p2->next;
            p4 = p3->next;
            
            p1->next = p3;
            p3->next = p2;
            p2->next = p4;
            p1 = p2;
        }
        return pseudoHead.next;
    }
};
```

# 容易出错的炫技版“指向指针的指针”的方案 4ms

```cpp
ListNode* swapPairs(ListNode* head) {
    ListNode **pp = &head, *a, *b;
    while ((a = *pp) && (b = a->next)) {
        a->next = b->next;
        b->next = a;
        *pp = b;      // *pp 初始化是head，随后是前继元素的next指针，这样做就不用存储pre节点的指针了
        pp = &(a->next);
    }
    return head;
}
```

[1]: https://leetcode.com/problems/swap-nodes-in-pairs/