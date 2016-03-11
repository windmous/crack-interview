题目链接: [75.Sort Colors][1]
难度: Medium

- 三种颜色的乱序vector进行排序，要求1 pass，并且常数额外空间

# Dijkstra's 3-way partitioning

参见algs4快排一节

```cpp
class Solution {
public:
	void sortColors(int A[], int n) {
		int second=n-1, zero=0;
		for (int i=0; i<=second; i++) {
			while (A[i]==2 && i<second) swap(A[i], A[second--]);
			while (A[i]==0 && i>zero) swap(A[i], A[zero++]);
		}
	}
};
```

这个代码和algs 4是一样的：
[   <v   ][lt   =v    ][k  待划分  gt][   >v   ]
```cpp
class Solution {
public:
    void sortColors(int A[], int n) {
        int lt = 0, gt = n-1;
        for(int k=0; k<=gt; )
        {
            if(A[k]==0)       swap(A[lt++], A[k++]);
            else if(A[k]==2)  swap(A[gt--], A[k]);
            else k++;
        }        
    }
};
```

# 三指针pioneer方案

```cpp
// one pass in place solution
void sortColors(int A[], int n) {
    int n0 = -1, n1 = -1, n2 = -1;
    for (int i = 0; i < n; ++i) {
        if (A[i] == 0) 
        {
            A[++n2] = 2; A[++n1] = 1; A[++n0] = 0;
        }
        else if (A[i] == 1) 
        {
            A[++n2] = 2; A[++n1] = 1;
        }
        else if (A[i] == 2) 
        {
            A[++n2] = 2;
        }
    }
}
```

# ???

思想应该是和dijstra's 3-way partitioning 一样的

```cpp
// one pass in place solution
void sortColors(int A[], int n) {
    int j = 0, k = n - 1;
    for (int i = 0; i <= k; ++i){
        if (A[i] == 0 && i != j)
            swap(A[i--], A[j++]);
        else if (A[i] == 2 && i != k)
            swap(A[i--], A[k--]);
    }
}

// one pass in place solution
void sortColors(int A[], int n) {
    int j = 0, k = n-1;
    for (int i=0; i <= k; i++) {
        if (A[i] == 0)
            swap(A[i], A[j++]);
        else if (A[i] == 2)
            swap(A[i--], A[k--]);
    }
}
```

[1]: https://leetcode.com/problems/sort-colors/