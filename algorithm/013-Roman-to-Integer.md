题目链接: [13.Roman to Integer][1]
难度: Easy

- 罗马数字转为整数(1<= n <= 3999)
- I（1）V（5）X（10）L（50）C（100）D（500）M（1000） 
- 位于大数的后面时就作为加数；位于大数的前面就作为减数

40ms
```cpp
class Solution {
public:
    int romanToInt(string s) {
        int a[26];
        a[0] = 0; 
        a['I' - 'A'] = 1;
        a['V' - 'A'] = 5;
        a['X' - 'A'] = 10;
        a['L' - 'A'] = 50;
        a['C' - 'A'] = 100;
        a['D' - 'A'] = 500;
        a['M' - 'A'] = 1000;
        
        char prev = 'A';
        int res = 0;
        for (auto c : s) {
            res += a[c - 'A'];
            if (a[prev - 'A'] < a[c - 'A']) 
                res -= a[prev - 'A'] * 2;   // 位于大数的前面，减两次是因为之前加过一次
            prev = c;
        }
        return res;
    }
};
```

[1]: https://leetcode.com/problems/roman-to-integer/