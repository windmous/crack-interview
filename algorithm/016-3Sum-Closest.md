题目链接: [16.3Sum Closest][1]
难度: Medium

- 在数组中找三个数使其和最接近给定的target，返回这三个数的和。保证有唯一解
- 注意与3sum的区别，本题每移动一次第二个数或者第三个数，都需要检查一次答案是否有更新

# 排序+左右夹逼 
12ms, 时间O(N^2)

```cpp
class Solution {
public:
	int threeSumClosest(vector<int>& nums, int target) {
		int len = nums.size();
		if (len <= 2) return -1;

		sort(nums.begin(), nums.end());
		int ans = nums[0] + nums[1] + nums[2]; // 不能置为INT_MAX，否则abs(INT_MAX - 某个负数)会等于一个很小的数！
		for (int i = 0; i < len;) {
			int left = i + 1, right = len - 1;
			while (left < right) {
				int sum = nums[i] + nums[left] + nums[right];
				if (abs(sum - target) < abs(ans - target)) ans = sum;

				if (sum == target) return sum;
				else if (sum < target) {
					do { ++left; } while (left < right && nums[left] == nums[left - 1]);
				}
				else {
					do { --right; } while (left < right && nums[right] == nums[right + 1]);
				}
			}

			do { ++i; } while (i < len && nums[i] == nums[i - 1]);
		}
		return ans;
	}
};
```


[1]: https://leetcode.com/problems/3sum-closest/