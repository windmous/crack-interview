题目链接: [9.Palindrome Number][1]
难度: Easy

- 判断一个数是否是回文数
- 负数不会是回文数
- 如果想reverse这个数，则要考虑可能会溢出。所以别朝着这个方向想了

```cpp
class Solution {
public:
    bool isPalindrome(int x) {
        if (x < 0) return false;
        
        int d = 1; // divisor
        while (x / d >= 10) d *= 10;
        
        while (x > 0) {
            if (x / d != x % 10) return false;
            x = (x % d) / 10;
            d /= 100; // 注意这里是100
        }
        return true;
    }
};
```

[1]: https://leetcode.com/problems/palindrome-number/