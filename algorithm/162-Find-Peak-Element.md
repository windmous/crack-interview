题目链接: [162.Find Peak Element][1]
难度: Medium

描述：给一个数组，求任意一个局部极值。你可以认为arr[-1]和arr[n+1]是无穷小。输入数组保证num[i] ≠ num[i+1]。

要求时间复杂度为O(log(N))。

# 二分法-迭代(8ms)
时间复杂度：O(logN)
空间复杂度：O(1)

```cpp
class Solution {
public:
    int findPeakElement(vector<int>& nums) {
        int x = 0, y = nums.size() - 1;
        while (x < y) { 
		// 循环不变量：nums[x-1] < nums[x] && nums[y] > nums[y+1]
            int mid = x + (y - x) / 2;
            if (nums[mid] < nums[mid + 1]) { // 此时nums[mid]不是peak
                x = mid + 1;
            } else {
                y = mid;
            }
        }
        
        return x;
    }
};
```

# 二分法-递归(4ms)
时间复杂度：O(logN)
空间复杂度：O(logN)

```cpp
class Solution {
public:
    int findPeakElement(const vector<int> &num) {
        return helper(num, 0, num.size()-1);
    }
    
private:
    int helper(const vector<int> &num, int low, int high) {
        if(low == high)
            return low;
        else {
            int mid = (low+high)/2;
            if (num[mid] > num[mid+1])
                return helper(num, low, mid);
            else
                return helper(num, mid+1, high);
        }
    }
};
```

[1]: https://leetcode.com/problems/find-peak-element/