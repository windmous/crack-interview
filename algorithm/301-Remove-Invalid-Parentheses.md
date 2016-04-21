题目链接: [301.Remove Invalid Parentheses][1]
难度: Hard

给一个字符串，消除串中若干左右括号，使剩余字符串括号合理。要求返回消除最少括号的所有字符串。

```
"()())()" -> ["()()()", "(())()"]
"(a)())()" -> ["(a)()()", "(a())()"]
")(" -> [""]
```


# dfs 9ms

第一轮找出必须消除的左右括号数目，记为rml和rmr
```
"()())()"
()()   )   ()
       ^
	   rml
```

随后调用dfs，碰到左右括号时，尝试保留或者删除之。变量open存的是待close的左括号数目。

用set存放答案是有必要的，因为dfs结果可能有重复答案。

https://leetcode.com/discuss/72208/easiest-9ms-java-solution

```cpp
class Solution {
public:
    vector<string> removeInvalidParentheses(string s) {
        int rml = 0, rmr = 0;
        for (int i = 0; i < s.length(); ++i) {
            if (s[i] == '(') ++rml;
            if (s[i] == ')') {
                if (rml > 0) --rml;
                else ++rmr;
            }
        }
        
        vector<char> path;
        unordered_set<string> set_ans;
        dfs(0, rml, rmr, 0, s, path, set_ans);
        
        return vector<string>(set_ans.begin(), set_ans.end());
    }
    
private:
    void dfs(int idx, int rml, int rmr, int open, string& s, vector<char>& path, unordered_set<string>& set_ans) {
        if (idx == s.length()) {
            if (rml == 0 && rmr == 0 && open == 0) set_ans.insert(string(path.begin(), path.end()));
            return;
        }
        
        if (s[idx] == '(') {
            // keep
            path.push_back(s[idx]);
            dfs(idx + 1, rml, rmr, open + 1, s, path, set_ans);
            path.pop_back();
            
            // remove
            if (rml > 0) dfs(idx + 1, rml - 1, rmr, open, s, path, set_ans);
        }
        else if (s[idx] == ')') {
            // keep 
            if (open > 0) {
                path.push_back(s[idx]);
                dfs(idx + 1, rml, rmr, open - 1, s, path, set_ans);
                path.pop_back();
            }
            
            // remove
            if (rmr > 0) dfs(idx + 1, rml, rmr - 1, open, s, path, set_ans);
        }
        else {
            path.push_back(s[idx]);
            dfs(idx + 1, rml, rmr, open, s, path, set_ans);
            path.pop_back();
        }
    }
};
```

[1]: https://leetcode.com/problems/remove-invalid-parentheses/