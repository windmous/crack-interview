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
# 适合面试法(90ms)
时间复杂度: O(NlogN)
空间复杂度：O(N)

根据法1修改而来，直接生成最终结果，不小产生额外的大量中间点

```cpp
class Solution {
public:
    vector<pair<int, int>> getSkyline(vector<vector<int>>& buildings) {
        typedef pair<int, int> point;
        // 使用堆可以保证先插入，后删除
        priority_queue<point, vector<point>, greater<point>> coords;
        for (const auto &building: buildings) {
            coords.emplace(building[0], -building[2]);
            coords.emplace(building[1], building[2]);
        }
        
        multiset<int> heights = {0};
        vector<point> result;
        int cur_height = 0;

        while (!coords.empty()) {
            point p = coords.top();
            coords.pop();
            if (p.second < 0) {
                heights.emplace(-p.second);
            } else {
                heights.erase(heights.find(p.second));
            }
            
            if (cur_height != *(heights.rbegin())) {
                cur_height = *heights.rbegin();
                if (result.empty() || result.back().first != p.first) {
                    result.emplace_back(p.first, cur_height);
                } else {
                    result.back().second = cur_height;
                }
            }
        }

        return result;
    }
};
```

# 分治法 52ms

利用分治法的难点在于合并两个skyline，在合并时，需要对每个x点，维护skyline1的当前高度h1和skyline2的当前高度h2，取二者中的较高者。

需要注意若将要插入的点的高度和已merge的skyline最后的一点的高度相同，则放弃插入此点。


```cpp
class Solution {
public:
    vector<pair<int, int>> getSkyline(vector<vector<int>>& buildings) {
        int len = buildings.size();
        if (len == 0) 
            return vector<pair<int, int>>{};
        else 
            return merge(buildings, 0, len - 1);
    }
    
    vector<pair<int, int>> merge(vector<vector<int>>& buildings, int left, int right) {
        if (left == right) {
            return vector<pair<int, int>> {make_pair(buildings[left][0], buildings[left][2]), 
                                           make_pair(buildings[left][1], 0)};
        }
        
        int mid = left + (right - left) / 2;
        auto part1 = merge(buildings, left, mid);
        auto part2 = merge(buildings, mid + 1, right);
        int idx1 = 0, idx2 = 0, h1 = 0, h2 = 0, x;
        
        vector<pair<int, int>> ans;
        while (idx1 != part1.size() || idx2 != part2.size()) {
            if (idx1 == part1.size()) {			// out of part1
                x = part2[idx2].first;
                h2 = part2[idx2++].second;
            } else if (idx2 == part2.size()) {  // out of part1
                x = part1[idx1].first;
                h1 = part1[idx1++].second;
            } else if (part1[idx1].first < part2[idx2].first) {	// next is from part1
                x = part1[idx1].first;
                h1 = part1[idx1++].second;
            } else if (part2[idx2].first < part1[idx1].first) { // next is from part2
                x = part2[idx2].first;
                h2 = part2[idx2++].second;
            } else  {							// x's are same
                x = part1[idx1].first;
                h1 = part1[idx1++].second;
                h2 = part2[idx2++].second;
            }
            if (ans.empty() || max(h1, h2) != ans.back().second)
                ans.emplace_back(make_pair(x, max(h1, h2)));
        }
        
        return ans;
    }
};

```

[1]: https://leetcode.com/problems/the-skyline-problem/