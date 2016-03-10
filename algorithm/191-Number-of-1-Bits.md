题目链接: [191.Number of 1 Bits][1]
难度: Easy

描述：给一个无符号整数N，求其二进制表示中1的个数。

# 迭代(8ms)
时间复杂度：O(logN)
空间复杂度：O(1)

```cpp
class Solution {
public:
    int hammingWeight(uint32_t n)
    {
        uint32_t c;
        for (c = 0; n; c++) 
        	n &= n - 1;
        return c;
    }
};
```

# 递归(4ms)
时间复杂度：O(logN)
空间复杂度：O(logN)

```cpp
class Solution {
public:
    int hammingWeight(uint32_t n) {
        return n == 0 ? 0 : 1 + hammingWeight(n & (n - 1));
    }   
};
```


[1]: https://leetcode.com/problems/number-of-1-bits/