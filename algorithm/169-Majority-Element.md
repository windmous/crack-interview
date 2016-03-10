题目链接: [169.Majority Element][1]
难度: Easy

描述：给定一组整数，找出majority element，即出现大于floor(n/2)次的元素。我们保证这样的元素在输入数组中肯定存在。

# Moore's voting algorithm(20ms)
时间复杂度：O(N)
空间复杂度：O(1)

```cpp
class Solution {
public:
    int majorityElement(vector<int>& nums) {
        int cnt = 0, res;
        for (int val : nums) {
            if (cnt == 0) res = val;
            if (res == val) ++cnt;
            else --cnt;
        }
        return res;
    }
}; 
```

# 排序法(24ms)
时间复杂度: O(N)
空间复杂度: O(1)
只要找出前[N/2]个元素，那么第[N/2]个元素必然是Majority Element。在C++中，nth_element可以保证将第k个元素放在第k个位置，同时将前k个元素放在1..k的位置上，但这前k个元素是无序的。如果追求有序，那么需要用partial_sort。

```cpp
class Solution {
public:
    int majorityElement(vector<int>& nums) {
        nth_element(nums.begin(), nums.begin() + nums.size() / 2, nums.end());
        return nums[nums.size() / 2];
    } 
};
```

# 蒙特卡洛方法(20ms)
时间复杂度：O(N)
空间复杂度：O(1)

```cpp
class Solution {
public:
    int majorityElement(vector<int>& nums) {
        const int n = nums.size();
        srand(unsigned(time(NULL)));
        while (true) {
            int idx = rand() % n;
            int candidate = nums[idx];
            int counts = 0; 
            if (count(nums.begin(), nums.end(), candidate) > n/2) {
                return candidate;
            }
        }
    }
};
```

# Bit统计(32ms)
时间复杂度：O(Nlog_2MAX_INT)
空间复杂度：O(1)

Another nice idea! The key lies in how to count the number of 1's on a specific bit. Specifically, you need a mask with a 1 on the i-the bit and 0 otherwise to get the i-th bit of each element in nums. The code is as follows.

感觉摩尔Votting算法是这个算法的并行版，效率更高。

```cpp
class Solution {
public:
    int majorityElement(vector<int>& nums) {
        int major = 0, n = nums.size();
        for (int i = 0, mask = 1; i < 32; i++, mask <<= 1) {
            int bitCounts = 0;
            for (int j = 0; j < n; j++) {
                if (nums[j] & mask) bitCounts++;
                if (bitCounts > n / 2) {
                    major |= mask;
                    break;
                }
            }
        } 
        return major;
    } 
};
```

# 分治法(24ms)
时间复杂度：O(NlogN)
空间复杂度：O(logN)

```cpp
class Solution {
public:
    int majorityElement(vector<int>& nums) {
        return majority(nums, 0, nums.size() - 1);
    }
private:
    int majority(vector<int>& nums, int left, int right) {
        if (left == right) return nums[left];
        int mid = left + ((right - left) >> 1);
        int lm = majority(nums, left, mid);
        int rm = majority(nums, mid + 1, right);
        if (lm == rm) return lm;
        return count(nums.begin() + left, nums.begin() + right + 1, lm) > count(nums.begin() + left, nums.begin() + right + 1, rm) ? lm : rm;
    }
}; 
```


[1]: https://leetcode.com/problems/majority-element/