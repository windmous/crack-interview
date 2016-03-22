题目链接: [31.Next Permutation][1]
难度: Medium

- 首先，从尾向头寻找最长的递增序列，直至num[i-1] < num[i] ;若找不着则说明整个队列都是递减的，下一个permutation回到开头，是从小到大递增序列
- 若找得到，则在num[i, end)中寻找比num[i-1]大的最小元素num[k]，因为num[i, end)是递减的，所以k是在num[i, end)中比num[i-1]大的最大下标
- 调换num[i-1]与num[k]
- 翻转num[i, end)

可以从这个角度理解，下一个permutation的k2，k3，k4都不能往后移动了，此时k[2~4]构成一个递减序列，k1的值指向下一个元素，这个元素是比2大的最小元素：
```cpp
for k1 in [1, →2, 3, 4] :
	// 假设k1 = 2
	for k2  in [1, 3, →4] :
		// 假设k2 = 4
		for k3 in [1, →3]:
			// 假设k3 = 3
			for k4 in [→1]:
				// 此时k4 = 1
				输出 [k1, k2, k3, k4]
```

```cpp
class Solution {
public:
    void nextPermutation(vector<int> &num) 
    {
        if (num.size() < 2) return ;

        // in reverse order, find the first number which is in increasing trend (we call it violated number here)
        int i;   // 务必令num.size() >= 2，否则会溢出
        for (i = nums.size()-2; i >= 0; -- i) {
            if (nums[i] < nums[i+1]) break;
        }
        
        reverse(nums.begin()+i+1, nums.end());
        if (i >= 0) {
            auto pivot = upper_bound(nums.begin()+i+1, nums.end(), nums[i]);
            swap(nums[i], *pivot);
        }
    }
};
```

# previous permutation 的版本

从尾向头寻找最长的递减序列

```cpp
class Solution {
public:
    void prevPermutation(vector<int> &num) 
    {
        if (num.empty()) return;

        // in reverse order, find the first number which is in decreasing trend (we call it violated number here)
        int i;
        for (i = num.size()-2; i >= 0; --i)
        {
            if (num[i] > num[i+1]) break;
        }

        reverse(begin(num)+i+1, end(num));
        if (i >= 0) {
            auto itr = lower_bound(num.rbegin(), num.rbegin()+(num.size()-i-1), num[i])-1;
            // swap them, done!
            swap(num[i], *itr);
        }
    }
};
```

[1]: https://leetcode.com/problems/next-permutation/