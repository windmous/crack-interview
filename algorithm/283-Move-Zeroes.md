题目链接: [283.Move Zeroes][1]
难度: Easy

描述：给定一组整数，将所有的0移动右侧，而将非零值移动左侧，注意非零值的相对顺序不能给改变。

# 模拟法(16ms)
时间复杂度：O(N)
空间复杂度：O(1)

维持A、B两个指针，A向前搜寻，B指向最早的空闲区域，一旦A发现了一个非0整数就移向

```cpp
class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        for (int i = 0, j = 0; i < nums.size(); i++) {
            if (nums[i])
               swap(nums[j++],nums[i]);
        }
    }
};
```

# STL方法(20ms)
时间复杂度：O(N)
空间复杂度：O(1)

直接调用STL的stable_partition即可完成该题目中指定的功能。

```cpp
class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        stable_partition(nums.begin(), nums.end(), [](int x) {return x != 0;});
    }
};
```

# STL方法2(20ms)
时间复杂度：O(N)
空间复杂度：O(1)

```cpp
class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        fill(remove_if(nums.begin(), nums.end(), 
                      [](int x) {return x == 0;}), 
             nums.end(), 0);
    }
};
```

[1]: https://leetcode.com/problems/move-zeroes/