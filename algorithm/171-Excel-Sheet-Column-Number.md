题目链接: [171.Excel Sheet Column Number][1]
难度: Easy

描述：给定一个字符串，按下述规则转换：
```
A -> 1
B -> 2
C -> 3
...
Z -> 26
AA -> 27
AB -> 28 
```

# 模拟(12ms)
时间复杂度：O(N)
空间复杂度：O(1)

```cpp
class Solution {
public:
    int titleToNumber(string s) {
        int ans = 0;
        for (const char c : s) {
            ans = ans * 26 + (c - 'A' + 1);
        }
        return ans;
    }
};
```


[1]: https://leetcode.com/problems/excel-sheet-column-number/