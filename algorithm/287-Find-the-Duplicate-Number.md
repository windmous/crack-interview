题目链接: [287.Find the Duplicate Number][1]
难度: Hard

描述：给定N+1个数，这些数都在范围[1,N]内。请证明这N+1个数里肯定有重复。假设这N+1个数中只有一个数字重复，请找出该数字。

要求：
1. 不能修改输入数组
2. 只能用O(1)空间
3. 时间复杂度应小于O(N^2)
4. 只有一个数字是重复的，但是该数字可能重复若干次。

# 二分法(24ms)
时间复杂度：O(NlogN)
空间复杂度：O(1)

```cpp
class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        int low = 1;
        int high = nums.size();

        while(low < high){
            int mid = low + (high-low)/2;
            const int less_nums = count_if(nums.begin(), nums.end(), 
                                          [mid](int x) {return x <= mid;});

            if(less_nums <= mid)
                low= mid + 1;
            else 
                high = mid;
        }
        
        return low;
    }
};
```

# 环检测法(15ms)
时间复杂度：O(N)
空间复杂度：O(1)

详细证明请参考[这里][2]。
据说Knuth花了24小时才解出本问题！

```cpp
class Solution {
public:
    int findDuplicate(vector<int> &nums) {
        int slow = 0, fast = 0;
        
        do{
            slow = nums[slow];
            fast = nums[nums[fast]];
        }while(slow != fast);
        
        slow = 0;
        while(slow != fast){
            slow = nums[slow];
            fast = nums[fast];
        }
        return slow;
    }
};
```


[1]: https://leetcode.com/problems/find-the-duplicate-number/
[2]: http://keithschwarz.com/interesting/code/?dir=find-duplicate