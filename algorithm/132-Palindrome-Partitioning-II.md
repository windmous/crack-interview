题目链接: [132.Palindrome Partitioning II][1]
难度: Hard

给定字符串s，将其划分成若干子串，每个子串都是回文。

P131 返回所有可行的分割

P132 返回最小的需要切割次数

# 动态规划

https://leetcode.com/discuss/9476/solution-does-not-need-table-palindrome-right-uses-only-space

cut数组的意义
```
0  1  2  3  4  5
a  b  a  e  e
-1 0  1  2  3  4  <- cut数组，第i项表示字符串s[0..i-1]需要的最少切割
         ^
-1     -1+1       <- 由于`aba`是palindrome导致的更新
-1       0    0+1 <- 由于`ee`是palindrome导致的更新
```

```cpp
class Solution {
public:
    int minCut(string s) {
        int n = s.size();
        vector<int> cut(n+1, 0);  // number of cuts for the first k characters
        for (int i = 0; i <= n; i++) cut[i] = i-1;  // 注意cut的初始化方式，其实这里只需要初始化cut[0]=-1即可，因为odd palindrome有对单个字母的更新
        for (int i = 0; i < n; i++) { // 这个for循环只会修改cut[k] (k>i)，此时cut[k](k<=i)已经保证是最终解
            for (int j = 0; i-j >= 0 && i+j < n && s[i-j]==s[i+j] ; j++) // odd length palindrome
                cut[i+j+1] = min(cut[i+j+1],1+cut[i-j]); 

            for (int j = 1; i-j+1 >= 0 && i+j < n && s[i-j+1] == s[i+j]; j++) // even length palindrome
                cut[i+j+1] = min(cut[i+j+1],1+cut[i-j+1]);
        }
        return cut[n];
    }
};
```

[1]: https://leetcode.com/problems/palindrome-partitioning-ii/