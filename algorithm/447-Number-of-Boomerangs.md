题目链接: [447.Number of Boomerangs][1]
难度: Easy

# Hash法 ()
```cpp
class Solution {
public:
    int numberOfBoomerangs(vector<pair<int, int>>& points) {
        int result = 0;
        const int N = points.size();
        
        unordered_map<int, int> cnt_map;
        for (int i = 0; i < N; ++ i) {
            cnt_map.clear();
            for (int j = 0; j < N; ++ j) if (i != j) {
                const int dy = points[i].first - points[j].first;
                const int dx = points[i].second - points[j].second;
                const int dist = dy * dy + dx * dx;
                result += 2 * cnt_map[dist] ++;
            }
        }
        
        return result;
    }
};
```
[1]: https://leetcode.com/problems/number-of-boomerangs
