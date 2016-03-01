题目链接: [220.Contains Duplicate III][1]
难度: Medium

注意，本题的difference指的绝对值距离

# Set方法(48ms)
时间复杂度：O(NlogN)
```cpp(48ms)
class Solution {
public:
    bool containsNearbyAlmostDuplicate(vector<int>& nums, int k, int t) {
        set<int> wind;
        for (int i = 0; i < nums.size(); ++ i) {
            if (i > k) 
                wind.erase(nums[i-k-1]);
            
            // nums[i] - t 代表nums[i] t范围的下界
            auto pos = wind.lower_bound(nums[i]-t);
            if (pos != wind.end() && *pos - nums[i] <= t) 
                return true;
            wind.insert(nums[i]);
        }
        
        return false;
    }
};
```

# 桶方法(36ms)
时间复杂度：O(N)

映射到同一个桶里的数字一定是在t范围内的，映射到相邻桶的则需要做必要检查。
注意，这里桶大小应该是t+1而不是t！

```cpp
class Solution {
public:
    bool containsNearbyAlmostDuplicate(vector<int>& nums, int k, int t) {
        if (k < 1 || t < 0 || nums.empty())  return false;
        
        // 求最小值，作为重映射时的基
        long long base = accumulate(nums.begin()+1, 
                                    nums.end(), nums[0], 
                                    [](int x, int y) {return min(x, y);});
        unordered_map<long long, long long> buckets;
        
        for (int i = 0; i < nums.size(); ++ i) {
            if (i > k) {
                buckets.erase((nums[i-k-1]-base)/(t+1));
            }
            
            const long long remapped_num = nums[i] - base;
            const long long bucket_id = remapped_num / (t + 1LL);
            if (buckets.find(bucket_id) != buckets.end() ||
                (buckets.find(bucket_id-1) != buckets.end() && (remapped_num - buckets[bucket_id-1]) <= t) ||
                (buckets.find(bucket_id+1) != buckets.end() && (buckets[bucket_id+1] - remapped_num <= t))) {
                    return true;
            }
            
            buckets[bucket_id] = remapped_num;
        }
        
        return false;
    }
};
```

[1]: https://leetcode.com/problems/contains-duplicate-iii/