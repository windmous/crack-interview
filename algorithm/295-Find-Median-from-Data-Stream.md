题目链接: [295.Find Median from Data Stream][1]
难度: Hard

描述：实现一个数据结构，支持下面两种操作：
1. void addNum(int num) - Add a integer number from the data stream to the data structure.
2. double findMedian() - Return the median of all elements so far.

例子：
```
add(1)
add(2)
findMedian() -> 1.5
add(3) 
findMedian() -> 2
```

# 双堆法
时间复杂度：findMedian O(1)    addNum O(logN)
空间复杂度：O(N)

使用两个堆，一个堆保存前N/2个较小元素，另一个堆维护后N/2个较大元素。

```cpp
class MedianFinder {
	// 防止求和时溢出
    priority_queue<long> small, large;
public:

    void addNum(int num) {
        small.push(num);
        large.push(-small.top());
        small.pop();
        if (small.size() < large.size()) {
            small.push(-large.top());
            large.pop();
        }
    }

    double findMedian() {
        return small.size() > large.size()
               ? small.top()
               : (small.top() - large.top()) / 2.0;
    }
};
```


```cpp
class MedianFinder {
public:

    // Adds a number into the data structure.
    void addNum(int num) {
       small.push(num);
       large.push(small.top());
       small.pop();
       
       if (large.size() > small.size()) {
           small.push(large.top());
           large.pop();
       }
       
    }

    // Returns the median of current data stream
    double findMedian() {
        return ((small.size() + large.size()) % 2 == 0) ? 0.5 * (small.top() + large.top()) : small.top();
    }
    
private:
    priority_queue<int> small; // 大根堆
    priority_queue<int, vector<int>, std::greater<int>> large; // 小根堆
};

// Your MedianFinder object will be instantiated and called as such:
// MedianFinder mf;
// mf.addNum(1);
// mf.findMedian();
```

[1]: https://leetcode.com/problems/find-median-from-data-stream/