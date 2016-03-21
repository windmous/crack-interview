题目链接: [168.Excel Sheet Column Title][1]
难度: Easy

描述：按下面顺序准换进制：

```
1 -> A
2 -> B
3 -> C
...
26 -> Z
27 -> AA
28 -> AB 
```

# 进制转换(0ms)
时间复杂度：O(log_{26} N)
空间复杂度：O(1)
```
由于N = 26^0*(bit0-'A'+1) + 26^1*bit1*(bit1-'A'+1) + 26^2*bit2*(bit2-'A'+1) + ...
故而得到下面代码：
```
```cpp
class Solution {
public:
    string convertToTitle(int n) {
        string result;
        while (n) {
            -- n;
            result += n % 26 + 'A';
            n /= 26;
        }
        
        reverse(result.begin(), result.end());
        return result;
    }
};
```

# 查表法(0ms)
时间复杂度：O(log_{26} N)
空间复杂度：O(1)

主要是解决n%26的时候Z回映射到0的问题：
```cpp
class Solution {
public:
    string convertToTitle(int n) {
        string i2c = "ZABCDEFGHIJKLMNOPQRSTUVWXY";
        string res;
    
        while (n) {
            res += i2c[n % 26];
            n = (n-1) / 26;
        }
        
        reverse(res.begin(), res.end());
        return res;
    }
};
```

# 递归(0ms)
时间复杂度：O(log_{26} N)
空间复杂度：O(log_{26} N)

```cpp
class Solution {
public:
    string convertToTitle(int n) {
        return n == 0 ? "" : convertToTitle((n - 1) / 26) + (char) ((n - 1) % 26 + 'A');
    }
};
```
[1]: https://leetcode.com/problems/excel-sheet-column-title/