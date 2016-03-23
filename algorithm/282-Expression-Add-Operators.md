题目链接: [282.Expression Add Operators][1]
难度: Hard

描述：给定一个只包含0-9字符的字符串以及一个整数target，向这个字符串中加入`+,-,*`各类运算符，使得字符串形成的表达式的计算结果为target。请返回所有满足该条件的表达式。

# DFS
时间复杂度：O(3^N)

```cpp
class Solution {
public:
    vector<string> addOperators(string num, int target) {
        vector<string> result;
        if(num.size()==0)   return result;
        help(result, "", num, target, 0, 0, 0);
        return result;
    }

    void help(vector<string> &result, string path, string num, int target, int pos, long cur, long prev){
        if(pos==num.size()){
            if(cur==target)   result.push_back(path);
            return;
        }
        for(int i=pos; i<num.size(); i++){
            // 数字的开始不能有多余的0
            if(num[pos]=='0' && i>pos) break;
            string _str=num.substr(pos, i-pos+1);
            long _value=stol(_str);
            
            if(pos==0)  {
                help(result, path+_str, num, target, i+1, _value, _value);
            }
            else{
                help(result, path+"+"+_str, num, target, i+1, cur+_value, _value);
                help(result, path+"-"+_str, num, target, i+1, cur-_value, -_value);
                help(result, path+"*"+_str, num, target, i+1, cur-prev+prev*_value, prev*_value);
            }
        }
    }
};
```

# DFS2 
时间复杂度：O(4^N)

dfs中途的求值结果可以表达为A+B*C的形式。假设下一个数字是n
```
初始状态：A + B * C = 0 + 1 * n

中间状态：

1） 新数并入前一个数： A + B * C := A       + B     * Cn
2） 加上新数：         A + B * C := (A+B*C) + 1     * n
3） 减去新数：         A + B * C := (A+B*C) - 1     * n
4)  乘以新数：         A + B * C := A       + (B*C) * n
```
```cpp
class Solution {
private:
	void dfs(long long A, long long B, long long C, 
	         string&& path, int level, string& num, long long target, vector<string>& answer) {
		if (level == num.length()) {
			if (A + B * C == target) answer.push_back(path);
		}
		else {
			if (C != 0) 
			    dfs(    A,     B, C * 10 + num[level] - '0',       path + num[level], level + 1, num, target, answer);
			dfs(A + B * C,     1,          num[level] - '0', path + "+" + num[level], level + 1, num, target, answer);
			dfs(A + B * C,    -1,          num[level] - '0', path + "-" + num[level], level + 1, num, target, answer);
			dfs(        A, B * C,          num[level] - '0', path + "*" + num[level], level + 1, num, target, answer);
		}
	}


public:
	vector<string> addOperators(string num, int target) {
		vector<string> answer;
		if (num.length() != 0)
			dfs(0, 1, num[0] - '0', num.substr(0, 1), 1, num, target, answer);
					
		return answer;
	}
};
```
[1]: https://leetcode.com/problems/expression-add-operators/