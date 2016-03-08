题目链接: [264.Ugly Number II][1]
难度: Medium

描述：输出第n个丑数。丑数就是因子只有2、3、5的正整数。

# 三队列法(64ms)
每一个丑数都是由另外一个丑数乘以2、3或5得来。我们知道，在已知当前丑数的前提下，下一个丑数必须是x\*2、y\*3以及z\*5，其中x、y、z是已知的某个丑数。

我们不妨设置3个队列，分别存放已知的丑数乘以2、3、5后的结果。这样在求下一个丑数的时候，我们只要对比下是哪个队列中哪个丑数最小即可。一旦新的丑数生成，我们将新丑数分别乘以2、3、5并加入到队列中。

```cpp
时间复杂度：O(N)
空间复杂度：O(N)

class Solution {
public:
    int nthUglyNumber(int n) {
        queue<int> q1, q2, q3;
        q1.push(1), q2.push(1), q3.push(1);
    
        int m = 0;
        for (int i = 0; i < n; ++i) {
            m = min({q1.front(), q2.front(), q3.front()});
            if (m == q1.front()) q1.pop();
            if (m == q2.front()) q2.pop();
            if (m == q3.front()) q3.pop();
            q1.push(2*m);
            q2.push(3*m);
            q3.push(5*m);
        }

        return m;
    }
};
```

# 单队列(16ms)
时间复杂度：O(N)
空间复杂度：O(N)

如果我们愿意保留所有的丑数，那么实际上就不需要3个队列了，只要用3个指针即可，如下面代码所示：

```cpp
class Solution {
public:
    int nthUglyNumber(int n) {
        vector<int> dp(n, 0);
        int p2 = 0, p3 = 0, p5 = 0;
        dp[0] = 1;
        
        for (int i = 1; i < n; ++ i) {
            dp[i] = min(dp[p2] * 2, min(dp[p3] * 3, dp[p5] * 5));
            if (dp[i] == dp[p2] * 2) p2 ++;
            if (dp[i] == dp[p3] * 3) p3 ++;
            if (dp[i] == dp[p5] * 5) p5 ++;
        }
        return dp.back();
    }
};
```

[1]: https://leetcode.com/problems/ugly-number-ii/