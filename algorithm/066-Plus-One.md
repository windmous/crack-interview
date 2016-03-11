题目链接: [66.Plus One][1]
难度: Easy

大数加1

# 直接上
```cpp
class Solution {
public:
    vector<int> plusOne(vector<int>& digits) {
        int carry = 1;
        for (auto itr = digits.rbegin(); itr != digits.rend(); ++itr) {
            carry = carry + *itr;
            *itr = carry % 10;
            carry = carry / 10;
        }
        if (carry) digits.insert(digits.begin(), carry);
        return digits;
    }
};
```

# for_each

```cpp
class Solution {
public:
    vector<int> plusOne(vector<int> &digits) {
        add(digits, 1);
        return digits;
    }
private:
    // 0 <= digit <= 9
    void add(vector<int> &digits, int digit) {
        int c = digit;  // carry, 进位

        for_each(digits.rbegin(), digits.rend(), [&c](int &d){
            d += c;
            c = d / 10;
            d %= 10;
        });

        if (c > 0) digits.insert(digits.begin(), 1);
    }
};
```

[1]: https://leetcode.com/problems/plus-one/