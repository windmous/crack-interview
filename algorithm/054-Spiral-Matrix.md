题目链接: [54.Spiral Matrix][1]
难度: Medium

# 模拟(0ms)
按照螺旋形状读取矩阵的各个元素，起点是左上角，开始方向向右。

```cpp
class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        vector<int> result;
        if (matrix.size() == 0) return result;
        int left = 0, right = matrix[0].size(), top = 0, bottom = matrix.size();

        while (left < right && top < bottom) {
            for (int i = left; i < right; ++ i)
                result.push_back(matrix[top][i]);
            ++ top;
            
            for (int i = top; i < bottom; ++ i)
                result.push_back(matrix[i][right-1]);
            -- right;
            
            if (top < bottom)
                for (int i = right-1; i >= left; -- i)
                    result.push_back(matrix[bottom-1][i]);
            -- bottom;
            
            if (left < right)
                for (int i = bottom-1; i >= top; -- i)
                    result.push_back(matrix[i][left]);
            ++ left;
        }
        
        return result;
    }
};
```

[1]: https://leetcode.com/problems/spiral-matrix/