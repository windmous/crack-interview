题目链接: [136.Single Number][1]
难度: Medium

描述：给定若干整数，除了一个整数外，其它整数均出现了两次，求这个出现一次的整数。

# 亦或方法(24ms)
时间复杂度：O(N)
空间复杂度：O(1)

```cpp
class Solution {
public:
    int singleNumber(vector<int>& nums) {
        return accumulate(nums.begin(), nums.end(), 0, 
                        [](int x, int y) {return x ^ y;});
    }
};
```

[1]: https://leetcode.com/problems/single-number/