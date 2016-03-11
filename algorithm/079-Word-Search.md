题目链接: [79.Word Search][1]
难度: Medium

- 在matrix中看看能否一笔画找到某个单词，笔画不能重叠

# dfs
```cpp
class Solution {
public:
	bool exist(vector<vector<char> > &board, string word) {
		m=board.size();
		n=board[0].size();
		for(int x=0;x<m;x++)
			for(int y=0;y<n;y++)
			{
				if(isFound(board,word.c_str(),x,y))
					return true;
			}
		return false;
	}
private:
	int m;
	int n;
	bool isFound(vector<vector<char> > &board, const char* w, int x, int y)
	{
		if(x<0||y<0||x>=m||y>=n||board[x][y]=='\0'||*w!=board[x][y])
			return false;
		if(*(w+1)=='\0')
			return true;
		char t=board[x][y];
		board[x][y]='\0';   // 修改此处
		if(isFound(board,w+1,x-1,y)||isFound(board,w+1,x+1,y)||isFound(board,w+1,x,y-1)||isFound(board,w+1,x,y+1))
			return true;    // 上下左右都找过去
		board[x][y]=t;		// 还原此处
		return false;
	}
};
```
[1]: https://leetcode.com/problems/word-search/