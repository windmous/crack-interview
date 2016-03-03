题目链接: [225.Implement Stack using Queues][1]
难度: Easy

# Push复杂法(0ms)
时间复杂度：Push为O(N)，其余为O(1)

```cpp
class Stack {
public:
    // Push element x onto stack.
    void push(int x) {
        q.push(x);
        for (int i = 1; i < q.size(); ++ i) {
            q.push(q.front());
            q.pop();
        }
    }

    // Removes the element on top of the stack.
    void pop() {
        q.pop();
    }

    // Get the top element.
    int top() {
        return q.front();
    }

    // Return whether the stack is empty.
    bool empty() {
        return q.empty();
    }
    
private:
    std::queue<int> q;
};
```

# 双队列法(0ms)
时间复杂度：Push为O(N^{1/2}), 其余为O(1)

```cpp
class Stack {
public:
    // Push element x onto stack.
    void push(int x) {
        first.push(x);
        for (int i = 1; i < first.size(); ++ i) {
            first.push(first.front());
            first.pop();
        }
        
        if (first.size() * first.size() > second.size()) {
            while (!second.empty()) {
                first.push(second.front());
                second.pop();
            }
            
            swap(first, second);
        }
    }

    // Removes the element on top of the stack.
    void pop() {
        if (first.empty()) {
            second.pop();
        } else {
            first.pop();
        }
    }

    // Get the top element.
    int top() {
        return first.empty() ? second.front() : first.front();
    }

    // Return whether the stack is empty.
    bool empty() {
        return first.empty() && second.empty();
    }
    
private:
    std::queue<int> first;
    std::queue<int> second;
};
```

# Pop复杂法(0ms)
时间复杂度：Pop方法为O(N)，其余为O(1)
```cpp
class Stack {
public:
    // Push element x onto stack.
    void push(int x) {
        q.push(x);
    }

    // Removes the element on top of the stack.
    void pop() {
        if (!q.empty()) {
            for (int i = 1; i < q.size(); ++ i) {
                q.push(q.front());
                q.pop();
            }
        }
        q.pop();
    }

    // Get the top element.
    int top() {
        return q.back();
    }

    // Return whether the stack is empty.
    bool empty() {
        return q.empty();
    }
    
private:
    std::queue<int> q;
};
```

[1]: https://leetcode.com/problems/implement-stack-using-queues/