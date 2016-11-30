题目链接: [363.Max Sum of Rectangle No Larger Than K][1]
难度: Hard

# 暴力(1029 ms)
时间复杂度：O[min(m,n)^2 * max(m,n) * log(max(m,n))]
空间复杂度：O(min(m, n))

难点在于，如何在一个array中找到连续的子数组，使得和不大于k。注意使用set

```cpp
class Solution {
public:
    int maxSumSubmatrix(vector<vector<int>>& matrix, int k) {
        const int N = matrix.size(), M = matrix[0].size();
        int ans = INT_MIN;
        for (int i = 0; i < M; ++ i) {
            vector<int> line = vector<int>(N, 0);
            for (int j = i; j < M; ++ j) {
                for (int k = 0; k < N; ++ k) {
                    line[k] += matrix[k][j];
                }
                
                int sum = 0;                
                set<int> ss = {0};
                for (int n : line) {
                    sum += n;
                    auto pos = ss.lower_bound(sum - k);
                    if (pos != ss.end()) {
                        ans = max(ans, sum - *pos);
                    }
                    ss.insert(sum);
                }
                
            }
        }
        return ans;
    }
};
```
[1]: https://leetcode.com/problems/max-sum-of-sub-matrix-no-larger-than-k
