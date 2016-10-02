题目链接: [164.Maximum Gap][1]
难度: Hard

描述：给定一个没排序的整数，求相邻两个整数差的最大值。要求在O(N)时间内解决。
输入的所有整数均为32bit非负整数。

# 桶方法(12ms)
时间复杂度：O(N)
空间复杂度：O(N)

```cpp

class Solution {
public:
    int maximumGap(vector<int>& nums) {
        const int N = nums.size();
        if (N < 2) return 0;
    
        vector<int> bucket_mins(N, 0x7fffffff), bucket_maxs(N);
        
        auto extreme_vals = std::minmax_element(nums.begin(), nums.end());
        const int min_n = *extreme_vals.first, 
                    max_n = *extreme_vals.second;

        if (min_n == max_n) return 0;
        const double ele_range = max_n - min_n;

        for (int n : nums) {
            int id = static_cast<int>((n-min_n) / ele_range * (N-1));
            bucket_mins[id] = min(bucket_mins[id], n);
            bucket_maxs[id] = max(bucket_maxs[id], n);
        }
        
        int ans = 0, lastMax = bucket_maxs[0];
        for (int i = 1; i < N; ++ i) {
            if (bucket_maxs[i] >= bucket_mins[i]) {
                ans = max(ans, bucket_mins[i] - lastMax);
                lastMax = bucket_maxs[i];
            }
        }
        
        return ans;
    }
};
```

# Count排序
时间复杂度：O(N+Range)
空间复杂度：O(N+Range)

本代码不能AC，主要是介绍一种排序思路。当最大元素-最小元素的值比较小的时候可以用该方法。

```cpp
class Solution {
public:
    int maximumGap(vector<int>& nums) {
        const int N = nums.size();
        if (N < 2) return 0;
        
        const int min_ele = *min_element(nums.begin(), nums.end());
        const int max_ele = *max_element(nums.begin(), nums.end());
        const int ele_range = max_ele - min_ele + 1;

        vector<int> cnt_tab(ele_range, 0);
        for_each(nums.begin(), nums.end(), [min_ele, &cnt_tab](int x){++cnt_tab[x-min_ele];});
        partial_sum(cnt_tab.begin(), cnt_tab.end(), cnt_tab.begin());
        
        vector<int> result(nums.size(), 0);
        for (int i = N-1; i >= 0; -- i) {
            result[--cnt_tab[nums[i]-min_ele]] = nums[i];
        }
        
        transform(result.begin()+1, result.end(), result.begin(),
                    result.begin(), std::minus<int>());
        return *max_element(result.begin(), result.end()-1);
    }
};

# 基数排序-手工版(16ms)
时间复杂度：O(N * log_2MAX_INT)
空间复杂度：O(N)

```cpp
class Solution {
public:
    int maximumGap(std::vector<int> &nums) {
        if (nums.size() < 2) return 0;
        
        const int N = nums.size();
        const int max_ele = *max_element(nums.begin(), nums.end());
        
        int exp = 1;
        vector<int> tmp(nums.size());
        while (max_ele / exp) {
            // 内部是个count sort过程
            array<int,10> cnt_tab = {0};
            for_each(nums.begin(), nums.end(), 
                [exp, &cnt_tab](int x) { ++ cnt_tab[(x/exp)%10]; });
            partial_sum(cnt_tab.begin(), cnt_tab.end(), cnt_tab.begin());
            
            for_each(nums.rbegin(), nums.rend(), // 逆序保证排序是stable的
                [exp,&cnt_tab,&tmp](int x) { tmp[--cnt_tab[(x/exp)%10]] = x; });
            
            nums.swap(tmp);
            exp *= 10;
        }
        
        int max_diff = 0;
        for (int i = 1; i < N; ++ i) {
            max_diff = max(max_diff, nums[i]-nums[i-1]);
        }
        return max_diff;
    }
};
```

# 基数排序-STL版本(20ms)
时间复杂度：O(N * log_2MAX_INT)
空间复杂度：O(N)(stable_partition需要)

```cpp
class Solution {
public:
    int maximumGap(std::vector<int> &num) {
        for(unsigned bit = 0; bit < 31; bit++)
        	// 注意必须使用stable_partition
        	// stable_partition在内存足够的情况下为O(N)，否则是O(NlogN)
            std::stable_partition(num.begin(), num.end(), [bit](int a){
                return !(a & (1 << bit));
            });
            
        int difference = 0;
        for(std::size_t i = 1; i < num.size(); i++) {
            difference = std::max(difference, num[i] - num[i-1]);
        }
        return difference;
    }
};
```

# 基数排序-二进制版本（32ms）

时间复杂度：O(N * log_2MAX_INT)

空间复杂度：O(N)
```cpp
class Solution {
public:
    int maximumGap(vector<int>& nums) {
        int len = nums.size();
        if (len < 2) return 0;
        vector<int> nums2(len);
        
        // radix sort
        for (int i = 0; i < 32; ++i) {
            int idx = 0;
            for (auto& num : nums) if ((num & (1 << i)) == 0) nums2[idx++] = num;
            for (auto& num : nums) if ((num & (1 << i)) != 0) nums2[idx++] = num;
            swap(nums, nums2);
        }
        
        int ans = 0;
        for (int i = 1; i < len; ++i) 
            ans = max(ans, nums[i] - nums[i - 1]);
        
        return ans;
    }
};
```
[1]: https://leetcode.com/problems/maximum-gap/