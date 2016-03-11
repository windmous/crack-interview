题目链接: [77.Combinations][1]
难度: Medium

- 从1..n这n个数中挑出k个数，求所有的挑法

# dfs
https://leetcode.com/discuss/12915/my-shortest-c-solution-using-dfs

my idea is using backtracking ,every time I push a number into vector,then I push a bigger one into it; then i pop the latest one,and push a another bigger one... and if I has push k number into vector,I push this into result;

```cpp
class Solution {
public:
    vector<vector<int> > combine(int n, int k) {
        vector<vector<int> > result;
        vector<int> path;
        dfs(n, k, 1, 0, path, result);
        return result;
    }
private:
    // start，开始的数, cur，已经选择的数目
    static void dfs(int n, int k, int start, int cur,
            vector<int> &path, vector<vector<int> > &result) {
        if (cur == k) {
            result.push_back(path);
        }
        for (int i = start; i <= n; ++i) {
            path.push_back(i);
            dfs(n, k, i + 1, cur + 1, path, result);
            path.pop_back();
        }
    }
};
```

# dfs 的迭代版
https://leetcode.com/discuss/63109/short-iterative-c-answer-8ms
```cpp
class Solution {
public:
    vector<vector<int>> combine(int n, int k) {
        vector<vector<int>> result;
        int i = 0;
        vector<int> p(k, 0);
        while (i >= 0) {
            p[i]++;
            if (p[i] > n) --i;
            else if (i == k - 1) result.push_back(p);
            else {
                ++i;
                p[i] = p[i - 1];
            }
        }
        return result;
    }
};
```

# 迭代
soul machine
```cpp
// use prev_permutation()
// 时间复杂度O((n-k)!)，空间复杂度O(n)
class Solution {
public:
    vector<vector<int> > combine(int n, int k) {
        vector<int> values(n);
        iota(values.begin(), values.end(), 1);

        vector<bool> select(n, false);
        fill_n(select.begin(), k, true);

        vector<vector<int> > result;
        do{
            vector<int> one(k);
            for (int i = 0, index = 0; i < n; ++i)
                if (select[i])
                    one[index++] = values[i];
            result.push_back(one);
        } while(prev_permutation(select.begin(), select.end()));
        return result;
    }
};
```

[1]: https://leetcode.com/problems/combinations/