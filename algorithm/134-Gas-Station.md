题目链接: [134.Gas Station][1]
难度: Medium

描述：一个环形路上有N个加油站，每个加油站可以加gas[i]升油，从第i站到下一站耗油cost[i]升。问汽车从哪一站开始能走完一环，汽车起始时邮箱是空的。

# 经典法(8ms)
时间复杂度：O(N)
空间复杂度：O(1)

本方法证明见[这里][2]

```cpp
class Solution {
public:
    int canCompleteCircuit(vector<int> &gas, vector<int> &cost) {
        int total_sum = 0;
        int start_idx = -1;
            
        for (int i = 0, sum = 0; i < gas.size(); ++ i) {
            total_sum += gas[i] - cost[i];
            sum += gas[i] - cost[i];
            if (sum < 0) {
                sum = 0;
                start_idx = i;
            }
        }
        
        return total_sum >= 0 ? start_idx+1 : -1;
    }
};
```

# 跳跃法(8ms)
时间复杂度：O(N)
空间复杂度：O(1)

```cpp
class Solution {
public:
    int canCompleteCircuit(vector<int> &gas, vector<int> &cost) {
        int i, j, n = gas.size();

        /*
         * If start from i, stop before station x -> no station k from i + 1 to x - 1 can reach x.
         * Bcoz if so, i can reach k and k can reach x, then i reaches x. Contradiction.
         * Thus i can jump directly to x instead of i + 1, bringing complexity from O(n^2) to O(n).
         */
        // start from station i
        for (i = 0; i < n; i += j) {
            int gas_left = 0;
            // forward j stations
            for (j = 1; j <= n; j++) {
                int k = (i + j - 1) % n;
                gas_left += gas[k] - cost[k];
                if (gas_left < 0)
                    break;
            }
            if (j > n)
                return i;
        }

        return -1;
    }
};
```

# 未命名法(8ms)
时间复杂度：O(N)
空间复杂度：O(1)

// 待证明
来源见[这里][3]

```cpp
class Solution {
public:
    int canCompleteCircuit(vector<int> &gas, vector<int> &cost) {

       int start = gas.size()-1;
       int end = 0;
       int sum = gas[start] - cost[start];
       while (start > end) {
          if (sum >= 0) {
             sum += gas[end] - cost[end];
             ++end;
          }
          else {
             --start;
             sum += gas[start] - cost[start];
          }
       }
       return sum >= 0 ? start : -1;
    }
};
```

[1]: https://leetcode.com/problems/gas-station/
[2]: https://leetcode.com/discuss/91749/proof-of-total-gas-is-greater-than-total-cost-there-solution
[3]: https://leetcode.com/discuss/16087/space-running-time-solution-anybody-have-posted-this-solution