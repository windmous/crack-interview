题目链接: [415.Add Strings][1]
难度: Easy

大整数相加

# Naive方法
时间复杂度：O(N)
空间复杂度：O(N)

```cpp
class Solution {
public:
    string addStrings(string num1, string num2) {
        const int len1 = num1.size(), len2 = num2.size();
        string result(max(len1, len2) + 1, '0');
        int p1 = len1-1, p2 = len2-1, i = result.size()-1;
        
        int carry = 0;
        while (p1 >= 0 || p2 >= 0) {
            int sum = carry;
            if (p1 >= 0) sum += num1[p1--] - '0';
            if (p2 >= 0) sum += num2[p2--] - '0';
            carry = sum / 10;
            result[i --] = sum % 10 + '0';
        }
        
        if (carry) result[0] = carry+'0';
        else result.erase(result.begin());
        return result;
    }
};
```

# 无额外空间法
时间复杂度：O(N)
空间复杂度：O(1)

```cpp
class Solution {
public:
    string addStrings(string num1, string num2) {
        const int len1 = num1.size(), len2 = num2.size();
        if (len1 > len2) return addStrings(num2, num1);
        
        int p1 = len1 - 1, p2 = len2 - 1;
        int carry = 0;
        while (p2 >= 0 && (carry || p1 >= 0)) {
            int sum = carry + (p1 >= 0 ? num1[p1--] - '0':0) + num2[p2] - '0';
            num2[p2--] = sum % 10 + '0';
            carry = sum / 10;
        }
        if (carry) num2.insert(num2.begin(), '0'+carry);
        return num2;
    }
};
```

[1]: https://leetcode.com/problems/add-strings
