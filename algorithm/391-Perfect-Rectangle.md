题目链接: [391.Perfect Rectangle][1]
难度: Hard

# 扫描线算法(519ms)
时间复杂度：O(NlogN)
空间复杂度：O(N)

使用skyline的扫描线策略，将矩形的边出入到一个set中，利用set快速判断是否有重叠。
注意，可以在logN时间内快速

```cpp
class Solution {
public:
    struct Comp {
        bool operator () (const pair<int,int> &v1, const pair<int,int> &v2) const {
           return v1.second <= v2.first;
        }
    };
    
    bool isRectangleCover(vector<vector<int>>& rectangles) {
        int min_y = INT_MAX, min_x = INT_MAX;
        int max_y = INT_MIN, max_x = INT_MIN;
        
        vector<vector<int>> events;
        int total_area = 0;
        for (const auto &rect : rectangles) {
            min_y = min(min_y, rect[0]);
            max_y = max(max_y, rect[2]);
            min_x = min(min_x, rect[1]);
            max_x = max(max_x, rect[3]);
            events.push_back({rect[1], 0, rect[0], rect[2]});
            events.push_back({rect[3], -1, rect[0], rect[2]});
            
            total_area += (rect[2]-rect[0]) * (rect[3]-rect[1]);
        }
        
        if (total_area != (max_y - min_y) * (max_x - min_x)) {
            return false;
        }
        
        sort(events.begin(), events.end());
        set<pair<int,int>, Comp> segments;
        for (const auto &e : events) {
            pair<int,int> edge{e[2], e[3]};
            if (e[1] == -1) {
                segments.erase(segments.find(edge));
            } else if (segments.find(edge) == segments.end()) {
                segments.insert(edge);
            } else {
                return false;
            }
        }
        
        return true;
    }
};
```

# 点个数统计法(182ms)
时间复杂度：O(N)
空间复杂度：O(N)

找规律后发现，除了大矩形的4个corners外所有点出现的次数都是偶数，其它均为奇数。

```cpp
class Solution {
public:
    struct pairhash {   //double hash function for pair key
        template <typename T, typename U>
        size_t operator()(const pair<T, U> &p) const {
            size_t l = hash<T>()(p.first), r = hash<U>()(p.second);
            return l + 0x9e3779b9 + (r << 6) + (r >> 2);
        }
    };
    
    bool isRectangleCover(vector<vector<int>>& rectangles) {
        int area = 0, xmin = INT_MAX, ymin = INT_MAX, xmax = INT_MIN, ymax = INT_MIN;
        unordered_map<pair<int, int>, int, pairhash> m;
        
        // Calculate area, and count points of appearances
        vector<pair<int, int>> points = {{0, 1}, {0, 3}, {2, 3}, {2, 1}};
        for (auto v : rectangles) {
            for (auto point : points) {
                if (++m[make_pair(v[point.first], v[point.second])] > 4) { return false; }
            }
            area += (v[2] - v[0]) * (v[3] - v[1]);
            xmin = min(xmin, v[0]), ymin = min(ymin, v[1]), xmax = max(xmax, v[2]), ymax = max(ymax, v[3]);
        }
        if (area != (xmax - xmin) * (ymax - ymin)) { return false; }
        
        // Check if points appearing odd number of times are exactly large rectangles' 4 corners
        vector<pair<int, int>> corners = {{xmin, ymin}, {xmin, ymax}, {xmax, ymax}, {xmax, ymin}};
        for (auto it = m.begin(); it != m.end(); it++) {
            if (it->second & 1 == 1) {
                auto pos = find(corners.begin(), corners.end(), it->first);
                if (pos == corners.end()) {
                    return false;
                } else {
                    corners.erase(pos);
                }
            }
        }
        return corners.empty();
    }
};
```


[1]: https://leetcode.com/problems/perfect-rectangle
