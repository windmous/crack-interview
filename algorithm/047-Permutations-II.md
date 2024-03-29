题目链接: [47.Permutations II][1]
难度: Medium

- 输出一个vector的所有permutation，vector中可能有重复元素

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

# 递归

```cpp
class Solution {
public:
    void recursion(vector<int> num, int i, int j, vector<vector<int> > &res) {
        if (i == j-1) {
            res.push_back(num);
            return;
        }
        for (int k = i; k < j; k++) {  // 决定将谁放入第i位
            if (i != k && num[i] == num[k]) continue;  // 跳过重复元素
            swap(num[i], num[k]);  // 将下一个不同元素放入第i位
            recursion(num, i+1, j, res);
        }
    }
    vector<vector<int> > permuteUnique(vector<int> &num) {
        sort(num.begin(), num.end());
        vector<vector<int> >res;
        recursion(num, 0, num.size(), res);
        return res;
    }
};
```

# 递归2
```cpp
class Solution {
public:
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        vector<vector<int>> result;
        vector<int> path;
        permute(result, path, nums);
        return result;
    }
    
    void permute(vector<vector<int>> &result, vector<int> &path, vector<int> &nums) {
        if (path.size() == nums.size()) {
            result.push_back(path);
            return ;
        }
        
        for (int i = 0; i < nums.size(); ++ i) {
            if (i && nums[i] == nums[i-1]) continue;
            int cnt = count(path.begin(), path.end(), nums[i]);
            int sum = count(nums.begin(), nums.end(), nums[i]);
            if (cnt < sum) {
                path.push_back(nums[i]);
                permute(result, path, nums);
                path.pop_back();
            }
        }
    }
};
```

[1]: https://leetcode.com/problems/permutations-ii/