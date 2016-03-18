题目链接: [166.Fraction to Recurring Decimal][1]
难度: Medium

Given numerator = 1, denominator = 2, return "0.5".
Given numerator = 2, denominator = 1, return "2".
Given numerator = 2, denominator = 3, return "0.(6)".

# 缓存法(4ms)
时间复杂度：?
空间复杂度：?

解决此题的关键是，一旦重复见到同一个余数，那么可以肯定出现了循环

```cpp
class Solution {
public:
    string fractionToDecimal(int64_t n, int64_t d) {
        if (n == 0) return "0";
    
        string res;
        if (n < 0 ^ d < 0) res += '-';

		// 建议使用long long，可能溢出    
        n = abs(n), d = abs(d);
        res += to_string(n / d);
    
        // in case no fractional part
        if (n % d == 0) return res;

        res += '.';

        unordered_map<int, int> cache;
        for (int64_t r = n % d; r; r %= d) {
            if (cache.count(r) > 0) {
                res.insert(cache[r], 1, '(');
                res += ')';
                break;
            }
    
            // the remainder is first seen
            // remember the current position for it
            cache[r] = res.size();
    
            r *= 10;
            res += to_string(r / d);
        }
    
        return res;
    }
};
```

[1]: https://leetcode.com/problems/fraction-to-recurring-decimal/