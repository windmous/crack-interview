题目链接: [174.Dungeon Game][1]
难度: Hard

描述：给定一个网格，每个网格有一些正数或者负数。你要从左上角走到右下角。注意智能只能向右或者向下走，每走到一个格子就把格子里的数值加上去。求：若要保持和始终大于0，开始时你的初始值至少是多少？

# 动态规划(12ms)
时间复杂度：O(MN)
空间复杂度：O(N)

令dp[i][j]表示从(i,j)出发所需要的最小初始值，则dp[i][j] = max(1, min(dp[i+1][j], dp[i][j+1])-dungeon[i][j])。

```cpp
class Solution {
public:
    int calculateMinimumHP(vector<vector<int>>& dungeon) {
        const int n = dungeon.size(), m = dungeon[0].size();
        vector<int> dp(n+1,INT_MAX);
        dp[n-1]=1;
        
        for (int j = m-1;j >= 0; -- j){
            for (int i = n-1; i >= 0; -- i){
                dp[i] = max(1, min(dp[i], dp[i+1]) - dungeon[i][j]);
            }
        }
        return dp[0];
    }
};
```

# 动态规划(16ms)
时间复杂度：O(MN)
空间复杂度：O(1)

这里利用了输入数组，不需要额外辅助空间。

```cpp
class Solution {
public:
    int calculateMinimumHP(vector<vector<int>>& dungeon) {
        // 这里没有做m==0的检查，因为不知道怎么返回。
        const int m = dungeon.size() - 1;
        const int n = dungeon[0].size() - 1;
    
        dungeon[m][n] = dungeon[m][n]>0 ? 1 : 1-dungeon[m][n];
    
        for (int i = m; i >= 0; i--) {
            for (int j = n; j >= 0; j--) {
                if (i < m && j < n)
                    dungeon[i][j] = min(dungeon[i + 1][j], dungeon[i][j + 1]) - dungeon[i][j];
                else if (i < m)
                    dungeon[i][j] = dungeon[i + 1][j] - dungeon[i][j];
                else if (j < n)
                    dungeon[i][j] = dungeon[i][j + 1] - dungeon[i][j];
    
                dungeon[i][j] = max(1, dungeon[i][j]);// < 0 ? 1 : dungeon[i][j];
            }
        }
    
        return dungeon[0][0];// > 0 ? 1 : abs(dungeon[0][0]) + 1;
    }
};
```

# 为什么要从右下角向左上角动归？
If we start from left top, in addition to minimize initial HP required to get (i,j), we also have to maximize HP left when we get (i,j) in order to decide whether we need more initial HP in the next step. It doesn't directly depend on things at (i-1,j) and (i,j-1).

For example, at some point we have two paths, from left or from up.

```
Left: min HP required is 1, max HP left is 1
Up: min HP required is 5, max HP left is 100
```

How do we choose now? If we choose smaller min HP required, this requirement may increase to 5 later anyway and 95 HP is wasted.

I'd be happy to know if anyone can do this from left-top (not trying different initial HP values).
[1]: https://leetcode.com/problems/dungeon-game/