题目链接: [303.Range Sum Query - Immutable][1]
难度: Easy

给一个数组，查询第i到第j个下标（闭区间）内元素之和。有多次查询

```cpp
class NumArray {
public:
    NumArray(vector<int> &nums) {
        int len = nums.size();
        accum.resize(len + 1);
        accum[0] = 0;
        for (int i = 0; i < len; ++i) 
            accum[i+1] = accum[i] + nums[i];
    }

    int sumRange(int i, int j) {
        return accum[j+1] - accum[i];
    }
private:
    vector<int> accum;
};

```

[1]: https://leetcode.com/problems/range-sum-query-immutable/