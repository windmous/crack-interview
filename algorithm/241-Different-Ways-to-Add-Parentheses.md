题目链接: [241.Different Ways to Add Parentheses][1]
难度: Medium

描述：给定一个含有加、减、乘的表达式，随意向其中加入括号，计算所有可能出现的结果。

本题时间复杂度不易确定，有兴趣的可以看看[这里][2]

# 暴力搜索(8ms)
时间复杂度：约O(4^n/{sqrt{n}})

```cpp
class Solution {
public:
    vector<int> diffWaysToCompute(string input) {
        vector<int> output;
        for (int i=0; i<input.size(); i++) {
            char c = input[i];
            if (ispunct(c))
                for (int a : diffWaysToCompute(input.substr(0, i)))
                    for (int b : diffWaysToCompute(input.substr(i+1)))
                        output.push_back(c=='+' ? a+b : c=='-' ? a-b : a*b);
        }
        return output.size() ? output : vector<int>{stoi(input)};
    }
};
```

# 动态规划-迭代(0ms)
```cpp
class Solution {
public:
    vector<int> diffWaysToCompute(string input) {
    vector<int> data;
    vector<char> ops;
    int num = 0;
    char op = ' ';
    // 下面加一个'+'主要是为了下面的while循环写的简略一些
    istringstream ss(input + "+");
    while(ss >> num && ss >> op) {
        data.push_back(num);
        ops.push_back(op);
    }
    const int size_i = data.size();
    //dp[i][j]记录[i,j]子串所有可能的结果
    vector<vector<vector<int>>> dp(size_i, vector<vector<int>>(size_i, vector<int>()));
    for (int i = 0; i < size_i; i += 1)
        for (int j = i; j >= 0; j -= 1) {
            if (i == j) {dp[j][i].push_back(data[i]); continue;}
            // ...j...k...i...
            for (int k = j; k < i; k += 1) {
                for (auto left : dp[j][k]) 
                    for (auto right : dp[k+1][i]) {
                    int val = 0;
                    switch(ops[k]) {
                        case '+': val = left + right; break;
                        case '-': val = left - right; break;
                        case '*': val = left * right; break;
                    }
                    dp[j][i].push_back(val);
                }
            }
        }
    
    return dp[0][size_i-1];
}
};
```


# 动态规划-记忆化搜索(4ms)

```cpp
class Solution {
public:
    vector<int> diffWaysToCompute(string input) {
        unordered_map<string, vector<int>> cache;
        return diffWaysToCompute(input, 0, input.size()-1, cache);
    }
private:
    vector<int> diffWaysToCompute(string& input, int start, int end, unordered_map<string, vector<int>>& cache) {
        string key=to_string(start)+"/"+to_string(end);
        if(cache.count(key)) return cache[key];
        
        vector<int> result;
        int num=0;
        for(int i=start; i<=end; ++i) {
            if(isdigit(input[i]))
                num=num*10+(input[i]-'0');
            else{ 
                vector<int> left=diffWaysToCompute(input, start, i-1, cache);
                vector<int> right=diffWaysToCompute(input, i+1, end, cache);
                for(auto l:left){
                    for(auto r: right){
                        if(input[i]=='+')
                            result.push_back(l+r);
                        else if(input[i]=='-')
                            result.push_back(l-r);
                        else if(input[i]=='*')
                            result.push_back(l*r);
                    }
                }
            }    
        }
        if(result.size()==0) result.push_back(num); //only single number
        return cache[key]=result;
    }
};
```

[1]: https://leetcode.com/problems/different-ways-to-add-parentheses/
[2]:https://leetcode.com/discuss/48494/what-is-the-time-complexity-of-divide-and-conquer-method