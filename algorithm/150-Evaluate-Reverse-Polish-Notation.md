题目链接: [150.Evaluate Reverse Polish Notation][1]
难度: Medium

描述：给出一个逆波兰式对其求值。

例子：
  ["2", "1", "+", "3", "*"] -> ((2 + 1) * 3) -> 9
  ["4", "13", "5", "/", "+"] -> (4 + (13 / 5)) -> 6

注意给出的数字可能为负数，例如["1", "-1", "+"] -> 0
  
# 迭代(16ms)
时间复杂度：O(N)
空间复杂度：O(N)

```cpp
class Solution {
public:
    int evalRPN(vector<string>& tokens) {
        stack<int> operands;
        
        for (const string &token : tokens) {
            if (token == "+" || token == "-" || token == "*" || token == "/") {
                const int r2 = operands.top(); operands.pop();
                const int r1 = operands.top(); operands.pop();
                
                switch(token[0]) {
                    case '+': operands.push(r1 + r2); break;
                    case '-': operands.push(r1 - r2); break;
                    case '*': operands.push(r1 * r2); break;
                    case '/': operands.push(r1 / r2); break;
                }
            } else {
                operands.push(std::stoi(token));
            }
        }
        return operands.top();
    }
};
```

# 递归(16ms)
时间复杂度：O(N)
空间复杂度：O(N)

```cpp
class Solution {
public:
    int evalRPN(vector<string>& tokens) {
        string s = tokens.back(); 
        tokens.pop_back();
        
        if (s== "*" || s=="/" || s=="+" || s == "-") {
        	// 注意临近的元素是r2，前面的是r1
            int r2 = evalRPN(tokens);
            int r1 = evalRPN(tokens);
            switch (s[0]) {
            case '*': return r1*r2;
            case '/': return r1/r2;
            case '+': return r1+r2;
            case '-': return r1-r2;
            }
        } else {
            return std::stoi(s);
        }
    }
};
```

[1]: https://leetcode.com/problems/evaluate-reverse-polish-notation/