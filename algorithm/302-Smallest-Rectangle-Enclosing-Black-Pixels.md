题目链接: [302.Smallest Rectangle Enclosing Black Pixels][1]
难度: Hard

找一个最小覆盖矩形
An image is represented by a binary matrix with 0 as a white pixel and 1 as a black pixel. The black pixels are connected, i.e., there is only one black region. Pixels are connected horizontally and vertically. Given the location (x, y) of one of the black pixels, return the area of the smallest (axis-aligned) rectangle that encloses all black pixels.

For example, given the following image:

[
  "0010",
  "0110",
  "0100"
]
and x = 0, y = 2,
Return 6.

# BFS(33ms)
时间复杂度：O(MN)
空间复杂度：O(1)

```cpp
class Solution {
public:
    int minArea(vector<vector<char>>& image, int y, int x) {
        int min_y = y, max_y = y;
        int min_x = x, max_x = x;
        
        queue<pair<int,int>> Q;
        static int delta[] = {0, -1, 0, 1, 0};
        Q.push({y, x});
        image[y][x] = '0';
        
        while (!Q.empty()) {
            y = Q.front().first, x = Q.front().second;
            Q.pop();
            min_y = min(min_y, y);
            max_y = max(max_y, y);
            min_x = min(min_x, x);
            max_x = max(max_x, x);
            
            for (int d = 0; d < 4; ++ d) {
                int new_y = y + delta[d];
                int new_x = x + delta[d+1];
                
                if (new_y >= 0 && new_y < image.size() && new_x >= 0 && new_x < image[0].size() && image[new_y][new_x] == '1') {
                    image[new_y][new_x] = '0';
                    Q.push({new_y, new_x});
                }
            }
        }
        return (max_y-min_y+1) * (max_x-min_x+1);
    }
};
```

# 二分法(19ms)
时间复杂度：O(NlogM + MlogN)
空间复杂度：O(1)

关键：由于只有一个黑色区域，所以向左或者向下投影后肯定只有一串连续的1，这奠定了使用二分的基础。我们搜索'1'的上边界和下边界

```cpp
class Solution {
public:
    int minArea(vector<vector<char>>& image, int x, int y) {
        const int N = image.size(), M = image[0].size();
        int min_x = bsearch(image, 0, x+1, 0, M, has_val_in_row, true);
        int max_x = bsearch(image, x, N, 0, M, has_val_in_row, false);
        int min_y = bsearch(image, 0, y+1, min_x, max_x, has_val_in_col, true);
        int max_y = bsearch(image, y, M, min_x, max_x, has_val_in_col, false);
        return (max_x-min_x) * (max_y-min_y);
    }

    template <typename T>
    int bsearch(vector<vector<char>> & image, int low, int high, int wind_low, int wind_high, T func, bool val) {
        while (low < high) {
            int mid = low + (high - low) / 2;
            if (func(image, mid, wind_low, wind_high) == val) {
                high = mid;
            } else {
                low = mid + 1;
            }
        }
        return low;
    }

    static bool has_val_in_row(vector<vector<char>> &image, int row, int low, int high) {
        return find(image[row].begin()+low, image[row].begin()+high, '1') != image[row].begin()+high;
    }

    static bool has_val_in_col(vector<vector<char>> &image, int col, int low, int high) {
        for (int i = low; i < high; ++ i) {
            if (image[i][col] == '1') {
                return true;
            }
        }
        return false;
    }
};
```


[1]: https://leetcode.com/problems/smallest-rectangle-enclosing-black-pixels/