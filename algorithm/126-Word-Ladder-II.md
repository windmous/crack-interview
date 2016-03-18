题目链接: [126.Word Ladder II][1]
难度: Hard

给定一个字典以及一个beginWord and endWord，问从beginWord 变化到 endWord的路径。一次变化只能改一个字母，且变化的词需要在词典中出现过。

容易想到所有单词能够组成一张图，但是字典可能很大，对字典建图容易超时。而且建图需要O(N^2)时间。以下方法会修改wordDict，实质是将这个图变成了树（森林），因为每个词到另一个词至多只有一条路径。

P126 求所有最短路径

P127 求最短路径的长度

# BFS+DFS

不难，但是很繁琐。这个答案作者从头尾两端同时搜索，用于加速。

https://leetcode.com/discuss/41689/88ms-accepted-solution-with-68ms-word-ladder-88ms-word-ladder

```cpp
class Solution {
public:
    vector<vector<string> > findLadders(string beginWord, string endWord, unordered_set<string> &dict) {
        vector<vector<string> > paths;
        vector<string> path(1, beginWord);
        if (beginWord == endWord) {
            paths.push_back(path);
            return paths;
        }
        unordered_set<string> words1, words2;
        words1.insert(beginWord);
        words2.insert(endWord);
        unordered_map<string, vector<string> > nexts;
        bool words1IsBegin = false;
        if (findLaddersHelper(words1, words2, dict, nexts, words1IsBegin))
            getPath(beginWord, endWord, nexts, path, paths);
        return paths;
    }
private:
    bool findLaddersHelper(
        unordered_set<string> &words1,
        unordered_set<string> &words2,
        unordered_set<string> &dict,
        unordered_map<string, vector<string> > &nexts,
        bool &words1IsBegin) {
        words1IsBegin = !words1IsBegin;
        if (words1.empty())
            return false;
        if (words1.size() > words2.size())
            return findLaddersHelper(words2, words1, dict, nexts, words1IsBegin);
        for (auto it = words1.begin(); it != words1.end(); ++it)
            dict.erase(*it);
        for (auto it = words2.begin(); it != words2.end(); ++it)
            dict.erase(*it);
        unordered_set<string> words3;
        bool reach = false;
        for (auto it = words1.begin(); it != words1.end(); ++it) {
            string word = *it;
            for (auto ch = word.begin(); ch != word.end(); ++ch) {
                char tmp = *ch;
                for (*ch = 'a'; *ch <= 'z'; ++(*ch))
                    if (*ch != tmp)
                        if (words2.find(word) != words2.end()) {
                            reach = true;
                            words1IsBegin ? nexts[*it].push_back(word) : nexts[word].push_back(*it);
                        }
                        else if (!reach && dict.find(word) != dict.end()) {
                            words3.insert(word);
                            words1IsBegin ? nexts[*it].push_back(word) : nexts[word].push_back(*it);
                        }
                *ch = tmp;
            }
        }
        return reach || findLaddersHelper(words2, words3, dict, nexts, words1IsBegin);
    }
    void getPath(
        string beginWord,
        string &endWord,
        unordered_map<string, vector<string> > &nexts,
        vector<string> &path,
        vector<vector<string> > &paths) {
        if (beginWord == endWord)
            paths.push_back(path);
        else
            for (auto it = nexts[beginWord].begin(); it != nexts[beginWord].end(); ++it) {
                path.push_back(*it);
                getPath(*it, endWord, nexts, path, paths);
                path.pop_back();
            }
    }
};
```
[1]: https://leetcode.com/problems/word-ladder-ii/