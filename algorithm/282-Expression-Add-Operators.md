题目链接: [282.Expression Add Operators][1]
难度: Hard

描述：给定一个只包含0-9字符的字符串以及一个整数target，向这个字符串中加入`+,-,*`各类运算符，使得字符串形成的表达式的计算结果为target。请返回所有满足该条件的表达式。

# DFS
时间复杂度：O(3^N)

```
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
[1]: https://leetcode.com/problems/expression-add-operators/