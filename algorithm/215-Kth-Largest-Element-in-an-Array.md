题目链接：[215. Kth Largest Element in an Array][1]

# 排序法
时间复杂度：O(NlogN)
```cpp
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        sort(nums.begin(), nums.end());
        return nums[nums.size() - k];
    }
};
```

# 堆排序
O(n + klogn) complexity: O(n) for build_max_heap; O(klogn) for k times of max_heapify in findKthLargest.

下面直接使用priority_queue，删除前k-1个元素即可
```cpp
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        priority_queue<int> pq(nums.begin(), nums.end());
        for (int i = 0; i < k - 1; i++)
            pq.pop(); 
        return pq.top();
    }
}; 
```

或者动手实现堆：

```cpp
class Solution {
public:   
    inline int left(int idx) {
        return (idx << 1) + 1;
    }
    inline int right(int idx) {
        return (idx << 1) + 2;
    }
    void max_heapify(vector<int>& nums, int idx) {
        int largest = idx;
        int l = left(idx), r = right(idx);
        if (l < heap_size && nums[l] > nums[largest]) largest = l;
        if (r < heap_size && nums[r] > nums[largest]) largest = r;
        if (largest != idx) {
            swap(nums[idx], nums[largest]);
            max_heapify(nums, largest);
        }
    }
    void build_max_heap(vector<int>& nums) {
        heap_size = nums.size();
        for (int i = (heap_size >> 1) - 1; i >= 0; i--)
            max_heapify(nums, i);
    }
    int findKthLargest(vector<int>& nums, int k) {
        build_max_heap(nums);
        for (int i = 0; i < k; i++) {
            swap(nums[0], nums[heap_size - 1]);
            heap_size--;
            max_heapify(nums, 0);
        }
        return nums[heap_size];
    }
private:
    int heap_size;
}
```

# 使用树/堆维持前k个元素
时间复杂度：O(NlogK)

## 使用堆
```cpp
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        // 维持迄今为止发现的最大的k个元素
        priority_queue<int, vector<int>, greater<int>> pq;
        for (int i = 0; i < nums.size(); i++) { 
            pq.push(nums[i]);
            // 踢掉最小元素
            if (pq.size() > k)
                pq.pop();
        }
        return pq.top();
    }
};
```

## 使用multiset
```cpp
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        multiset<int> mset;
        int n = nums.size();
        for (int i = 0; i < n; i++) { 
            mset.insert(nums[i]);
            if (mset.size() > k)
                // 踢掉最小元素
                mset.erase(mset.begin());
        }
        return *mset.begin();
    }
};
```

# Partition法(184ms)
平均：O(N)，最坏：O(N^2)
如果加上shuffle，那么可以认为性能到O(N)
```cpp
class Solution { 
public:
    int partition(vector<int>& nums, int left, int right) {
        // 注意该partition是讲大于pivot的放到左边，小于pivot的放到右边
        int pivot = nums[left];
        int l = left + 1, r = right;
        while (l <= r) {
            if (nums[l] < pivot && nums[r] > pivot)
                swap(nums[l++], nums[r--]);
            if (nums[l] >= pivot) l++; 
            if (nums[r] <= pivot) r--;
        }
        swap(nums[left], nums[r]);
        return r;
    }

    int findKthLargest(vector<int>& nums, int k) {
        int left = 0, right = nums.size() - 1;
        while (true) {
            int pos = partition(nums, left, right);
            if (pos == k - 1) return nums[pos];
            if (pos > k - 1) right = pos - 1;
            else left = pos + 1;
        }
    }
};
```

[1]: https://leetcode.com/problems/kth-largest-element-in-an-array/