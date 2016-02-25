题目链接：[213. House Robber II][1]

## 动态规划(0ms)
关键是掌握问题拆分方法
```
class Solution {
public:
    int rob(vector<int>& nums) {
        const int n = nums.size();
        if (n < 2) return n ? nums[0] : 0;
        return max(do_rob(nums, 0, n - 2),
                   do_rob(nums, 1, n - 1));
    }
    
private:
    int do_rob(const vector<int> &nums, int left, int right) {
        int pre = 0, cur = 0;
        for (int i = left; i <= right; ++ i) {
            const int temp = max(pre + nums[i], cur);
            pre = cur;
            cur = temp;
        }
        
        return cur;
    }
};
```

[1]: https://leetcode.com/problems/house-robber-ii/