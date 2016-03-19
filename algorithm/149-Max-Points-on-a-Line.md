题目链接: [149.Max Points on a Line][1]
难度: Hard

描述：给n个2D平面上的点，求最大的N，使这N个点共线。

本题思路枚举所有可能的直线，然后统计落在直线上的点。Naive的实现耗费O(N^3)，但其实可以一边枚举直线一边统计值的。

## 哈希法(16ms)
时间复杂度：O(N^2)
空间复杂度：O(N^2)

使用哈希表记录共线的点有多少个。hashmap的key是斜率，value是点的个数。

```cpp
/**
 * Definition for a point.
 * struct Point {
 *     int x;
 *     int y;
 *     Point() : x(0), y(0) {}
 *     Point(int a, int b) : x(a), y(b) {}
 * };
 */
class Solution {
public:
    int maxPoints(vector<Point>& points) {
        unordered_map<float, int> slopes;
        int maxp = 0, n = points.size();
        
        for (int i = 0; i < n; i++) {
            slopes.clear();
            int duplicate = 1, max_one_line = 0;
            for (int j = i + 1; j < n; j++) {
                if (points[j].x == points[i].x && points[j].y == points[i].y) {
                    duplicate++;
                    continue;
                }
                float slope = (points[j].x == points[i].x) ? INT_MAX : 
                              (float)(points[j].y - points[i].y) / (points[j].x - points[i].x);
                max_one_line = max(++ slopes[slope], max_one_line);
            }
            maxp = max(maxp, duplicate + max_one_line);
        }
        return maxp;
    }
};
```

# 哈希法（安全版本）(28ms)
时间复杂度：O(N^2)
空间复杂度：O(1)

由于浮点数有时候不精确，所以用有理数作为key、value。

```cpp
/**
 * Definition for a point.
 * struct Point {
 *     int x;
 *     int y;
 *     Point() : x(0), y(0) {}
 *     Point(int a, int b) : x(a), y(b) {}
 * };
 */
class Solution { 
public: 
    int maxPoints(vector<Point>& points) {
        map<pair<int, int>, int> slopes;
        int maxp = 0, n = points.size();
        for (int i = 0; i < n; i++) {
            slopes.clear();
            int duplicate = 1, max_one_line = 0;
            for (int j = i + 1; j < n; j++) {
                if (points[j].x == points[i].x && points[j].y == points[i].y) {
                    duplicate++;
                    continue;
                }
                int dx = points[j].x - points[i].x;
                int dy = points[j].y - points[i].y;
                int dvs = gcd(dx, dy);
                max_one_line = max(max_one_line, ++slopes[make_pair(dx / dvs, dy / dvs)]);
            }
            maxp = max(maxp, duplicate + max_one_line); 
        } 
        return maxp;
    }
private:
    int gcd(int num1, int num2) {
        while (num2) {
            int temp = num2; 
            num2 = num1 % num2;
            num1 = temp;
        }
        return num1;
    }
};
```

[1]: https://leetcode.com/problems/max-points-on-a-line/