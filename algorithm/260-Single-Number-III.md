题目链接: [260.Single Number III][1]
难度: Medium

描述：给定一串整数，其中有两个数字仅出现了一次，其余数字均出现两次。请找出这两个仅出现一次的数字。

# 奇偶(16ms)
时间复杂度：O(N)
空间复杂度：O(1)

When diff == numeric_limits<int>::min(), -diff is also numeric_limits<int>::min(). Therefore, the value of diff after executing diff &= -diff is still numeric_limits<int>::min(). The answer is still correct.这种情况下二进制表示上只有最高位1。

```cpp
class Solution
{
public:
    vector<int> singleNumber(vector<int>& nums) 
    {
        // Pass 1 : 
        // Get the XOR of the two numbers we need to find
        int diff = accumulate(nums.begin(), nums.end(), 0, bit_xor<int>());
        // 得到最低位bit1
        diff &= -diff;

        // Pass 2 :
        vector<int> rets = {0, 0}; // this vector stores the two numbers we will return
        for (int num : nums)
        {
            if ((num & diff) == 0) // the bit is not set
            {
                rets[0] ^= num;
            }
            else // the bit is set
            {
                rets[1] ^= num;
            }
        }
        return rets;
    }
};
```

下面是本方法的简化版本：(20ms)
```cpp
class Solution
{
public:
    vector<int> singleNumber(vector<int>& nums) {
        int a = 0, b = 0;
        for (int n : nums)                 a ^= n;
        for (int n : nums) if (n & a & -a) b ^= n;
        return {a ^ b, b};
    }
};


```


[1]: https://leetcode.com/problems/single-number-iii/