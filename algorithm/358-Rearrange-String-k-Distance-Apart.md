题目链接: [358.Rearrange String k Distance Apart][1]
难度: Hard

Given a non-empty string str and an integer k, rearrange the string such that the same characters are at least distance k from each other.

All input strings are given in lowercase letters. If it is not possible to rearrange the string, return an empty string "".

Example 1:
str = "aabbcc", k = 3

Result: "abcabc"

The same letters are at least distance 3 from each other.
Example 2:
str = "aaabc", k = 3 

Answer: ""

It is not possible to rearrange the string.
Example 3:
str = "aaadbbcc", k = 2

Answer: "abacabcd"

Another possible answer is: "abcabcda"

The same letters are at least distance 2 from each other.
Credits:
Special thanks to @elmirap for adding this problem and creating all test cases.

# 贪心(66ms)
时间复杂度：O(N)
空间复杂度：O(1)

可以使用priority_queue缩小常数项。

```cpp
class Solution {
public:
    string rearrangeString(string str, int k) {
        array<int, 128> cnt = {0}, valid = {0};
        for (char c : str) cnt[c] ++;
        
        string result;
        for (int i = 0; i < str.size(); ++ i) {
            // search for the desired character
            char c = 0;
            for (char j = 'a'; j <= 'z'; ++ j) {
                if (i >= valid[j] && cnt[j] > cnt[c]) {
                    c = j;
                }
            }
            
            if (c == 0) return "";
            result += c;
            cnt[c] --;
            valid[c] = i + k;
        }
        return result;
    }
};
```

[1]: https://leetcode.com/problems/rearrange-string-k-distance-apart
