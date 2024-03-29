题目链接: [59.Spiral Matrix II][1]
难度: Medium

给数字n，要求将1~n^2螺旋形地填入矩阵中。

逆问题见P54

# 简洁写法(4ms)

写入的轨迹总是正方形，所以不可能出现一个横条或者一个竖条的情况，故而第3个和第4个循环那里不用加判断。

```cpp
class Solution {
public:
    vector<vector<int>> generateMatrix(int n) {
        vector<vector<int>> result(n, vector<int>(n));
        
        for (int i = 0, no = 1; no <= n*n; ++ i) {
            for (int j = i; j < n-i; ++ j) {
                result[i][j] = no ++;
            }
            
            for (int j = i + 1; j < n - i; ++ j) {
                result[j][n-i-1] = no ++;
            }
            
            for (int j = n-i-2; j >= i; -- j) {
                result[n-i-1][j] = no ++;
            }
            
            for (int j = n-i-2; j >= i+1; -- j) {
                result[j][i] = no ++;
            }
        }
        
        return result;
    }
};
```

# Archive
```cpp
class Solution {
    public:
        vector<vector<int> > generateMatrix(int n) {
            vector<vector<int> > ret( n, vector<int>(n) );
            int k = 1, i = 0;
            while( k <= n * n )
            {
                int j = i;
                    // four steps
                while( j < n - i )             // 1. horizonal, left to right
                    ret[i][j++] = k++;
                j = i + 1;
                while( j < n - i )             // 2. vertical, top to bottom
                    ret[j++][n-i-1] = k++;
                j = n - i - 2;
                while( j > i )                  // 3. horizonal, right to left 
                    ret[n-i-1][j--] = k++;
                j = n - i - 1;
                while( j > i )                  // 4. vertical, bottom to  top 
                    ret[j--][i] = k++;
                i++;      // next loop
            }
            return ret;
        }
    };
```

[1]: https://leetcode.com/problems/spiral-matrix-ii/