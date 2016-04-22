题目链接: [307.Range Sum Query - Mutable][1]
难度: Medium

在P303基础上，原数组可被改变。改变和查询是均匀分布的。

# 线段树 

详见 https://leetcode.com/articles/range-sum-query-mutable/

```cpp
class NumArray {
public:
    NumArray(vector<int> &nums) {
        n = nums.size();
        tree = vector<int>(n * 2, 0);
        for (int i = 0; i < n; ++i) 
            tree[i + n] = nums[i];
        for (int i = n - 1; i >= 0; --i)
            tree[i] = tree[i * 2] + tree[i * 2 + 1];
    }

    void update(int i, int val) {
        int idx = i + n, ori = tree[idx];
        while (idx > 0) {
            tree[idx] = tree[idx] - ori + val;
            idx /= 2;
        }
    }

    int sumRange(int i, int j) {
        int l = i + n, r = j + n, sum = 0;
        while (l <= r) {
            if (l % 2 == 1) {
                sum += tree[l];
                ++l;
            }
            if (r % 2 == 0) {
                sum += tree[r];
                --r;
            }
            l /= 2;
            r /= 2;
        }
        return sum;
    }
    
private:
    vector<int> tree;
    int n;
};

```

[1]: https://leetcode.com/problems/range-sum-query-mutable/