题目链接: [401.Binary Watch][1]
难度: Easy

# 打表法 (0ms)

记录下0-60每个字符的bit 1个数即可。
注意该问题必须认真考虑数据范围，即小时必须在0-11内，分钟必须在0-60内。

```cpp
class Solution {
public:
    Solution() : digits(7) {
        for (int i = 0; i < 60; ++ i) {
            digits[ones(i)].push_back(i);
        }
    }
    
    static int ones(int x) {
        int val = 0;
        while (x) {
            ++ val;
            x &= (x-1);
        }
        return val;
    }
    
    vector<string> readBinaryWatch(int num) {
        vector<string> result;    
        for (int i = max(0, num-6); i <= min(num, 3); ++ i) {
            for (int h : digits[i]) if (h < 12) {
                for (int m : digits[num-i]) if (m < 60) {
                    result.push_back(to_string(h) + (m < 10 ? ":0" : ":") + to_string(m));
                }
            }
        }
        return result;
    }
    
    vector<vector<int>> digits;
};
```

# 暴力搜索法
```cpp
class Solution {
public:
    vector<string> readBinaryWatch(int num) {
        vector<string> result;
        for (int h = 0; h < 12; ++ h) {
            for (int m = 0; m < 60; ++ m) {
                if (bitset<10>((h<<6)+m).count() == num) {
                    result.push_back(to_string(h) + (m < 10 ? ":0" : ":") + to_string(m));
                }
            }
        }
        return result;
    }
};
```

[1]: https://leetcode.com/problems/binary-watch
