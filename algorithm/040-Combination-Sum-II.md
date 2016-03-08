题目链接: [40.Combination Sum II][1]
难度: Medium

- 在一个候选集C中找到和为T的所有组合，候选集的元素在每个答案中只能用一次（但可能有重复元素）

# dfs 12ms

```cpp
class Solution {
public:
    vector<vector<int> > combinationSum2(vector<int> &candidates, int target) {
        sort(candidates.begin(), candidates.end());
        vector<vector<int> > res;
        vector<int> combination;
        combinationSum2(candidates, target, res, combination, 0);
        return res;
    }
private:
    void combinationSum2(vector<int> &candidates, int target, vector<vector<int> > &res, vector<int> &combination, int begin) {
        if  (!target) {
            res.push_back(combination);
            return;
        }
        for (int i = begin; i != candidates.size() && target >= candidates[i]; ++i)
            if (i == begin || candidates[i] != candidates[i - 1]) { // 若 i ！= begin，并且candidate[i] == candidate[i - 1]，说明即将扫描的元素刚出现过，若执意要扫则会出现重复结果
                combination.push_back(candidates[i]);
                combinationSum2(candidates, target - candidates[i], res, combination, i + 1);
                combination.pop_back();
            }
    }
};
```


[1]: https://leetcode.com/problems/combination-sum-ii/