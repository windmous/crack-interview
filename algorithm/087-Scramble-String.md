题目链接: [87.Scramble String][1]
难度: Hard

将字符串按照树的形式表达，任意个非叶子节点扭转后得到的字符串称为scramble，问两个字符串是否互为scramble

# 递归+剪枝 4ms

纯递归会导致超时，此处剪枝策略是两个scramble strings包含的各个字符个数一定是相同的。
（将string转换成const char*似乎可以避免substr的花费，但是两个程序在OJ上都是4ms）

https://leetcode.com/discuss/36470/share-my-4ms-c-recursive-solution
```cpp
class Solution {
public:
    bool isScramble(string s1, string s2) {
        if(s1==s2)
            return true;

        int len = s1.length();
        int count[26] = {0};
        for(int i=0; i<len; i++)
        {
            count[s1[i]-'a']++;
            count[s2[i]-'a']--;
        }

        for(int i=0; i<26; i++)
        {
            if(count[i]!=0)
                return false;
        }

        for(int i=1; i<=len-1; i++)
        {
            if( isScramble(s1.substr(0,i), s2.substr(0,i)) && isScramble(s1.substr(i), s2.substr(i)))
                return true;
            if( isScramble(s1.substr(0,i), s2.substr(len-i)) && isScramble(s1.substr(i), s2.substr(0,len-i)))
                return true;
        }
        return false;
    }
};
```

# 动态规划

设状态为f[n][i][j]，表示长度为$n$，起点为s1[i]和起点为s2[j]两个字符串是否互为scramble，则状态转移方程为

f[n][i][j] =  (对所有k) (f[k][i][j] && f[n-k][i+k][j+k]) || (f[k][i][j+n-k] && f[n-k][i+k][j])

```cpp
class Solution {
public:
    bool isScramble(const string& s1, const string& s2) {
        const int N = s1.size();
        if (N != s2.size()) return false;

        // f[n][i][j]，表示长度为n，起点为s1[i]和
        // 起点为s2[j]两个字符串是否互为scramble
        bool f[N + 1][N][N];
        fill_n(&f[0][0][0], (N + 1) * N * N, false);

        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                f[1][i][j] = s1[i] == s2[j];

        for (int n = 1; n <= N; ++n) {
            for (int i = 0; i + n <= N; ++i) {
                for (int j = 0; j + n <= N; ++j) {
                    for (int k = 1; k < n; ++k) {
                        if ((f[k][i][j] && f[n - k][i + k][j + k]) ||
                                (f[k][i][j + n - k] && f[n - k][i + k][j])) {
                            f[n][i][j] = true;
                            break;
                        }
                    }
                }
            }
        }
        return f[N][0][0];
    }
};
```
[1]: https://leetcode.com/problems/scramble-string/