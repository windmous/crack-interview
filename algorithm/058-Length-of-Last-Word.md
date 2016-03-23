题目链接: [58.Length of Last Word][1]
难度: Easy

给一个字符串，返回最后一个单词的长度。
For example, 
Given s = "Hello World",
return 5.

```cpp
class Solution {
public:
    int lengthOfLastWord(string s) {
        auto start = find_if(s.rbegin(), s.rend(), [](char c) {return c != ' ';});
        return distance(start, find(start, s.rend(), ' '));
    }
};
```

```cpp
int lengthOfLastWord(string s) {
  int count =0;
  for(int i = s.size()-1; i >= 0 ;i--) {
      if (count && s[i] == ' ')  return count;
      if (s[i] != ' ') count ++;
  }
  return count;
}
```


```cpp
int lengthOfLastWord(string s) {
	stringstream ss(s);
	int len = 0;
	string tmp;
	while (ss >> tmp) {
		len = tmp.size();
	}
	return len;
}
```
[1]: https://leetcode.com/problems/length-of-last-word/