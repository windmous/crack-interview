题目链接: [233.Number of Digit One][1]
难度: Medium

# 迭代(0ms)
```cpp
class Solution {
public:
    int countDigitOne(int n) {
        int num = 0, base = 1, unit = 0;
        int ans = 0, digit;
        while (n) {
            digit = n % 10;
            n /= 10;
            
            if (digit >= 1) {
                ans += digit * unit;
                if (digit == 1) {
                    ans += num + 1;
                } else {
                    ans += base;
                }
            }
            
            unit = unit * 10 + base;
            num += digit * base;
            base *= 10;
        }
        return ans;
    }
};
```

[1]: https://leetcode.com/problems/number-of-digit-one/