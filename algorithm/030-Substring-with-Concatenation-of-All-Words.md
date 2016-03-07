题目链接: [30.Substring with Concatenation of All Words][1]
难度: Hard

- You are given a string, s, and a list of words, words, that are all of the same length. Find all starting indices of substring(s) in s that is a concatenation of each word in words exactly once and without any intervening characters.
- 直接暴力搜，将words放在一个bag中，将扫描到i之后出现的词放在另一个bag中，难点是如何判断两个bag相等

52ms，复杂度：O（s的长度）

```cpp
class Solution {
public:
    vector<int> findSubstring(string s, vector<string>& words) {
        vector<int> ans;
        int n = s.size(), cnt = words.size();
        if (n <= 0 || cnt <= 0) return ans;
        
        // 记录words中每个单词出现的次数
        unordered_map<string, int> dict;
        for (auto &str : words)
            ++dict[str];
        
        // travel all sub string combinations
        int wl = words[0].size();
        for (int i = 0; i < wl; ++i) {  // 复杂度 O（wl）
            int left = i, count = 0;  // count统计从i开始有多少词和dict已经重了
            unordered_map<string, int> tdict;
            for (int j = i; j <= n - wl; j += wl) {  // 复杂度 O（s的长度 / wl）
                string str = s.substr(j, wl);
                // a valid word, accumulate results
                if (dict.count(str)) {
                    tdict[str]++;
                    if (tdict[str] <= dict[str]) 
                        ++count;
                    else {  // 新加的这个词出现次数太多了，需要吐到在i之后头一次出现这个词的时候
                        while (tdict[str] > dict[str]) {
                            string str1 = s.substr(left, wl);
                            --tdict[str1];
                            if (tdict[str1] < dict[str1]) --count;
                            left += wl;
                        }
                    }
                    
                    if (count == cnt) {
                        ans.push_back(left);
                        --tdict[s.substr(left, wl)];
                        --count;
                        left += wl;
                    }
                }
                // not a valid word, reset all vars
                else {
                    tdict.clear();
                    count = 0;
                    left = j + wl;
                }
            }
        }
        return ans;
    }
};
```

[1]: https://leetcode.com/problems/substring-with-concatenation-of-all-words/