题目链接: [34.Search for a Range][1]
难度: Medium

- 寻找有序数组中值为target的下标起点和终点

# STL 12ms
```cpp
class Solution {
public:
	vector<int> searchRange(vector<int>& nums, int target) {
		const int l = distance(nums.begin(), lower_bound(nums.begin(), nums.end(), target));
		const int u = distance(nums.begin(), prev(upper_bound(nums.begin(), nums.end(), target)));
		if (l == nums.size() || nums[l] != target) // not found
			return vector < int > { -1, -1 };
		else
			return vector < int > { l, u };
	}
};
```

# 二分查找 12ms

class Solution {
public:
	vector<int> searchRange(vector<int>& nums, int target) {
		auto lower = lower_bound(nums.begin(), nums.end(), target);
		auto uppper = upper_bound(lower, nums.end(), target);
		if (lower == nums.end() || *lower != target)
			return vector<int> { -1, -1 };
		else
			return vector<int> {distance(nums.begin(), lower), distance(nums.begin(), prev(uppper))};
	}
	template<typename ForwardIterator, typename T>
	ForwardIterator lower_bound(ForwardIterator first,
		ForwardIterator last, T value) {  // 这种情况下要尽量将last向左移
		while (first != last) { 
			auto mid = next(first, distance(first, last) / 2);
			if (value > *mid) first = ++mid;
			else last = mid; // value <= *mid
		}
		return first;
	}
	template<typename ForwardIterator, typename T>
	ForwardIterator upper_bound(ForwardIterator first,
		ForwardIterator last, T value) {  // 这种情况下要尽量将first向右移
		while (first != last) {
			auto mid = next(first, distance(first, last) / 2);
			if (value >= *mid) first = ++mid; // 仅此不同
			else last = mid;    // value < *mid
		}
		return first;
	}
};

[1]: https://leetcode.com/problems/search-for-a-range/