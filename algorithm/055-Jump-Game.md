题目链接: [55.Jump Game][1]
难度: Medium

P45 jump-game II 的简化版，判断能否到达最后一个元素

```cpp
class Solution {
public:
    bool canJump(vector<int>& nums) {
        if (nums.size() < 2) return true;
        
        int reach = 0;
        for (int i = 0; i < nums.size() && reach >= i; ++i)
            reach = max(reach, i + nums[i]);
        return reach >= nums.size() - 1;
    }
};
```

[1]: https://leetcode.com/problems/jump-game/