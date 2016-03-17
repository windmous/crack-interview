题目链接: [115.Distinct Subsequences][1]
难度: Hard

给两个字符串，判断第二个字符串在第一个字符串中以子串的形式（可为非连续）出现了几次。

Here is an example:
S = "rabbbit", T = "rabbit"

Return 3.

# 动态规划

soul machine

https://leetcode.com/discuss/2143/any-better-solution-that-takes-less-than-space-while-in-time


```cpp
/**
 * Solution (DP):
 * We keep a m*n matrix and scanning through string S, while
 * m = T.length() + 1 and n = S.length() + 1
 * and each cell in matrix Path[i][j] means the number of distinct subsequences of 
 * T.substr(1...i) in S(1...j)
 * 
 * Path[i][j] = Path[i][j-1]            (discard S[j])
 *              +     Path[i-1][j-1]    (S[j] == T[i] and we are going to use S[j])
 *                 or 0                 (S[j] != T[i] so we could not use S[j])
 * while Path[0][j] = 1 and Path[i][0] = 0.
 */
int numDistinct(string S, string T) {
    int m = T.length();
    int n = S.length();
    if (m > n) return 0;    // impossible for subsequence
    vector<vector<int>> path(m+1, vector<int>(n+1, 0));
    for (int k = 0; k <= n; k++) path[0][k] = 1;    // initialization

    for (int j = 1; j <= n; j++) {
        for (int i = 1; i <= m; i++) {
            path[i][j] = path[i][j-1] + (T[i-1] == S[j-1] ? path[i-1][j-1] : 0);
        }
    }

    return path[m][n];
}
```

# 上面那个方法的滚动数组形式

```cpp
/**
 * Further optimization could be made that we can use only 1D array instead of a
 * matrix, since we only need data from last time step.
 */

int numDistinct(string S, string T) {
    int m = T.length();
    int n = S.length();
    if (m > n) return 0;    // impossible for subsequence

    vector<int> path(m+1, 0);
    path[0] = 1;            // initial condition

    for (int j = 1; j <= n; j++) {
        // traversing backwards so we are using path[i-1] from last time step
        for (int i = m; i >= 1; i--) {  
            path[i] = path[i] + (T[i-1] == S[j-1] ? path[i-1] : 0);
        }
    }

    return path[m];
}
```

[1]: https://leetcode.com/problems/distinct-subsequences/