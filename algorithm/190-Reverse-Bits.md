题目链接: [190.Reverse Bits][1]
难度: Easy

描述：给一个32bit无符号整数，求将所有二进制位左右逆序后的结果。

# 位操作法(4ms)
时间复杂度：O(log INT_MAX)
空间复杂度：O(1)
```cpp
class Solution {
public:
    uint32_t reverseBits(uint32_t n) {
        int ans = 0;
        for (int i = 0; i < 32; ++ i, n >>=1) {
            ans = (ans << 1) | (n & 1);
        }
        
        return ans;
    }
};
```

# 位操作2(4ms)

时间复杂度：O(log MAX_INT)
空间复杂度：O(1)

我们用4bit作为一个字母表示，那么前3次的变换如下：
abcdefgh -> efghabcd -> ghefcdab -> hgfedcba

```cpp
class Solution {
public:
    uint32_t reverseBits(uint32_t n) {
        n = (n >> 16) | (n << 16);
        n = ((n & 0xff00ff00) >> 8) | ((n & 0x00ff00ff) << 8);
        n = ((n & 0xf0f0f0f0) >> 4) | ((n & 0x0f0f0f0f) << 4);
        n = ((n & 0xcccccccc) >> 2) | ((n & 0x33333333) << 2);
        n = ((n & 0xaaaaaaaa) >> 1) | ((n & 0x55555555) << 1);
        return n;
    }
};
```

# In-Place解法(4ms)
时间复杂度：O(logMAX_INT)
空间复杂度：O(1)

本节利用了一个技巧，即如果需要交换两个bit，那么只要在两个地方都对1亦或一次即可

```cpp
class Solution {
public:
    uint32_t reverseBits(uint32_t n) {
        for (int i = 0; i < 16; i++)
            if ((n >> i & 1) ^ (n >> (31 - i) & 1)) // 两个bit值不相同
                n ^= (1 << i | 1 << (31 - i));
        return n;
    }
};
```

# 查表法(8ms)
时间复杂度：O((log2 MAX_INT)/2)
空间复杂度：O(MAX_BYTE)

本方法使用空间换时间的策略，预先计算每个字节(8位)反转之后的结果并存到表里。在求解时直接对每个byte逆序即可。

你可以选择缓存更小的bit数（如4bit）或者更多的bit数（如16bit）

```cpp
class Solution {
public:
    uint32_t reverseBits(uint32_t n) {
        static const uint8_t lookup[] = {0, 128, 64, 192, 32, 160, 96, 224, 16, 144, 80, 208, 48, 176, 112, 240, 8, 136, 72, 200, 40, 168, 104, 232, 24, 152, 88, 216, 56, 184, 120, 248, 4, 132, 68, 196, 36, 164, 100, 228, 20, 148, 84, 212, 52, 180, 116, 244, 12, 140, 76, 204, 44, 172, 108, 236, 28, 156, 92, 220, 60, 188, 124, 252, 2, 130, 66, 194, 34, 162, 98, 226, 18, 146, 82, 210, 50, 178, 114, 242, 10, 138, 74, 202, 42, 170, 106, 234, 26, 154, 90, 218, 58, 186, 122, 250, 6, 134, 70, 198, 38, 166, 102, 230, 22, 150, 86, 214, 54, 182, 118, 246, 14, 142, 78, 206, 46, 174, 110, 238, 30, 158, 94, 222, 62, 190, 126, 254, 1, 129, 65, 193, 33, 161, 97, 225, 17, 145, 81, 209, 49, 177, 113, 241, 9, 137, 73, 201, 41, 169, 105, 233, 25, 153, 89, 217, 57, 185, 121, 249, 5, 133, 69, 197, 37, 165, 101, 229, 21, 149, 85, 213, 53, 181, 117, 245, 13, 141, 77, 205, 45, 173, 109, 237, 29, 157, 93, 221, 61, 189, 125, 253, 3, 131, 67, 195, 35, 163, 99, 227, 19, 147, 83, 211, 51, 179, 115, 243, 11, 139, 75, 203, 43, 171, 107, 235, 27, 155, 91, 219, 59, 187, 123, 251, 7, 135, 71, 199, 39, 167, 103, 231, 23, 151, 87, 215, 55, 183, 119, 247, 15, 143, 79, 207, 47, 175, 111, 239, 31, 159, 95, 223, 63, 191, 127, 255};
        
        uint32_t ret;
        register uint8_t *p = (uint8_t *)&n, *q = (uint8_t *)&ret;
    
    	// 这里要再逆序一次
        q[0] = lookup[p[3]];
        q[1] = lookup[p[2]];
        q[2] = lookup[p[1]];
        q[3] = lookup[p[0]];
    
        return ret;
    }
};
```


# bitfiled法(8ms)
时间复杂度：O(log INT_MAX)
空间复杂度：O(1)

本方法利用了C++的bitfield语法，不建议使用。

```cpp
class Solution {
public:
    uint32_t reverseBits(uint32_t n) {
        struct bs
        {
            unsigned int _00:1; unsigned int _01:1; unsigned int _02:1; unsigned int _03:1;
            unsigned int _04:1; unsigned int _05:1; unsigned int _06:1; unsigned int _07:1;
            unsigned int _08:1; unsigned int _09:1; unsigned int _10:1; unsigned int _11:1;
            unsigned int _12:1; unsigned int _13:1; unsigned int _14:1; unsigned int _15:1;
            unsigned int _16:1; unsigned int _17:1; unsigned int _18:1; unsigned int _19:1;
            unsigned int _20:1; unsigned int _21:1; unsigned int _22:1; unsigned int _23:1;
            unsigned int _24:1; unsigned int _25:1; unsigned int _26:1; unsigned int _27:1;
            unsigned int _28:1; unsigned int _29:1; unsigned int _30:1; unsigned int _31:1;
        } *b = (bs*)&n, 
        c = 
        {	// 逆序存放
              b->_31, b->_30, b->_29, b->_28
            , b->_27, b->_26, b->_25, b->_24
            , b->_23, b->_22, b->_21, b->_20
            , b->_19, b->_18, b->_17, b->_16
            , b->_15, b->_14, b->_13, b->_12
            , b->_11, b->_10, b->_09, b->_08
            , b->_07, b->_06, b->_05, b->_04
            , b->_03, b->_02, b->_01, b->_00
        };

        return *(unsigned int *)&c;
    }
};
```


[1]: https://leetcode.com/problems/reverse-bits/