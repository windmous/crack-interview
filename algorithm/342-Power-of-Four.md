题目链接: [342. Power of Four][1]
难度: Medium

求一个有符号32bit整数是否是4的幂

# 位操作(8ms)
时间复杂度：O(1)

第三个条件可使用归纳法证明

```
Proof #1: (4^n-1) = (4-1) (4^(n-1) + 4^(n-2) + 4^(n-3) + ..... + 4 + 1)

Proof #2 (by induction) 4^(n+1) - 1 = 44^n -1 = 34^n + 4^n-1. The first is divided by 3, the second is proven by induction hypothesis
```

```cpp
class Solution {
public:
    bool isPowerOfFour(int num) {
        return num > 0 && !(num & (num - 1)) && (num - 1) % 3 == 0;
    }
};
```

# 位操作2(8ms)
时间复杂度：O(1)

```cpp
class Solution {
public:
    bool isPowerOfFour(int num) {
        return num > 0 && !(num & (num - 1)) && (num & 0x55555555) == num;
    }
};
```
# 数学法(8ms)
时间复杂度：视log实现而定
```cpp
class Solution {
public:
    bool isPowerOfFour(int num) {
        return num > 0 && int(log10(num) / log10(4)) - log10(num) / log10(4) == 0;
    }
};
```

# 循环(4ms)
时间复杂度：O(log N)

```cpp
class Solution {
public:
    bool isPowerOfFour(int num) {
        while (num && (num % 4 == 0)) {
            num /= 4;
        }
        return num == 1;
    }
};
```

[1]: https://leetcode.com/problems/power-of-four/