题目链接：[2. Add Two Numbers][1]
# 迭代法
时间复杂度：O(n)

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
    ListNode *addTwoNumbers(ListNode *l1, ListNode *l2) {
        ListNode dummy(-1), *prev = &dummy;
        int sum = 0;
        
        while (l1 || l2 || sum) {
            if (l1) {
                sum += l1->val;
                l1 = l1->next;
            }
            
            if (l2) {
                sum += l2->val;
                l2 = l2->next;
            }
            
            // 无需额外条件判断
            prev->next = new ListNode(sum % 10);
            sum /= 10;
            prev = prev->next;
        }
        
        return dummy.next;
    }
};
```

# 递归法
平均时间复杂度：O(n)，最坏是O(n^2)

下面的解有几个问题，所以不建议使用：

1. 长链表容易爆栈。
2. 如果l1和l2两个链表不等长，那么下述代码会修改输入链表的内容。
3. 存在内存泄露。当(a>=10)成立时，直接修改了p->next而未做内存释放。
4. 当进位特别多，比如9999+9999时，时间复杂度为(n^2)

```cpp
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        if (l1 == NULL and l2 == NULL) return NULL;
        else if (l1 == NULL) return l2; 
        else if (l2 == NULL) return l1; 

        int a = l1->val + l2->val;
        ListNode *p = new ListNode(a % 10);
        p->next = addTwoNumbers(l1->next,l2->next);
        if (a >= 10) p->next = addTwoNumbers(p->next, new ListNode(1));
        return p;
    }
};
```


[1]: https://leetcode.com/problems/add-two-numbers/