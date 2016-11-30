题目链接: [321.Create Maximum Number][1]
难度: Hard

# 暴力
时间复杂度：O((M+N)^3)
空间复杂度：O(M+N)

枚举i，从nums1中找i个元素、nums2中找k-i个元素，使得合成后最大

从nums中找i个元素实际为寻找“最大下降子序列”，且我们使用drop变量限制可以扔掉的数量，用栈完成推到策略。
合成这里使用了贪心策略。

两处都不简单啊。。。

```cpp
class Solution {
public:
    vector<int> maxNumber(vector<int>& nums1, vector<int>& nums2, int k) {
        vector<int> result;
        for (int i = max<int>(0, k-nums2.size()); i <= k && i <= nums1.size(); ++ i) {
            auto temp = concat(select_k(nums1, i), select_k(nums2, k-i));
            result = max(temp, result);
        }        
        return result;
    }
    
    vector<int> concat(vector<int> v1, vector<int> v2) {
        vector<int> result;
        while (v1.size() + v2.size()) {
            auto &now = v1 > v2 ? v1 : v2;
            result.push_back(now[0]);
            now.erase(now.begin());
        }
        return result;
    }
    
    vector<int> select_k(vector<int> &nums, const int k) {
        int drop = nums.size() - k;
        vector<int> result;
        for (int i = 0; i < nums.size(); ++ i) {
            while (drop > 0 && !result.empty() && result.back() < nums[i]) {
                drop --;
                result.pop_back();
            }
            result.push_back(nums[i]);
        }
        result.resize(k);
        return result;
    }
};
```

[1]: https://leetcode.com/problems/create-maximum-number/