题目链接: [316.Remove Duplicate Letters][1]
难度: Medium

# 栈方法(6ms)
时间复杂度：O(N)
空间复杂度：O(N)

巧妙之极的方法

```cpp
class Solution {
public:
    string removeDuplicateLetters(string s) {
        array<int, 128> dups = {0}, kept = {0};
        for (char c : s) {
            dups[c] ++;
        }
        
        stack<char> stk;
        for (int i = 0; i < s.size(); dups[s[i]] --, i ++ ) {
            if (kept[s[i]]) continue;
            while (!stk.empty() && stk.top() >= s[i] && dups[stk.top()] > 0)  {
                kept[stk.top()] = false;
                stk.pop();                
            }
            stk.push(s[i]);
            kept[s[i]] = true;
        }
        
        string result;
        while (!stk.empty()) {
            result += stk.top();
            stk.pop();
        }
        
        reverse(result.begin(), result.end());
        return result;
    }
};
```

# Naive方法
时间复杂度：O(N^2)
空间复杂度：O(N)
搜索到某个必要位置就停止
```cpp
class Solution {
public:
    string removeDuplicateLetters(string s) {
        array<int, 128> dups = {0}, kept = {0};
        for (char c : s) {
            dups[c] ++;
        }
        
        string result;
        for (int i = 0; i < s.size(); ) {
            array<int, 128> cur_del = {0};
            int min_idx = -1;
            for (int j = i; j < s.size(); ++ j) {
                if (kept[s[j]]) continue;
                else {
                    cur_del[s[j]] ++;
                    if (min_idx < 0 || s[min_idx] > s[j]) {
                        min_idx = j;
                    }
                    
                    if (dups[s[j]] <= cur_del[s[j]]) break;
                }
            }
            
            if (min_idx == -1) break;
            else {
                result += s[min_idx];
                for (int j = i; j <= min_idx; ++ j) {
                    -- dups[s[j]];
                }
                kept[s[min_idx]] = 1;
                i = min_idx + 1;
            }
        }
        return result;
    }
};
```

[1]: https://leetcode.com/problems/remove-duplicate-letters/