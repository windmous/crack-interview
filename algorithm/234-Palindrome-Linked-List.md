题目链接: [234.Palindrome Linked List][1]
难度: Easy

描述：给定一个链表，判断这个链表所有的元素能不能构成回文串。

# 反转矩阵法
首先使用快慢指针法找到链表中点，将后半段链表反转，然后与前半段链表对比即可。

```cpp
class Solution {
public:
    bool isPalindrome(ListNode* head) {
        if(head==NULL||head->next==NULL)
            return true;

        // 使用快慢指针法寻找中点
        ListNode* slow=head;
        ListNode* fast=head;
        while(fast->next!=NULL&&fast->next->next!=NULL){
            slow=slow->next;
            fast=fast->next->next;
        }
        // 反转后半段指针
        slow->next=reverseList(slow->next);
        slow=slow->next;

        // 一定要用slow作为终止判定！后半段链表可能比前半段链表少一个元素
        while(slow!=NULL){
            if(head->val!=slow->val)
                return false;
            head=head->next;
            slow=slow->next;
        }
        return true;
    }
    ListNode* reverseList(ListNode* head) {
        ListNode* pre=NULL;
        ListNode* next=NULL;
        while(head!=NULL){
            next=head->next;
            head->next=pre;
            pre=head;
            head=next;
        }
        return pre;
    }
};
```


[1]: https://leetcode.com/problems/palindrome-linked-list/