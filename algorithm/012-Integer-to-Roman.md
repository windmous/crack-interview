题目链接: [12.Integer to Roman][1]
难度: Medium

- 整数(1<= n <= 3999)转为罗马数字
- I（1）V（5）X（10）L（50）C（100）D（500）M（1000） 

44ms

```cpp
class Solution {
public:
    string intToRoman(int num) {
        string M[] = {"", "M", "MM", "MMM"};
        string C[] = {"", "C", "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM"};
        string X[] = {"", "X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC"};
        string I[] = {"", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX"};
        return M[num/1000] + C[(num%1000)/100] + X[(num%100)/10] + I[num%10];
    }
};
```

[1]: https://leetcode.com/problems/integer-to-roman/