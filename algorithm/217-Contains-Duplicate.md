题目链接: [217.Contains Duplicate][1]
难度: Easy

# 排序法(NlgN)(36ms)
```cpp
class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        for (int i = 1; i < nums.size(); ++ i) {
            if (nums[i] == nums[i-1])
                return true;
        }
        return false;
    }
};
```

或者使用STL：
```cpp
class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        return nums.size() != distance(nums.begin(), unique(nums.begin(), nums.end()));
    }
};
```

# 哈希表(52ms)
时间复杂度：O(N)
```cpp
class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
        return nums.size() > unordered_set<int>(nums.begin(), nums.end()).size();
    }
};
```



[1]: https://leetcode.com/problems/contains-duplicate/