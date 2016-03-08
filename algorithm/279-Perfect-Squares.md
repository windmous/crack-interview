题目链接: [279.Perfect Squares][1]
难度: Medium

描述：给定一个整数n，求最少可以用多少个平方数相加得到该整数。

# 动态规划(440ms)
时间复杂度：O(NlogN)
空间复杂度：O(N)
```cpp
class Solution 
{
public:
    int numSquares(int n) 
    {
        if (n <= 0) 
            return 0;
            
        // cntPerfectSquares[i] = the least number of perfect square numbers 
        // which sum to i. Note that cntPerfectSquares[0] is 0.
        vector<int> cntPerfectSquares(n + 1, INT_MAX);
        cntPerfectSquares[0] = 0;
        for (int i = 1; i <= n; i++) {
            // For each i, it must be the sum of some number (i - j*j) and 
            // a perfect square number (j*j).
            for (int j = 1; j*j <= i; j++) {
                cntPerfectSquares[i] = 
                    min(cntPerfectSquares[i], cntPerfectSquares[i - j*j] + 1);
            }
        }

        return cntPerfectSquares.back();
    }
};
```

# BFS(80ms)
时间复杂度：O(N)
空间复杂度：O(N) ? 

```cpp
class Solution 
{
public:
    int numSquares(int n) 
    {
        if (n <= 0)
        {
            return 0;
        }

        vector<int> squares;
        // vis负责记录第n个节点
        vector<int> vis(n);
        
        // 生成所有基础平方数，它们只需要1个值
        for (int i = 1; i*i <= n; i++) {
            squares.push_back(i*i);
            vis[i*i - 1] = 1;
        }

        // If n is a perfect square number, return 1 immediately.
        if (squares.back() == n) {
            return 1;
        }

        // 隐式图搜索，节点i到j有边当且仅当i+k=j，其中k为某个平方数
        queue<int> q;
        for_each(squares.begin(), squares.end(), [&q](int x) {q.push(x);});

        int level = 1; // 当前访问的层数
        while (!q.empty()) {
            level ++;
            int searchQSize = q.size();
            for (int i = 0; i < searchQSize; i++)
            {
                int tmp = q.front();
                for (auto& j : squares)
                {
                    if (tmp + j == n) {
                        // We have reached node n.
                        return level;
                    } else if ((tmp + j < n) && (vis[tmp + j - 1] == 0)) {
                        vis[tmp + j - 1] = level;
                        q.push(tmp + j);
                    } else if (tmp + j > n) {
                        // We don't need to consider the nodes which are greater ]
                        // than n.
                        break;
                    }
                }

                q.pop();
            }
        }

        return 0;
    }
};
```

# 数学法(4ms)
时间复杂度：O(logN)
空间复杂度：O(1)


简直是黑科技好嘛！详情见注释吧。

```cpp
class Solution 
{  
private:  
    int is_square(int n)
    {  
        int sqrt_n = (int)(sqrt(n));  
        return (sqrt_n*sqrt_n == n);  
    }

public:
    // Based on Lagrange's Four Square theorem, there 
    // are only 4 possible results: 1, 2, 3, 4.
    int numSquares(int n) 
    {  
        // If n is a perfect square, return 1.
        if(is_square(n)) {
            return 1;  
        }

        // The result is 4 if and only if n can be written in the 
        // form of 4^k*(8*m + 7). Please refer to 
        // Legendre's three-square theorem.
        while ((n & 3) == 0) { // n%4 == 0  
            n >>= 2;  
        }
        if ((n & 7) == 7) {// n%8 == 7
            return 4;
        }

        // Check whether 2 is the result.
        int sqrt_n = (int)(sqrt(n)); 
        for(int i = 1; i <= sqrt_n; i++) {  
            if (is_square(n - i*i)) {
                return 2;  
            }
        }  

        return 3;  
    }  
}; 
```

[1]: https://leetcode.com/problems/perfect-squares/