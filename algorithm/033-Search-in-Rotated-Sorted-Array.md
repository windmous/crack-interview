题目链接: [33.Search in Rotated Sorted Array][1]
难度: Hard

- 在[4 5 6 7 0 1 2]这样的Rotated Sorted Array中找某个元素的下标，array保证没有重复元素
- mid只有三种情况：
```
1)           2)
                     /
      o            o <-2
     /           /
   o <- 1      o              o
 /                          / 
o                         o <-3
                         /
						 
```
# 二分查找 4ms

先找到最小元素的下标，然后在这个偏移量上调用二分查找

```cpp
class Solution {
public:
    int search(int A[], int n, int target) {
        int lo=0,hi=n-1;
        // find the index of the smallest value using binary search.
        // Loop will terminate since mid < hi, and lo or hi will shrink by at least 1.
        // Proof by contradiction that mid < hi: if mid==hi, then lo==hi and loop would have been terminated.
        while(lo<hi){
            int mid=(lo+hi)/2;
            if(A[mid]>A[hi]) lo=mid+1;
            else hi=mid;
        }
        // lo==hi is the index of the smallest value and also the number of places rotated.
        int rot=lo;
        lo=0;hi=n-1;
        // The usual binary search and accounting for rotation.
        while(lo<=hi){
            int mid=(lo+hi)/2;
            int realmid=(mid+rot)%n;
            if(A[realmid]==target)return realmid;
            if(A[realmid]<target)lo=mid+1;
            else hi=mid-1;
        }
        return -1;
    }
};
```

# 二分查找 4ms

不用偏移量，直接找

```cpp
class Solution {
public:
    int search(vector<int>& nums, int target) {
        int low = 0, high = nums.size();
        while (low < high) {
            const int mid = low + (high - low) / 2;
            if (nums[mid] == target) 
                return mid;
                
            if (nums[low] <= nums[mid]) {
                if (nums[low] <= target && target < nums[mid]) {
                    high = mid;
                } else {
                    low = mid + 1;
                }
            } else {
                if (nums[mid] < target && target <= nums[high-1]) {
                    low = mid + 1;
                } else {
                    high = mid;
                }
            }
        }
        
        return -1;
    }
};
```

[1]: https://leetcode.com/problems/search-in-rotated-sorted-array/