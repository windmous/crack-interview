题目链接: [238.Product of Array Except Self][1]
难度: Medium

描述：给定一个数组A，输入另一个数组B，使得:
```
B[i] = A[0]*A[1]*...*A[i-1]*A[i+1]*...A[N]
```
不准用除法，除了输出所开的数组外只能用常量空间。

# Trival扫描(64ms)
时间复杂度：O(N)
空间复杂度：O(N)

这里为了方便理解，还是开了两个数组。

```cpp
cclass Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        const int n=nums.size();
        
        vector<int> fromBegin(n);
        fromBegin[0]=1;
        vector<int> fromLast(n);
        fromLast[n-1]=1;

        transform(fromBegin.begin(), fromBegin.end()-1, nums.begin(),
                  fromBegin.begin()+1, multiplies<int>());
        transform(fromLast.rbegin(), fromLast.rend()-1, nums.rbegin(),
                  fromLast.rbegin()+1, multiplies<int>());

        vector<int> res(n);
        transform(fromBegin.begin(), fromBegin.end(), 
                fromLast.begin(), res.begin(), multiplies<int>());
        return res;
    }
};
```
# 扫描2(56ms)
时间复杂度：O(N)
空间复杂度：O(1)

扫描1的简化版

```cpp
class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int n=nums.size();
        int fromBegin=1;
        int fromLast=1;
        vector<int> res(n,1);

        // 下面的代码可以用partial_sum简化
        for(int i=0;i<n;i++){
            res[i]*=fromBegin;
            fromBegin*=nums[i];
            res[n-1-i]*=fromLast;
            fromLast*=nums[n-1-i];
        }
        return res;
    }
};
```

# 扫描2STL版本(64ms)
时间复杂度：O(N)
空间复杂度：O(1)

使用STL改写了扫描2，提升X格。
```cpp
class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int n=nums.size();
        int fromBegin=1;
        int fromLast=1;
        vector<int> res(n,1);

        partial_sum(nums.begin(), nums.end()-1, res.begin()+1, multiplies<int>());
        partial_sum(nums.rbegin(), nums.rend(), nums.rbegin(), multiplies<int>());
        transform(res.begin(), res.end()-1, nums.begin()+1, res.begin(), multiplies<int>());

        return res;
    }
};
```


[1]: https://leetcode.com/problems/product-of-array-except-self/