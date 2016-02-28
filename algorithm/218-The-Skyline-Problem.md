题目链接: [218.The Skyline Problem][1]
难度: Hard

# 法1(876ms)
时间复杂度：O(NlogN)

```cpp
class Solution {
public:
    vector<pair<int, int>> getSkyline(vector<vector<int>>& buildings) {
        multimap<int, int> coords;
        for (const auto &building: buildings) {
            coords.emplace(building[0], building[2]);
            // 令右边界优先退出
            coords.emplace(building[1], -building[2]);
        }
        
        multiset<int> heights = {0};
        map<int, int> corners;
        for (const auto &p : coords) {
            if (p.second > 0) {
                heights.emplace(p.second);
            } else {
                // 只删除一个
                heights.erase(heights.find(-p.second));
            }
            
            int cur_height = *heights.rbegin();
            corners[p.first] = cur_height;
        }
        
        typedef pair<int,int> point;
        auto eq = [](const point &lhs, const point &rhs) {return lhs.second == rhs.second;};
        vector<point> result;
        unique_copy(corners.begin(), corners.end(), back_inserter(result), eq);
        return result;
    }
};
```

# 堆方法(824ms)
时间复杂度:O(NlogN)
```cpp
class Solution {
public:
    vector<pair<int, int>> getSkyline(vector<vector<int>>& buildings) {
        typedef pair<int, int> ipair;
        int cur = 0;
        const int len = buildings.size();
        vector<ipair> result;
        priority_queue<ipair> pq; // First element is height, and the second is end position
        
        while (!pq.empty() || cur < len) {
            // 结果位置
            int cur_x = pq.empty() ? buildings[cur][0] : pq.top().second;
            if (cur >= len || !pq.empty() && buildings[cur][0] > pq.top().second) {
                while (!pq.empty() && pq.top().second <= cur_x) {
                    pq.pop();
                }
            } else {
                cur_x = buildings[cur][0];
                while (cur < len && buildings[cur][0] == cur_x) {
                    pq.push(ipair(buildings[cur][2], buildings[cur][1]));
                    ++ cur;
                }
            }
            
            int cur_h = pq.empty() ? 0 : pq.top().first;
            // 许多时候这里不会引发结果插入
            if (result.empty() || result.back().second != cur_h) 
                result.push_back(ipair(cur_x, cur_h));
        }
        
        return result;
    }
};
```

[1]: https://leetcode.com/problems/the-skyline-problem/