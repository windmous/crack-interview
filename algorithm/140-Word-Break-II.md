题目链接: [140.Word Break II][1]
难度: Hard

描述：跟139一样，不过要求输出所有可行的解

s = "catsanddog",
dict = ["cat", "cats", "and", "sand", "dog"].

A solution is ["cats and dog", "cat sand dog"].


# 动态规划1
时间复杂度：O(N^2)
空间复杂度：?

dp[i]存放s[0:i]的所有合法切分。本答案会TLE。
```cpp
class Solution {
public:
    vector<string> wordBreak(string s, unordered_set<string>& wordDict) {
        vector<vector<string>> dp(s.size() + 1);
        dp[0].push_back("");
        
        for (int i = 1; i <= s.size(); ++ i) {
            for (int j = i - 1; j >= 0; -- j) {
                string word = s.substr(j, i-j);
                if (!dp[j].empty() && wordDict.find(word) != wordDict.end()) {
                    for (const string &s : dp[j]) {
                        dp[i].push_back(s.empty() ? word : (s + " " + word));
                    }
                }
            }
        }
        
        return dp[s.size()];
    }
};
```

# 动态规划（备忘录）(12ms)
时间复杂度：O(N^2)
空间复杂度：？

跟上面的动归相比，这里只计算必要的中间结果。

```cpp
class Solution {
public:
    vector<string> wordBreak(string s, unordered_set<string>& wordDict) {
        //unordered_map<int, vector<string>> memo {{s.size(), {""}}}; 
		//                                            ^
		// error C2398: Element '1': conversion from 'unsigned int' to 'const int &' requires a narrowing conversion
        unordered_map<int, vector<string>> memo{ make_pair<int, vector<string>>( s.size(), { "" } ) }; // 注意终结符

        // 必须为sentences提供类型，否则无法调用自身。
        function<vector<string>(int)> sentences = [&](int i) {
            if (!memo.count(i))
                for (int j=i+1; j<=s.size(); j++)
                    if (wordDict.count(s.substr(i, j-i)))
                        for (string tail : sentences(j))
                            memo[i].push_back(s.substr(i, j-i) + (tail=="" ? "" : ' ' + tail));
            return memo[i];
        };
        return sentences(0);
    }
};
```


[1]: https://leetcode.com/problems/word-break-ii/