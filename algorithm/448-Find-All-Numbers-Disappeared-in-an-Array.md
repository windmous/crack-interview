题目链接: [448.Find All Numbers Disappeared in an Array][1]
难度: Easy

# 置换法
时间复杂度：O(N)
空间复杂度：O(1)

```cpp
class Solution {
public:
    vector<int> findDisappearedNumbers(vector<int>& nums) {
        for (int i = 0; i < nums.size(); ) {
            if (nums[i] == (i + 1) || nums[i] == -1) ++ i;
            else if (nums[nums[i]-1] != nums[i]) swap(nums[i], nums[nums[i]-1]);
            else nums[i++] = -1;
        }
        
        vector<int> result;
        for (int i = 0; i < nums.size(); ++ i) {
            if (nums[i] == -1) {
                result.push_back(i + 1);
            }
        }
        return result;
    }
};
```

# Mark by Negative标记法
时间复杂度：O(N)
空间复杂度：O(1)

如果一个位置的数字为负，表示这里被访问过了。

```cpp
class Solution {
public:
    vector<int> findDisappearedNumbers(vector<int>& nums) {
        for (int i = 0; i < nums.size(); ++ i) {
            int val = abs(nums[i]) - 1;
            nums[val] = -abs(nums[val]);
        }
        
        vector<int> result;
        for (int i = 0; i < nums.size(); ++ i) {
            if (nums[i] > 0) {
                result.push_back(i+1);
            }
        }
        return result;
    }
};
```

[1]: https://leetcode.com/problems/find-all-numbers-disappeared-in-an-array/
