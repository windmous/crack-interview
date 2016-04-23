题目链接: [299.Bulls and Cows][1]
难度: Easy

给一串数secret和对其的猜测guess，返回“位置和数字都对” --> A , “位置不对但数字对” --> B

例如Secret number:  "1807"，Friend's guess: "7810"，返回"1A3B"

```cpp
class Solution {
public:
    string getHint(string secret, string guess) {
        int a = 0, b = 0, len = secret.length();
        
        vector<int> sec(10, 0), gue(10, 0);
        for (int i = 0; i < len; ++i) {
            if (secret[i] == guess[i]) ++a;
            ++sec[secret[i] - '0'];
            ++gue[guess[i] - '0'];
        }
        
        for (int i = 0; i < 10; ++i) {
            b += min(sec[i], gue[i]);
        }
        b -= a;
        
        return to_string(a) + "A" + to_string(b) + "B";
    }
};
```

[1]: https://leetcode.com/problems/bulls-and-cows/