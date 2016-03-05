题目链接: [11.Container With Most Water][1]
难度: Medium

- 有n个相互间隔为1的木板，高度是a1, ..., an，挑出两根木板使得它们和x轴相连的容器能装下的水最多
- 设n=6，考虑解空间，纵轴为左边木板，横轴为右边木板，x表示空间无效，-表示排除此解
- 若a1 < a6，则高度取决于a1，{a1, an}要优于{a1, ap} (1 < p < 6)，故排除之
```
  1 2 3 4 5 6
1 x ------- o
2 x x
3 x x x 
4 x x x x
5 x x x x x
6 x x x x x x
```
- 若a2 > a6，则高度取决于a6，{a2, a6}要优于{ap, a6}(2 < p < 6)，故排除之
```
  1 2 3 4 5 6
1 x ------- o
2 x x       o
3 x x x     |
4 x x x x   |
5 x x x x x |
6 x x x x x x
```
以此类推。

# 搜索
时间O(N)

28 ms
```cpp
class Solution {
public:
    int maxArea(vector<int>& height) {
        int i = 0, j = height.size() - 1, maxArea = 0, h;
        while (i < j) {
            if (height[i] < height[j]) {
                maxArea = max(maxArea, height[i] * (j - i));
                ++i;
            } else {
                maxArea = max(maxArea, height[j] * (j - i));
                --j;
            }
        }
        return maxArea;
    }
};
```

24 ms
```cpp
int maxArea(vector<int>& height) {
    int water = 0;
    int i = 0, j = height.size() - 1;
    while (i < j) {
        int h = min(height[i], height[j]);
        water = max(water, (j - i) * h);
        while (height[i] <= h && i < j) i++; 
        while (height[j] <= h && i < j) j--;
    }
    return water;
}
```

[1]: https://leetcode.com/problems/container-with-most-water/