题目链接: [407.Trapping Rain Water II][1]
难度: Hard

# BFS + priority_queue(155ms, 13.33%)

```cpp
class Solution {
public:
    int trapRainWater(vector<vector<int>>& heightMap) {
        if(heightMap.size()==0) return 0;
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> que;
        int row = heightMap.size(), col = heightMap[0].size();
        vector<vector<int>> visited(row, vector<int>(col, 0));
        int ans = 0, Max = INT_MIN;
        for(int i = 0; i < row; i++)
        {
            for(int j = 0; j < col; j++)
            {
                if(!(i==0 || i==row-1 || j==0 || j==col-1)) continue;
                que.push(make_pair(heightMap[i][j], i*col+j));
                visited[i][j] = 1;
            }
        }
        vector<vector<int>> dir{{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
        while(!que.empty())
        {
            auto val = que.top(); que.pop();
            int height = val.first, x = val.second/col, y = val.second%col;
            Max = max(Max, height);
            for(auto d: dir)
            {
                int x2 = x + d[0], y2 = y + d[1];
                if(x2>=row || x2<0 || y2<0 || y2>=col || visited[x2][y2]) continue;
                visited[x2][y2] = 1;
                if(heightMap[x2][y2] < Max) ans += Max - heightMap[x2][y2];
                que.push(make_pair(heightMap[x2][y2], x2*col+y2));
            }
        }
        return ans;
    }
};
```

[1]: https://leetcode.com/problems/trapping-rain-water-ii
