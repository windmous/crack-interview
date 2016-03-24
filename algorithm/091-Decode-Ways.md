题目链接: [91.Decode Ways][1]
难度: Medium

```
'A' -> 1
'B' -> 2
...
'Z' -> 26
```

Given encoded message "12", it could be decoded as "AB" (1 2) or "L" (12).

求给定的字母字符串，能有多少decode的方法

# 动态规划（Naive)(4ms)
```cpp
class Solution {
public:
    int numDecodings(string s) {
        if (!s.size() || s[0] == '0') return 0;

        // dp[i]表示前i个元素有多少decode方法
        vector<int> dp(s.size() + 1, 0);
        dp[0] = 1;
        dp[1] = 1;

        for (int i = 1; i < s.size(); ++ i) {
            const int idx = i + 1;
            if (s[i] == '0') {
                if (s[i-1] == '1' || s[i-1] == '2') {
                    dp[idx] = dp[idx-2];
                }
            } else if (s[i-1] == '1' || s[i-1]=='2' && s[i] <='6') {
                // 可以与前面结合或者不结合
                dp[idx] = dp[idx-1] + dp[idx-2];
            } else {
                // 单独存在
                dp[idx] = dp[idx-1];
            }
        }
        
        return dp[s.size()];
    }
};
```

# 动态规划
https://leetcode.com/discuss/21090/a-concise-dp-solution

```cpp
int numDecodings(string s) {
    if (!s.size() || s.front() == '0') return 0;
    // r2: decode ways of s[i-2] , r1: decode ways of s[i-1] 
    int r1 = 1, r2 = 1;

    for (int i = 1; i < s.size(); i++) {
        // zero voids ways of the last because zero cannot be used separately
        // 此时即使0是合法的，r1和r2也会变得相等，因为s[i]与s[i-1]不可分割
        if (s[i] == '0') r1 = 0;

        // possible two-digit letter, so new r1 is sum of both while new r2 is the old r1
        if (s[i - 1] == '1' || s[i - 1] == '2' && s[i] <= '6') {
            r1 = r2 + r1;
            r2 = r1 - r2;
        } else { // one-digit letter, no new way added
            r2 = r1;
        }
    }

    return r1;
}
```

[1]: https://leetcode.com/problems/decode-ways/