题目链接: [3.Longest Substring Without Repeating Characters][1]
难度: Medium

- 找字符串中最长的子串，这个子串不含重复字符

# 动态规划(16ms)
在charIndex中记录所有字符上次在s中出现的index，在i向前扫描过程中更新start，保持start和i之间没有重复元素
时间O(n)，空间O(n)

```cpp
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        vector<int> charIndex(256, -1);
        int start = 0, longest = 0; // update with DP
        for (int i = 0; i < s.length(); ++i) {
            start = max(start, charIndex[s[i]] + 1);
            charIndex[s[i]] = i;
            longest = max(longest, i - start + 1);
        }
        return longest;
    }
};
```

# 双指针（指针之间的内容符合条件）2 pass 

方法摘自[此处][2]，详见P76
```cpp
int lengthOfLongestSubstring(string s) {
	vector<int> map(128,0);
	int counter=0, begin=0, end=0, d=0; 
	while(end<s.size()){
		if(map[s[end++]]++>0) counter++; 
		while(counter>0) if(map[s[begin++]]-->1) counter--;
		d=max(d, end-begin); //while valid, update d，此时的counter == 0
	}
	return d;
}
```

[1]: https://leetcode.com/problems/longest-substring-without-repeating-characters/
[2]: https://leetcode.com/discuss/72701/here-10-line-template-that-can-solve-most-substring-problems