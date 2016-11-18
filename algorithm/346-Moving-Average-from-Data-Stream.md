题目链接: [346.Moving Average from Data Stream][1]
难度: Easy

Given a stream of integers and a window size, calculate the moving average of all integers in the sliding window.

For example,
MovingAverage m = new MovingAverage(3);
m.next(1) = 1
m.next(10) = (1 + 10) / 2
m.next(3) = (1 + 10 + 3) / 3
m.next(5) = (10 + 3 + 5) / 3
Show Company Tags
Show Tags

# A Naive solution
```cpp
class MovingAverage {
public:
    /** Initialize your data structure here. */
    MovingAverage(int size) : N(size), sum(0) {
        
    }
    
    double next(int val) {
        sum += val;
        nums.push(val);
        if (nums.size() > N) {
            sum -= nums.front();
            nums.pop();
        }
        return sum / nums.size();
    }
    
    const int N;
    queue<int> nums;
    double sum;
};

/**
 * Your MovingAverage object will be instantiated and called as such:
 * MovingAverage obj = new MovingAverage(size);
 * double param_1 = obj.next(val);
 */
```

[1]: https://leetcode.com/problems/moving-average-from-data-stream
