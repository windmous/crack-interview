题目链接: [90.Subsets II][1]
难度: Medium

- 给定可能含有重复元素的集合，返回所有子集
- 单个子集中可以有重复元素，但是不能有相同的子集

参见P78

# dfs增量构造法 8ms

```cpp
class Solution {
public:
    vector<vector<int> > subsetsWithDup(vector<int> &S) {
        sort(S.begin(), S.end());  // 必须排序

        vector<vector<int> > result;
        vector<int> path;

        dfs(S, S.begin(), path, result);
        return result;
    }

private:
    static void dfs(const vector<int> &S, vector<int>::iterator start,
            vector<int> &path, vector<vector<int> > &result) {
        result.push_back(path);
		//每次到达此处，都是选择放入下一个位置的元素。这个元素不能和之前放在此处的元素重复
        for (auto i = start; i < S.end(); i++) {
            if (i != start && *i == *(i-1)) continue;
            path.push_back(*i);
            dfs(S, i + 1, path, result);
            path.pop_back();
        }
    }
};
```

# 迭代 12ms

这是P78中的迭代：

This problem can also be solved iteratively. Take [1, 2, 3] in the problem statement as an example. The process of generating all the subsets is like:
```
1. Initially: [[]]
2. Adding the first number to all the existed subsets: [[], [1]];
3. Adding the second number to all the existed subsets: [[], [1], [2], [1, 2]];
4. Adding the third number to all the existed subsets: [[], [1], [2], [1, 2], [3], [1, 3], [2, 3], [1, 2, 3]].
Have you got the idea :-)
```

到了这题的改变是：If we want to insert an element which is a dup, we can only insert it after the newly inserted elements from last step.

```cpp
vector<vector<int> > subsetsWithDup(vector<int> &S) {
    sort(S.begin(), S.end());
    vector<vector<int>> ret = {{}};
    int size = 0, startIndex = 0;
    for (int i = 0; i < S.size(); i++) {
        startIndex = i >= 1 && S[i] == S[i - 1] ? size : 0;
        size = ret.size();
        for (int j = startIndex; j < size; j++) {
            vector<int> temp = ret[j];
            temp.push_back(S[i]);
            ret.push_back(temp);
        }
    }
    return ret;
}
```

# bit manipulation 20ms

soul machine中给出一种bit manipulation的方法，用set去重（个人感觉这样实现不太好）

```cpp
class Solution {
public:
    vector<vector<int> > subsetsWithDup(vector<int> &S) {
        sort(S.begin(), S.end()); // 必须排序
        // 用 set 去重，不能用 unordered_set，因为输出要求有序
        set<vector<int> > result;
        const size_t n = S.size();
        vector<int> v;

        for (size_t i = 0; i < 1U << n; ++i) {
            for (size_t j = 0; j < n; ++j) {
                if (i & 1 << j)
                    v.push_back(S[j]);
            }
            result.insert(v);
            v.clear();
        }
        vector<vector<int> > real_result;
        copy(result.begin(), result.end(), back_inserter(real_result));
        return real_result;
    }
};
```

[1]: https://leetcode.com/problems/subsets-ii/