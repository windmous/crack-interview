题目链接: [50.Pow(x, n)][1]
难度: Medium

- 二分法，x^n = x^(n/2) * x^(n/2) * x^(n%2)
- 注意n可能为负数，灵魂机器没考虑n=INT_MIN的情况

```cpp
class Solution {
public:
    double myPow(double x, int n) {
        if (n == 0) return 1;
        double v = myPow(x, n/2);
        if      (n % 2 == 0) return v * v;
        else if (n % 2 == 1) return v * v * x;
        else                 return v * v / x; // 此时n % 2 == -1
    }
};
```

[1]: https://leetcode.com/problems/powx-n/