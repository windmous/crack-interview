题目链接: [263.Ugly Number][1]
难度: Easy

描述：给定一个整数，判定其是否是一个丑数。所谓丑数就是其因子中只有2、3、5。

# 模拟(8ms)
```cpp
class Solution {
public:
    bool isUgly(int num) {
        if (num <= 0) return false;
        for (int factor : {2,3,5}) {
            while (num % factor == 0) {
                num /= factor;
            }
        }
        
        return num == 1;
    }
};
```

[1]: https://leetcode.com/problems/ugly-number/