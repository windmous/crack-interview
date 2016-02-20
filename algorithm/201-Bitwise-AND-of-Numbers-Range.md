题目链接：[201. Bitwise AND of Numbers Range][1]
# 迭代1(84ms)
时间复杂度：O(logn)

本方法试图找出范围m、n最左侧的共同部分

```cpp
class Solution {
public:
    int rangeBitwiseAnd(int m, int n) {
        int c = 0;
        // m=11001, n=11100，则终止时得到00011。
        while (m != n) {
            m >>= 1;
            n >>= 1;
            c ++;
        }
        
        return m << c;
    }
};
```

# 迭代2(72ms)
时间复杂度：O(logn)

```cpp
class Solution {
public:
    int rangeBitwiseAnd(int m, int n) {
        while (m < n) 
            // 删去n中最低的一个1bit
            n = n & (n-1);
            
        return n;
    }
};
```

# 迭代3(64ms)
时间复杂度：O(logn)
```cpp
class Solution {
public:
    int rangeBitwiseAnd(int m, int n) {
        int mask = ~0;
        while ((m&mask) != (n&mask)) {
            mask <<= 1;
        }
        return m & mask;
    }
};
```

# 迭代4(72ms)
时间复杂度: O(logn)

本质还是找左侧的common part。
```cpp
class Solution {
public:
    int rangeBitwiseAnd(int m, int n) {
        int c = 0;
        for (int mask=m^n; mask; mask>>=1, c++) ;
        return (m >> c) << c;
    }
};
```

# 迭代推广(84ms)
时间复杂度：O(loglogn)
伪常数方法，使用了循环展开

```cpp
class Solution {
public:
    int rangeBitwiseAnd(int m, int n) {
        int diff = m^n;
        diff|=diff>>1, diff|=diff>>2, diff|=diff>>4, diff|=diff>>8, diff|=diff>>16;
        return ~diff & m;
    }
};
```

此方法跟下面方法异曲同工(68ms)
```cpp
class Solution {
public:
    int rangeBitwiseAnd(int m, int n) {
        int xmask = m ^ n;
        int mlen = 0;
        int mask;

        if ((xmask >> (mlen + 16)) > 0) mlen += 16;
        if ((xmask >> (mlen + 8)) > 0) mlen += 8;
        if ((xmask >> (mlen + 4)) > 0) mlen += 4;
        if ((xmask >> (mlen + 2)) > 0) mlen += 2;
        if ((xmask >> (mlen + 1)) > 0) mlen ++;

        mask = ~0 << mlen;

        return m & mask;
    }
};
```

# 数学法1(72ms)
时间复杂度：O(1)

可以用数学方法消掉上面的迭代过程

```cpp
class Solution {
public:
    int rangeBitwiseAnd(int m, int n) {
        int c = (int)ceil(log(n-m+1) / log(2));
        return ((m&n) >> c) << c;
    }
};
```

# 数学法2(68ms)
也可以用log求异或结果的最高位
```cpp
class Solution {
public:
    int rangeBitwiseAnd(int m, int n) {
        int c = ceil(log(m^n) / log(2));
        // 注意必须用m，用n回出错，比如m=4, n=6
        return (m >> c) << c;
    }
};
```

# 递归法(84ms)
优势是写起来简单，只有一行
```cpp
class Solution {
public:
    int rangeBitwiseAnd(int m, int n) {
        // m < n时说明未提取到左侧公共部分
        return (m < n) ? (rangeBitwiseAnd(m>>1, n>>1) << 1) : m;
    }
};
```

[1]: https://leetcode.com/problems/bitwise-and-of-numbers-range/