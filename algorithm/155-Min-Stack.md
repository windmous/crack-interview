题目链接: [155.Min Stack][1]
难度: Easy

描述：设计一个栈，要求除了push、top、pop外，还能支持getMin()操作

# 双栈法(28ms)
时间复杂度：O(1)
空间复杂度：O(N)

```cpp
class MinStack {
private:
    stack<int> s1; // 记录数据
    stack<int> s2; // 记录最小值
public:
    void push(int x) {
        s1.push(x);
        if (s2.empty() || x <= getMin())  // 注意使用<=，故意造成duplicate
            s2.push(x);       
    }
    
    void pop() {
        if (s1.top() == getMin())  
            s2.pop();
        s1.pop();
    }
    
    int top() {
        return s1.top();
    }
    
    int getMin() {
        return s2.top();
    }
};
```

# 单栈法1(28ms)
时间复杂度：O(N)
空间复杂度：O(N)

核心思想是往栈里存value与最小值的gap。这样一旦出现了一个负的gap，就表示当前值比min还小，也就是出现了新的最小值！

```cpp
class MinStack {
private:
    stack<long long> ss;
    long long min_val = 0x7FFFFFFF;
public:
    void push(int x) {
        if (ss.empty()) {
            ss.push(0ll);
            min_val = x;
        } else {
            ss.push(x - min_val);
            if (x < min_val) min_val = x;
        }
    }
    
    void pop() {
        if (ss.empty()) return ;
        
        auto val = ss.top();
        ss.pop();
        if (val < 0) {
            min_val = min_val - val;
        }
    }
    
    int top() {
        const auto val = ss.top();
        return val > 0 ? (val + min_val) : min_val;
    }
    
    int getMin() {
        return min_val;
    }
};
```

# 单栈法2(28ms)
时间复杂度：O(N)
空间复杂度：O(N)

单栈法1的问题在于，它使用了long long，必须在某些时候转换类型。我们可以在发现一个更小的min_val之后，将min_val压入栈中，通过牺牲一点空间来免除类型转换问题。

```cpp
class MinStack {
private:
    stack<int> ss;
    int min_val = INT_MAX;
public:
    void push(int x) {
        if (ss.empty() || min_val >= x) {
            ss.push(min_val);
            min_val = x;
        }
        ss.push(x);
    }
    
    void pop() {
        if (ss.top() == min_val) {
            ss.pop();
            min_val = ss.top(); // 恢复老的min_val
            ss.pop();
        } else {
            ss.pop();
        }
        
        if (ss.empty()) 
            min_val = INT_MAX;
    }
    
    int top() {
        return ss.top();
    }
    
    int getMin() {
        return min_val;
    }
};
```


[1]: https://leetcode.com/problems/min-stack/