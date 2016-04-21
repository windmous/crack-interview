题目链接: [309.Best Time to Buy and Sell Stock with Cooldown][1]
难度: Medium

可以买卖任意多次，但是卖出的后一天不能买入。求最大收益。

# 动态规划

```cpp
class Solution {
public:
	int maxProfit(vector<int>& prices) {
		int len = prices.size();
		if (len <= 1) return 0;
		
		// wait：等待买入，buy：执行买入，sell：执行卖出，hold：持有股票。所存数字是第i天执行此操作的最大收益
		vector<int> wait(len, 0), buy(len, 0), sell(len, 0), hold(len, 0);  // 可将vector改为单变量
		buy[0] = -prices[0]; 
		sell[0] = INT_MIN; // 第一天显然不能卖出
		hold[0] = INT_MIN; // 第一天显然不能持有

		for (int i = 1; i < len; ++i) {
			buy[i] = wait[i - 1] - prices[i];
			wait[i] = max(wait[i - 1], sell[i - 1]);
			sell[i] = max(buy[i - 1], hold[i - 1]) + prices[i];
			hold[i] = max(buy[i - 1], hold[i - 1]);
		}
		return max(wait[len - 1], sell[len - 1]); // 最后一天只能为wait或者sell
	}
};
```

[1]: https://leetcode.com/problems/best-time-to-buy-and-sell-stock-with-cooldown/