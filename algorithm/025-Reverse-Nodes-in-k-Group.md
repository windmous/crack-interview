题目链接: [25.Reverse Nodes in k-Group][1]
难度: Hard

- 将链表以k个一组进行反转
For example,
Given this linked list: 1->2->3->4->5

For k = 2, you should return: 2->1->4->3->5

For k = 3, you should return: 3->2->1->4->5

# 递归 26ms

利用递归先将第k+1个元素之后的都反转好，再考虑当前的1~k个元素。

```cpp
class Solution {
public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        ListNode* curr = head;
        int count = 0;
        while (curr != NULL && count != k) { // 找第k+1个元素
            curr = curr->next;
            ++count;
        }
        
        if (count == k) { // if k+1 node is found
            curr = reverseKGroup(curr, k); // reverse list with k+1 node as head
            // head - head-pointer to direct part, 指向待翻转区域的头
            // curr - head-pointer to reversed part 指向已翻转完毕区域的头
            while (count-- > 0) {
                ListNode* tmp = head->next; // tmp - next head in direct part
                head->next = curr;  // preappending "direct" head to the reversed list 
                curr = head;  // move head of reversed part to a new node
                head = tmp;   // move "direct" head to the next node in direct part
            }
            head = curr;
        }
        return head;
    }
};
```

# 非递归 24ms

- 用一个指针指向当前k个元素组之前的那个元素

```cpp
class Solution {
public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        if (head == NULL || k == 1) return head;
        
        int num = 0;
        ListNode dummy(-1);
        dummy.next = head;
        ListNode *pre = &dummy, *cur = &dummy, *nex;
        
        while (cur = cur->next)  // 统计共有多少个node
            ++num;
            
        while (num >= k) {
            cur = pre->next;
            nex = cur->next;
			// 这个for循环的目的是将nex加入“已逆序好的队列”头部
            for (int i = 1; i < k; ++i) { // 开始：pre - [已逆序好的队列 cur(队尾)]  - nex 
                cur->next = nex->next;
                nex->next = pre->next;
                pre->next = nex;
                nex = cur->next;          // 结束： pre - [旧nex（队头） 已逆序好的队列 cur(队尾)]  - 新nex 
            }
            pre = cur;
            num -= k;
        }
        return dummy.next;
    }
};
```

# 非递归（26ms）
- 用一个指针指向当前k个元素组之前的那个元素

```cpp
class Solution {
public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        if (head == nullptr || k <= 1) return head;
        ListNode dummy(-1);
        ListNode *cur = head, *tail = &dummy;
        int len = 0;
        for (ListNode *p = head; p != nullptr; p = p->next, ++ len);
        
        while (len >= k) {
            ListNode *next_tail = cur;
            for (int i = 0; i < k; ++ i) {
                ListNode *temp = cur->next;
                cur->next = tail->next;
                tail->next = cur;
                cur = temp;
            }
            tail = next_tail;
            len -= k;
        }
        tail->next = cur;
        return dummy.next;
    }
};
```

[1]: https://leetcode.com/problems/reverse-nodes-in-k-group/