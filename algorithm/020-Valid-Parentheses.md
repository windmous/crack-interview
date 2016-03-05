题目链接: [20.Valid Parentheses][1]
难度: Easy

- 判断是否为合法的括号串

0ms

```cpp
class Solution {
public:
    bool isValid(string s) {
        stack<char> paren;
        for (auto& c : s) {
            switch (c) {
                case '(': 
                case '{': 
                case '[': paren.push(c); break;
                case ')': if (paren.empty() || paren.top()!='(') return false; else paren.pop(); break;
                case '}': if (paren.empty() || paren.top()!='{') return false; else paren.pop(); break;
                case ']': if (paren.empty() || paren.top()!='[') return false; else paren.pop(); break;
                default: ; // pass
            }
        }
        return paren.empty() ;
    }
};
```

[1]: https://leetcode.com/problems/valid-parentheses/