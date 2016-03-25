题目链接: [123.Best Time to Buy and Sell Stock III][1]
难度: Hard

给定股票的每日价格。

P121 只允许交易一笔，求最高利益。

P122 允许交易多笔，但是各笔交易不允许重叠，求最高利益。

P123 只允许交易至多两笔，求最高利益。

P188 只允许交易至多K笔，求最高利益。

# 简单动态规划，O(n), O(n)

soul machine 中的解法。虽然需要3趟，也不容易拓展成k笔，但是个人认为可读性高。

```cpp

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        if (prices.size() < 2) return 0;
        vector<int> left(prices.size(), 0);
        vector<int> right(prices.size(), 0);
        
        for (int i=1, valley=prices[0]; i < prices.size(); ++ i) {
            left[i] = max(left[i-1], prices[i] - valley);
            valley = min(valley, prices[i]);
        }
        
        for (int i=prices.size()-2, peak=prices.back(); i >= 0; -- i) {
            right[i] = max(right[i+1], peak - prices[i]);
            peak = max(peak, prices[i]);
        }
        
        // 我们不用担心第i个stock会被左右购买两次的情况，此时两个交易直接合并即可
        int ans = 0;
        for (int i = 0; i < prices.size(); ++ i) {
            ans = max(ans, left[i] + right[i]);
        }
        return ans;
    }
};
```

# O(n), O(1)

https://leetcode.com/discuss/18330/is-it-best-solution-with-o-n-o-1

非常机智的想法。维护四个变量，hold1, release1, hold2, release2，分别指第一次买入，第一次卖出，第二次买入，第二次卖出时的最高净利润（因此买入时利润可为负数）。


拓展到K笔也很简单。

```java
public class Solution {
    public int maxProfit(int[] prices) {
        int hold1 = Integer.MIN_VALUE, hold2 = Integer.MIN_VALUE;
        int release1 = 0, release2 = 0;
        for(int i:prices){                              // Assume we only have 0 money at first
            release2 = Math.max(release2, hold2+i);     // The maximum if we've just sold 2nd stock so far.
            hold2    = Math.max(hold2,    release1-i);  // The maximum if we've just buy  2nd stock so far.
            release1 = Math.max(release1, hold1+i);     // The maximum if we've just sold 1nd stock so far.
            hold1    = Math.max(hold1,    -i);          // The maximum if we've just buy  1st stock so far. 
        }
        return release2; ///Since release1 is initiated as 0, so release2 will always higher than release1.
    }
}
```

# 动态规划

https://leetcode.com/discuss/15153/a-clean-dp-solution-which-generalizes-to-k-transactions

这个解答很给力，拓展性也很好，但是用在P188时会超时，原因是P188中有k特别大的特殊情况，此时需要做个优化，当k>=天数/2的时候，问题退化成P122，允许交易任意多笔。

这个是原作者给的答案，其中的tmpMax并不是很直观，有人在评论中加上备注：
```
// dpProfit[t][i]: maximum Profit using at most t transactions up to day i (including day i)
// dpProfit[t][i] = max(dpProfit[t][i - 1], prices[i] - prices[j] + dpProfit[t - 1][j]) for all j in range [0, i - 1]
//                = max(dpProfit[t][i - 1], prices[i] + max(dpProfit[t - 1][j] - prices[j])) for all j in range [0, i - 1]
//                = max(dpProfit[t][i - 1], prices[i] + max prev [t - 1] trans profit at the corresponding j in range [0, i - 1] less price at j)
//                                                      maxPreProfitLessI inside loop iterations
//                                                      Note: subtracting price at j is for the last additional transaction to sell at day i
```

```cpp
class Solution {
public:
    int maxProfit(vector<int> &prices) {
        // f[k, ii] represents the max profit up until prices[ii] (Note: NOT ending with prices[ii]) using at most k transactions. 
        // f[k, ii] = max(f[k, ii-1], prices[ii] - prices[jj] + f[k-1, jj]) { jj in range of [0, ii-1] }
        //          = max(f[k, ii-1], prices[ii] + max(f[k-1, jj] - prices[jj]))
        // f[0, ii] = 0; 0 times transation makes 0 profit
        // f[k, 0] = 0; if there is only one price data point you can't make any money no matter how many times you can trade
        if (prices.size() <= 1) return 0;
        else {
            int K = 2; // number of max transation allowed
            int maxProf = 0;
            vector<vector<int>> f(K+1, vector<int>(prices.size(), 0));
            for (int kk = 1; kk <= K; kk++) {
                int tmpMax = f[kk-1][0] - prices[0];
                for (int ii = 1; ii < prices.size(); ii++) {
                    f[kk][ii] = max(f[kk][ii-1], prices[ii] + tmpMax);
                    tmpMax = max(tmpMax, f[kk-1][ii] - prices[ii]);
                    maxProf = max(f[kk][ii], maxProf);
                }
            }
            return maxProf;
        }
    }
};
```

有评论说maxProf没有必要，直接返回`f[K][prices.size()-1]`即可。jianchao.li.fighter给出了对应的解：

```cpp
class Solution { 
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size(), num = 2;
        if (n <= 1) return 0;
        vector<vector<int> > dp(num + 1, vector<int>(n, 0));
        for (int k = 1; k <= num; k++) {
            int temp = dp[k - 1][0] - prices[0];
            for (int i = 1; i < n; i++) {
                dp[k][i] = max(dp[k][i - 1], prices[i] + temp);
                temp = max(temp, dp[k - 1][i] - prices[i]);
            }
        }
        return dp[num][n - 1];
    } 
};
```

[1]: https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iii/