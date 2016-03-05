题目链接: [221.Maximal Square][1]
难度: Medium

描述：从一个充满0-1元素的矩阵中找出一个最大的子*方阵*，该子方阵的元素全是1。返回该方阵之面积。

# 动态规划1(12ms)
时间复杂度：O(N^2)
空间复杂度：O(N)

设dp\[m\]\[n\]为动归时所用数组，则t = dp\[i\]\[j\]表示(i, j)位置的元素是一个全1方阵的右下角元素，该方阵大小为t。

于是，动归公式为：
```
dp[i][j] = min(dp[i][j-1], dp[i-1][j], dp[i-1][j-1]) + 1    if dp[i][j] == '1'
           0                                                if dp[i][j] == '0'
``` 

dp数组实际上只要一行或者一列即可。下面使用一列，代码如下

TODO：优化行序扫描，因为C数组是行主序的，效率更高。
```cpp
int maximalSquare(vector<vector<char>>& matrix) {
    if (matrix.empty()) return 0;
    int m = matrix.size(), n = matrix[0].size();
    vector<int> dp(m + 1, 0);
    int maxsize = 0, pre = 0;
    for (int j = 0; j < n; j++) {
        for (int i = 1; i <= m; i++) {
        	// 此时dp[i]的元素实际是dp[i][j-1]
            int temp = dp[i];

            if (matrix[i - 1][j] == '1') {
            	// dp[i-1]实际是dp[i-1][j]
            	// pre的值是dp[i-1][j-1]
                dp[i] = min(dp[i], min(dp[i - 1], pre)) + 1;
                maxsize = max(maxsize, dp[i]);
            }
            else dp[i] = 0; 
            pre = temp;
        }
    }
    return maxsize * maxsize;
}
```

# 动态规划2(12ms)
时间复杂度：O(N^2)
空间复杂度：O(1)

这里使用输入matrix作为dp数组：
```cpp
class Solution {
public:
    int maximalSquare(vector<vector<char>>& matrix) {
        if(matrix.empty() || matrix[0].empty()) return 0;
        int maxSize = 0;        
        vector<vector<int>> m(matrix.size(), vector<int>(matrix[0].size(), 0));
        for(int r = 0 ; r < m.size() ; ++r) {
            for(int c = 0 ; c < m[0].size() ; ++c) {
            	// 下面这个实现省略了不少条件判定
                m[r][c] = matrix[r][c]-'0';
                if(r && c && m[r][c]) {
                    m[r][c] += min(m[r-1][c], min(m[r][c-1], m[r-1][c-1]));
                }
                maxSize = max(maxSize, m[r][c]);
            }
        }
        return maxSize*maxSize;
    }
};
```


[1]: https://leetcode.com/problems/maximal-square/