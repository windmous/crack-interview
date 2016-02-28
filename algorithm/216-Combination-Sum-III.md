题目链接: [216.Combination Sum III][1]
难度: Medium

[TODO] 非递归解法

# 回溯法1(0ms)
时间复杂度：O(9^k)
```cpp
class Solution {
public:
    void solve(vector<vector<int>> &result, vector<int> path, int k, int n) {
        if (path.size() == k && n == 0) {
            result.push_back(path);
        }
        
        if (path.size() < k) {
            for (int i = path.empty()?1:path.back()+1; i <= min(9, n); ++ i) {
                path.push_back(i);
                solve(result, path, k, n-i);
                path.pop_back();
            }
        }
    }
    vector<vector<int>> combinationSum3(int k, int n) {
        vector<vector<int>> result;
        vector<int> path;
        solve(result, path, k, n);
        return result;
    }
};
```

# 回溯法(4ms)
时间复杂度：O(2^9)
```cpp
class Solution {
public:
    void solve(int n, int k, int i, vector<int> path, vector<vector<int>>& result) {
        if (i == 10) {
            if (n != 0 || k != 0) return ;
            result.push_back(path);
            return ;
        }
        
        solve(n, k, i+1, path, result);
        if (k > 0 && n >= i) {
            path.push_back(i);
            solve(n-i, k-1, i+1, path, result);
        }
    }
    vector<vector<int>> combinationSum3(int k, int n) {
        vector<vector<int>> result;
        vector<int> path;
        solve(n, k, 1, path, result);
        return result;
    }
};
```

[1]: https://leetcode.com/problems/combination-sum-iii/