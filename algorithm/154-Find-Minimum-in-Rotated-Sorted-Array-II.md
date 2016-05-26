题目链接: [154.Find Minimum in Rotated Sorted Array II][1]
难度: Hard

描述：给定一个旋转的排序数组，找出最小值。注意数组中可能有重复元素。

# 二分法(8ms)
时间复杂度：O(N)
空间复杂度：O(1)

```cpp
class Solution {
public:
    int findMin(vector<int>& nums) {
        int low = 0, high = nums.size() - 1;
        while (low < high) {
            const int mid = low + (high - low) / 2;
            if (nums[mid] == nums[high] && nums[low] == nums[high]) {
                return *min_element(nums.begin()+low, nums.begin()+high);
            } else if (nums[mid] > nums[high]) {
                low = mid + 1;
            } else {
                high = mid;
            }
        }
        return nums[low];
    }
};
```

# 二分法(8ms)

```cpp
class Solution {
public:
    int findMin(vector<int>& nums) {
        int low = 0, high = nums.size();
        while (low < high) {
            int mid = low + (high - low) / 2;
            // 找到转折点
            if (mid != low && nums[mid] < nums[mid-1]) {
                return nums[mid];
            } else if (nums[low] == nums[mid] && nums[mid] == nums[high-1]) {
                return *min_element(nums.begin()+low, nums.begin()+high);
            } else if (nums[mid] <= nums[high-1]) {
                high = mid;
            } else {
                low = mid + 1;
            }
        }
        return nums[low];
    }
};
```


[1]: https://leetcode.com/problems/find-minimum-in-rotated-sorted-array-ii/