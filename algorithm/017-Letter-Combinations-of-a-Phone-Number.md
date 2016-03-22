题目链接: [17.Letter Combinations of a Phone Number][1]
难度: Medium

- 将一串电话号码转为手机按键对应的所有可能字符串
- dfs递归很容易，但要提高效率就得考虑递归展开

# 迭代（非递归）(0ms)
时间O(3^N)

```cpp
class Solution {
public:
    vector<string> letterCombinations(string digits) {
        static const vector<string> v = {"", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
        
        vector<string> result;
        for (const char c : digits) {
            if (!isdigit(c)) break;
            
            string candidate = v[c-'0'];
            vector<string> tmp;
            
            if (result.empty()) {
                transform(candidate.begin(), candidate.end(), back_inserter(tmp),
                                [](char c) {return string(1, c);});
            } else {
                for (const string &str : result) {
                    transform(candidate.begin(), candidate.end(), back_inserter(tmp),
                                [&str](char c) {return str + c;});
                }
            }
            
            swap(tmp, result);
        }
        
        return result;
    }
};
```

[1]: https://leetcode.com/problems/letter-combinations-of-a-phone-number/