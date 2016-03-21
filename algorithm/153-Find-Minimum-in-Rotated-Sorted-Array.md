题目链接: [153.Find Minimum in Rotated Sorted Array][1]
难度: Medium

描述：给出一个旋转的排序数组，求最小值。数组中所有元素均不重复

# 二分法(4ms)
时间复杂度：O(logN)
空间复杂度：O(1)

```cpp
class Solution {
public:
    int findMin(vector<int>& nums) {
        int low = 0, high = nums.size() - 1;
        while (low < high && nums[low] >= nums[high]) { // 循环不变量：转折点在nums[low..high]之中
            const int mid = low + (high - low) / 2;
            if (nums[mid] >= nums[high]) {
                low = mid + 1;
            } else {
                high = mid;
            }
        }
        
        return nums[low];
    }
};
```

[1]: https://leetcode.com/problems/find-minimum-in-rotated-sorted-array/