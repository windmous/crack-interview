题目链接: [6.ZigZag Conversion][1]
难度: Easy

- 将输入字符串按照zigzag重排各字符

# 遍历 16ms
time o(n), space o(1)

```
class Solution {
public:
    string convert(string s, int numRows) {
        if (numRows == 1) return s;
        int len = s.length(), seg = numRows * 2 - 2;
        string res;
        for (int i = 0; i < len; i += seg) {
            res += s[i];
        }
        for (int bias = 1; bias < numRows - 1; ++bias) {
            for (int i = 0; i < len; i += seg) {
                if (i + bias < len) {
                    res += s[i + bias];
                    if (i + seg - bias < len) {
                        res += s[i + seg - bias];
                    }
                }
            }
        }
        for (int i = numRows - 1; i < len; i += seg) {
            res += s[i];
        }
        return res;
    }
};
```

[1]: https://leetcode.com/problems/zigzag-conversion/