题目链接: [198.House Robber][1]
难度: Easy

描述：给定一组整数，请从其中选出一些整数使它们的和最大。注意选择的整数在输入数组中不能是相邻的。

# 动态规划(0ms)
时间复杂度：O(N)
空间复杂度：O(1)

令dp[i]表示前i个元素中最大的非相邻子序列和，那么dp[i+1] =max(dp[i], dp[i-1]+nums[i+1])

```cpp
class Solution {
public:
    int rob(vector<int>& nums) {
        if (nums.size() == 0) return 0;
        if (nums.size() == 1) return nums[0];
        
        vector<int> dp(nums.size(), 0);
        dp[0] = nums[0];
        dp[1] = max(nums[0], nums[1]);
        
        for (int i = 2; i < nums.size(); ++ i) {
            dp[i] = max(dp[i - 1], dp[i - 2] + nums[i]);
        }
        return dp[nums.size() - 1];
    }
};
```

# 动归优化版(0ms)
时间复杂度：O(N)
空间复杂度：O(1)

上面的DP数组我们只用了两个元素，所以直接用两个整数代表这两个元素即可：

```cpp
class Solution {
public:
    int rob(vector<int>& nums) {
        int x = 0, y = 0;
        for (int i = 0; i < nums.size(); ++i) {
            if (i & 1) {
                x = max(x + nums[i], y);
            } else {
                y = max(y + nums[i], x);
            }
        }
        return max(x, y);
    }
};
```

[1]: https://leetcode.com/problems/house-robber/