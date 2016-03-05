题目链接: [22.Generate Parentheses][1]
难度: Medium

- 给出n个括号能够组合成的所有合法括号串

# 递归 0ms

```cpp
class Solution {
public:
    vector<string> generateParenthesis(int n) {
        vector<string> res;
        addingpar(res, "", n, 0);
        return res;
    }
    
	// n 是待添加的'('的个数，m是待添加的')'的个数
    void addingpar(vector<string> &v, string str, int n, int m){
        if(n==0 && m==0) { // 都加完了，退出递归
            v.push_back(str);
            return;
        }
        if(m > 0){ addingpar(v, str+")", n, m-1); }
        if(n > 0){ addingpar(v, str+"(", n-1, m+1); } // 加上1个左括号会导致需要添加一个右括号
    }
};
```

[1]: https://leetcode.com/problems/generate-parentheses/