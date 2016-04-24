题目链接: [53.Maximum Subarray][1]
难度: Medium

- 在串中找到和最大的连续子串

# O(n)时间，O(1)空间

第i个元素要么加入之前的子串，要么自起炉灶
```cpp
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int len = nums.size();
        if (len <= 1) return nums[0];
        
        int res = nums[0], subseq = nums[0];
        for (int i = 1; i < len; ++i) {
            subseq = max(subseq + nums[i], nums[i]);
            res = max(res, subseq);
        }
        return res;
    }
};
```

[1]: https://leetcode.com/problems/maximum-subarray/