题目链接: [81.Search in Rotated Sorted Array II][1]
难度: Medium

- 在[4 5 6 7 0 1 2]这样的Rotated Sorted Array中找某个元素是否存在，与P33相比，此题的array可能有重复元素
- mid只有三种情况：
```
1)           2)
                     /
      o            o <-2
     /           /
   o <- 1      o              o
 /                          / 
o                         o <-3
                         /
						 
```

# 二分查找
```cpp
class Solution {
public:
    bool search(vector<int>& nums, int target) {
        int low = 0, high = nums.size();
        while (low < high) {
            const int mid = low + (high - low) / 2;
            if (target == nums[mid]) {
                return true;
            }
            
            if (nums[low] < nums[mid]) {
                if (nums[low] <= target && target < nums[mid]) {
                    high = mid;
                } else {
                    low = mid + 1;
                }
            } else if (nums[low] > nums[mid]) {
                if (nums[mid] < target && target <= nums[high-1]) {
                    low = mid + 1;
                } else {
                    high = mid;
                }
            } else {
                ++ low;
            }
        }
        return false;
    }
};
```

[1]: https://leetcode.com/problems/search-in-rotated-sorted-array-ii/