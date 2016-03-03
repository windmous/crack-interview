题目链接: [224.Basic Calculator][1]
难度: Medium

# 栈方法(19ms)
```cpp
class Solution {
public:
    int calculate(string s) {
        stack<int> s_nums, s_signs;
        int num = 0, sign = 1;
        int result = 0;
        
        for (char c : s) {
            if (isdigit(c)) {
                num = num * 10 + c - '0';
            } else if (!isspace(c)){
                result += num * sign;
                num = 0;
                
                if (c == '+') sign = 1;
                else if (c == '-') sign = -1;
                else if (c == '(') {
                    s_nums.push(result);
                    s_signs.push(sign);
                    
                    result = 0;
                    sign = 1;
                } else if (c == ')') {
                    result = s_nums.top() + result * s_signs.top();
                    s_nums.pop();
                    s_signs.pop();
                }
            }
        }
        
        if (num) result += sign * num;
        return result;
    }
};
```

[1]: https://leetcode.com/problems/basic-calculator/