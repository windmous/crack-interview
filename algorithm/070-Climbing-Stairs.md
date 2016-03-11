题目链接: [70.Climbing Stairs][1]
难度: Easy

要爬n步楼梯，每次只能爬一步或者2步，求总方法个数
f(n) = f(n − 1) + f(n − 2)
 
0ms
 
```cpp
class Solution {
public:
    int climbStairs(int n) {
        int prev = 0, cur = 1;
        for (int i = 1; i <= n; ++i) {
            int tmp = cur;
            cur += prev;
            prev = tmp;
        }
        return cur;
    }
};
 ```

[1]: https://leetcode.com/problems/climbing-stairs/