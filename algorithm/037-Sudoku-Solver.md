题目链接: [37.Sudoku Solver][1]
难度: Hard

- 得到数独的一个解

# 暴力求解 96ms

```cpp
class Solution {
public:
	bool solveSudoku(vector<vector<char> > &board) {
		for (int i = 0; i < 9; ++i)
			for (int j = 0; j < 9; ++j) {
				if (board[i][j] == '.') {
					for (int k = 0; k < 9; ++k) {
						board[i][j] = '1' + k;
						if (isValid(board, i, j) && solveSudoku(board))
							return true;
						board[i][j] = '.';
					}
					return false;
				}
			}
		return true;
	}
private:
	// 检查(x, y)是否合法
	bool isValid(const vector<vector<char> > &board, int x, int y) {
		int i, j;
		for (i = 0; i < 9; i++) // 检查y列
			if (i != x && board[i][y] == board[x][y])
				return false;
		for (j = 0; j < 9; j++) // 检查x行
			if (j != y && board[x][j] == board[x][y])
				return false;
		for (i = 3 * (x / 3); i < 3 * (x / 3 + 1); i++)
			for (j = 3 * (y / 3); j < 3 * (y / 3 + 1); j++)
				if ((i != x || j != y) && board[i][j] == board[x][y])
					return false;
		return true;
	}
};
```

# 递归 44ms
```cpp
class Solution {
public:
	bool check(vector<vector<char>> &board, int i, int j, char val)
	{
		int row = i - i%3, column = j - j%3;
		for(int x=0; x<9; x++) if(board[x][j] == val) return false;
		for(int y=0; y<9; y++) if(board[i][y] == val) return false;
		for(int x=0; x<3; x++)
		for(int y=0; y<3; y++)
			if(board[row+x][column+y] == val) return false;
		return true;
	}
	
	bool solveSudoku(vector<vector<char>> &board, int i, int j)
	{
		if(i==9) return true;
		if(j==9) return solveSudoku(board, i+1, 0);
		if(board[i][j] != '.') return solveSudoku(board, i, j+1);

		for(char c='1'; c<='9'; c++)
		{
			if(check(board, i, j, c))
			{
				board[i][j] = c;
				if(solveSudoku(board, i, j+1)) return true;
				board[i][j] = '.';
			}
		}

		return false;
	}

    void solveSudoku(vector<vector<char>>& board) {
        solveSudoku(board, 0, 0);
    }
};
```

[1]: https://leetcode.com/problems/sudoku-solver/