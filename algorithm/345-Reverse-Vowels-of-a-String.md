题目链接: [345.Reverse Vowels of a String][1]
难度: Easy

# 双指针法(9ms)
时间复杂度：O(N)
空间复杂度：O(1)

主要是学会string::find的用法，可以用来作为探针搜索字符串

```cpp
class Solution {
public:
    string reverseVowels(string s) {
        const int N = s.size();
        int i = 0, j = N - 1;
        static const string vowels = "aoeiuAOEIU";
        
        while (i < j) {
            while (i < j && vowels.find(s[i]) == string::npos) ++ i;
            while (i < j && vowels.find(s[j]) == string::npos) -- j;
            if (i < j) swap(s[i++], s[j--]);
        }
        
        return s;
    }
};
```

# STL方法2(16ms)
时间复杂度：O(N^2)
空间复杂度：O(1)

主要是熟悉find_first_of和find_last_of的用法，它们可以对多个chars试图命中。

```cpp
class Solution {
public:
    string reverseVowels(string s) {
        const int N = s.size();
        int i = 0, j = N - 1;
        static const char *vowels = "aoeiuAOEIU";
        
        while (i < j) {
            i = s.find_first_of(vowels, i);
            j = s.find_last_of(vowels, j);
            if (i < j) swap(s[i++], s[j--]);
        }
        return s;
    }
};
```

[1]: https://leetcode.com/problems/reverse-vowels-of-a-string
