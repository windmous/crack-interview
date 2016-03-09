题目链接: [43.Multiply Strings][1]
难度: Medium

- 大整数乘法
- 有两个Corner case要考虑，第一是答案有leading 0时，第二是答案为0时

# 借助vector暂存结果 12ms

模拟小学数学教的整数乘法的操作，index解释详见[此处][2]
```cpp
class Solution {
public:
    string multiply(string num1, string num2) {
        int m = num1.length(), n = num2.length();
        vector<int> pos(m + n);
        
        for (int i = m - 1; i >= 0; --i) {
            for (int j = n - 1; j >= 0; --j) {
                int mul = (num1[i] - '0') * (num2[j] - '0');
                int p1 = i + j, p2 = i + j + 1;
                int sum = mul + pos[p2];
                
                pos[p1] += sum / 10;
                pos[p2] =  sum % 10;
            }
        }
        
        string ans;
        for (int i = 0; i < pos.size(); ++i) {
            if (ans == "" && pos[i] == 0)  // 防止pos为{0,0,0,1}造成输出“0001”的答案
                continue;
            ans.append(to_string(pos[i])); 
        }
        return ans == "" ? "0" : ans; // 考虑答案为0的情况
    }
};
```

# 直接在string上操作 8ms 

和上面的想法是一样的

```cpp
string multiply(string num1, string num2) {
    string sum(num1.size() + num2.size(), '0');

    for (int i = num1.size() - 1; 0 <= i; --i) {
        int carry = 0;
        for (int j = num2.size() - 1; 0 <= j; --j) {
            int tmp = (sum[i + j + 1] - '0') + (num1[i] - '0') * (num2[j] - '0') + carry;
            sum[i + j + 1] = tmp % 10 + '0';
            carry = tmp / 10;
        }
        sum[i] += carry;
    }

    size_t startpos = sum.find_first_not_of("0");
    if (string::npos != startpos) {
        return sum.substr(startpos);
    }
    return "0";
}
```

[1]: https://leetcode.com/problems/multiply-strings/
[2]: https://leetcode.com/discuss/71593/easiest-java-solution-with-graph-explanation