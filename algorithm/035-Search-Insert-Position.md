题目链接: [35.Search Insert Position][1]
难度: Medium

- 实现lower_bound

#左闭右开
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

# 左闭右闭

```cpp
class Solution {
public:
    int searchInsert(vector<int>& nums, int target) {
        int len = nums.size();
        if (len == 0) return 0;
        
        int left = 0, right = len - 1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if      (nums[mid] < target) left = mid + 1;
            else if (nums[mid] > target) right = mid - 1;
            else                         right = mid - 1;
        }
        
        return left;
    }
};
```

[1]: https://leetcode.com/problems/search-insert-position/