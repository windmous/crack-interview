题目链接: [151.Reverse Words in a String][1]
难度: Medium

描述：给定一个单词串，将各个单词出现的次序反过来。中间的空格全部压缩为1个。

Given s = "the sky is blue",
return "blue is sky the".

# Inplace方法(8ms)
时间复杂度：O(N)
空间复杂度：O(1)

翻转每个单词， 最终翻转整个串即可完成。

```cpp
class Solution {
public:
    void reverseWords(string &s) {
        const int sz = s.size();
        int i = 0, j = 0;
        while (i < sz)
        {
        	// 搜素下一个单词的开始
            while (i < sz && s[i] == ' ') i++; //i is the start of the word
            if (i < sz && j > 0) // j > 0表示第一个单词不加空格
                s[j++] = ' ';
            int start = j; // 单词的开始
            while (i < sz && s[i] != ' ')
                s[j++] = s[i++];
            reverse(s.begin()+start, s.begin()+j);
        }
        
        s.resize(j);
        reverse(s.begin(), s.end());
    }
};
```


[1]: https://leetcode.com/problems/reverse-words-in-a-string/