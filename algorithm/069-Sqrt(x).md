题目链接: [69.Sqrt(x)][1]
难度: Medium

# 二分法 O(LOG N)
8ms
```cpp
class Solution {
public:
    int mySqrt(int x) {
		if (x < 2) return x;
        int left = 1, right = x;

        while(true) {
            const int mid = left + (right - left) / 2;
            if (mid > x / mid)  
				right = mid - 1;
			else {
				// mid是sqrt(x)的条件：mid * mid <= x < (mid+1) * (mid+1)
				if (mid + 1 > x / (mid + 1))  
					return mid;
				else
					left = mid + 1;
			}
        }
        return -1;
    }
};
```

# bit manipulation O(1)

逐个确定int解的每一位
```cpp
class Solution {
public:
	int mySqrt(int x) {
		unsigned int res = 0;
		for (int i = 15; i >= 0; i--)
		{
			if ((res + (1 << i)) * (res + (1 << i)) <= x)
				res += (1 << i);
		}
		return res;
	}
};
```

# Newton's method

略专业
https://en.wikipedia.org/wiki/Integer_square_root#Using_only_integer_division

```cpp
    long r = x;
    while (r*r > x)
        r = (r + x/r) / 2;
    return r;
```

[1]: https://leetcode.com/problems/sqrtx/