题目链接: [406.Queue Reconstruction by Height][1]
难度: Medium

# 排序法（69ms)
时间复杂度：O(N^2)

利用规律：身高最小的人不会影响其它人。

```cpp
class Solution {
public:
    vector<pair<int, int>> reconstructQueue(vector<pair<int, int>>& people) {
        sort(people.begin(), people.end(), [](const pair<int,int> &p1, const pair<int, int> &p2) {
            return p1.first > p2.first || (p1.first == p2.first && p1.second < p2.second);
        });
        vector<pair<int,int>> result;
        for (const auto &p : people) {
            result.insert(result.begin()+p.second, p);
        }
        
        return result;
    }
};
```

[1]: https://leetcode.com/problems/queue-reconstruction-by-height
