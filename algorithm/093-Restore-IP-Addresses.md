题目链接: [93.Restore IP Addresses][1]
难度: Medium

Given "25525511135", return ["255.255.11.135", "255.255.111.35"]
返回所有可能的IP划分

```cpp
class Solution {
public:
    vector<string> restoreIpAddresses(string s) {
        vector<string> res;
        int len = s.length();
        for (int i = 1; i < 4 && i < len - 2; ++i) {
            for (int j = i + 1; j < i + 4 && j < len - 1; ++j) {
                for (int k = j + 1; k < j + 4 && k < len; ++k) {
                    string s1 = s.substr(0, i), s2 = s.substr(i, j - i), s3 = s.substr(j, k - j), s4 = s.substr(k, len - k);
                    if (isValid(s1) && isValid(s2) && isValid(s3) && isValid(s4)) {
                        res.push_back(s1+"."+s2+"."+s3+"."+s4);
                    }
                }
            }
        }
        return res;
    }
    
private:
    bool isValid(string& s) {                    // 允许“0”，但不允许“01”等leading 0形式存在
        if (s.length() > 3 || s.length() == 0 || (s[0] == '0' && s.length() > 1) || stoi(s) > 255) 
            return false;
        return true;
    }
};
```

[1]: https://leetcode.com/problems/restore-ip-addresses/