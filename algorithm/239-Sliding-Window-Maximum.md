题目链接: [239.Sliding Window Maximum][1]
难度: Hard

给定一个未排序的int数组以及一个滑动窗口的大小，求出该滑动窗口从头到尾的滑动过程中每个窗口内的最大元素，要求时间复杂度为O(N)。

# Monotonic Queue(96ms)
时间复杂度：O(N)
空间复杂度：O(K)

```cpp
class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
    	// 记录当前窗口里最大的值的坐标
        deque<int> dq;
        vector<int> ans;
        for (int i=0; i<nums.size(); i++) {
            if (!dq.empty() && dq.front() == i-k) dq.pop_front();
            while (!dq.empty() && nums[dq.back()] < nums[i])
                dq.pop_back();
            dq.push_back(i);
            if (i>=k-1) ans.push_back(nums[dq.front()]);
        }
        return ans;
    }
};
```

# 分段法(92ms)
时间复杂度：O(N)
空间复杂度：O(N)

本质就是桶方法，在每个桶中我们计算其从左向右最大值和从右向左的最大值。

对于每个滑动窗口，我们将窗口开始的元素所在的桶即下一个相邻桶拿出来，merge一下即可。

```cpp
class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        if (nums.empty() || k <= 0) return {};
        
        vector<int> max_left(nums.size()), max_right(nums.size());
        max_left[0] = nums[0];
        max_right[max_right.size()-1] = nums.back();
        
        // 计算各个桶
        for (int i = 1; i < nums.size(); ++ i) {
            max_left[i] = (i % k == 0) ? nums[i] : max(max_left[i-1], nums[i]);
            const int j = nums.size() - i - 1;
            max_right[j] = (j % k == 0) ? nums[j] : max(max_right[j+1], nums[j]);
        }
        
        vector<int> ans;
        transform(max_right.begin(), max_right.end()-k+1,
                  max_left.begin()+k-1, back_inserter(ans), 
                  [](int x, int y){return max(x, y);});
        return ans;
    }
};
```


# 双栈法
// 代码太长，暂时略过

# multiset法(152ms)
时间复杂度：O(NLogK)
空间复杂度：O(K)

```cpp
class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        vector<int> result;
        if (k == 0) return result;
        multiset<int> w;
        for (int i = 0, n = (int)nums.size(); i < n; i++) {
            if (i >= k)
                w.erase(w.find(nums[i-k]));
            w.insert(nums[i]);
            if (i >= k-1)
                result.push_back(*w.rbegin());
        }
        return result;
    }
};
```

# 堆方法(120ms)
时间复杂度：O(NlogK)
空间复杂度：O(K)

```cpp
class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        vector<int> result;
        if (k == 0) return result;
        priority_queue<pair<int, int>> w;
        for (int i = 0, n = (int)nums.size(); i < n; i++) {
        	// 销毁所有窗外的元素
            while (!w.empty() && w.top().second <= i-k)
                w.pop();
            w.push(make_pair(nums[i],i));
            if (i >= k-1)
                result.push_back(w.top().first);
        }
        return result;
    }
};
```

[1]: https://leetcode.com/problems/sliding-window-maximum/