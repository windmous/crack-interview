题目链接: [425.Word Squares][1]
难度: Hard

Given a set of words (without duplicates), find all word squares you can build from them.

A sequence of words forms a valid word square if the kth row and column read the exact same string, where 0 ≤ k < max(numRows, numColumns).

For example, the word sequence ["ball","area","lead","lady"] forms a word square because each word reads the same both horizontally and vertically.

b a l l
a r e a
l e a d
l a d y
Note:
There are at least 1 and at most 1000 words.
All words will have the exact same length.
Word length is at least 1 and at most 5.
Each word contains only lowercase English alphabet a-z.
Example 1:

Input:
["area","lead","wall","lady","ball"]

Output:
[
  [ "wall",
    "area",
    "lead",
    "lady"
  ],
  [ "ball",
    "area",
    "lead",
    "lady"
  ]
]

Explanation:
The output consists of two word squares. The order of output does not matter (just the order of words in each word square matters).
Example 2:

Input:
["abat","baba","atan","atal"]

Output:
[
  [ "baba",
    "abat",
    "baba",
    "atan"
  ],
  [ "baba",
    "abat",
    "baba",
    "atal"
  ]
]

Explanation:
The output consists of two word squares. The order of output does not matter (just the order of words in each word square matters).
Show Company Tags
Show Tags
Show Similar Problems

# 暴力搜索(175ms, 54.54%)
由于题目要求输出所有的可能性，所以无疑要暴力了，在DFS的时候注意剪枝即可。

下面的前缀Hashmap可以改成Trie树

```cpp
class Solution {
public:
    vector<vector<string>> wordSquares(vector<string>& words) {
        // Remove duplicated elements
        sort(words.begin(), words.end());
        words.erase(unique(words.begin(), words.end()), words.end());
        
        // Build some data structures for recording
        unordered_map<string, vector<int>> prefix_map;
        vector<string> square(words[0].size());
        vector<vector<string>> result;
        
        for (int i = 0; i < words.size(); ++ i) {
            string prefix;
            prefix_map[prefix].push_back(i);
            
            for (int j = 0; j < words[i].size(); ++ j) {
                prefix += words[i][j];
                prefix_map[prefix].push_back(i);
            }
        }
        
        solve(0, square, result, prefix_map, words);
        return result;
    }
    
    void solve(int lev, vector<string> &square, vector<vector<string>> &result, unordered_map<string, vector<int>> &prefix_map, vector<string> &words) {
        if (lev == square.size()) {
            result.push_back(square);
            return ;
        }
        
        string prefix;
        for (int i = 0; i < lev; ++ i) {
            prefix += square[i][lev];
        }
        
        for (int n : prefix_map[prefix]) {
            square[lev] = words[n];
            solve(lev+1, square, result, prefix_map, words);
        }
    }
};
```

[1]: https://leetcode.com/problems/word-squares
