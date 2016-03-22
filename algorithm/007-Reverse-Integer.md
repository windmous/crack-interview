题目链接: [7.Reverse Integer][1]
难度: Easy

- 返回整数各位数字逆序结果，如果溢出返回0
- 考点是如何判断溢出，但讨论区多数答案是用long long来存，治标不治本

# 判断溢出 12ms
```cpp
class Solution {
public:
    int reverse(int x) {
        if (x == INT_MIN) return 0; 
        int res = 0, xp = x > 0 ? x : -x; // xp: x positive
        while (xp > 0) {
            int digit = xp % 10;
            if (res > INT_MAX / 10 || (res == INT_MAX / 10 && digit > INT_MAX % 10)) {
                return 0; // overflow
            } else {
                res = res * 10 + digit;
                xp /= 10;
            }
        }
        if (x > 0) return res;
        else return -res; // res can't be INT_MAX, safe to negate
    }
};
```

# 用long long存，8ms
```cpp
class Solution {
public:
    int reverse(int x) {
        // 用x >= 0 ? x : -x会导致溢出
        long long lx = abs(static_cast<long long>(x));
        long long res = 0;
        while (lx > 0) {
            res = res * 10 + lx % 10;
            lx /= 10;
        }
        if (x < 0) res = -res;
        if (res > INT_MAX || res < INT_MIN) return 0;
        else return static_cast<int>(res);
    }
};
```

[1]: https://leetcode.com/problems/reverse-integer/