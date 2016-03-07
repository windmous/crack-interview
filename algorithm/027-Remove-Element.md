题目链接: [27.Remove Element][1]
难度: Easy

- 实现STL的remove函数，删除指定元素

4ms
```cpp
class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        int begin=0;
        for(int i=0;i<nums.size();i++) 
            if(nums[i]!=val) 
                nums[begin++]=std::move(nums[i]); // move虽然对于int没卵用，但在模板类中就有用了
        return begin;
    }
};
```

4ms
```cpp
class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        return remove(nums.begin(), nums.end(), val) - nums.begin(); 
    }
};
```

[1]: https://leetcode.com/problems/remove-element/