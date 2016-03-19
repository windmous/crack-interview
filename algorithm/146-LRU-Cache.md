题目链接: [146.LRU Cache][1]
难度: Hard

# 组合Hash和list法(172ms)
时间复杂度：O(1)
空间复杂度：O(N)

我们使用链表存储缓存Item，靠前的元素表示最近访问过，一旦缓存满了可以直接将链表最后一个元素删掉。另外使用一个Hash表记录各个元素存储的位置。

如果想提高运行速度，可以在HashMap中同时记录value和迭代器，而在list中仅记录访问顺序。

```cpp
class LRUCache{
public:
    struct CacheNode {
        int key;
        int value;
        CacheNode(int k, int v) : key(k), value(v) {}
    };
    
    LRUCache(int capacity) {
        this->capacity = capacity;    
    }
    
    int get(int key) {
        if (cacheMap.find(key) != cacheMap.end()) {
            // 将节点插入到cacheList的头部, splice仅操作链表节点
            cacheList.splice(cacheList.begin(), cacheList, cacheMap[key]);
            cacheMap[key] = cacheList.begin();
            return cacheList.front().value;
        } else {
            return -1;
        }
    }
    
    void set(int key, int value) {
        if (cacheMap.find(key) != cacheMap.end()) {
            // 缓存命中，应该更新
            cacheMap[key]->value = value;
            cacheList.splice(cacheList.begin(), cacheList, cacheMap[key]);

            // 如果将cacheMap的元素类型换成pair<int, list<CacheNode>::iterator>，那么
            // 可以省掉一次查表
            cacheMap[key] = cacheList.begin();
        } else { // 缓存未命中，插入新的缓存项
            if (cacheList.size() == capacity) {
                cacheMap.erase(cacheList.back().key);
                cacheList.pop_back();
            }
            
            cacheList.emplace_front(key, value);
            cacheMap[key] = cacheList.begin();
        }
    }
    
private:
    // 本Cache的最大容量
    int capacity;
    // 存储Cache中的数据项，Item的位置同时表示最近访问次序
    list<CacheNode> cacheList;
    // 用来加速Key查询
    unordered_map<int, list<CacheNode>::iterator> cacheMap;
};
```

[1]: https://leetcode.com/problems/lru-cache/