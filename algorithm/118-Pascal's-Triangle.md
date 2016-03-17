题目链接: [118.Pascal&#39;s Triangle][1]
难度: Easy

P118 生成n行杨辉三角。

P119 生成第n行杨辉三角。限制使用空间O(N)


```cpp
class Solution {
public:
    vector<vector<int> > generate(int numRows) {
        vector<vector<int>> r(numRows);

        for (int i = 0; i < numRows; i++) {
            r[i].resize(i + 1);
            r[i][0] = r[i][i] = 1;

            for (int j = 1; j < i; j++)
                r[i][j] = r[i - 1][j - 1] + r[i - 1][j];
        }

        return r;
    }
};
```

[1]: https://leetcode.com/problems/pascals-triangle/