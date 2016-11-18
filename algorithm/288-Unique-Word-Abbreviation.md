题目链接: [288.Unique Word Abbreviation][1]
难度: Easy

An abbreviation of a word follows the form <first letter><number><last letter>. Below are some examples of word abbreviations:

a) it                      --> it    (no abbreviation)

     1
b) d|o|g                   --> d1g

              1    1  1
     1---5----0----5--8
c) i|nternationalizatio|n  --> i18n

              1
     1---5----0
d) l|ocalizatio|n          --> l10n
Assume you have a dictionary and given a word, find whether its abbreviation is unique in the dictionary. A word's abbreviation is unique if no other word from the dictionary has the same abbreviation.

Example: 
Given dictionary = [ "deer", "door", "cake", "card" ]

isUnique("dear") -> 
false

isUnique("cart") -> 
true

isUnique("cane") -> 
false

isUnique("make") -> 
true

Show Company Tags
Show Tags
Show Similar Problems

# Hash表
时间复杂度：O(N) / O(1)
空间复杂度：O(N)

判断一个是否Unique的要求是：
必须对单词去重
1) 单词的缩写在字典中不存在
2) 单词的缩写虽然在字典中存在，但是单词本身也在字典中，且单词的缩写是唯一的。

```cpp
class ValidWordAbbr {
public:
    ValidWordAbbr(vector<string> &dictionary) : word_set(dictionary.begin(), dictionary.end()) {
        for (const string &word : word_set) {
            string abbre = get_abbre(word);
            word_cnt[abbre] = min(2, ++ word_cnt[abbre]);
        }
    }

    bool isUnique(string word) {
        string abbre = get_abbre(word);
        return word_cnt.count(abbre) == 0 || (word_cnt[abbre] == 1 && word_set.count(word) != 0);
    }

private:
    string get_abbre(const string &word) {
        if (word.size() <= 2) return word;
        else return word[0] + to_string(word.size()-2) + word.back();
    }

    unordered_map<string, int> word_cnt;
    unordered_set<string> word_set;
};
```

[1]: https://leetcode.com/problems/unique-word-abbreviation/