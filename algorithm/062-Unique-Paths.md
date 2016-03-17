题目链接: [62.Unique Paths][1]
难度: Medium

统计从grid左上角到右下角的不同路径个数，只能往右或往下走

# 简单的动态规划，0ms

```cpp
class Solution {
public:
    int uniquePaths(int m, int n) {
        vector<int> f(n, 0);
        f[0] = 1;
        for (int row = 0; row < m; ++row) {
            for (int col = 1; col < n; ++col) {
                f[col] = f[col - 1] + f[col];
            }
        }
        return f[n - 1];
    }
};
```

# 数学公式

共需要走 m + n - 2步，其中有m - 1步是向下走的，C（m + n - 2）选（m - 1）

```cpp
class Solution {
public:
    typedef long long int64_t;
    // 求阶乘, n!/(start-1)!，即 n*(n-1)...start，要求 n >= 1
    static int64_t factor(int n, int start = 1) {
        int64_t  ret = 1;
        for(int i = start; i <= n; ++i)
            ret *= i;
        return ret;
    }
    // 求组合数 C_n^k
    static int64_t combination(int n, int k) {
        // 常数优化
        if (k == 0) return 1;
        if (k == 1) return n;

        int64_t ret = factor(n, k+1);
        ret /= factor(n - k);
        return ret;
    }

    int uniquePaths(int m, int n) {
        // max 可以防止n和k差距过大，从而防止combination()溢出
        return combination(m+n-2, max(m-1, n-1));
    }
};
```

[1]: https://leetcode.com/problems/unique-paths/