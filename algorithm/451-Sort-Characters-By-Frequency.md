题目链接: [451.Sort Characters By Frequency][1]
难度: Medium

# Naive Count and Sort (39ms)
时间复杂度：O(NlogN，非准确估计) 
空间复杂度：O(N)

```cpp
class Solution {
public:
    string frequencySort(string s) {
        unordered_map<char, int> cnt_map;
        for (char c : s) {
            cnt_map[c] ++;
        }
        
        vector<pair<int, char>> items;
        for (auto& it : cnt_map) {
            items.push_back({it.second, it.first});
        }
        sort(items.begin(), items.end());
        
        string result;
        for (auto it = items.rbegin(); it != items.rend(); ++ it) {
            result.append(it->first, it->second);
        }
        
        return result;
    }
};
```

# 桶方法 (549ms)
时间复杂度：O(N)
空间复杂度：O(N)

该方法非常巧妙，用长度作为key进行hash。

```cpp
class Solution {
public:
    string frequencySort(string s) {
        unordered_map<char, int> cnt_map;
        for (char c : s) {
            cnt_map[c] ++;
        }
        
        vector<string> buckets(s.size()+1);
        for (auto &item : cnt_map) {
            buckets[item.second].append(item.second, item.first);
        }
        
        return accumulate(buckets.rbegin(), buckets.rend(), string(""));        
    }
};
```

[1]: https://leetcode.com/problems/sort-characters-by-frequency/
