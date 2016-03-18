题目链接: [128.Longest Consecutive Sequence][1]
难度: Hard

给定未排序的数组，找出排序后最长的连续相邻的串的长度。

Given an unsorted array of integers, find the length of the longest consecutive elements sequence.

For example,
Given (100, 4, 200, 1, 3, 2),
The longest consecutive elements sequence is (1, 2, 3, 4). Return its length: 4.

Your algorithm should run in O(n) complexity.

# 哈希表存边界

https://leetcode.com/discuss/18886/my-really-simple-java-o-n-solution-accepted

注意到连续相邻的数组，只有首尾两个元素是重要的。

We will use HashMap. The key thing is to keep track of the sequence length and store that in the boundary points of the sequence. For example, as a result, for sequence {1, 2, 3, 4, 5}, map.get(1) and map.get(5) should both return 5.

Whenever a new element n is inserted into the map, do two things:

1. See if n - 1 and n + 1 exist in the map, and if so, it means there is an existing sequence next to n. Variables left and right will be the length of those two sequences, while 0 means there is no sequence and n will be the boundary point later. Store (left + right + 1) as the associated value to key n into the map.

2. Use left and right to locate the other end of the sequences to the left and right of n respectively, and replace the value with the new length.

Everything inside the for loop is O(1) so the total time is O(n). Please comment if you see something wrong. Thanks.

```cpp
class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        int res = 0;
        unordered_map<int, int> map;
        for (int n : nums) {
            if (map.find(n) == map.end()) {
                int left = (map.find(n - 1) != map.end()) ? map[n - 1] : 0;
                int right = (map.find(n + 1) != map.end()) ? map[n + 1] : 0;
                // sum: length of the sequence n is in
                int sum = left + right + 1;
                map[n] = sum;
                
                // keep track of the max length
                res = max(sum, res);
                
                // extend the length to the boundary(s)
                // of the sequence
                // will do nothing if n has no neighbors
                map[n - left] = sum;
                map[n + right] = sum;
            } else {
                // duplicate 
                continue;
            }
        }
        return res;
    }
};
```

# 上面解法的精简版

https://leetcode.com/discuss/16711/possibly-shortest-cpp-solution-only-6-lines

```cpp
int longestConsecutive(vector<int> &num) {
    unordered_map<int, int> m;
    int r = 0;
    for (int i : num) {
        if (m[i]) continue;
        r = max(r, m[i] = m[i + m[i + 1]] = m[i - m[i - 1]] = m[i + 1] + m[i - 1] + 1);
    }
    return r;
}
```

[1]: https://leetcode.com/problems/longest-consecutive-sequence/