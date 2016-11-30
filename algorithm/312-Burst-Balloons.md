题目链接: [312.Burst Balloons][1]
难度: Hard

# 动态规划(36ms,70.6%)
时间复杂度：O(N^3)
空间复杂度：O(1)

思考过程：
1. 暴力搜索，N!
2. 简单DP, 2^N
3. 分治法，burst一个气球然后分成两块；
4. reverse 分治：burst最后一个气球然后分成两半，碉堡了


```cpp
class Solution {
public:
    int maxCoins(vector<int>& inums) {
        vector<int> nums = {1};
        nums.reserve(inums.size()+2);
        for (int n : inums) {
            if (n > 0) {
                nums.push_back(n);
            }
        }
        nums.push_back(1);
        
        const int N = nums.size();
        vector<vector<int>> dp(N, vector<int>(N, 0));
        for (int len = 1; len < N; ++ len) {
            for (int left = 1; left + len < N; ++ left) {
                const int right = left + len;
                for (int i = left; i < right; ++ i) {
                    dp[left][right] = max(dp[left][right], nums[left-1]*nums[i]*nums[right] + dp[left][i]+dp[i+1][right]);
                }
            }
        }
        return dp[1][N-1];
    }
};
```

[1]: https://leetcode.com/problems/burst-balloons/