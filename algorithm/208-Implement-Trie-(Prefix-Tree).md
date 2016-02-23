题目链接：[208. Implement Trie (Prefix Tree)][1]

# Trival方法(60ms)
下面的代码在TrieNode中用一个数组保存孩子节点，优点是实现简单，缺点是存在浪费。可以使用vector简化。

```cpp
class TrieNode {
public:
    TrieNode *children[26];
    int shared;
    bool is_end;    
    
    TrieNode(bool b=false) : children{nullptr}, shared(0), is_end(b) {}
    
    TrieNode *get_child(char ch) {
        return children[ch - 'a'];
    }
    
    void set_child(char ch, TrieNode *child) {
        children[ch - 'a'] = child;
    }
};

class Trie {
public:
    Trie() {
        root = new TrieNode();
    }
    
    ~Trie() {
        delete root;
    }

    // Inserts a word into the trie.
    void insert(string word) {
        // 避免shared标记被重复添加
        if (search(word)) return ;
        
        TrieNode *cur = root;
        for (char c : word) {
            TrieNode *child = cur->get_child(c);
            if (!child) {
                cur->set_child(c, child=new TrieNode());
            }
            
            cur = child;
            ++ cur->shared;
        }
        
        cur->is_end = true;
    }

    // Returns if the word is in the trie.
    bool search(string word) {
        TrieNode *cur = root;
        for (char c : word) {
            if (nullptr == (cur = cur->get_child(c))) {
                return false;
            }
        }
        
        return cur->is_end;
    }

    // Returns if there is any word in the trie
    // that starts with the given prefix.
    bool startsWith(string prefix) {
        TrieNode *cur = root;
        for (char c : prefix) {
            if (nullptr == (cur = cur->get_child(c))) {
                return false;
            }
        }
        
        return true;
    }

private:
    TrieNode* root;
};

// Your Trie object will be instantiated and called as such:
// Trie trie;
// trie.insert("somestring");
// trie.search("key");
```
[1]: https://leetcode.com/problems/implement-trie-prefix-tree/
