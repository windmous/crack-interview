题目链接: [290.Word Pattern][1]
难度: Easy

描述：给定一个pattern和一个由单词组成的字符串，判断字符串是否满足该pattern。

Examples:

1.pattern = "abba", str = "dog cat cat dog" should return true.
2.pattern = "abba", str = "dog cat cat fish" should return false.
3.pattern = "aaaa", str = "dog cat cat dog" should return false.
4.pattern = "abba", str = "dog dog dog dog" should return false.

# 编码法(0ms)
时间复杂度：O(N)
空间复杂度：O(N)

原理跟`205. Isomorphic Strings`一致。
```cpp
class Solution {
public:
    bool wordPattern(string pattern, string str) {
        unordered_map<string, int> w2i;
        unordered_map<char, int> c2i;
        
        istringstream sin(str);
        int i = 0;
        for (string word; sin >> word; ++ i) {
            if (i == str.size() || w2i[word] != c2i[pattern[i]])
                return false;
            w2i[word] = c2i[pattern[i]] = i + 1;
        }
        
        return i == pattern.size();
    }
};
```

# 编码法2(0ms)
时间复杂度：O(N)
空间复杂度：O(N)

本次不直接对整个<string, word>编码了，而是直接将char映射到word

```cpp
class Solution {
public:
    bool wordPattern(string pattern, string str) 
    {
        istringstream ss(str);
        string word;
        unordered_map<char, string> bmap;
        unordered_map<string, char> rbmap;
    
        for (char c : pattern) {
            if (!(ss >> word))
                return false;
            // emplace返回<iterator, bool>，第一个元素是
            // 新插入元素的迭代器。对迭代器解引用返回<key, value>对
            if ( bmap.emplace(c,word).first->second != word)
                return false;
            if (rbmap.emplace(word,c).first->second != c)
                return false;
        }
        return ! getline(ss, word, ' ');   
    }
};
```

[1]: https://leetcode.com/problems/word-pattern/