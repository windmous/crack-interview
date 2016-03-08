题目链接: [273.Integer to English Words][1]
难度: Medium

描述：给定一个整数，给出该整数的英语发音。比如给123，你应该输出"One Hundred Twenty Tree"

# 模拟1-递归(8ms)
时间复杂度：O(logN)
空间复杂度：O(logN)

下面的代码虽说是递归，但是可以保证每次递归深度只有大约4层。

```cpp
class Solution {
 public:
    string digits[20] = {"Zero", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen"};
    string tens[10] = {"Zero", "Ten", "Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety"};

    string int2string(int n) {
        if (n >= 1000000000) {
            return int2string(n / 1000000000) + " Billion" + int2string(n % 1000000000);
        } else if (n >= 1000000) {
            return int2string(n / 1000000) + " Million" + int2string(n % 1000000);
        } else if (n >= 1000) {
            return int2string(n / 1000) + " Thousand" + int2string(n % 1000);
        } else if (n >= 100) { // 仅100以下时才输出
            return int2string(n / 100) + " Hundred" + int2string(n % 100);
        } else if (n >= 20) {
            return  " " + tens[n / 10] + int2string(n % 10);
        } else if (n >= 1) {
            return " " + digits[n];
        } else {
        	// 输入为0
            return "";
        }
    }

    string numberToWords(int num) {
        if (num == 0) {
            return "Zero";
        } else {
            string ret = int2string(num);
            return ret.substr(1, ret.length() - 1);
        }
    }
};
```

# 模拟2-非递归(4ms)
时间复杂度：O(N)
空间复杂度：O(1)

分成千、百万、十亿等几个部分，分别求解。

```cpp
class Solution {
    string helper(int num){
        const static char* less_ten[] =
        { "", " One", " Two", " Three", " Four", " Five", " Six", " Seven", " Eight", " Nine" };
        const static char* less_twenty[] =
        { " Ten", " Eleven", " Twelve", " Thirteen", " Fourteen", " Fifteen", " Sixteen", " Seventeen", " Eighteen", " Nineteen" };
        const static char* less_hundred[] =
        { "", "", " Twenty", " Thirty", " Forty", " Fifty", " Sixty", " Seventy", " Eighty", " Ninety" };
    
        string s;
        if (num != 0){
            //get hundredth, tenth, and single digit
            int hundred = num / 100;
            num %= 100; 
            int tenth = num / 10; 
            int single = num % 10; 
    
    		// 下面这块一定要缜密一些
            if (hundred) s = s + less_ten[hundred] + " Hundred";
    
            if (tenth){
                if (tenth == 1){ //special handling, choose from less_twenty based on value of single
                    s += less_twenty[single];
                    return s;
                }
                else  s += less_hundred[tenth];
            }
            if (single) s += less_ten[single];
        }
        return s;
    }
    
public:
    string numberToWords(int num) {
        const static char* unit[] = 
            { "", " Thousand", " Million", " Billion" };
        int parts[4] = {0};
        for(int i  = 0; i < 4; ++i){
            parts[i] = num % 1000;
            num /= 1000; 
        }

        string s; 
        for(int i = 0; i < 4; ++i){
            if(parts[i] == 0) continue; 
            s = helper(parts[i]) + unit[i] + s;  
        }
        s = s.size() ? s.substr(1) : "Zero";
        return s;
    }
};
```

[1]: https://leetcode.com/problems/integer-to-english-words/