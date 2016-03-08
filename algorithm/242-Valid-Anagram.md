题目链接: [242.Valid Anagram][1]
难度: Easy

给定A，B两个字符串，所有字符均为小写字母。判定B字符串是不是A字符串以某种顺序重新排列字母后得到的。

# Hash法(12ms)
时间复杂度：O(N)
空间复杂度：O(1)

```cpp
class Solution {
public:
    bool isAnagram(string s, string t) {
        if (s.length() != t.length()) return false;
        const int n = s.length();
        array<int,26> counts = {0};
        
        for (int i = 0; i < n; i++) { 
            counts[s[i] - 'a']++;
            counts[t[i] - 'a']--;
        }
        
        return find_if(counts.begin(), counts.end(), 
                       bind(not_equal_to<int>(), 0, placeholders::_1)) == counts.end();
    }
};
```

# Hash法STL版本(16ms)
时间复杂度：O(N)
空间复杂度：O(1)

使用两次扫描，第二次扫描时一旦counts数组减小至0以下即停止。

```cpp
class Solution {
public:
    bool isAnagram(string s, string t) {
        if (s.length() != t.length()) return false;
        const int n = s.length();
        
        array<int,26> counts = {0};
        for_each(s.begin(), s.end(), [&counts](char x){++counts[x-'a'];});
        return t.end() == find_if(t.begin(), t.end(), 
                                [&counts](char x){return --counts[x-'a'] < 0;});
    }
};
```

# 哈希码法
我们计算两个

# 排序法(76ms)
时间复杂度：O(NlogN)

```cpp
class Solution {
public:
    bool isAnagram(string s, string t) { 
        sort(s.begin(), s.end());
        sort(t.begin(), t.end());
        return s == t; 
    }
};
```



[1]: https://leetcode.com/problems/valid-anagram/