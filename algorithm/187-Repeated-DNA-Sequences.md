题目链接: [187.Repeated DNA Sequences][1]
难度: Medium

描述：给一个字符串，其只包含A、C、G、T四个字母。找出所有的长度为10且重复出现的子序列。注意，子序列允许重叠，比如字符串为11个A组成，那么我们认为str[0-9]和str[1-10]是相等的，即10个A组成的字串有重复。

本题实质考查面试者设计哈希函数的能力，即如何对长度为10的序列做hash映射。

# Hash法(92ms)
时间复杂度：O(N)
空间复杂度：O(N)

A、C、G、T四个字母ASCII码最后的三个bit分别为'001'、'011'、'111'、'100'。所以我们可以用这三个bit来区分4个字母，然后用3 * 10 = 30bit的整数来表示过去10个字母。

```cpp
class Solution {
public:
    vector<string> findRepeatedDnaSequences(string s) {
        unordered_map<int, int> m;
        vector<string> r;
        int t = 0, i = 0, ss = s.size();
        while (i < 9)
            t = t << 3 | s[i++] & 7;
        while (i < ss)
            if (m[t = t << 3 & 0x3FFFFFFF | s[i++] & 7]++ == 1)
                r.push_back(s.substr(i - 10, 10));
        return r;
    }
};
```

# Trival Hash法(16ms)
时间复杂度：O(N)
空间复杂度：O(N)

上面的代码需要熟知ASCII的结构，实际面试不现实。下面是比较容易使用的寻常方法：
```cpp
class Solution {
public:
    static int encode(char c) {
        // 虽然使用了switch结构，但编译器一般会优化为hash表水平
        switch(c) {
            case 'A': return 0;
            case 'C': return 1;
            case 'T': return 2;
            case 'G': return 3;
        }
        return -1;
    }

    vector<string> findRepeatedDnaSequences(string s) {
    	// 我们使用2bit来记录一个字母，10个字母需要20bit
        bitset<1048576> vis_once, vis_twice;
        const int len = s.size();
        if (len < 11) return {};
        
        vector<string> ans;
        int hashNum = accumulate(s.begin(), s.begin()+9, 0, 
                                [](int x, char y) {return x << 2 | encode(y);});
        for (int i = 9; i < len; ++i) {
            hashNum = (hashNum << 2 | encode(s[i])) & 0xfffff;
            if (vis_once[hashNum] && !vis_twice[hashNum]) { 
                ans.push_back(s.substr(i-9, 10));
                vis_twice.set(hashNum);
            } else vis_once.set(hashNum);
        }
        return ans;
    }
};
```


[1]: https://leetcode.com/problems/repeated-dna-sequences/