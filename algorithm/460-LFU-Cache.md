题目链接: [460.LFU Cache][1]
难度: Hard

# Hash法
时间复杂度：O(1)
空间复杂度：O(N)

本题的关键：
1) 注意使用min_freq来track目前最小的被访问数量
2) 理解set方法的功能，即如果key重复，其实是可以修改value就可以的。

```cpp
class LFUCache {
public:
    LFUCache(int capacity) : min_freq(INT_MAX), cap(capacity) {

    }

    int get(int key) {
        if (vals.count(key) == 0)
            return -1;

        int pre_freq = freqs[key] ++;
        qs[pre_freq].erase(positions[key]);
        qs[pre_freq+1].push_back(key);
        positions[key] = --qs[pre_freq+1].end();

        if (qs[pre_freq].empty()) {
            qs.erase(pre_freq);
            if (min_freq == pre_freq) {
                min_freq ++;
            }
        }

        return vals[key];
    }

    void set(int key, int value) {
        if (cap == 0) return ;
        
        if (get(key) != -1) {
            vals[key] = value;
            return ;
        }

        if (vals.size() >= cap) {
            int to_del = qs[min_freq].front();
            freqs.erase(to_del);
            vals.erase(to_del);
            positions.erase(to_del);
            qs[min_freq].pop_front();

            if (qs[min_freq].empty()) {
                qs.erase(min_freq);
            }
        }

        min_freq = 1;
        freqs[key] = 1;
        vals[key] = value;
        qs[1].push_back(key);
        positions[key] = -- qs[1].end();
    }

private:
    int min_freq;
    const int cap;
    unordered_map<int, int> freqs; // key->freqs
    unordered_map<int, int> vals; // key->value
    unordered_map<int, list<int>::iterator> positions; // key->iterator
    unordered_map<int, list<int>> qs; // freq->list_of_keys
};
```

[1]: https://leetcode.com/problems/lfu-cache/
