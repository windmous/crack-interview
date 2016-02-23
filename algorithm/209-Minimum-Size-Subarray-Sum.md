题目链接：[209. Minimum Size Subarray Sum][1]

# 迭代法(4ms)
时间复杂度：O(n)
空间复杂度：O(1)

```cpp
class Solution {
public:
    int minSubArrayLen(int s, vector<int>& nums) {
        int start = 0, sum = 0, ans = INT_MAX;
        
        for (int i = 0; i < nums.size(); ++ i) {
            sum += nums[i];
            while (sum >= s) {
                ans = min(ans, i - start + 1);
                sum -= nums[start ++];
            }
        }
        
        return ans == INT_MAX ? 0 : ans;
    }
};
```

# 二分法(12ms)
时间复杂度：O(nlogn)
空间复杂度：O(n)

```cpp
class Solution {
public:
    int minSubArrayLen(int s, vector<int>& nums) {
        // 计算积分数组
        vector<int> sums = nums;
        for (int i = 1; i < sums.size(); ++ i) {
            sums[i] = sums[i - 1] + nums[i];
        }
        
        int ans = INT_MAX;
        for (int i = 0; i < nums.size(); ++ i) {
            auto pos = lower_bound(sums.begin()+i,
                                   sums.end(),
                                   sums[i]-nums[i]+s);
            if (pos != sums.end()) {
                ans = min<int>(ans, distance(sums.begin(), pos)-i+1);
            }
        }
        
        return ans == INT_MAX ? 0 : ans;
    }
};
```

# 二分法2(8ms)
本方法直接二分搜索数组长度本身
时间复杂度：O(nlogn)
空间复杂度：O(1)

```cpp
class Solution {
public:
    int minSubArrayLen(int s, vector<int>& nums) {
        int i = 1, j = nums.size();
        int ans = 0;
        while (i <= j) {
            int mid = i + (j - i) / 2;
            if (window_exists(mid, nums, s)) {
                ans = mid;
                j = mid - 1;
            } else {
                i = mid + 1;
            }
        }
        return ans;
    }
    
    bool window_exists(int size, vector<int> &nums, int s) {
        int sum = 0;
        for (int i = 0; i < nums.size(); ++ i) {
            if (i >= size) {
                sum -= nums[i - size];
            }
            
            if ((sum+=nums[i]) >= s) return true;
        }
        return false;
    }
};
```

[1]: https://leetcode.com/problems/minimum-size-subarray-sum/
