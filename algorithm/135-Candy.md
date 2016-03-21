题目链接: [135.Candy][1]
难度: Hard

You are giving candies to these children subjected to the following requirements:

Each child must have at least one candy.
Children with a higher rating get more candies than their neighbors.

注意，相同rating的孩子可以不必分配相同的糖果。返回需要的最少糖数。

# 两次遍历法(40ms)
时间复杂度：O(N)
空间复杂度：O(N)

```cpp
class Solution {
public:
    int candy(vector<int> &ratings) {
    	const int N = ratings.size();
        vector<int> result(ratings.size());
        for (int i = 1; i < N ; ++ i) {
            if (ratings[i] > ratings[i - 1])
                result[i] = result[i - 1] + 1;
        }
        
        for (int i = N - 2; i >= 0; -- i) {
            if (ratings[i] > ratings[i + 1]) 
                result[i] = max(result[i], result[i + 1] + 1);
        }
        
        return accumulate(result.begin(), result.end(), ratings.size());
    }
};
```

# 单次遍历法
时间复杂度：O(N)
空间复杂度：O(1)

我们知道rating值逐渐变大的过程，可以计算一个峰顶的左半边高度，但是却无法计算右半边高度。于是，我们转而在下坡到底的时候再计算下坡所分的糖果数。详细注释参考[这里][2]



```cpp
/*
  3
    2     2
1	  1 1 
------------
1 2 2 2 1 2 <- prev
0 0 1 2 0 0 <- countDown
*/

class Solution {
public:
    int candy(vector<int> &ratings) {
    	if (ratings.empty()) return 0;
    	// prev: 前一个上坡的高度
    	// countDown: 下坡的高度
    	// total: 最终答案
        int total = 1, prev = 1, countDown = 0;
        for (int i = 1; i < ratings.size(); i++) {
            if (ratings[i] >= ratings[i-1]) {	// 出现转折时计算前一个下坡的情形
                if (countDown > 0) {
                    total += countDown*(countDown+1)/2; // arithmetic progression
                    if (countDown >= prev) total += countDown - prev + 1;
                    countDown = 0;
                    prev = 1;
                }
                prev = ratings[i] == ratings[i-1] ? 1 : prev+1;
                total += prev;
            } else countDown++;
        }
        if (countDown > 0) { // if we were descending at the end
            total += countDown*(countDown+1)/2;
            if (countDown >= prev) total += countDown - prev + 1;
        }
        return total;
    }
};
```

# 单次遍历法2

将ratings拆分成若干个严格递减的数组。注意处理相邻孩子rating值相同的情况。

```cpp
class Solution {
public:
    int candy(vector<int>& ratings) {
        int answer = 0, lastChild = 0, j;

        for (int i = 0; i < ratings.size(); i = j + 1) {
            j = i;
            while (j + 1 < ratings.size() && ratings[j + 1] < ratings[j]) // ratings[i..j]是一个严格递减的数组
                ++j;

            answer += (j - i + 1) * (j - i + 2) / 2;
            if (i > 0 && ratings[i] > ratings[i - 1] && j - i + 1 <= lastChild) { // 如第i个孩子比lastChild（i-1）强，则要给他加糖
                answer = answer - (j - i + 1) + lastChild + 1;
            }

			// lastChild是第i-1个孩子得到的糖数
            if (i == j && i != 0 && ratings[i] > ratings[i-1]) lastChild += 1; // 只有当数组递增时，lastChild才递增
            else                                               lastChild = 1;
        }
        return answer;
    }
};
```


[1]: https://leetcode.com/problems/candy/
[2]: https://leetcode.com/discuss/23835/one-pass-constant-space-java-solution