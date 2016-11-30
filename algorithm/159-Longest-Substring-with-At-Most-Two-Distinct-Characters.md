题目链接: [159.Longest Substring with At Most Two Distinct Characters][1]
难度: Hard

# 尺取法(3ms, 81.51%)
时间复杂度：O(N)
空间复杂度：O(1)

```cpp
class Solution {
public:
    int lengthOfLongestSubstringTwoDistinct(string s) {
        array<int, 128> tab = {0};
        int counter = 0, ans = 0;
        int begin = 0, end = 0;
        while (end < s.size()) {
            if (tab[s[end ++]] ++ == 0) counter ++;
            while (counter > 2) if (tab[s[begin++]] -- == 1) counter --;
            ans = max(ans, end - begin);
        }
        return ans;
    }
};
```

[1]: https://leetcode.com/problems/longest-substring-with-at-most-two-distinct-characters/