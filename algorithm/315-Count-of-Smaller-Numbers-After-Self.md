题目链接: [315.Count of Smaller Numbers After Self][1]
难度: Hard

高端解：Binary Search Tree, Binary Indexed Tree, Segment Tree

# MergeSort方法(43ms)
时间复杂度：O(NlogN)
空间复杂度：O(N+logN)

```cpp
class Solution {
public:
    vector<int> countSmaller(vector<int>& nums) {
        vector<pair<int,int>> elements, aux;
        aux.resize(nums.size());
        
        for (int i = 0; i < nums.size(); ++ i) {
            elements.push_back({nums[i],i});
        }
        
        vector<int> result(nums.size(), 0);
        solve(elements, aux, result, 0, nums.size());
        return result;
    }
    
    void solve(vector<pair<int,int>> &nums, vector<pair<int,int>> &aux, vector<int> &result, int low, int high) {
        if (high - low <= 1) return ;
        int mid = low + (high - low) / 2;
        solve(nums, aux, result, low, mid);
        solve(nums, aux, result, mid, high);
        merge_and_count(nums, aux, result, low, mid, high);
    }
    
    void merge_and_count(vector<pair<int,int>> &nums, vector<pair<int,int>> &aux, vector<int> &result, 
            int low, int mid, int high) {
        copy(nums.begin()+low, nums.begin()+high, aux.begin()+low);
        int i = low, j = mid, k = low;
        while (i < mid && j < high) {
            if (aux[i].first <= aux[j].first) {
                nums[k++] = aux[i];
                result[aux[i ++].second] += j - mid;
            } else {
                nums[k++] = aux[j++];
            }
        }
        
        while (i < mid) {
            nums[k++] = aux[i];
            result[aux[i++].second] += j - mid;
        }
        while (j < high) nums[k++] = aux[j++];
    }
};
```

[1]: https://leetcode.com/problems/count-of-smaller-numbers-after-self/