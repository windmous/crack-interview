题目链接: [289.Game of Life][1]
难度: Medium

描述：给一个m\*n的格子，每个格子有0、1两种状态。格子上的状态按照下面的规则变化：
```
若当前格子状态是1，那么
1) 若周围状态为1的元素少于2个，那么当前格子状态也变为0.
2) 若周围状态为1的元素为2个或者3个，那么当前格子状态不变。
3) 若周围状态为1的元素多余3个，那么当前格子状态变为0.

若当前格子状态是0，那么
4) 若周围状态为1的元素个数为3个，那么当前格子状态变为1.
```
要求：必须直接在输入数组上修改。

# 高位记录法(0ms)
时间复杂度：O(MN)
空间复杂度：O(1)

```cpp
class Solution {
public:
    void gameOfLife(vector<vector<int>>& board) {
        int m = board.size(), n = m ? board[0].size() : 0;
        for (int i=0; i<m; ++i) {
            for (int j=0; j<n; ++j) {
                int cnt = -board[i][j];
                for (int ni=max(i-1, 0); ni<min(i+2, m); ++ni)
                    for (int nj=max(j-1, 0); nj<min(j+2, n); ++nj)
                        cnt += board[ni][nj] & 1;
                
                if ((cnt | board[i][j]) == 3)
                    board[i][j] |= 2; // 设置alive位
            }
        }
        for (int i=0; i<m; ++i)
            for (int j=0; j<n; ++j)
                board[i][j] >>= 1;
    }
};
```

# 高位计数法(3ms)
时间复杂度：O(MN)
空间复杂度：O(1)

我们利用第2位及以上的bit来统计周围出现1的元素个数。那么假设当前处理的元素是'@'，那么我们通知那些X元素，将自己的值（0或1）传递给它们。而与此同时，那些'O'其实都已经被访问过了，他们的值已经传递到了当前的'@'位置，故而'@'的状态已经计算完成了。

```
O O O 
O @ X
X X X
```

```cpp
class Solution {
public:
    void gameOfLife(vector<vector<int>>& board) {
        if(board.empty()) return;
        const int m = board.size();
        const int n = board[0].size();
        for(int i=0; i<m; i++) {
            for(int j=0; j<n; j++) {
                check(board,i,j,i+1,j-1);
                check(board,i,j,i+1,j);
                check(board,i,j,i+1,j+1);
                check(board,i,j,i,j+1);

                // 周围是1的元素个数为2或者3
                if(board[i][j]>=5 && board[i][j]<=7) board[i][j]=1;
                else board[i][j]=0;
            }
        }
    }
private:
    void check(vector<vector<int>>& board, int i, int j, int a, int b) {
        const int m = board.size();
        const int n = board[0].size();
        if(a>=m || b<0 || b>=n) return;
        if(board[i][j]%2!=0) board[a][b]+=2;
        if(board[a][b]%2!=0) board[i][j]+=2;
    } 
};
```

# 关于Follow-up
Follow-up中提到，目前题目操纵的数组board是一个有限的M\*N数组。假设数组是无限的则应如何处理？如果开始时边缘有许多1，那么边缘外的元素也会渐渐出现一些1的。

老实说这个follow-up是什么意思木怎么看懂，先暂时信任[这里][2]的解释。由于无限大的board是没法表示的，所以我们将所有值为1的元素的坐标放到一个集合中，然后求一轮迭代后值为1的元素的坐标：

```python
def gameOfLifeInfinite(self, live):
	# live是个集合，元素类型是二元组，为一个坐标
    ctr = collections.Counter((I, J)
                              for i, j in live
                              for I in range(i-1, i+2)
                              for J in range(j-1, j+2)
                              if I != i or J != j)
    # 只有周围值为1的元素的个数为2或者3值才为1
    return {ij
            for ij in ctr
            if ctr[ij] == 3 or ctr[ij] == 2 and ij in live}
```

上面的代码可以写成下面的格式以便不熟悉python者理解：
```python
def gameOfLifeInfinite(self, live):
    neighbors = collections.Counter()
    for i, j in live:
        for I in (i-1, i, i+1):
            for J in (j-1, j, j+1):
                if I != i or J != j:
                    neighbors[I, J] += 1
    new_live = set()
    for ij in neighbors.keys():
        if neighbors[ij] == 3 or neighbors[ij] == 2 and ij in live:
            new_live.add(ij)
    return new_live
```

# 打表法(0ms)
时间复杂度：O(MN)
空间复杂度：O(Min(M, N))

本方法使用额外的一行（或者一列）来记录信息，适合输入是bool类型的情况。

```cpp
class Solution {
public:
    struct Fb {
        vector<vector<int>>& board;
        vector<int> frontier;
        // 缓存了哪一行
        int fpos;
        
        Fb(vector<vector<int>>& b) : board(b), frontier(board[0]), fpos(-1) {}
        int at(int i, int j) {
            // 代理访问第i,j位置的元素。如果i是当前正被缓存的行，那么
            // 返回缓存的数据。否则从board直接返回
            if (j < 0 || j >= frontier.size())
                return 0;
            if (i < 0 || i >= board.size())
                return 0;
            if (i == fpos) {
                return frontier[j];
            }
            return board[i][j];
        }
        void push(vector<int>& nf) {
            fpos++;
            if (fpos < board.size())
                frontier = board[fpos]; // 缓存该行
            if (fpos >= 0)
                swap(board[fpos], nf); // 将实际值更新到board
        }
    };
    void gameOfLife(vector<vector<int>>& board) {
        // Fb的作用是缓存第i-1行原始数据。因为处理第i行的时候实际上
        // 第n-i行已经被更新了。
        Fb fb(board);
        vector<int> newline(board[0].size(), 0);
        for (int i = 0; i < board.size(); ++i) {
            for (int j = 0; j < board[i].size(); ++j) {
                int cnt = 0;
                for (int ni = i-1; ni <= i+1; ++ ni)
                    for (int nj = j-1; nj <= j+1; ++ nj)
                        if (ni != i && nj != j) cnt += board[ni][nj];

                newline[j] = (cnt == 2 && fb.at(i,j)) || cnt == 3;
            }
            fb.push(newline);
        }
    }
};
```




[1]: https://leetcode.com/problems/game-of-life/
[2]: https://leetcode.com/discuss/62185/infinite-board-solution