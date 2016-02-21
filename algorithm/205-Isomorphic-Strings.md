题目链接：[205. Isomorphic Strings][1]

所有方法时间复杂度均为O(n)

# Trival方法(8ms)
```cpp
class Solution {
public:
    bool isIsomorphic(string s, string t) {
        if (s.size() != t.size()) {
            return false;
        }
        
        char fmap[128] = {0}, rmap[128] = {0};
        for (int i = 0; i < s.size(); ++ i) {
            if (fmap[s[i]] == 0 && rmap[t[i]] == 0) {
                fmap[s[i]] = t[i];
                rmap[t[i]] = s[i];
            } else if (fmap[s[i]] != t[i] || rmap[t[i]] != s[i]) {
                return false;
            }
        }
        
        return true;
    }
};
```

# 编码法(8ms)
```cpp
class Solution {
public:
    bool isIsomorphic(string s, string t) {
        if (s.size() != t.size()) {
            return false;
        }
        
        int tab1[128] = {0}, tab2[128] = {0};
        int cnt = 1;
        for (int i = 0; i < s.size(); ++ i) {
            if (tab1[s[i]] != tab2[t[i]]) {
                return false;
            }
            
            # 实际直接写成tab1[s[i]] = tab2[t[i]] = i+1也能AC
            # 但写成下面的形式能避免Overflow
            if (tab1[s[i]] == 0) {
                tab1[s[i]] = tab2[t[i]] = cnt ++;
            }
        }
        
        return true;
    }
};
```

# 集合方法
本方法用python编写，代码仅一行，比较拉风故收录于此：

```python
def isIsomorphic(self, s, t):
    return len(set(zip(s, t))) == len(set(s)) and len(set(zip(t, s))) == len(set(t))
```

[1]: https://leetcode.com/problems/isomorphic-strings/