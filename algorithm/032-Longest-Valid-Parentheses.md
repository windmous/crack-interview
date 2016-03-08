题目链接: [32.Longest Valid Parentheses][1]
难度: Hard

- 求给定由'('和')'组成的字符串中合法括号的最长长度

# 栈 12ms

栈内存储非法的‘）’的下标

```cpp
class Solution {
public:
    int longestValidParentheses(string s) {
        int n = s.length(), longest = 0;
        stack<int> st;
        for (int i = 0; i < n; ++i) {
            if (s[i] == '(') st.push(i);  
            else {
                if (!st.empty()) { 
                    if (s[st.top()] == '(') st.pop();  
                    else st.push(i);   // 这是一个非法的)，将其下标存入stack
                }
                else st.push(i);
            }
        }
        
        if (st.empty()) longest = n;
        else {
            int a = n, b = 0;
            while (!st.empty()) {
                b = st.top(); st.pop();
                longest = max(longest, a - b - 1);
                a = b;
            }
            longest = max(longest, a);
        }
        return longest;
    }
};
```

# 栈 16ms



[1]: https://leetcode.com/problems/longest-valid-parentheses/