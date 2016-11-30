题目链接: [280.Wiggle Sort][1]
难度: Medium

Given an unsorted array nums, reorder it in-place such that nums[0] <= nums[1] >= nums[2] <= nums[3]....

For example, given nums = [3, 5, 2, 1, 6, 4], one possible answer is [1, 6, 2, 5, 3, 4].

# 迭代(52ms)
时间复杂度：O(N)
空间复杂度：O(1)

```cpp
class Solution {
public:
    void wiggleSort(vector<int>& nums) {
        for (int i = 1; i < nums.size(); i += 2) {
            if (nums[i] < nums[i-1]) swap(nums[i], nums[i-1]);
            if (i + 1 < nums.size() && nums[i]<nums[i+1]) swap(nums[i], nums[i+1]);
        }
    }
};
```

[1]: https://leetcode.com/problems/wiggle-sort/