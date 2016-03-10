题目链接: [172.Factorial Trailing Zeroes][1]
难度: Easy

描述：给定一个整数n，求n!的结果中末尾0的个数

# 迭代(4ms)
时间复杂度：O(log_5N)
空间复杂度：O(1)

末尾的0来自于10，而10来自于2\*5，所以我们只要统计1\*2\*...\*(N-1)\*N中因子2和5出现的总次数即可，由于2的出现次数远多于5，我们仅统计5出现的次数即可。

```cpp
class Solution {
public:
    int trailingZeroes(int n) {
        int count = 0;
        while(n /= 5) count += n;
        return count;
    }
};
```

# 递归
时间复杂度：O(log_5N)
空间复杂度：O(log_5N)

```cpp
class Solution {
public:
    int trailingZeroes(int n) {
        if(n < 5) return 0;
        else return n/5 + trailingZeroes(n/5);
    }
};
```



[1]: https://leetcode.com/problems/factorial-trailing-zeroes/