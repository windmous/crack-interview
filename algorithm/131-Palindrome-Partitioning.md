题目链接: [131.Palindrome Partitioning][1]
难度: Medium

给定字符串s，将其划分成若干子串，每个子串都是回文。

P131 返回所有可行的分割

P132 返回最小的需要切割次数

# DFS

https://leetcode.com/discuss/18984/java-backtracking-solution

```cpp
class Solution {
public:
    vector< vector<string> > partition(string s) {
        vector< vector<string> > result;
        vector< string > tmp;
        recurPartition(s, 0, tmp, result);
        return result;
    }
    void recurPartition(string &s, int start, vector<string> &tmp, vector< vector<string> > &result){
        if(start==s.size()){
            result.push_back(tmp);
        }
        for(int i=start+1; i<=s.size();i++){
            if(isPalindrome(s, start, i)){	// 尝试切割s[start..i]
                tmp.push_back(s.substr(start, i-start));
                recurPartition(s, i, tmp, result);
                tmp.pop_back();
            }
        }
    }
    bool isPalindrome(string &s, int begin, int end){
        int left=begin;
        int right=end-1;
        while(left<right){
            if(s[left++]!=s[right--])
                return false;
        }
        return true;
    }
};
```


[1]: https://leetcode.com/problems/palindrome-partitioning/