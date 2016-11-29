题目链接: [421.Maximum XOR of Two Numbers in an Array][1]
难度: Medium

Given a non-empty array of numbers, a0, a1, a2, … , an-1, where 0 ≤ ai < 231.

Find the maximum result of ai XOR aj, where 0 ≤ i, j < n.

Could you do this in O(n) runtime?

Example:

Input: [3, 10, 5, 25, 2, 8]

Output: 28

Explanation: The maximum result is 5 ^ 25 = 28.
Subscribe to see which companies asked this question

# Hash法
时间复杂度：O(N)
空间复杂度：O(N)

核心思路：从高位到低位逐Bit确认。Hash改成Trie可以跑更快

```cpp
class Solution {
public:
    int findMaximumXOR(vector<int>& nums) {
        int result = 0;
        for (int i = 31; i >= 0; -- i) {
            unordered_set<int> s;
            for (int n : nums) {
                s.insert(n >> i);
            }
            
            result <<= 1;
            for (int n : s) {
                if (s.count(n ^ (result+1))) {
                    result ++;
                    break;
                }
            }
        }
        return result;
    }
};
```

[1]: https://leetcode.com/problems/maximum-xor-of-two-numbers-in-an-array
