题目链接: [45.Jump Game II][1]
难度: Hard

- 数组中每个元素表示从这能跳多远，求跳至尾部花费的最少步数

# 贪心 16ms


```cpp
class Solution {
public:
	int jump(const vector<int>& nums) {
		int step = 0; // 最少步数
		int left = 0;
		int right = 0; // [left, right] 表示这一步能跳多远
		if (nums.size() == 1) return 0;
		while (left <= right) { // 尝试从每一层跳最远
		// 题目保证有解，因此不会跳出循环，但加上left <= right这个条件可以应对到不了终点的case
			++step;
			const int old_right = right;
			for (int i = left; i <= old_right; ++i) {
				int new_right = i + nums[i];
				if (new_right >= nums.size() - 1) return step;
				if (new_right > right) right = new_right;
			}
			left = old_right + 1;
		}
		return 0;
	}
};
```

[1]: https://leetcode.com/problems/jump-game-ii/