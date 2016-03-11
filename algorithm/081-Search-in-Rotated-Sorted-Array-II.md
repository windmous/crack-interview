题目链接: [81.Search in Rotated Sorted Array II][1]
难度: Medium

- 在[4 5 6 7 0 1 2]这样的Rotated Sorted Array中找某个元素是否存在，与P33相比，此题的array可能有重复元素
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

# 二分查找
```cpp
class Solution {
public:
  bool search(int A[], int n, int target) {
    int lo =0, hi = n-1;
    int mid = 0;
    while(lo<hi){
          mid=(lo+hi)/2;
          if(A[mid]==target) return true;
          if(A[mid]>A[hi]){ // 情况2
              if(A[mid]>target && A[lo] <= target) hi = mid;
              else lo = mid + 1;
          }else if(A[mid] < A[hi]){  // 情况1、3
              if(A[mid]<target && A[hi] >= target) lo = mid + 1;
              else hi = mid;
          }else{ // A[mid] == A[hi]，此时不知道该往哪边走，试考虑1151111和1111511找5的情况
              hi--;
          }

    }
    return A[lo] == target ? true : false;
  }
};
```

[1]: https://leetcode.com/problems/search-in-rotated-sorted-array-ii/