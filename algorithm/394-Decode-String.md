题目链接: [394.Decode String][1]
难度: Medium

# 栈迭代法(0ms)
时间复杂度：O(N)
空间复杂度：O(N)

```cpp
class Solution {
public:
    string decodeString(string s) {
        stack<string> strs_s;
        stack<int> cnt_s;
        strs_s.push("");
        
        int idx = 0;
        while (idx < s.size()) {
            if (s[idx] == ']') {
                stringstream ss;
                int n = cnt_s.top();
                while (n --) {
                    ss << strs_s.top();
                }
                
                strs_s.pop();
                cnt_s.pop();
                
                strs_s.top() += ss.str();
                ++ idx;
            } else if (isdigit(s[idx])) {
                int cnt_end = s.find('[', idx);
                cnt_s.push(stoi(s.substr(idx, cnt_end-idx)));
                strs_s.push("");
                idx = cnt_end + 1;
            } else {
                strs_s.top() += s[idx++];
            }
        }
        return strs_s.top();
    }
};
```

# 递归法(0ms)
时间复杂度：O(N)
空间复杂度：O(N)

```cpp
class Solution {
public:
    string decodeString(string s) {
        int idx = 0;
        return solve(s, idx);
    }
    
    string solve(const string &s, int &idx) {
        string result;
        while (idx < s.size()) {
            if (s[idx] == ']') {
                idx ++;
                break;
            } else if (!isdigit(s[idx])) {
                result += s[idx++];
            } else {
                int rep_end = s.find('[', idx);
                int n = stoi(s.substr(idx, rep_end - idx));
                string sub_str = solve(s, idx=rep_end+1);

                while (n--) {
                    result += sub_str;
                }
            }
        }
        return result;
    }
};
```


[1]: https://leetcode.com/problems/decode-string
