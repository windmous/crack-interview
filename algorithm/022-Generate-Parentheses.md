题目链接: [22.Generate Parentheses][1]
难度: Medium

- 给出n个括号能够组合成的所有合法括号串

# 递归 0ms

```cpp
class Solution {
public:
    vector<string> generateParenthesis(int n) {
        vector<string> res;
        addingpar(res, "", n, 0);
        return res;
    }
    
	// n 是待添加的'('的个数，m是待添加的')'的个数
    void addingpar(vector<string> &v, string str, int n, int m){
        if(n==0 && m==0) { // 都加完了，退出递归
            v.push_back(str);
            return;
        }
        if(m > 0){ addingpar(v, str+")", n, m-1); }
        if(n > 0){ addingpar(v, str+"(", n-1, m+1); } // 加上1个左括号会导致需要添加一个右括号
    }
};
```


# 动态规划

只使用了dp矩阵的右上角部分，向右走表示加），向下走表示加（，不能越过对角线走到左下角。

以下是滚动数组实现。

```cpp
class Solution {
public:
    vector<string> generateParenthesis(int n) {
        vector<vector<string>> dp(n + 1, vector<string>());
        dp[0].push_back(string(""));
        
        for (int i = 1; i < n + 1; ++i) {
            for (auto res : dp[i - 1])
                dp[i].push_back(res + "(");
        }
        
        for (int i = 1; i < n + 1; ++i) {
            for (auto& res : dp[i]) {
                res = res + ")";
            }
            for (int j = i + 1; j < n + 1; ++j) {
                for (auto& res : dp[j]) {
                    res = res + ")";
                }
                for (auto& res : dp[j - 1]) {
                    dp[j].push_back(res + "(");
                }
            }
        }
        return dp[n];
    }
};
```

[1]: https://leetcode.com/problems/generate-parentheses/