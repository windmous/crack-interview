题目链接: [393.UTF-8 Validation][1]
难度: Medium

# Naive实现(28ms)
时间复杂度：O(4N)
空间复杂度：O(1)

做个模板往前扫描即可。

```cpp
class Solution {
public:
    bool validUtf8(vector<int>& data) {
        int prefix[] = {0, 0xC0, 0xE0, 0xF0};
        int mask[] = {0x80, 0xE0, 0xF0, 0xF8};
        for (int i = 0; i < data.size(); ) {
            bool ok = false;
            for (int j = 0; j < 4 && !ok; ++ j) {
                if ((data[i] & mask[j]) == prefix[j]) {
                    for (int k = 0; k < j; ++ k) {
                        if (i+k+1 >= data.size() || (data[i+k+1] & 0xC0) != 0x80) {
                            return false;
                        }
                    }
                    ok = true;
                    i += j + 1;
                }
            }
            if (!ok) return false;
        }
        return true;
    }
};
```

# if-caluse策略(22ms)
时间复杂度：O(4N)
空间复杂度：O(1)
主要是认识到，UTF-8不是包含所有情况的，提防255
```cpp
class Solution {
public:
    bool validUtf8(vector<int>& data) {
        int cnt = 0;
        for (int c : data) {
            if (cnt == 0) {
                if ((c >> 3) == 0x1E) cnt = 3;
                else if ((c >> 4) == 0x0E) cnt = 2;
                else if ((c >> 5) == 0x06) cnt = 1;
                else if ((c >> 7) == 1) return false;
            } else if ((c & 0xC0) != 0x80) {
                return false;
            } else {
                cnt --;
            }
        }
        return cnt == 0;
    }
};
```


[1]: https://leetcode.com/problems/utf-8-validation
