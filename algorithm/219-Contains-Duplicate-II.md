题目链接: [219.Contains Duplicate II][1]
难度: Easy

# 排序法(24ms)
时间复杂度：O(NlogN)
空间复杂度：O(N)

```cpp
class Solution {
public:
    bool containsNearbyDuplicate(vector<int>& nums, int k) {
        vector<pair<int, int>> nc_pairs;
        for (int i = 0; i < nums.size(); ++ i) {
            nc_pairs.push_back(make_pair(nums[i], i));
        }
        
        sort(nc_pairs.begin(), nc_pairs.end());
        for (int i = 1; i < nc_pairs.size(); ++ i) {
            if (nc_pairs[i].first == nc_pairs[i-1].first && 
                nc_pairs[i].second - nc_pairs[i-1].second <= k) {
                return true;
            }
        }
        return false;
    }
};
```

# 滑窗法(28ms)
时间复杂度：O(N)
空间复杂度：O(K)

```cpp
class Solution {
public:
    bool containsNearbyDuplicate(vector<int>& nums, int k) {
        unordered_set<int> wind;
        for (int i = 0; i < nums.size(); ++ i) {
            if (i > k) wind.erase(nums[i - k - 1]);
            if (!wind.insert(nums[i]).second) return true;
        }
        return false;
    }
};
```

# 哈希表法(32ms)
时间复杂度：O(N)
空间复杂度：O(N)

```cpp
class Solution {
public:
    bool containsNearbyDuplicate(vector<int>& nums, int k) {
        unordered_map<int, int> nmap;
        for (int i = 0; i < nums.size(); ++ i) {
            if (nmap.find(nums[i]) == nmap.end() || i - nmap[nums[i]] > k) {
                nmap[nums[i]] = i;
            } else {
                return true;
            }
        }
        return false;
    }
};
```

[1]: https://leetcode.com/problems/contains-duplicate-ii/