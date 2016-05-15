题目链接: [211.Add and Search Word - Data structure design][1]
难度: Medium

实现一个tried树，支持addWord和searchWord两个函数，其中searchWord给的word字符串可以带有'.'，表示匹配任意字符。

# Trie树

```cpp
struct TrieNode{
    vector<TrieNode*> next;
    bool isEnd = false;
    TrieNode() {
        next = vector<TrieNode*> (26, nullptr);
    }
};

class WordDictionary {
public:
    WordDictionary() {
        root = new TrieNode();
    }
    
    // Adds a word into the data structure.
    void addWord(string word) {
        TrieNode* ptr = root;
        for (int i = 0; i < word.size(); ++i) {
            if (ptr->next[word[i] - 'a'] == nullptr) {
                ptr->next[word[i] - 'a'] = new TrieNode();
            }
            ptr = ptr->next[word[i] - 'a'];
        }
        ptr->isEnd = true;
    }

    // Returns if the word is in the data structure. A word could
    // contain the dot character '.' to represent any one letter.
    bool search(string word) {
        return dfs(root, word, 0);
    }
    
private:
    TrieNode* root;
    bool dfs(TrieNode* ptr, const string& word, int idx) {
        if (idx == word.size()) return ptr->isEnd;
        if (word[idx] == '.') {
            for (int i = 0; i < 26; ++i) {
                if (ptr->next[i] != nullptr && dfs(ptr->next[i], word, idx + 1) == true) {
                    return true;
                }
            }
            return false;
        } else {
            if (ptr->next[word[idx] - 'a'] != nullptr)
                return dfs(ptr->next[word[idx] - 'a'], word, idx + 1);
            else 
                return false;
        }
    }
};

// Your WordDictionary object will be instantiated and called as such:
// WordDictionary wordDictionary;
// wordDictionary.addWord("word");
// wordDictionary.search("pattern");
```

[1]: https://leetcode.com/problems/add-and-search-word-data-structure-design/