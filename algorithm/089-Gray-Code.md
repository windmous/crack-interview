题目链接: [89.Gray Code][1]
难度: Medium

返回n位格雷码的sequence

# 公式

第i个格雷码是：
G(i) = i^ (i/2)
```cpp
class Solution {
public:
    vector<int> grayCode(int n) {
        vector<int> vi;
        for (int i = 0; i < (1<<n); ++i) vi.push_back(i ^ (i >> 1));
        return vi;
    }
};
```
# 反射

除最高位之外其余的镜像对称，可按照此规则枚举
```
    0
    1
  ---
  1 1
  1 0
-----
1 1 0
1 1 1 
1 0 1 
1 0 0
-----
...
```
```cpp
vector<int> grayCode(int n) 
{         
    vector<int> result(1, 0);        
    for (int i = 0; i < n; i++) {
        int curCount = result.size();
        // push back all element in result in reverse order
        while (curCount) {
            curCount--;
            int curNum = result[curCount];
            curNum += (1<<i);
            result.push_back(curNum);
        } 
    }
    return result;
}
```

```cpp
class Solution {
public:
    vector<int> grayCode(int n) {
        vector<int> result = {0};
        result.reserve(1<<n);
        
        for (int i = 0; i < n; ++ i) {
            int high_bit = 1 << i;
            for (int j = result.size()-1; j >= 0; -- j) {
                result.push_back(result[j] | high_bit);
            }
        }
        
        return result;
    }
};
```

[1]: https://leetcode.com/problems/gray-code/