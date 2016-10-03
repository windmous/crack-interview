题目链接: [167.Two Sum II - Input array is sorted][1]
难度: Medium

夹逼方法(6ms)
时间复杂度：O(N)
空间复杂度：O(1)
```cpp
class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {
        if (numbers.size() <= 1) return {};
        
        int low = 0, high = numbers.size() - 1;
        while (low < high) {
            int sum = numbers[low] + numbers[high];
            if (sum == target) {
                return {low+1, high + 1};
            } else if (sum < target) {
                low ++;
            } else {
                high --;
            }
        }
        return {};
    }
};
```

[1]: https://leetcode.com/problems/two-sum-ii-input-array-is-sorted/