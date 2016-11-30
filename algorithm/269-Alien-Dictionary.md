题目链接: [269.Alien Dictionary][1]
难度: Hard

There is a new alien language which uses the latin alphabet. However, the order among letters are unknown to you. You receive a list of words from the dictionary, where words are sorted lexicographically by the rules of this new language. Derive the order of letters in this language.

For example,
Given the following words in dictionary,

[
  "wrt",
  "wrf",
  "er",
  "ett",
  "rftt"
]
The correct order is: "wertf".

Note:
You may assume all letters are in lowercase.
If the order is invalid, return an empty string.
There may be multiple valid order of letters, return any one of them is fine.

# Naive拓扑排序（不高明）

```cpp
class Solution {
public:
    string alienOrder(vector<string>& words) {
        vector<set<char>> graph(128);

        unordered_set<char> chars;
        for (int i = 0; i < words.size(); ++ i) {
            for (int j = 0; j < words[i].size(); ++ j) {
                chars.insert(words[i][j]);
            }
        }

        if (chars.empty()) return "";
        else if (chars.size() == 1) return string(1, *chars.begin());

        for (int i = 1; i < words.size(); ++ i) {
            int j = 0;
            while (j < words[i].size() && j < words[i-1].size() && words[i][j] == words[i-1][j]) ++ j;
            if (j == words[i].size() || j == words[i-1].size()) {
                if (words[i-1].size() > words[i].size()) return "";
                else continue;
            }
            graph[words[i][j]].insert(words[i-1][j]);
        }

        vector<int> inds(128, 0);
        queue<char> q;
        for (char c : chars) {
            for (char n : graph[c]) {
                inds[n] ++;
            }
        }

        string result;
        for (char c : chars) {
            if (inds[c] == 0)
                q.push(c);
        }

        while (!q.empty()) {
            while (!q.empty()) {
                int item = q.front();
                q.pop();
                result += item;
                for (char x : graph[item]) {
                    if (-- inds[x] == 0) {
                        q.push(x);
                    }
                }
            }
        }

        reverse(result.begin(), result.end());
        return result.size() == chars.size() ? result : "";
    }
};
```

[1]: https://leetcode.com/problems/alien-dictionary/