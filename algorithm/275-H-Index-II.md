题目链接: [275.H-Index II][1]
难度: Medium

描述：跟[H-Index]一致，不过使用预先将citations排好序了。

# 二分法(12ms)
```cpp
class Solution {
public:
    int hIndex(vector<int>& citations) {
        int left=0, len = citations.size(), right= len-1,  mid;
        while(left<=right)
        {
            mid=left+ (right-left)/2;
            if(citations[mid] >= (len-mid)) right = mid - 1;
            else left = mid + 1;
        }
        return len - left;
    }
};
```

# 标准二分法
```cpp
class Solution {
public:
    int hIndex(vector<int>& citations) {
        const int N = citations.size();
        int low = 0, high = N;
        while (low < high) {
            const int mid = low + (high - low) / 2;
            if (citations[mid] >= N-mid) {
                high = mid;
            } else {
                low = mid + 1;
            }
        }
        return N - low;
    }
};
```

[1]: https://leetcode.com/problems/h-index-ii/