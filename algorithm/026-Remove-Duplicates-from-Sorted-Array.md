题目链接: [26.Remove Duplicates from Sorted Array][1]
难度: Easy

- 实现STL的unique操作，给sorted vector，删除重复元素，返回元素个数

32ms

```cpp
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        if (nums.empty()) return 0;
        int len = 1;
        for (int i = 1; i < nums.size(); ++ i) {
            if (nums[i] != nums[i-1]) {
                nums[len ++] = nums[i];
            }
        }
        return len;
    }
};
```

35ms
```cpp
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        return unique(nums.begin(), nums.end()) - nums.begin();
    }
};
```

[1]: https://leetcode.com/problems/remove-duplicates-from-sorted-array/