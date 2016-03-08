题目链接: [35.Search Insert Position][1]
难度: Medium

- 实现lower_bound

8ms

```cpp
class Solution {
public:
	int searchInsert(vector<int>& nums, int target) {
		return distance(nums.begin(), lower_bound(nums.begin(), nums.end(), target));
	}
	template<typename ForwardIterator, typename T>
	ForwardIterator lower_bound(ForwardIterator first,
		ForwardIterator last, T value) {
		while (first != last) {
			auto mid = next(first, distance(first, last) / 2);
			if (value > *mid) first = ++mid;
			else last = mid;
		}
		return first;
	}
};
```

[1]: https://leetcode.com/problems/search-insert-position/