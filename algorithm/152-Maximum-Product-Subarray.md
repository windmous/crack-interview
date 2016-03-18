题目链接: [152.Maximum Product Subarray][1]
难度: Medium

描述：给一个数组，求最大的子数组乘积

# 动态规划(4ms)
时间复杂度：O(N)
空间复杂度：O(1)

最大值有两个来源，若当前值为负数，则与之前最小的负数相乘可得到更大的整数。若当前值为正数，则与之前最大的数相乘即可得到更大的整数。

```
class Solution {
public:
    int maxProduct(vector<int>& nums) {
    	// 将ans、max_val等初始化为0，则下面这行是必须的
        if (nums.size() == 1) return nums[0];
        
        int ans = 0;
        int max_val = 0, min_val = 0;
        
        for (const int e : nums) {
            if (e < 0) {
                swap(max_val, min_val);
            }
            
            max_val = max(e, max_val * e);
            min_val = min(e, min_val * e);
            
            ans = max(ans, max_val);
        }
        
        return ans;
    }
};
```


# 模式思考(4ms)
时间复杂度：O(N)
空间复杂度：O(1)

给定连续的一串数，我们将相邻的同符号正数相乘，最终得到类似AbCdEfG这种字符串，其中我们用小写表示负数，大写表示正数。如果是以负数开始，那么可以假设A或者G是1即可。

对于串AbCdEfG，最大值必然是AbCdE和CdEfG两者之一，任意其它子字符串均可扩展。所以下述方法分别从左到右和从右到左搜索，最终得到结果。对于可能存在的0元素，程序直接将product重置。

```cpp
class Solution {
public:
    int maxProduct(vector<int>& nums) {
        int frontProduct = 1;
        int backProduct = 1;
        int ans = INT_MIN;
        
        for (int i = 0; i < nums.size(); ++i) {
            frontProduct *= nums[i];
            backProduct *= nums[nums.size() - i - 1];
            
            ans = max(ans,max(frontProduct,backProduct));
            
            frontProduct = frontProduct == 0 ? 1 : frontProduct;
            backProduct = backProduct == 0 ? 1 : backProduct;
        }
        return ans;
    }
};
```

[1]: https://leetcode.com/problems/maximum-product-subarray/