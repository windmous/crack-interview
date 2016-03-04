题目链接: [5.Longest Palindromic Substring][1]
难度: Medium

- 返回最长的回文子串
- 关键在于如何处理连续重复出现的元素

# 暴力搜索 8ms
时间O(N^2) 空间O(1)
```cpp
class Solution {
public:
    string longestPalindrome(string s) {
        if (s.size() < 2) return s;
        int min_start = 0, max_len = 1, len = s.length();

        // i is the mid pointer, j is left pointer, k is right pointer
        for (int i = 0; i < len; ) { // i每次更新都指向下一个不同于当前元素的元素
            if (len - i <= max_len / 2) break;
            int j = i, k = i;
            while (k < len - 1 && s[k + 1] == s[k])
                ++k; // skip duplicate
            i = k + 1; // i 可以直接跳过重复元素
            while (k < len - 1 && j > 0 && s[k + 1] == s[j - 1]) { // expand
                ++k; 
                --j;
            }
            int new_len = k - j + 1;
            if (new_len > max_len) {
                min_start = j;
                max_len = new_len;
            }
        }
        return s.substr(min_start, max_len);
    }
};

```

# Manacherą's Algorithm
时间O(n), 空间O(n)

[1]: https://leetcode.com/problems/longest-palindromic-substring/