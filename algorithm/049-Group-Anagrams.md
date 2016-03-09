题目链接: [49.Group Anagrams][1]
难度: Medium

Given an array of strings, group anagrams together.

For example, given: ["eat", "tea", "tan", "ate", "nat", "bat"], 
Return:

[
  ["ate", "eat","tea"],
  ["nat","tan"],
  ["bat"]
]

# 将单词中的字母重新排序 68ms

```cpp
class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_map<string, vector<string> > group;
        for (const auto& str : strs) {
            string key = str;
            sort(key.begin(), key.end());
            group[key].push_back(str);
        }
        
        vector<vector<string>> result;
        for (auto it = group.begin(); it != group.end(); ++it) {
            sort(it->second.begin(), it->second.end());
            result.emplace_back(std::move(it->second));  // c++ 11，速度提升4ms
        }
        
        return result;
    }
};
```

[1]: https://leetcode.com/problems/anagrams/