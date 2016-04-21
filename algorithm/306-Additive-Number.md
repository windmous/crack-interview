题目链接: [306.Additive Number][1]
难度: Medium

判断一个数字字符串是否能拆成一个数组，满足：

1. 数组至少有三个元素

2. 每个元素没有leading 0

3. 每个元素都是前两个元素之和


For example:
```
"112358" is an additive number because the digits can form an additive sequence: 1, 1, 2, 3, 5, 8.
1 + 1 = 2, 1 + 2 = 3, 2 + 3 = 5, 3 + 5 = 8

"199100199" is also an additive number, the additive sequence is: 1, 99, 100, 199.
1 + 99 = 100, 99 + 100 = 199
```


# dfs

```cpp
class Solution {
public:
	bool isAdditiveNumber(string num) {
		int len = num.size();
		if (len <= 2) return false;

		for (int beg2 = 1; beg2 < len - 1; ++beg2) {
			for (int end2 = beg2 + 1; end2 < len; ++end2) { // end2 can't be len，否则没有三个数
				if (match(num, 0, beg2, beg2, end2)) return true;
			}
		}
		return false;
	}

private:
	bool match(string& s, int beg1, int end1, int beg2, int end2) {
		// leading 0 check
		if (end1 - beg1 != 1 && s[beg1] == '0') return false;
		if (end2 - beg2 != 1 && s[beg2] == '0') return false;

		int len = s.size();
		if (end2 == len) return true;
		string ab = add(s, beg1, end1, beg2, end2);
		if (end2 + ab.size() > len) return false;
		for (int i = end2; i < end2 + ab.size(); ++i)
			if (s[i] != ab[i - end2]) return false;
		return match(s, beg2, end2, end2, end2 + ab.size());
	}

	string add(string& s, int beg1, int end1, int beg2, int end2) {
		string res;
		int carry = 0, len1 = end1 - beg1, len2 = end2 - beg2;

		for (int i = 0; i < len1 || i < len2; ++i) {
			carry += i >= len1 ? 0 : s[end1 - 1 - i] - '0';
			carry += i >= len2 ? 0 : s[end2 - 1 - i] - '0';
			res = to_string(carry % 10) + res;
			carry /= 10;
		}
		if (carry) res = to_string(carry) + res;
		return res;
	}
};
```

[1]: https://leetcode.com/problems/additive-number/