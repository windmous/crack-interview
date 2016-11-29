题目链接: [397.Integer Replacement][1]
难度: Medium

# Hash法(3ms)
时间复杂度：O(logN)
空间复杂度：O(logN)
```cpp
class Solution {
public:
    unordered_map<long long,int> cache;
    
    int integerReplacement(long long n) {
        if (n == INT_MAX) return 32;
        else if (n == 1) return 0;
        else if (cache.count(n)) return cache[n];
        else if (n&1) return cache[n] = 1+min(integerReplacement(n+1), integerReplacement(n-1));
        else return cache[n] = 1+integerReplacement(n/2);
    }
};
```

# 暴力(9ms)
时间复杂度：O(logN)
空间复杂度：O(logN)

```cpp
class Solution {
public:
    int integerReplacement(long long n) {
        if (n == INT_MAX) return 32;
        else if (n == 1) return 0;
        else if (n&1) return 1+min(integerReplacement(n+1), integerReplacement(n-1));
        else return 1+integerReplacement(n/2);
    }
};
```

# 贪心法()
时间复杂度：O(logN)
空间复杂度：O(logN)
```cpp
class Solution {
public:
    int integerReplacement(long long n) {
        if (n == INT_MAX) return 32;
        int step = 0;
        while (n != 1) {
            step ++;
            if (n & 1) {
                if ((n+1) % 4 == 0 && n != 3) n ++;
                else n --;
            } else {
                n >>= 1;
            }
        }
        return step;
    }
};
```


[1]: https://leetcode.com/problems/integer-replacement
