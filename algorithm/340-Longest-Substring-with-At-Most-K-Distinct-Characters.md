题目链接: [340.Longest Substring with At Most K Distinct Characters][1]
难度: Hard

# 尺取法扫描(9ms)
时间复杂度：O(N)
空间复杂度：O(1)

```cpp
class Solution {
public:
    int lengthOfLongestSubstringKDistinct(string s, int k) {
        array<int, 128> tab = {0};
        int counter = 0, ans = 0;
        int begin = 0, end = 0;
        while (end < s.size()) {
            if (tab[s[end++]] ++ == 0) counter ++;
            while (counter > k) if (tab[s[begin++]]-- == 1) counter --;
            ans = max(ans, end - begin);
        }
        return ans;
    }
};
```
[1]: https://leetcode.com/problems/longest-substring-with-at-most-k-distinct-characters
