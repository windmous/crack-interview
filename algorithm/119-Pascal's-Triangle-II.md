题目链接: [119.Pascal&#39;s Triangle II][1]
难度: Easy

P118 生成n行杨辉三角。

P119 生成第n行杨辉三角。限制使用空间O(N)

# 滚动数组

唯一难点就是从后往前更新。

```cpp
class Solution {
public:
    vector<int> getRow(int rowIndex) {
        vector<int> A(rowIndex+1, 0);
        A[0] = 1;
        for(int i=1; i<rowIndex+1; i++)
            for(int j=i; j>=1; j--)
                A[j] += A[j-1];
        return A;
    }
};
```

[1]: https://leetcode.com/problems/pascals-triangle-ii/