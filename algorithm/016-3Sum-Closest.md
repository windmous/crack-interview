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
		if(nums.size() < 3) return 0;
		int closest = nums[0]+nums[1]+nums[2];
		sort(nums.begin(), nums.end());
		
		for(int first = 0 ; first < nums.size()-2 ; ++first) {
			if(first > 0 && nums[first] == nums[first-1]) continue; // skip duplication
			int second = first+1;
			int third = nums.size()-1;            
			while(second < third) {
				int curSum = nums[first]+nums[second]+nums[third];
				if(curSum == target) return curSum;
				if(abs(target-curSum)<abs(target-closest)) {
					closest = curSum;
				}
				if(curSum > target) {
					--third;
				} else {
					++second;
				}
			}
		}
		return closest;
	}
};
```


[1]: https://leetcode.com/problems/3sum-closest/