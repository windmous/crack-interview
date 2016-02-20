题目链接：[204. Count Primes][1]

# Sieve of Eratosthenes(308ms)
时间复杂度：O(nloglogn)
空间复杂度：O(n)

```cpp
class Solution {
public:
    int countPrimes(int n) {
        vector<bool> is_prime(n, true);
        is_prime[0] = is_prime[1] = false;
        for (int i = 2; i * i <= n; ++ i) {
            if (is_prime[i]) {
                for (int j = i * i; j < n; j += i) {
                    is_prime[j] = false;
                }
            }
        }
        
        return count(is_prime.begin(), is_prime.end(), true);
    }
};
```

# Sieve of Eratosthenes，优化版本(16ms)
```cpp
class Solution {
public:
    int countPrimes(int n) {
        if (n <= 2) return false;
        // trick1: 不使用vector，使用数组
        bool passed[n] = {false};
        // 初始个数，删去所有偶数，同时删除1，添加2
        int ans = n/2;
        int upper = sqrt(n);
        
        // trick2: 只处理奇数
        for (int i = 3, j, step; i <= upper; i += 2) {
            if (!passed[i]) {
                // trick3: 使用step，每次前进两倍(跳过的那个肯定是偶数)
                for (step=i*2, j = i*i; j < n; j += step) {
                    if (!passed[j]) {
                        passed[j] = true;
                        -- ans;
                    }
                }
            }
        }
        
        return ans;
    }
};
```

# 压缩内存版
基于上面的优化，可以知道passed数组奇数元素没有用到，可以删掉的，处理速度可以提到12ms，见[这里][2].


[1]: https://leetcode.com/problems/count-primes/
[2]: https://leetcode.com/discuss/65257/12ms-c-solution