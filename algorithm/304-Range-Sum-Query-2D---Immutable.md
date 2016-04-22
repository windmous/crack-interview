题目链接: [304.Range Sum Query 2D - Immutable][1]
难度: Medium

返回矩阵中某个子矩阵的元素之和。

```cpp
class NumMatrix {
public:
	NumMatrix(vector<vector<int>> &matrix) {
		if (matrix.size() == 0 || matrix[0].size() == 0) return;
		int h = matrix.size(), w = matrix[0].size();

		accum = vector<vector<int>>(h + 1, vector<int>(w + 1, 0));
		for (int i = 0; i < h; ++i) {
			int ac = 0;
			for (int j = 0; j < w; ++j) {
				ac += matrix[i][j];
				accum[i + 1][j + 1] = accum[i][j + 1] + ac;
			}
		}
	}

	int sumRegion(int row1, int col1, int row2, int col2) {
		return accum[row2 + 1][col2 + 1] - accum[row2 + 1][col1] - accum[row1][col2 + 1] + accum[row1][col1];
	}
private:
	vector<vector<int> > accum;
};

```
[1]: https://leetcode.com/problems/range-sum-query-2d-immutable/