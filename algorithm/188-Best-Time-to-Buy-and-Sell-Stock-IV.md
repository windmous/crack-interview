题目链接: [188.Best Time to Buy and Sell Stock IV][1]
难度: Hard

给定股票的每日价格。

P121 只允许交易一笔，求最高利益。

P122 允许交易多笔，但是各笔交易不允许重叠，求最高利益。

P123 只允许交易至多两笔，求最高利益。

P188 只允许交易至多K笔，求最高利益。


# 动态规划

解法和P123的最后一个动态规划思路一致。P188中有k特别大的特殊情况，此时需要做个优化，当k>=天数/2的时候，问题退化成P122，允许交易任意多笔。

https://leetcode.com/discuss/62026/clean-java-dp-solution-with-comment


```cpp
class Solution {
public:
    int maxProfit(int k, vector<int>& prices) {
        if (prices.empty() || k <= 0) return 0;
        
        if (k >= prices.size() / 2) {
            int ans = 0;
            for (int i = 1; i < prices.size(); ++ i) {
                ans += max(0, prices[i] - prices[i-1]);
            }
            return ans;
        }
        
        vector<int> dp(prices.size());
        for (int i = 0; i < k; ++ i) {
            int local_max = 0 - prices[0];
            for (int j = 1; j < prices.size(); ++ j) {
                int tmp = dp[j];
                dp[j] = max(dp[j-1], local_max + prices[j]);
                local_max = max(tmp - prices[j], local_max);
            }
        }
        
        return dp.back();
    }
};
```

```java
/**
 * dp[i, j] represents the max profit up until prices[j] using at most i transactions. 
 * dp[i, j] = max(dp[i, j-1], prices[j] - prices[jj] + dp[i-1, jj]) { jj in range of [0, j-1] }
 *          = max(dp[i, j-1], prices[j] + max(dp[i-1, jj] - prices[jj]))
 * dp[0, j] = 0; 0 transactions makes 0 profit
 * dp[i, 0] = 0; if there is only one price data point you can't make any transaction.
 */

public int maxProfit(int k, int[] prices) {
    int n = prices.length;
    if (n <= 1)
        return 0;

    //if k >= n/2, then you can make maximum number of transactions.
    if (k >=  n/2) {
        int maxPro = 0;
        for (int i = 1; i < n; i++) {
            if (prices[i] > prices[i-1])
                maxPro += prices[i] - prices[i-1];
        }
        return maxPro;
    }

    int[][] dp = new int[k+1][n];
    for (int i = 1; i <= k; i++) {
        int localMax = dp[i-1][0] - prices[0];
        for (int j = 1; j < n; j++) {
            dp[i][j] = Math.max(dp[i][j-1],  prices[j] + localMax);
            localMax = Math.max(localMax, dp[i-1][j] - prices[j]);
        }
    }
    return dp[k][n-1];
}
```

[1]: https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iv/