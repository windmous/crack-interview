题目链接: [274.H-Index][1]
难度: Medium

描述：给定一组整数A，求一个最大的整数n使得集合{x>n:x \in A} + {x==n:x \in A}的任意子集的大小恰好为n。

疑问：实际上这样的n最多只有一个，见[这里][2]

# 桶方法(4ms)
时间复杂度：O(N)
空间复杂度：O(N)

要解决此问题，关键是要知道大于某个整数的元素个数有多少个。在general的情况下要用O(1)时间回答此问题通常需要先排序。但是本题下由于元素与元素总个数存在一定约束，导致可以先建立N个桶（N为元素总个数），然后用桶完成计数。

这里需要说明的是为什么将大于N的元素都统一放到了一个桶里。这是因为解的定义域是在[0, N]内，对>=N的元素做更详细的统计（指用更多的桶）是没有意义的。我们利用这些桶的方式分别是：>=N的元素有多少个？>=N-1的元素有多少个等等。我们绝不会问>=N+1的元素有多少个，N+1绝对不可能是问题的解。

```cpp
class Solution {
public:
    int hIndex(vector<int>& citations) {
        if(citations.empty())
            return 0;
        
        vector<int> buckets(citations.size()+1, 0);
        for (int n : citations) {
            if (n >= citations.size()) 
                buckets[buckets.size()-1] ++;
            else
                buckets[n] ++; 
        }
        
        int sum = 0;
        for (int i = citations.size(); i >= 0; -- i) {
            if ((sum += buckets[i]) >= i) 
                return i;
        }
        
        return 0;
    }
};
```

# 模拟桶方法(4ms)
时间复杂度：O(N)
空间复杂度：O(1)

上面的桶方法固然巧妙，但是需要额外开一个数组。这里直接使用输入的citations数组作为统计，相当巧妙，详情见注释。

```cpp
class Solution {
public:
    int hIndex(vector<int>& citations) {
        // Here, we fill the input array with counts, where
        // (-citations[i] - 1) is exactly the number
        // of papers having i publications.
        // Negative because we need to distinguish it from
        // the citation counts that we haven't processed yet.
        // Note that we'll just throw away any counts >= citations.length,
        // but we'll never need those.
        for (int i = 0; i < citations.size(); ++i) {
            int count = citations[i];
            if (count < 0)
                continue; // already processed
            citations[i] = -1; // the count starts with 0
            for (int nextCount; count < citations.size() &&
                                (nextCount = citations[count]) >= 0; ) {
                // We haven't got enough space to count those
                // >= citations.length, but neither we need them.
                citations[count] = -2; // we've just seen one
                count = nextCount;
            }
            // The loop above could have terminated either
            // 1) because count >= citations.length (we don't count those) or
            // 2) because we hit an element that already stores a count.
            // In the second case we need to increment that count since
            // we've just encountered another element with the same value.
            if (count < citations.size()) {
                --citations[count];
            }
        }
        for (int h = 0, less = 0; h < citations.size(); ++h) {
            int count = -citations[h] - 1;
            // Logically, the loop below must have this condition:
            // citations.length - less >= h && less + count >= citations.length - h,
            // but the first of these is really redundant. Indeed, it is obviously
            // true on the first iteration, and it follows that if it was true for
            // some "h", then it would be true for "h + 1". Indeed, the "less" variable
            // on this iteration is what "less + count" was on the previous one, so 
            // the (citations.length - less >= h) condition, in terms of
            // the previous-iteration values, is nothing but really
            // (citations.length - (less + count) >= h + 1),
            // which is exactly the same as (citations.length - (h + 1) >= (less + count))
            // or (citations.length - h > (less + count)), but if that was false, then
            // (less + count >= citations.length - h) would be true on the previous
            // iteration, and the whole thing would have terminated earlier.
            // 上面这一大堆没怎么看，下面是本人理解(windpls)。下面令T(otal)代替citations.size()
            // 实际上，要确认一个h是不是H-index，我们要满足下面两个式子才可以：
            // 1) T - less >= h
            // 2) T - less - count < h + 1
            // 即包含引用量为h的那些paper就OK，一旦再向前走一步，踢掉引用量为h+1的论文，那么数量就
            // 不够了。条件2)可以转换为T-less-count <= h，即less+count >= T-h
            // 那么问题变成，为什么条件1)可以省略呢？假设h=k时条件1)会失败，那么实际上在h=k-1时由于2)
            // 成立会导致程序return退出！故而我们可以直接省略，推导如下：
            // 由假设知， T - less_k < k 
            // 则:       T - (count_k + less_{k-1}) < (k-1)+1
            // 而条件2)在h=k-1时会有：
            //           T - (count_k, less_{k-1}) < (k_1)+1
            // 也就是说，只要h=k时条件1)失败，那么实际上在h=k-1时条件2)也就成立了，而此时条件1)也成立，
            // 故而程序已经retrun。
            if (less + count >= citations.size() - h)
                return h;
            less += count;
        }
        return citations.size();
    }
};
```

# Partition方法(4ms)
时间复杂度：最坏O(N^2)，平均O(N)
空间复杂度：O(log1)


这个解法卡好久，主要是Partition方法很不熟悉，建议看看[cpp_reference][3]，那里介绍了如何用Partition实现quicksort。
```cpp
class Solution {
public:
    int hIndex(vector<int>& citations) {
        auto start = citations.begin(), end = citations.end();
        int hIndex = 0;
        
        while (start < end) {
            const int pivot = *start;
            auto mid = partition(start, end,
                    [pivot](int x){return x < pivot;});
                    
            if (distance(mid, citations.end()) <= pivot) {
                hIndex = distance(mid, citations.end());
                end = mid;
            } else {
                partition(mid, end,[pivot](int x){return pivot >= x;});
                start = mid+1;
            }
        }
        
        return hIndex;
    }
};
```


# 排序法(4ms)
时间复杂度：O(NlogN)
空间复杂度：O(1)

```cpp
class Solution {
public:
    int hIndex(vector<int>& citations) {
        if(citations.empty())
            return 0;
        sort(citations.begin(), citations.end());
        
        const int n=citations.size();
        int i=0;
        // 一旦citations[i] >= (n-i)，
        // 就意味着有n-i个元素值都>=(n-i)
        while(i<n && citations[i]<(n-i)) i++;
        return n-i;
    }
};
```

[1]: https://leetcode.com/problems/h-index/
[2]: https://leetcode.com/discuss/56001/is-it-possible-to-have-two-this-problem-please-give-an-example
[3]: http://en.cppreference.com/w/cpp/algorithm/partition