题目链接: [72.Edit Distance][1]
难度: Hard

# 经典动归

- 如果c==d，则f[i][j]=f[i-1][j-1]；
- 如果c!=d，

        如果将c替换成d，则f[i][j]=f[i-1][j-1]+1；

        如果在c后面添加一个d，则f[i][j]=f[i][j-1]+1；

        如果将c删除，则f[i][j]=f[i-1][j]+1；

# 二维动归

```cpp
class Solution {
public:
    int minDistance(const string &word1, const string &word2) {
        const size_t n = word1.size();
        const size_t m = word2.size();
        // 长度为n的字符串，有n+1个隔板
        int f[n + 1][m + 1];
        for (size_t i = 0; i <= n; i++)
            f[i][0] = i;
        for (size_t j = 0; j <= m; j++)
            f[0][j] = j;

        for (size_t i = 1; i <= n; i++) {
            for (size_t j = 1; j <= m; j++) {
                if (word1[i - 1] == word2[j - 1])
                    f[i][j] = f[i - 1][j - 1];
                else {
                    int mn = min(f[i - 1][j], f[i][j - 1]);
                    f[i][j] = 1 + min(f[i - 1][j - 1], mn); //左、上、左上三者最小值+1
                }
            }
        }
        return f[n][m];
    }
};
```

# 二维动归+滚动数组 
```cpp
class Solution {
public:
    int minDistance(const string &word1, const string &word2) {
        if (word1.length() < word2.length())
            return minDistance(word2, word1);

        int f[word2.length() + 1];
        int upper_left = 0; // 额外用一个变量记录f[i-1][j-1]

        for (size_t i = 0; i <= word2.size(); ++i)
            f[i] = i;

        for (size_t i = 1; i <= word1.size(); ++i) {
            upper_left = f[0];
            f[0] = i;

            for (size_t j = 1; j <= word2.size(); ++j) {
                int upper = f[j];

                if (word1[i - 1] == word2[j - 1])
                    f[j] = upper_left;
                else
                    f[j] = 1 + min(upper_left, min(f[j], f[j - 1]));

                upper_left = upper;
            }
        }

        return f[word2.length()];
    }
};
```

[1]: https://leetcode.com/problems/edit-distance/