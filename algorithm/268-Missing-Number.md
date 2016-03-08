题目链接: [268.Missing Number][1]
难度: Medium

描述：给n个不同的数字，这n个数字实际是从n+1个从0开始的连续整数中剔除了一个得到的。请找出踢掉的这个数是几。

要求线性时间内解决，且仅使用常数空间。注意输入的n个数字不是按序排放的。

# 位运算(36ms)
时间复杂度：O(N)
空间复杂度：O(1)

设给定的nums的大小为N，则若没有踢掉某数字，每个数字及其索引是：
```
索引：0 1 2 ... N
整数：0 1 2 ... N
```

由于踢掉了一个数字（假设踢掉了1），则变成了：
```
索引：0 1 2 ... N-1
整数：0 - 2 ... N-1 N
```
因此，若使用XOR运算将所有索引和整数异或一次，将得到：(x ^ N)，其中x是缺失的数值。因此我们只要将其与N再异或一次就得到目标值x了。

```cpp
class Solution {
public:
    int missingNumber(vector<int>& nums) {
        int result = 0;
        for (int i = 0; i < nums.size(); i++)
            result ^= nums[i]^(i+1);
        return result;
    }
};
```

# 排序+二分法(68ms)
时间复杂度：O(NlogN)
空间复杂度：O(1)

由于输入已经是排序了的，所以我们只要搜索一个位置i使nums[i]!=i即可。

```cpp
class Solution {
public:
    int missingNumber(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        
        int x = 0, y = nums.size();
        while (x < y) {
            int mid = (x + y) / 2;
            if (nums[mid] == mid) x = mid + 1;
            else y = mid;
        }
        
        return x;
    }
};
```

# 加和法(36ms)
时间复杂度：O(N)
空间复杂度：O(1)

看看理论上序列的和跟实际的序列和之差即可。
```cpp
class Solution {
public:
    int missingNumber(vector<int>& nums) {
        int sum = (nums.size() * (nums.size() + 1)) / 2;
        return sum - accumulate(nums.begin(), nums.end(), 0);
    }
};
```

# Swap法(40ms)
时间复杂度：O(N)
空间复杂度：O(1)

我们试图让num[i]回到坐标为nums[i]的位置上。最终检测一下哪里失常即可。

```cpp
class Solution {
public:
    int missingNumber(vector<int>& nums) {
        for (int i = 0; i < nums.size(); ++i) {
        	// 每一次swap都会令一个整数回到它应到的位置上
            while (nums[i] != i && nums[i] < nums.size()) 
                swap(nums[i], nums[nums[i]]);
        }
    
        for (int i = 0; i < nums.size(); ++i)
            if (nums[i] != i) return i;
    
        return nums.size();
    }
};
```

[1]: https://leetcode.com/problems/missing-number/