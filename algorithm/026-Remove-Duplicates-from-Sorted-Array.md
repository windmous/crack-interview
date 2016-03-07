题目链接: [26.Remove Duplicates from Sorted Array][1]
难度: Easy

- 实现STL的unique操作，给sorted vector，删除重复元素，返回元素个数

32ms

```cpp
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        if (nums.size() < 2) 
            return nums.size();
        
        int pre = 1, post = 1;
        while (post < nums.size()) {
            if (nums[post] != nums[post - 1]) 
                nums[pre++] = nums[post++];
            else  
                ++post;
        }
        
        return pre;
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