题目链接: [88.Merge Sorted Array][1]
难度: Easy

- 归并两个sorted vector，第一个vector只放了前m个元素，有足够多额外空间存放第二个vector
- 难点是想到从后往前merge

# 投票最高
https://leetcode.com/discuss/8233/this-is-my-ac-code-may-help-you
```cpp
class Solution {
public:
    void merge(int A[], int m, int B[], int n) {
        int i=m-1;
        int j=n-1;
        int k = m+n-1;
        while(i >=0 && j>=0)
        {
            if(A[i] > B[j])
                A[k--] = A[i--];
            else
                A[k--] = B[j--];
        }
        while(j>=0)
            A[k--] = B[j--];
    }
};
```

# 一行终结
https://leetcode.com/discuss/30859/1-line-solution
```cpp
while(n>0) A[m+n-1] = (m==0||B[n-1] > A[m-1]) ? B[--n] : A[--m];
```


[1]: https://leetcode.com/problems/merge-sorted-array/