题目链接: [68.Text Justification][1]
难度: Hard


# 强行上

https://leetcode.com/discuss/13610/share-my-concise-c-solution-less-than-20-lines
For each line, I first figure out which words can fit in. According to the code, these words are words[i] through words[i+k-1]. Then spaces are added between the words. The trick here is to use mod operation to manage the spaces that can't be evenly distrubuted: the first (L-l) % (k-1) gaps acquire an additional space.

```cpp
vector<string> fullJustify(vector<string> &words, int L) {
    vector<string> res;
    for(int i = 0, k, l; i < words.size(); i += k) { // 每次循环表示一行，插入words[i] through words[i+k-1].
        for(k = l = 0; i + k < words.size() && l + words[i+k].size() <= L - k; k++) {
            l += words[i+k].size(); // l表示占用的space，k表示第i+k个单词
        }
        string tmp = words[i];
        for(int j = 0; j < k - 1; j++) { // 这个加空格的方式虽然很巧妙，但是私以为不适合debug，可读性也不强
            if(i + k >= words.size()) tmp += " ";
            else tmp += string((L - l) / (k - 1) + (j < (L - l) % (k - 1)), ' ');
            tmp += words[i+j+1];
        }
        tmp += string(L - tmp.size(), ' ');
        res.push_back(tmp);
    }
    return res;
}
```

[1]: https://leetcode.com/problems/text-justification/