题目链接: [122.Best Time to Buy and Sell Stock II][1]
难度: Medium

给定股票的每日价格。

P121 只允许交易一笔，求最高利益。
P122 允许交易多笔，但是各笔交易不允许重叠，求最高利益。
P123 只允许交易至多两笔，求最高利益。
P188 只允许交易至多K笔，求最高利益。

# 这题依然很简单，只累加上坡，忽略下坡即可

https://leetcode.com/discuss/2012/is-this-question-a-joke

```java
public class Solution {
public int maxProfit(int[] prices) {
    int total = 0;
    for (int i=0; i< prices.length-1; i++) {
        if (prices[i+1]>prices[i]) total += prices[i+1]-prices[i];
    }

    return total;
}
```
[1]: https://leetcode.com/problems/best-time-to-buy-and-sell-stock-ii/