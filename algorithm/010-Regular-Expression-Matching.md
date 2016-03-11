题目链接: [10.Regular Expression Matching][1]
难度: Hard

- 给一个string和一个可能包含`.`和`*`的pattern，判断该字符串是否匹配此pattern
- 将string转成const char*是很有必要的，因为substr太过耗时

# 递归 28ms
```cpp
class Solution {
public:
    bool isMatch(string s, string p) {
        return isMatch(s.c_str(), p.c_str());
    }

private:
    bool isMatch(const char*s, const char* p) {
        if (p[0] == '\0') return s[0] == '\0';

        // pattern is not empty
        if (p[1] == '*') {
            // 首先试试p[0,1]不吞s任何字符行不行，若不行再尝试先吞下s的1个字符
            return isMatch(s, p + 2) || (s[0] != '\0' && (s[0] == p[0] || p[0] == '.') && isMatch(s + 1, p));
        } else {
            // 必须吞下一个字符
            return s[0] != '\0' && (s[0] == p[0] || p[0] == '.') && isMatch(s + 1, p + 1);
        }
    }
};
```

[1]: https://leetcode.com/problems/regular-expression-matching/