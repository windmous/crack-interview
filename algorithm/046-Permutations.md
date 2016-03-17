题目链接: [46.Permutations][1]
难度: Medium

- 输出一个vector的所有permutation，vector中没有重复元素。
- 这道题只要求得到所有的permutation，没有要求输出的permutation是排好序的，dfs解法的输出就是没有排序的结果。

# 调用next_permutation 16ms

人工实现next_permutation详见P31

```cpp
class Solution {
public:
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>> result;
        sort(nums.begin(), nums.end());
        
        do {
            result.push_back(nums);
        } while (next_permutation(nums.begin(), nums.end()));
        return result;
    }
};
```

# dfs遍历 12ms

```cpp
class Solution {
public:
    vector<vector<int> > permute(vector<int> &num) {
        vector<vector<int> > result;

        permuteRecursive(num, 0, result);
        return result;
    }

    // permute num[begin..end]
    // invariant: num[0..begin-1] have been fixed/permuted
    void permuteRecursive(vector<int> &num, int begin, vector<vector<int> > &result)    {
        if (begin >= num.size()) {
            // one permutation instance
            result.push_back(num);
            return;
        }

        for (int i = begin; i < num.size(); i++) {
            swap(num[begin], num[i]);
            permuteRecursive(num, begin + 1, result);
            // reset
            swap(num[begin], num[i]);
        }
    }
};
```

[1]: https://leetcode.com/problems/permutations/