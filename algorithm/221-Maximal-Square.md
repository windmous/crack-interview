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
class Solution {
public:
    int maximalSquare(vector<vector<char>>& matrix) {
        if (matrix.empty()) return 0;
        const int M = matrix.size(), N = matrix[0].size();
        vector<int> dp(N+1, 0);
        int ans = 0;
        
        for (int i = 0; i < M; ++ i) {
            int upper_left = dp[0];
            for (int j = 1; j <= N; ++ j) {
                int temp = dp[j];
                if (matrix[i][j-1] == '1') {
                    dp[j] = min({dp[j-1], dp[j], upper_left}) + 1;
                    ans = max(ans, dp[j]);
                } else {
                    dp[j] = 0;
                }
                upper_left = temp;
            }
        }
        
        return ans * ans;
    }
};
```

一种更简洁的写法：
```cpp
class Solution {
public:
    int maximalSquare(vector<vector<char>>& matrix) {
        if (matrix.empty()) return 0;
        const int M = matrix.size(), N = matrix[0].size();
        vector<int> dp(N+1, 0);
        int ans = 0;
        
        for (int i = 0; i < M; ++ i) {
            int upper_left = dp[0];
            for (int j = 1; j <= N; ++ j) {
                int temp = dp[j];
                dp[j] = (matrix[i][j-1] - '0') * (min({dp[j-1], dp[j], upper_left}) + 1);
                ans = max(ans, dp[j]);
                upper_left = temp;
            }
        }
        
        return ans * ans;
    }
};
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