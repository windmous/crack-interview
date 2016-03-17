题目链接: [85.Maximal Rectangle][1]
难度: Hard

- 在只包含0和1的矩阵中，找到全为1的最大矩形

# 动态规划

https://leetcode.com/discuss/20240/share-my-dp-solution

维护left，right和height三个滚动数组，各自的意义与规则：
```
left(i,j) = max(left(i-1,j), curleft), curleft can be determined from the current row
right(i,j) = min(right(i-1,j), curright), curright can be determined from the current row
height(i,j) = height(i-1,j) + 1, if matrix[i][j]=='1';
height(i,j) = 0, if matrix[i][j]=='0'
```

假如matrix[i][j]为1，那么维护前，matrix[i][curleft 到 j]都为1，matrix[i][j 到 curright]都为1；
维护后，候选答案是（i, j）点最高height所能触及的最大矩形，故而left[i][j]到right[i][j]的点的1的高度都需要有height(i, j)那么高。
最大矩形的上边界肯定会成为某个点的最高点，因此一定会被扫描到。


实例：
If you think this algorithm is not easy to understand, you can try this example:

0 0 0 1 0 0 0 
0 0 1 1 1 0 0 
0 1 1 1 1 1 0
The vector "left" and "right" from row 0 to row 2 are as follows

row 0:

l: 0 0 0 3 0 0 0
r: 7 7 7 4 7 7 7

row 1:

l: 0 0 2 3 2 0 0
r: 7 7 5 4 5 7 7 

row 2:

l: 0 1 2 3 2 1 0
r: 7 6 5 4 5 6 7


```cpp
class Solution {
public:
    int maximalRectangle(vector<vector<char> > &matrix) {
        if (matrix.empty()) return 0;
        const int m = matrix.size();
        const int n = matrix[0].size();
        int left[n], right[n], height[n];
        fill_n(left, n, 0); fill_n(right, n, n); fill_n(height, n, 0);
        int maxA = 0;
        for (int i = 0; i < m; i++) {
            int cur_left = 0, cur_right = n;
            for (int j = 0; j < n; j++) { // compute height (can do this from either side)
                if (matrix[i][j] == '1') height[j]++;
                else height[j] = 0;
            }
            for (int j = 0; j < n; j++) { // compute left (from left to right)
                if (matrix[i][j] == '1') left[j] = max(left[j], cur_left);
                else { left[j] = 0; cur_left = j + 1; }
            }
            // compute right (from right to left)
            for (int j = n - 1; j >= 0; j--) {
                if (matrix[i][j] == '1') right[j] = min(right[j], cur_right);
                else { right[j] = n; cur_right = j; }
            }
            // compute the area of rectangle (can do this from either side)
            for (int j = 0; j < n; j++)
                maxA = max(maxA, (right[j] - left[j])*height[j]);
        }
        return maxA;
    }
}
```

# 转为P84，求直方图中最大矩形问题

```cpp
int maximalRectangle(vector<vector<char>>& matrix) {
	if (matrix.size() == 0 || matrix[0].size() == 0) 
		return 0;

	int height = matrix.size();
	int width = matrix[0].size();
	int answer = 0;

	vector<int> h;
	for (int i = 0; i < width; ++i) 
		h.push_back(matrix[0][i] - '1');

	answer = max(answer, largestRectangleArea(h)); // 调用P84
	for (int i = 1; i < height; ++i) {
		for (int j = 0; j < width; ++j) {
			if (matrix[i][j] == '1') 
				++h[j];
			else
				h[j] = 0;
		}
		answer = max(answer, largestRectangleArea(h)); // 调用P84
	}
	return answer;
}
```



[1]: https://leetcode.com/problems/maximal-rectangle/