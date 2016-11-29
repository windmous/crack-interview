题目链接: [305.Number of Islands II][1]
难度: Hard

# 并查集+Hash
时间复杂度：O(KlogMN)
空间复杂度：O(K)

```cpp
class UFSet {
public:
    UFSet(int k) : parent(k, 0), total_sets(0), num_sets(0) {
        iota(parent.begin(), parent.end(), 0);
    }
    
    int insert() {
        return num_sets++, total_sets++;
    }
    
    void merge(int s1, int s2) {
        int p1 = get_parent(s1);
        int p2 = get_parent(s2);
        if (p1 == p2) return ;
        else {
            parent[p1] = p2;
            num_sets --;
        }
    }
    
    int get_num_sets() const {
        return this->num_sets;
    }
    
    int get_parent(int no) {
        if (parent[no] == no) return no;
        else return parent[no] = get_parent(parent[no]);
    }
    
private:
    vector<int> parent;
    int num_sets, total_sets;
};

class Solution {
public:
    vector<int> numIslands2(int m, int n, vector<pair<int, int>>& positions) {
        unordered_map<int, int> islands;
        vector<int> result;
        static int deltas[] = {0, -1, 0, 1, 0};
        UFSet ss(positions.size());
        
        for (auto &pt : positions) {
            int y = pt.first, x = pt.second;
            const int code = y * n + x;
            if (islands.count(code)) continue;
            int id = ss.insert();
            islands[code] = id;
            
            for (int d = 0; d < 4; ++ d) {
                int new_y = y + deltas[d];
                int new_x = x + deltas[d+1];
                const int new_code = new_y * n + new_x;
                
                if (new_y >= 0 && new_y < m && new_x >= 0 && new_x < n && islands.count(new_code)) {
                    ss.merge(id, islands[new_code]);
                }
            }
            
            result.push_back(ss.get_num_sets());
        }
        
        return result;
    }
};
```

[1]: https://leetcode.com/problems/number-of-islands-ii/