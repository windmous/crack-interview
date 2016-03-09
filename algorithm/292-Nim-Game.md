题目链接: [292.Nim Game][1]
难度: Easy

描述：有一堆石头，两个人轮流取走石头，每次可以取1,2,3块。两个人都异常聪明，每轮都会选最优策略。假设你第一个取，问能不能必胜？

# 分析法(0ms)
时间复杂度：O(1)
空间复杂度：O(1)

当石头个数n<4的时候，我们知道第一个取的人肯定必胜。当n==4时，第一个取的人必输。当8>n>4时，我们知道，只要第一个取的人使剩下的石头为4即可必胜。而n==8的时候，第一个取的人会使剩下的石头个数变为5-7，那么由前面分析知道第二个人必胜，我们必输。由此类推，只要n不是4的整数倍我们即可必胜。

可以使用数学归纳法严谨地证明：
```
Sufficient Condition ("n = 4k => the first guy encounters n = 4k will fail")

(1) Base case, true; (2) Assume n = 4k makes one who take the first step from n=4k fail. For n = 4(k+1), you have no strategy to make your opponent be the one take the first step from n'=4k, while he can, thus you will fail. Therefore, for any "n = 4k", you will fail.

Necessary Condition ("fail => n = 4k")

If the statement "fail => n = 4k" is true then the statement "n != 4k => win" is true. We can prove the later one: if n != 4k, thus n = 4k +1, or 4k + 2, or 4k + 3. For any of n = 4k +1, or 4k + 2, or 4k + 3, you can remove 1, or 2, or 3 stones to make your opponent be the guy who first encounter "n is a multiple of 4 (n = 4 k' )" situation in which the opponent is doom to fail, because we have proved "n = 4k => the first guy encounters n = 4k will fail". Therefore we've prove "n != 4k => win" is true, so "fail => n = 4k" is true.

So now we can confirm the one line solution is correct:

return n%4 == 0? false: true;


```

```cpp
class Solution {
public:
    bool canWinNim(int n) {
        return n % 4 == 0 ? false : true;
    }
};
```

# Naive动态规划



[1]: https://leetcode.com/problems/nim-game/