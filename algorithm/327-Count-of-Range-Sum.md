题目链接: [327.Count of Range Sum][1]
难度: Hard

# MergeSort方法(42ms)
时间复杂度：O(NlogN)
空间复杂度：O(logN + N)

两个核心trick：
1. 转成partial_sum后再执行merge_sort
2. 注意要插入一个额外的0， 否则用两两相减原则不能枚举所有的range-sum
3. 注意merge的时候是两层

```cpp
class Solution {
public:
    int countRangeSum(vector<int>& nums, int lower, int upper) {
        vector<long long> sums = {0};
        sums.insert(sums.end(), nums.begin(), nums.end());
        partial_sum(sums.begin(), sums.end(), sums.begin());
        aux.resize(sums.size());
        return solve(sums, 0, sums.size(), lower, upper);
    }

    int solve(vector<long long> &nums, int low, int high, const int val_lower, const int val_upper) {
        if (high - low <= 1)
            return 0;

        int mid = low + (high - low) / 2;
        int cnt = solve(nums, low, mid, val_lower, val_upper) + solve(nums, mid, high, val_lower, val_upper);

        // Do merge
        copy(nums.begin()+low, nums.begin()+high, aux.begin()+low);
        int i = low, j = mid, k = mid, l = mid, idx = low;
        for (int n = low; n < mid; ++ n) {
            while (k < high && aux[k] - aux[n] < val_lower) ++ k;
            while (l < high && aux[l] - aux[n] <= val_upper) ++ l;
            cnt += l - k;
        }

        while (i < mid && j < high) {
            if (aux[i] < aux[j]) nums[idx++] = aux[i++];
            else nums[idx++] = aux[j++];
        }
        while (i < mid) nums[idx++] = aux[i++];
        while (j < high) nums[idx++] = aux[j++];
        return cnt;
    }

    vector<long long> aux;
};
```

[1]: https://leetcode.com/problems/count-of-range-sum/