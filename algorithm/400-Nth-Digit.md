题目链接: [400.Nth Digit][1]
难度: Easy

# 循环法
时间复杂度：O(logN)
空间复杂度：O(1)

```cpp
class Solution {
public:
    int findNthDigit(int n) {
    	// unit represents the number of digits of one number
        long long unit = 1, range = 9;
        while (n > range*unit) {
            n -= range*unit++;
            range *= 10;
        }
        // Find the exact number n-th digit lies in
        long long num = pow(10, unit-1) + (n - 1)/ unit;
        // Extract the exact digit
        return to_string(num)[(n-1)%unit] - '0';
    }
};
```

[1]: https://leetcode.com/problems/nth-digit
