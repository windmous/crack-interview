题目链接: [227.Basic Calculator II][1]
难度: Medium

# 迭代1(20ms)
时间复杂度：O(N)
```cpp
class Solution {
public:
    int calculate(string s) {
        istringstream is("+" + s + "+");
        int ans = 0, term = 0, tmp;
        char op;
        
        while (is >> op) {
            if (op == '+' || op == '-') {
                ans += term;
                is >> term;
                term *= (op == '+') ? 1 : -1;
            } else {
                is >> tmp;
                if ('*' == op) term *= tmp;
                else if ('/' == op) term /= tmp;
            }
        }
        return ans;
    }
};
```

# 栈方法(32ms)
时间复杂度：O(N)
好处是容易扩充到有括号的情况
```cpp
class Solution {
public:
    int calculate(string s) {
        istringstream is("^" + s + "$");
        stack<int> s_terms;
        stack<char> s_ops;
        int term = 0, tmp;
        char op;
        
        // 运算符总是先于term被push到栈中的
        while (is >> op) {
            switch (op) {
                case '^':
                    s_ops.push('+');
                    is >> term;
                    break;
                case '+':
                case '-':
                    s_terms.push(term);
                    s_ops.push(op);
                    is >> term;
                    break;
                case '*':
                case '/':
                    is >> tmp;
                    term = (op == '*') ? (term * tmp) : (term / tmp);
                    break;
                case '$':
                    s_terms.push(term);
                    break;
            }
        }
        
        int ans = 0;
        while (!s_ops.empty()) {
            ans += s_terms.top() * (s_ops.top() == '+' ? 1 : -1);
            s_terms.pop();
            s_ops.pop();
        }
        
        return ans;
    }
};
```

[1]: https://leetcode.com/problems/basic-calculator-ii/