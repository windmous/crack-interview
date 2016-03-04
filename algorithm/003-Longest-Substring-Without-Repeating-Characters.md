题目链接: [3.Longest Substring Without Repeating Characters][1]
难度: Medium

- 找字符串中最长的子串，这个子串不含重复字符

# 动态规划(16ms)
在charIndex中记录所有字符上次在s中出现的index，在i向前扫描过程中更新start，保持start和i之间没有重复元素
时间O(n)，空间O(n)

```cpp
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        vector<int> charIndex(256, -1);
        int start = 0, longest = 0; // update with DP
        for (int i = 0; i < s.length(); ++i) {
            start = max(start, charIndex[s[i]] + 1);
            charIndex[s[i]] = i;
            longest = max(longest, i - start + 1);
        }
        return longest;
    }
};
```

[1]: https://leetcode.com/problems/longest-substring-without-repeating-characters/