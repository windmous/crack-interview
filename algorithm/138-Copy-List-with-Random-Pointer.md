题目链接: [138.Copy List with Random Pointer][1]
难度: Hard

描述：假设链表的除了next指针外，还有一个指针随机指向一个节点。请拷贝该链表。

# 法1(108ms)
时间复杂度：O(N)
空间复杂度：O(1)

本方法分三轮：
1. 创建每个节点的副本，并放在节点后面，如ABC，复制后为AaBbCc
2. 修改副本的random指针
3. 将副本链表与原始链表剥离

```cpp
class Solution {
public:
    RandomListNode *copyRandomList(RandomListNode *head) {
        RandomListNode *newHead, *l1, *l2;
        if (head == NULL) return NULL;
        for (l1 = head; l1 != NULL; l1 = l1->next->next) {
            l2 = new RandomListNode(l1->label);
            l2->next = l1->next;
            l1->next = l2;
        }
    
        newHead = head->next;
        for (l1 = head; l1 != NULL; l1 = l1->next->next) {
            if (l1->random != NULL) 
                l1->next->random = l1->random->next;
        }
    
        for (l1 = head; l1 != NULL; l1 = l1->next) {
            l2 = l1->next;
            l1->next = l2->next;
            if (l2->next != NULL) 
                l2->next = l2->next->next;
        }
    
        return newHead;
    }
};
```

# 方法2(108ms)
时间复杂度：O(N)
空间复杂度：O(1)

跟方法1大致类似，不过是将副本挂在原始节点的random上，然后将副本的next指向原始的random。
详细注释参考[这里][2]

```cpp
class Solution {
public:
    RandomListNode *copyRandomList(RandomListNode *head) {
        RandomListNode *newHead, *l1, *l2;
        if (head == NULL) return NULL;
    
        for (l1 = head; l1 != NULL; l1 = l1->next) {
            l2 = new RandomListNode(l1->label);
            l2->next = l1->random;
            l1->random = l2;
        }
    
        newHead = head->random;
        for (l1 = head; l1 != NULL; l1 = l1->next) {
            l2 = l1->random;
            l2->random = l2->next ? l2->next->random : NULL;
        }
    
        for (l1 = head; l1 != NULL; l1 = l1->next) {
            l2 = l1->random;
            l1->random = l2->next;
            l2->next = l1->next ? l1->next->random : NULL;
        }
    
        return newHead;
    }
};
```


[1]: https://leetcode.com/problems/copy-list-with-random-pointer/
[2]: https://leetcode.com/discuss/18049/algorithms-without-extra-array-table-algorithms-explained