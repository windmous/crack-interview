题目链接: [231.Power of Two][1]
难度: Easy

# 位运算trick(8ms)
时间复杂度: O(1)
```cpp
class Solution {
public:
    bool isPowerOfTwo(int n) {
        return !(n & (n-1)) && n > 0;
    }
};
```

# 迭代(8ms)
时间复杂度：O(logN)
```cpp
class Solution {
public:
    bool isPowerOfTwo(int n) {
        while (n > 1) {
            if (n & 1) return false;
            n >>= 1;
        }
        
        return n == 1;
    }
};
```

[1]: https://leetcode.com/problems/power-of-two/