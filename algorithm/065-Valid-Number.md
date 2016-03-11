题目链接: [65.Valid Number][1]
难度: Hard

判断一个string是否为valid number（实数），题目没有说明valid  number的标准，所以做起来很蛋疼。


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