题目链接: [139.Word Break][1]
难度: Medium

描述：给定一个字符串s和一个字典，判定是否可以在s中插一些空格，使s的所有单词均在字典中。

# 动态规划
时间复杂度：O(N^2)
空间复杂度：O(N)

令dp[i]表示子串s[0:i]（左开右闭区间）是否存在合法的切割。初始化时令dp[0] = true，其它均为false。

```cpp
class Solution {
public:
    bool wordBreak(string s, unordered_set<string>& wordDict) {
        vector<bool> dp(s.size() + 1, false);
        dp[0] = true;
        for (int i = 1; i <= s.size(); ++ i) {
            for (int j = i - 1; j >= 0; -- j) {
                if (dp[j] && wordDict.find(s.substr(j, i-j)) != wordDict.end()) {
                    dp[i] = true;
                    break;
                }
            }
        }
        
        return dp[s.size()];
    }
};
```

# 上述方法的另一版本

vector只存合法的结尾

```cpp
class Solution {
public:
    bool wordBreak(string s, unordered_set<string>& wordDict) {
        vector<int> goodEnd = {0};

        for (int i = 1; i <= s.size(); ++ i) {
            for (auto e : goodEnd) { // 改为rbegin到rend遍历可以提速，因为词典多数单词都较短
                if (wordDict.find(s.substr(e, i-e)) != wordDict.end()) {
                    goodEnd.push_back(i);
                    break;
                }
            }
        }

        return goodEnd.back() == s.size();
    }
};
```

[1]: https://leetcode.com/problems/word-break/