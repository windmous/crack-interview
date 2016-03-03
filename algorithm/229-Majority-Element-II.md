题目链接: [229.Majority Element II][1]
难度: Medium

# Boyer-Moore Majority Vote algorithm
时间复杂度：O(N)

```cpp(20ms)
class Solution {
public:
    vector<int> majorityElement(vector<int>& nums) {
        if (nums.size() <= 1) return nums;
        
        int cand1, cnt1 = 0;
        int cand2, cnt2 = 0;
        
        for (int n : nums) {
            if (n == cand1) ++ cnt1;
            else if (n == cand2) ++ cnt2;
            else if (0 == cnt1) {cand1 = n; cnt1 = 1;}
            else if (0 == cnt2) {cand2 = n; cnt2 = 1;}
            else {--cnt1; --cnt2;}
        }
        
        cnt1 = count(nums.begin(), nums.end(), cand1);
        cnt2 = count(nums.begin(), nums.end(), cand2);
        
        vector<int> result;
        if (cnt1 > nums.size() / 3.0) result.push_back(cand1);
        if (cnt2 > nums.size() / 3.0) result.push_back(cand2);
        return result;
    }
};
```

# 随机法(20ms)
随机猜一个数，看看它有没有超过1/3。一共猜10次，能至少猜中1个1/3数的概率是 1 - (2/3)^10
```cpp
class Solution {
public:
    vector<int> majorityElement(vector<int>& nums) {
        if (nums.size() <= 1) return nums;
        
        default_random_engine e;
        uniform_int_distribution<int> u(0, nums.size()-1);
        vector<int> result;
        for (int i = 0; i < 10; ++ i) { // try 10 time at most
            int candidate = nums[u(e)];
            if (find(result.begin(), result.end(), candidate) != result.end()) 
                continue;
                
            if (count(nums.begin(), nums.end(), candidate) > nums.size() / 3.0) {
                result.push_back(candidate);
            }
        }
        
        return result;
    }
};
```

[1]: https://leetcode.com/problems/majority-element-ii/