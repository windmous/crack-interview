题目链接: [330.Patching Array][1]
难度: Medium

# 迭代(6ms,56.95%)
时间复杂度：O(N)
空间复杂度：O(1)

Let miss be the smallest sum in [0,n] that we might be missing. Meaning we already know we can build all sums in [0,miss). Then if we have a number num <= miss in the given array, we can add it to those smaller sums to build all sums in [0,miss+num). If we don't, then we must add such a number to the array, and it's best to add miss itself, to maximize the reach.

```cpp
class Solution {
public:
    int minPatches(vector<int>& nums, int n) {
        long miss = 1;
        int ans = 0, i = 0;
        while (miss <= n) {
            if (i < nums.size() && miss >= nums[i]) {
                miss += nums[i++];
            } else {
                miss += miss;
                ans ++;
            }
        }
        return ans;
    }
};
```

[1]: https://leetcode.com/problems/patching-array/