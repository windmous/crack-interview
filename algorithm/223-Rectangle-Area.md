题目链接: [223.Rectangle Area][1]
难度: Easy

# 几何法(32ms)

[Sum of areas - Overlapped area]

```cpp
class Solution {
public:
    int computeArea(int A, int B, int C, int D, int E, int F, int G, int H) {
    	// 求重叠的矩形部分
        int left = max(A, E), right = max(left, min(C, G));
        int bottom = max(B, F), top = max(bottom, min(D, H));
        return (C-A)*(D-B) + (G-E)*(H-F) - (right-left)*(top-bottom);
    }
};
```

[1]: https://leetcode.com/problems/rectangle-area/