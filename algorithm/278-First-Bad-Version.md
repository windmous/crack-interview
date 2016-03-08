题目链接: [278.First Bad Version][1]
难度: Easy

描述：给定n个版本，其中某一个版本是坏版本，且该版本之后的所有版本也被定义为坏版本。请找出第一个坏版本。

# 二分搜索(1ms)
时间复杂度：O(logN)
空间复杂度：O(1)

```cpp
// Forward declaration of isBadVersion API.
bool isBadVersion(int version);

class Solution {
public:
    int firstBadVersion(int n) {
        int lower = 1, upper = n, mid;
        while(lower < upper) {
            mid = lower + (upper - lower) / 2;
            if(!isBadVersion(mid)) lower = mid + 1;   /* Only one call to API */
            else upper = mid;
        }
        return lower;   /* Because there will alway be a bad version, return lower here */
    }
};
```

[1]: https://leetcode.com/problems/first-bad-version/