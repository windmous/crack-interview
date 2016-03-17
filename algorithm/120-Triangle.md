题目链接: [120.Triangle][1]
难度: Medium

给一个形状和杨辉三角一样的数堆，求从顶到底的和最小的路径。

# 自底向上

```cpp
class Solution {
public:
    int minimumTotal(vector<vector<int> > &triangle) {
        for (int i=triangle.size()-2; i>=0; --i){
            for (int j=triangle[i].size() - 1; j>=0; --j){
                triangle[i][j] += min(triangle[i+1][j], triangle[i+1][j+1]);
            }
        }
        return triangle[0][0];
    }
};
```

[1]: https://leetcode.com/problems/triangle/