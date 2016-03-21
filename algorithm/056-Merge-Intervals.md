题目链接: [56.Merge Intervals][1]
难度: Hard

排序之后都好办。注意P56的排序准则和P57的不一样，P56是按照每个interval的start大小来排序。

```cpp
vector<Interval> merge(vector<Interval>& ins) {
    if (ins.empty()) return vector<Interval>{};
    vector<Interval> res;
    sort(ins.begin(), ins.end(), [](Interval a, Interval b){return a.start < b.start;});
    res.push_back(ins[0]);
    for (int i = 1; i < ins.size(); i++) {
        if (res.back().end < ins[i].start) res.push_back(ins[i]);
        else
            res.back().end = max(res.back().end, ins[i].end);
    }
    return res;
}
```

[1]: https://leetcode.com/problems/merge-intervals/