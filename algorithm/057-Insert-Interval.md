题目链接: [57.Insert Interval][1]
难度: Hard

此题答案统计中C++ ~ 600ms，Java ~ 10ms， Python ~ 100 ms，猜测是leetcode做了什么手脚

# STL  时间O(log N)  580ms
```cpp
class Solution {
public:
    vector<Interval> insert(vector<Interval>& intervals, Interval newInterval) {
        auto compare = [] (const Interval &intv1, const Interval &intv2)
                          { return intv1.end < intv2.start; };
		// 注意equal_range使用compare的方法，compare实际上返回的是a < b的结果
		// Two elements, a and b are considered equivalent if (!(a<b) && !(b<a)) or if (!comp(a,b) && !comp(b,a))
		// 两个interval “相等”的条件是各自的end都大于对方的start
        auto range = equal_range(intervals.begin(), intervals.end(), newInterval, compare);
        auto itr1 = range.first, itr2 = range.second;
        if (itr1 == itr2) {
            intervals.insert(itr1, newInterval);
        } else {
            itr2--;
            itr2->start = min(newInterval.start, itr1->start);
            itr2->end = max(newInterval.end, itr2->end);
            intervals.erase(itr1, itr2);
        }
        return intervals;
    }
};
```

[1]: https://leetcode.com/problems/insert-interval/