题目链接: [232.Implement Queue using Stacks][1]
难度: Easy

# 双栈模拟法(0ms)
时间复杂度：peek、pop平摊复杂度为O(1)，最坏复杂度为O(N)；其余操作复杂度为O(1)
```cpp
class Queue {
public:
    // Push element x to the back of queue.
    void push(int x) {
        input.push(x);
    }

    // Removes the element from in front of queue.
    void pop(void) {
        make_output_ready();
        output.pop();
    }

    // Get the front element.
    int peek(void) {
        make_output_ready();
        return output.top();
    }

    // Return whether the queue is empty.
    bool empty(void) {
        return input.empty() && output.empty();
    }
    
private:
    void make_output_ready() {
        if (output.empty()) {
            while (!input.empty()) {
                output.push(input.top());
                input.pop();
            }
        }
    }

    stack<int> input, output;
};
```

# 单栈法1(0ms)
时间复杂度：push为O(N)，其余均为O(1)
```cpp
class Queue {
public:
    // Push element x to the back of queue.
    void push(int x) {
        stack<int> helper;
        while (!data.empty()) {
            helper.push(data.top());
            data.pop();
        }
        
        data.push(x);
        while (!helper.empty()) {
            data.push(helper.top());
            helper.pop();
        }
    }

    // Removes the element from in front of queue.
    void pop(void) {
        data.pop();
    }

    // Get the front element.
    int peek(void) {
        return data.top();
    }

    // Return whether the queue is empty.
    bool empty(void) {
        return data.empty();
    }
    
private:
    stack<int> data;
};
```

# 单栈法2(0ms)
时间复杂度：push为O(N)，其余为O(1)
注意：此方法可能导致StackOverflow!

```cpp
class Queue {
public:
    // Push element x to the back of queue.
    void push(int x) {
        if (data.empty()) {
            data.push(x);
        } else {
            int tmp = data.top();
            data.pop();
            push(x);
            data.push(tmp);
        }
    }

    // Removes the element from in front of queue.
    void pop(void) {
        data.pop();
    }

    // Get the front element.
    int peek(void) {
        return data.top();
    }

    // Return whether the queue is empty.
    bool empty(void) {
        return data.empty();
    }
    
private:
    stack<int> data;
};
```

[1]: https://leetcode.com/problems/implement-queue-using-stacks/