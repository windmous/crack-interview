题目链接: [17.Letter Combinations of a Phone Number][1]
难度: Medium

- 将一串电话号码转为手机按键对应的所有可能字符串
- dfs递归很容易，但要提高效率就得考虑递归展开

# 递归展开
时间O(3^N)

0ms
```cpp
vector<string> letterCombinations(string digits) {
    vector<string> result;
    if(digits.empty()) return vector<string>();
    static const vector<string> v = {"", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
    result.push_back("");   // add a seed for the initial case
    for(int i = 0 ; i < digits.size(); ++i) {
        int num = digits[i]-'0';
        if(num < 0 || num > 9) break;
        const string& candidate = v[num];
        if(candidate.empty()) continue;
        vector<string> tmp;
        for(int j = 0 ; j < candidate.size() ; ++j) {
            for(int k = 0 ; k < result.size() ; ++k) {
                tmp.push_back(result[k] + candidate[j]);
            }
        }
        result.swap(tmp); // swap提高了效率
    }
    return result;
}
```

[1]: https://leetcode.com/problems/letter-combinations-of-a-phone-number/