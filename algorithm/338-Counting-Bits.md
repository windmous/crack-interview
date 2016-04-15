题目链接: [338.Counting Bits][1]
难度: Medium

求[0,N]范围内每个整数的二进制表示中1的个数。

# 动态规划(120ms)
时间复杂度：O(N)

```cpp
class Solution {
public:
    vector<int> countBits(int num) {
        vector<int> result(num+1);
        for (int i = 1; i <= num; ++ i) {
            result[i] = result[i & (i-1)] + 1;
        }
        return result;
    }
};
```

[1]: https://leetcode.com/problems/increasing-triplet-subsequence/