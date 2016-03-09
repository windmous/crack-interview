题目链接: [53.Maximum Subarray][1]
难度: Medium

- 在串中找到和最大的连续子串

# O(n)时间，O(1)空间

第i个元素要么加入之前的子串，要么自起炉灶
```cpp
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int result = INT_MIN, subseq = 0;
        for (auto &i : nums) {
            subseq = max(subseq + i, i);
            result = max(result, subseq);
        }
        return result;
    }
};
```

[1]: https://leetcode.com/problems/maximum-subarray/