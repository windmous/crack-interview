题目链接: [41.First Missing Positive][1]
难度: Hard

- 找vector中第一个没出现的正整数，vector中可能包含重复元素、超大数、0和负数

# 打乒乓球法 4ms

```cpp
class Solution
{
public:
    int firstMissingPositive(int A[], int n)
    {
        for(int i = 0; i < n; ++ i)
            while(A[i] > 0 && A[i] <= n && A[A[i] - 1] != A[i])
                swap(A[i], A[A[i] - 1]);

        for(int i = 0; i < n; ++ i)
            if(A[i] != i + 1)
                return i + 1;

        return n + 1;
    }
};
```

# 略微改写(6ms)
```cpp
class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        const int N = nums.size();
        for (int i = 0; i < N; ) {
            if (nums[i] > 0 && nums[i] <= N && nums[nums[i]-1] != nums[i]) {
                swap(nums[i], nums[nums[i]-1]);
            } else {
                ++ i;
            }
        }
        
        for (int i = 0; i < N; ++ i) {
            if (nums[i] != i + 1) {
                return i + 1;
            }
        }
        return N + 1;
    }
};
```

[1]: https://leetcode.com/problems/first-missing-positive/