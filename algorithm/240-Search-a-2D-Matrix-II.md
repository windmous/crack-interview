题目链接: [240.Search a 2D Matrix II][1]
难度: Medium

描述：给定一个矩阵，每一行和每一列的数据都是单调递增的。现在给定一个值，问该矩阵中是否存在该元素。

下面只给出了集中常见解法，更全面的解法见[这里][3]。本题不存在O(log(m)+log(n))的解，其下限为O(m*log(M/m))，见[这里][4]。

# 搜索法(236ms)
时间复杂度：O(M+N)，或者说O(max(M, N))，两者一样的。
空间复杂度：O(1)
```cpp
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int m = matrix.size();
        if (m == 0) return false;
        int n = matrix[0].size();
    
        int i = 0, j = n - 1;
        while (i < m && j >= 0) {
            if (matrix[i][j] == target)
                return true;
            else if (matrix[i][j] > target) {
                j--;
            } else 
                i++;
        }
        return false;
    }
};
```

# 二分法(1500ms)
注意下面的N是指矩阵里所有元素个数
时间复杂度：O(N^log(4,3)) < O(N)
空间复杂度：O(logN)

详细分析见[这里][2]

```cpp
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        if(matrix.size()==0) return false;
        int row=matrix.size(), col=matrix[0].size();
        return help(matrix, 0, row-1, 0, col-1, target);
    }

    bool help(vector<vector<int>>& matrix, int row_start, int row_end, int col_start, int col_end, int target) {
    	// 注意row_start和row_end组成的是一个闭区间。col同理
        if(row_start>row_end || col_start>col_end)  return false;
        int row_mid=(row_start+row_end)/2, col_mid=(col_start+col_end)/2;

        if(matrix[row_mid][col_mid]==target)    return true;
        else if(matrix[row_mid][col_mid]>target){
        	// 此时右下角是不可能的了
            /*** left-up || left-down || right-up ***/
            return help(matrix, row_start, row_mid-1, col_start, col_mid-1, target) ||
                help(matrix, row_mid, row_end, col_start, col_mid-1, target) ||
                help(matrix, row_start, row_mid-1, col_mid, col_end, target);
        }
        else{
        	// 此时左上角是不可能的了
            /*** right-down || left-down || right-up ***/
            return help(matrix, row_mid+1, row_end, col_mid+1, col_end, target) ||
                help(matrix, row_mid+1, row_end, col_start, col_mid, target) ||
                help(matrix, row_start, row_mid, col_mid+1, col_end, target);
        }
    }
};
```

# 搜索法2(800ms)
时间复杂度：O(mlogn)
```cpp
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        for (int i = 0; i < matrix.size(); ++ i) {
            if (matrix[i][0] > target) return false;
            else if (matrix[i].back() < target) continue;
            
            if (binary_search(matrix[i].begin(), matrix[i].end(), target)) {
                return true;
            }
        }
        
        return false;
    }
};
```

这里有个哥们使用了二分法搜索从哪行开始测试以及到哪行截止，时间复杂度不变，速度为320ms。


[1]: https://leetcode.com/problems/search-a-2d-matrix-ii/
[2]: https://leetcode.com/discuss/83239/clean-c-implementation-with-detailed-complexity-analysis
[3]: http://articles.leetcode.com/searching-2d-sorted-matrix-part-ii
[4]: https://leetcode.com/discuss/51108/is-theres-a-o-log-m-log-n-solution-i-know-o-n-m-and-o-m-log-n