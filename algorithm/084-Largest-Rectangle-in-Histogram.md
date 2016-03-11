题目链接: [84.Largest Rectangle in Histogram][1]
难度: Hard

- 给出一个vector<int> height,在其中找到面积最大的矩形。原题有图

# 栈：存储高度递增的序列

```cpp
class Solution {
public:
    int largestRectangleArea(vector<int> &height) {
        stack<int> s;
        height.push_back(0); // 注意这里塞了一个0在尾部，目的是最终栈能清空
        int result = 0;
        for (int i = 0; i < height.size(); ) {
            if (s.empty() || height[i] > height[s.top()])
                s.push(i++);
            else {
                int tmp = s.top();
                s.pop(); 
				// 此时height[tmp]比height[s.top()]和height[i]都高，所以直接算结果，之后栈中就没它的事了，因为栈只存一个递增高度的子串的下标
                result = max(result,
                        height[tmp] * (s.empty() ? i : i - s.top() - 1));
            }
        }
        return result;
    }
};
```

# 分治法

最大矩形 = max（左半边最大矩形 ，右半边最大矩形，横跨两边的最大矩形）

```cpp
class Solution {
    int maxCombineArea(const vector<int> &height, int s, int m, int e) {
        // Expand from the middle to find the max area containing height[m] and height[m+1]
        int i = m, j = m+1;
        int area = 0, h = min(height[i], height[j]);
        while(i >= s && j <= e) {
            h = min(h, min(height[i], height[j]));
            area = max(area, (j-i+1) * h);
            if (i == s) {
                ++j;
            }
            else if (j == e) {
                --i;
            }
            else {
                // if both sides have not reached the boundary,
                // compare the outer bars and expand towards the bigger side
                if (height[i-1] > height[j+1]) {
                    --i;
                }
                else {
                    ++j;
                }
            }
        }
        return area;
    }
    int maxArea(const vector<int> &height, int s, int e) {
        // if the range only contains one bar, return its height as area
        if (s == e) {
            return height[s];
        }
        // otherwise, divide & conquer, the max area must be among the following 3 values
        int m = s + (e-s)/2;
        // 1 - max area from left half
        int area = maxArea(height, s, m);
        // 2 - max area from right half
        area = max(area, maxArea(height, m+1, e));
        // 3 - max area across the middle
        area = max(area, maxCombineArea(height, s, m, e));
        return area;
    }
public:
    int largestRectangleArea(vector<int> &height) {
        if (height.empty()) {
            return 0;
        }
        return maxArea(height, 0, height.size()-1);
    }
};
```

[1]: https://leetcode.com/problems/largest-rectangle-in-histogram/