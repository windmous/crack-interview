题目链接: [80.Remove Duplicates from Sorted Array II][1]
难度: Medium

- 给定sorted array，去除多余的duplicate，但允许元素出现两次

https://leetcode.com/discuss/42348/3-6-easy-lines-c-java-python-ruby
```cpp
int removeDuplicates(vector<int>& nums) {
    int i = 0;
    for (int n : nums)
        if (i < 2 || n > nums[i-2])
            nums[i++] = n;
    return i;
}
```


[1]: https://leetcode.com/problems/remove-duplicates-from-sorted-array-ii/