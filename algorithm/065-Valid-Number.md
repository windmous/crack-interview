题目链接: [65.Valid Number][1]
难度: Hard

判断一个string是否为valid number（实数），题目没有说明valid  number的标准，所以做起来很蛋疼。

# DFA(8ms)

```cpp
class Solution {
public:
    bool isNumber(string s) {
        int i = 0;

        // skip the whilespaces
        while (s[i] == ' ') i ++;
    
        // check the significand
        if (s[i] == '+' || s[i] == '-') i++; // skip the sign if exist
    
        int n_nm, n_pt;
        for(n_nm = 0, n_pt = 0; isdigit(s[i]) || s[i]=='.'; i++)
            s[i] == '.' ? n_pt++:n_nm++;
            
        if (n_pt > 1 || n_nm < 1) // no more than one point, at least one digit
            return false;
    
        // check the exponent if exist
        if(s[i] == 'e') {
            i++;
            if(s[i] == '+' || s[i] == '-') i++; // skip the sign
    
            int n_nm = 0;
            while (isdigit(s[i])) {
                ++ n_nm;
                ++ i;
            }
            
            if(n_nm < 1)
                return false;
        }

        // the remaining string must all be blanks   
        return find_if(s.begin()+i, s.end(), [](char x){return x != ' ';}) == s.end();
    }
};
```

# 正则表达式

leetcode不支持cpp的正则表达式，VS13中编译通过

```cpp
class Solution {
public:
	bool isNumber(string s) {
		std::regex r(R"dd( *(\+|-)?(\d+(\.\d*)?|\.\d+)(e(\+|-)?\d+)? *)dd", std::regex::icase);
		std::smatch base_match;
		return regex_match(s, base_match, r);
	}
};
```

# 构造DFA

由于规则不明，此处略去

[1]: https://leetcode.com/problems/valid-number/