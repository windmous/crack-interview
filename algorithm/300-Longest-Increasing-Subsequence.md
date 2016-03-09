题目链接: [300.Longest Increasing Subsequence][1]
难度: Medium

描述：求最长的单调递增子序列长度。

# 动态规划1
时间复杂度：O(N^2)
空间复杂度：O(N)

令dp[i]表示子数组A[0...i]中最长公共子序列的长度。

```cpp
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        if (nums.size() == 0) return 0;
        
        vector<int> dp(nums.size(), 1);
        for (int i = 0; i < nums.size(); ++ i) {
            for (int j = 0; j < i; ++ j) {
                if (nums[i] > nums[j]) {
                    dp[i] = max(dp[i], 1+dp[j]);
                }
            }
        }
        
        return *max_element(dp.begin(), dp.end());
    }
};
```


# 动态规划2(4ms)
时间复杂度：O(NlogN)
空间复杂度：O(N)

思路：维护已经访问的部分中最长的且最“小”的子序列。这里最小的比价方法同字符串。只要维护好该序列，新来一个元素，我们通过简单的二分搜索即可知道是否能增长该子序列了。

```cpp
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        vector<int> res;
        for(int i=0; i<nums.size(); i++) {
            auto it = std::lower_bound(res.begin(), res.end(), nums[i]);
            if(it==res.end()) res.push_back(nums[i]);
            else *it = nums[i];
        }
        return res.size();
    }
};
```

# 动态规划3(5ms)
时间复杂度：O(NlogN)
空间复杂度：O(1)

我们可以直接使用输入的nums数组来记录最长公共子序列。

```cpp
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        if (nums.size() == 0)
            return nums.size();
        
        vector<int>::iterator lis_end = nums.begin();
        for (int& val : nums) {
            auto it = lower_bound(nums.begin(), lis_end, val);
            *it = val;
            if (it == lis_end)
                lis_end++;
        }
    
        return lis_end - nums.begin();
    }
};
```

[1]: https://leetcode.com/problems/longest-increasing-subsequence/