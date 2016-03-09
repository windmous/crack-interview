题目链接: [284.Peeking Iterator][1]
难度: Medium

描述：目前已存在一个Iterator类，它有next和hasNext两个方法。现在要求设计一个PeekingIterator，要求除了next和hasNext两个方法之外，还要有一个peek操作。

# 预取+缓存法
时间复杂度：O(1)
空间复杂度：O(1)

我们直接预取下一个元素，当peek的时候就返回这个预取结果，当next的时候我们预取下一个位置。

```cpp
// Below is the interface for Iterator, which is already defined for you.
// **DO NOT** modify the interface for Iterator.
class Iterator {
    struct Data;
	Data* data;
public:
	Iterator(const vector<int>& nums);
	Iterator(const Iterator& iter);
	virtual ~Iterator();
	// Returns the next element in the iteration.
	int next();
	// Returns true if the iteration has more elements.
	bool hasNext() const;
};


class PeekingIterator : public Iterator {
public:
    int next_ele;
    bool has_next;
    
	PeekingIterator(const vector<int>& nums) : Iterator(nums) {
	    // Initialize any member here.
	    // **DO NOT** save a copy of nums and manipulate it directly.
	    // You should only use the Iterator interface methods.
	    has_next = Iterator::hasNext();
	    if (has_next) next_ele = Iterator::next();
	}

    // Returns the next element in the iteration without advancing the iterator.
	int peek() {
	    return next_ele;
	}

	// hasNext() and next() should behave the same as in the Iterator interface.
	// Override them if needed.
	int next() {
        int temp = next_ele;
        has_next = Iterator::hasNext();
        if (has_next) next_ele = Iterator::next();
        
        return temp;
	}

	bool hasNext() const {
        return has_next;
	}
};
```

# 复制法(4ms)
时间复杂度：O(1)
空间复杂度：O(1)

这个方法的好处是PeekingIterator不需要持有任何的缓存数据。缺点是效率可能比较慢(视Iterator的实现而定)，并且Iterator保证不会修改data的数据。

```cpp
// Below is the interface for Iterator, which is already defined for you.
// **DO NOT** modify the interface for Iterator.
class Iterator {
    struct Data;
	Data* data;
public:
	Iterator(const vector<int>& nums);
	Iterator(const Iterator& iter);
	virtual ~Iterator();
	// Returns the next element in the iteration.
	int next();
	// Returns true if the iteration has more elements.
	bool hasNext() const;
};


class PeekingIterator : public Iterator
{
public:
    PeekingIterator(const vector<int> &nums) : Iterator(nums)
    {
    }

    int peek()
    {
        return Iterator(*this).next();
    }

    int next()
    {
        return Iterator::next();
    }

    bool hasNext() const
    {
        return Iterator::hasNext();
    }
};
```

[1]: https://leetcode.com/problems/peeking-iterator/