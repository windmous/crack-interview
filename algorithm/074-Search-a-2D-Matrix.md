题目链接: [74.Search a 2D Matrix][1]
难度: Medium

在矩阵中找是否存在某个元素，This matrix has the following properties:

Integers in each row are sorted from left to right.
The first integer of each row is greater than the last integer of the previous row.


# 二分查找 O（log(m + n)）
本质就是有序数组，直接二分查找。
评论区有人问能否先二分查找行O(LOG M)，再二分查找列O(LOG N)，这样的复杂度是O(LOG M + LOG N) = O (LOG (MN))，劣于直接二分查找。

```cpp
class Solution {
public:
    bool searchMatrix(vector<vector<int> > &matrix, int target) {
        int n = matrix.size();
        int m = matrix[0].size();
        int l = 0, r = m * n - 1;
        while (l != r){
            int mid = (l + r - 1) >> 1;
            if (matrix[mid / m][mid % m] < target)
                l = mid + 1;
            else 
                r = mid;
        }
        return matrix[r / m][r % m] == target;
    }
};
```

[1]: https://leetcode.com/problems/search-a-2d-matrix/