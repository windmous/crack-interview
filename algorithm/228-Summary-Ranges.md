题目链接: [228.Summary Ranges][1]
难度: Easy

# 模拟法(0ms)
时间复杂度：O(N)
```cpp
class Solution {
public:
    vector<string> summaryRanges(vector<int>& nums) {
        vector<string> result;
        
        for (int i = 0; i < nums.size(); ++ i) {
            const int pre = nums[i];
            while (i + 1 < nums.size() && nums[i+1] == nums[i]+1)
                ++ i;
            if (nums[i] == pre) {
                result.push_back(std::to_string(pre));
            } else {
                result.push_back(std::to_string(pre) + "->" + std::to_string(nums[i]));
            }
        }
        return result;
    }
};
```


[1]: https://leetcode.com/problems/summary-ranges/