题目链接: [44.Wildcard Matching][1]
难度: Hard

- 匹配字符串与pattern，pattern中除字符外可包含`?`（匹配一个字符）与`*`（匹配多个字符）
- 与10. regular expression matching不同之处在于正则表达式中的`*`是其前面字符出现多次的意思，这里的`*`表示匹配任意个字符

# O(length(string) * length(pattern)) 时间，O(1)空间，16 ms

```cpp
class Solution {
public:
    bool isMatch(string s, string p) {
        // next_start记录匹配失败后应该回溯到哪个位置开始
        int star = -1, next_start;
        int i = 0, j = 0;
        while (i < s.size()) {
            if (p[j] == '?' || s[i] == p[j]) {
                i ++;   // 常规匹配
                j ++;
            } else if (p[j] == '*') {
                star = j ++;
                // 下次应该让*吞掉一个字符
                next_start = i + 1; 
            } else if (star >= 0) { // 匹配失败，回溯
                // 下次要让*吞掉更多字符
                i = next_start ++;
                j = star + 1;
            } else {
                return false;
            }
        }
        
        while (p[j] == '*') ++ j;
        return j == p.size();
    }
};
```

# 动态规划 256 ms

我的解法，时间O（length(string) * length(pattern)，空间O（length(string)），虽然下面的实现是O（length(string) * length(pattern）

```cpp
class Solution {
public:
	bool isMatch(string s, string p) {
		if (p == "" && s != "")
			return false;

		int width = s.length();
		int height = p.length();

		bool** mat = new bool*[height + 1]; // 换成vector<vector<bool>>会超时
		for (int i = 0; i <= height; ++i) {
			mat[i] = new bool[width + 1];
		}

		// init first line
		mat[0][0] = true;
		for (int i = 1; i <= width; ++i)
			mat[0][i] = false;

		for (int i = 1; i <= height; ++i) {
			if (p[i - 1] == '*') {
				bool flag = mat[i - 1][0];
				mat[i][0] = mat[i - 1][0];
				for (int j = 1; j <= width; ++j) {
					flag |= mat[i - 1][j];
					mat[i][j] = flag;
				}
			}
			else if (p[i - 1] == '?') {
				mat[i][0] = false;
				for (int j = 1; j <= width; ++j)
					mat[i][j] = mat[i - 1][j - 1];
			}
			else {
				mat[i][0] = false;
				for (int j = 1; j <= width; ++j) {
					if (p[i - 1] == s[j - 1])
						mat[i][j] = mat[i - 1][j - 1];
					else
						mat[i][j] = false;
				}
			}
		}
		// TODO 释放资源
		return mat[height][width];
	}
};
```

# 递归 （超时）

从10. regular expression matching迁移过来的代码惨遭TLE

```cpp
class Solution {
public:
	bool isMatch(string s, string p) {
		return isMatch(s.c_str(), p.c_str());
	}

private:
	bool isMatch(const char* s, const char* p) {
		if (p[0] == '\0') return s[0] == '\0';

		// pattern is not empty
		if (p[0] == '*') {
			while (*p == '*') ++p;
			return (s[0] != '\0' && isMatch(s + 1, p - 1)) || isMatch(s, p);
		}
		else {
			return s[0] != '\0' && (p[0] == '?' || s[0] == p[0]) && isMatch(s + 1, p + 1);
		}
	}
};

```



[1]: https://leetcode.com/problems/wildcard-matching/