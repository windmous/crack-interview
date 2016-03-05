题目链接: [14.Longest Common Prefix][1]
难度: Easy

- 寻找一组string的最长公共前缀

8ms
```cpp
class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        string prefix;
        for (int idx = 0; strs.size() > 0; prefix += strs[0][idx], ++idx) {
            for (int row = 0; row < strs.size(); ++row) {
                if (idx >= strs[row].size() || (row > 0 && strs[row][idx] != strs[row - 1][idx]))
                    return prefix;
            }
        }
        
        return prefix;
    }
};
```
[1]: https://leetcode.com/problems/longest-common-prefix/