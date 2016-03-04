题目链接: [4.Median of Two Sorted Arrays][1]
难度: Hard

- 寻找两个有序队列的第k个数
- 二分查找较短队列的第t个数，另一个队列对应的数是第k-t，直到第一条队列的前t个数和第二条队列的前k-t个数共同构成的“左半边队列”，小于剩下的“右半边队列”
- 特殊情况是i搜到最左或最右时的处理

# 二分查找  44ms 
时O(log(min(m, n)))，空O(1)

```cpp
class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int m = nums1.size(), n = nums2.size();
        
        if (m > n) 
            return findMedianSortedArrays(nums2, nums1);
        
        /*half_len设置成这样是为了保证“左半边元素”个数大于等于“右半边元素”，例如m+n=5时，half_len为3。这么设置是和return时找max_of_left还是min_of_right是对应的。*/
        int imin = 0, imax = m, half_len = (m + n + 1) / 2, i, j, max_of_left, min_of_right;

        while (imin <= imax) {
            i = (imin + imax) / 2;
            j = half_len - i;
            if (j > 0 && i < m && nums2[j - 1] > nums1[i]) {
                // i is too small, must increase it
                imin = i + 1;
            } else if (i > 0 && j < n && nums1[i - 1] > nums2[j]) {
                // i is too big, must decrease it
                imax = i - 1;
            } else {
                // i刚刚好，此时注意最左和最右的边界条件
                if (i == 0) max_of_left = nums2[j - 1];
                else if (j == 0) max_of_left = nums1[i - 1];
                else max_of_left = max(nums1[i - 1], nums2[j - 1]);
                
                if ((m + n) % 2 != 0) return max_of_left;
                
                if (i == m) min_of_right = nums2[j];
                else if (j == n) min_of_right = nums1[i];
                else min_of_right = min(nums1[i], nums2[j]);
                
                return (max_of_left + min_of_right) / 2.0;
            }
        }
    }
};

```


[1]: https://leetcode.com/problems/median-of-two-sorted-arrays/