题目链接: [39.Combination Sum][1]
难度: Medium

- 在一个候选集C中找到和为T的所有组合，候选集的元素可使用多次

# dfs 16ms

```cpp
class Solution {
public:
    vector<vector<int> > combinationSum(vector<int> &candidates, int target) {
        sort(candidates.begin(), candidates.end());
        vector<vector<int> > res;      // 最终结果
        vector<int> combination;       // 中间结果
        combinationSum(candidates, target, res, combination, 0);
        return res;
    }
private:
    void combinationSum(vector<int> &candidates, int target, vector<vector<int> > &res, vector<int> &combination, int begin) {
        if  (!target) {
            res.push_back(combination);
            return;
        }
        for (int i = begin; i != candidates.size() && target >= candidates[i]; ++i) {
            combination.push_back(candidates[i]);
            combinationSum(candidates, target - candidates[i], res, combination, i);
            combination.pop_back();
        }
    }
};
```


# 动态规划 44ms

answer[i] 是`vector<vector<int>>`类型，存的是和为i的所有元素组合
对于每个候选元素，尽量多地将其塞入answer中

```cpp
class Solution {
public:
	vector<vector<int> > combinationSum(vector<int> &candidates, int target) {
		vector<vector<vector<int> >> answer(target + 1);

		sort(candidates.begin(), candidates.end());
		answer[0].emplace_back(vector<int>());
		for (int i = 0; i<candidates.size(); ++i) { // 对每个候选元素
			for (int j = 0; j <= target - candidates[i]; ++j) { // 找到可以塞入的地方
				for (int k = 0; k < answer[j].size(); ++k) {    // 逐个塞入
					vector<int> ans = answer[j][k];
					ans.push_back(candidates[i]);
					answer[j + candidates[i]].emplace_back(ans);
				}
			}
		}
		return answer[target];
	}
};
```


[1]: https://leetcode.com/problems/combination-sum/