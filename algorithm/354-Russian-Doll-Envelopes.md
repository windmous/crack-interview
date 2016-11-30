题目链接: [354.Russian Doll Envelopes][1]
难度: Hard

# 动态规划(42ms, 90.19%)
时间复杂度：O(NlogN)
空间复杂度：O(N)

Since the width is increasing, we only need to consider height.
[3, 4] cannot contains [3, 3], so we need to put [3, 4] before [3, 3] when sorting otherwise it will be counted as an increasing number if the order is [3, 3], [3, 4]

```cpp
class Solution {
public:
    static bool comp(const pair<int, int>& i, const pair<int, int>& j) {
        if (i.first == j.first)
            return i.second > j.second;
        return i.first < j.first;
    }
    
    int maxEnvelopes(vector<pair<int, int>>& envelopes) {
        vector<int> candidates;
        sort(envelopes.begin(), envelopes.end(), comp);
        vector<int> dp;
        for (int i = 0; i < envelopes.size(); ++i) {
            auto itr = lower_bound(dp.begin(), dp.end(), envelopes[i].second);
            if (itr == dp.end()) {
                dp.push_back(envelopes[i].second);
            } else {
                *itr = envelopes[i].second;
            }
        }
        return dp.size();
    }
};
```

[1]: https://leetcode.com/problems/russian-doll-envelopes
