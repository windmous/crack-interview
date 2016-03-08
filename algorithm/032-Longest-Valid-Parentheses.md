题目链接: [32.Longest Valid Parentheses][1]
难度: Hard

- 求给定由'('和')'组成的字符串中合法括号的最长长度

# 栈 12ms

栈内存储非法的‘）’和候选的‘（’的下标，候选的‘（’可能是合法的

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

# 栈 8ms 

原理和上面一样，这个方法动态维护maxL，因此代码量减少了不少

```cpp
class Solution {
public:
    int longestValidParentheses(string s) {
        stack<int> stk;
        stk.push(-1);
        int maxL=0;
        for(int i=0;i<s.size();i++)
        {
            int t=stk.top();
            if(t!=-1&&s[i]==')'&&s[t]=='(')
            {
                stk.pop();
                maxL=max(maxL,i-stk.top());
            }
            else // t == -1(栈空)，或者 s[i] == '('，或者s[t] == ')'
                stk.push(i);
        }
        return maxL;
    }
};
```

# 栈 16ms

原理：(()()) -> (2()) -> (22) -> 6

```cpp
class Solution {
public:
    int longestValidParentheses(string s) {
        stack<int> st;
        for (int i = 0; i < s.length(); ++i) {
            if (s[i] == '(') st.push(-1);
            else {
                int accum = 0, leftParen = 0;
                while (!st.empty() && st.top() > 0) {
                    accum += st.top();
                    st.pop();
                }
                if (!st.empty()) {
                    if (st.top() == -1) {
                        st.pop();
                        st.push(accum + 2);
                    } else {
                        st.push(accum);
                        st.push(-2);
                    }
                } else {
                    st.push(accum);
                    st.push(-2);
                }
            }
        }
        
        int longest = 0;
        while (!st.empty()) {
            int accum = 0;
            while (!st.empty() && st.top() > 0) {
                accum += st.top();
                st.pop();
            }
            
            longest = max(longest, accum);
            if (!st.empty()) st.pop();
        }
        return longest;
    }
};
```

# DP 8ms

构造数组longest[]，其中longest[i]存的是以i为结尾的最长有效括号字符串，注意s[i]也包括在这个有效字符串中。

If s[i] is '(', set longest[i] to 0,because any string end with '(' cannot be a valid one. 
Else if s[i] is ')' 
     If s[i-1] is '(', longest[i] = longest[i-2] + 2 
     Else if s[i-1] is ')' and s[i-longest[i-1]-1] == '(', longest[i] = longest[i-1] + 2 + longest[i-longest[i-1]-2] 
For example, input "()(())", at i = 5, longest array is [0,2,0,0,2,0], longest[5] = longest[4] + 2 + longest[1] = 6. 


```cpp
int longestValidParentheses(string s) {
	if(s.length() <= 1) return 0;
	int curMax = 0;
	vector<int> longest(s.size(),0);
	for(int i=1; i < s.length(); i++){
		if(s[i] == ')'){
			if(s[i-1] == '('){
				longest[i] = (i-2) >= 0 ? (longest[i-2] + 2) : 2;
				curMax = max(longest[i],curMax);
			}
			else{ // if s[i-1] == ')', combine the previous length.
				if(i-longest[i-1]-1 >= 0 && s[i-longest[i-1]-1] == '('){
					longest[i] = longest[i-1] + 2 + ((i-longest[i-1]-2 >= 0)?longest[i-longest[i-1]-2]:0);
					curMax = max(longest[i],curMax);
				}
			}
		}
		//else if s[i] == '(', skip it, because longest[i] must be 0
	}
	return curMax;
}
```

[1]: https://leetcode.com/problems/longest-valid-parentheses/