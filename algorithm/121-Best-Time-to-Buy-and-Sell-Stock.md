题目链接: [121.Best Time to Buy and Sell Stock][1]
难度: Medium

给定股票的每日价格。

P121 只允许交易一笔，求最高利益。
P122 允许交易多笔，但是各笔交易不允许重叠，求最高利益。
P123 只允许交易至多两笔，求最高利益。
P188 只允许交易至多K笔，求最高利益。

# 这题比较简单

```cpp
int maxProfit(vector<int> &prices) {
    int maxPro = 0;
    int minPrice = INT_MAX;
    for(int i = 0; i < prices.size(); i++){
        minPrice = min(minPrice, prices[i]);
        maxPro = max(maxPro, prices[i] - minPrice);
    }
    return maxPro;
}
```

[1]: https://leetcode.com/problems/best-time-to-buy-and-sell-stock/