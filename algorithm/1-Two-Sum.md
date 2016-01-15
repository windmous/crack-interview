题目链接：[1.Two Sum][1]
# 基于哈希表解法
平均时间复杂度：O(n)

要点：
1. 不需要一开始将所有元素都放入哈希表，而是在迭代过程中插入元素。
2. 可以将Wanted number放入哈希表中(见解2)。
3. 如果有**重复元素**则可能有多个解，但本题保证只有一个解。
4. 要考虑最终解实际是两个重复元素的情况，注释中已加以标注。

## 解1
```cpp
vector<int> twoSum(vector<int> &numbers, int target)
{
    //Key is the number and value is its index in the vector.
    unordered_map<int, int> hash;
    vector<int> result;
    for (int i = 0; i < numbers.size(); i++) {
        int numberToFind = target - numbers[i];

        //if numberToFind is found in map, return them
        if (hash.find(numberToFind) != hash.end()) {
            //+1 because indices are NOT zero based
            result.push_back(hash[numberToFind] + 1);
            result.push_back(i + 1);            
            return result;
        }

        // 将元素插入放到后面可以避免重复元素问题。
        hash[numbers[i]] = i;
    }
    return result;
}
```

## 解2：插入Wanted Number

```cpp
class Solution {
public:
    vector<int> twoSum(vector<int> &numbers, int target) {
        unordered_map<int, int> hash;
        vector<int> result;
        
        for (int i = 0; i < numbers.size(); ++ i) {
            if (hash.find(numbers[i]) != hash.end()) {
                result.push_back(hash[numbers[i]] + 1);
                result.push_back(i + 1);
                return result;
            }
            
            // 此处改为插入Wanted Number
            hash[target-numbers[i]] = i;
        }
        return result;
    }
};
```

## 解3：一开始将所有元素插入hash表
```cpp
class Solution {
public:
    vector<int> twoSum(vector<int> &numbers, int target) {
        unordered_map<int, int> hash;
        vector<int> result;
        
        for (int i = 0; i < numbers.size(); ++ i) {
            hash[numbers[i]] = i;
        }
        
        for (int i = 0; i < numbers.size(); ++ i) {
            const int gap = target - numbers[i];
            // 注意hash[gap]必须大于i，处理重复元素问题
            if (hash.count(gap) && hash[gap] > i) {
                result.push_back(i + 1);
                result.push_back(hash[gap] + 1);
                break;
            }
        }
        return result;
    }
};
```

# 排序夹逼法
时间复杂度：O(nlogn)
可以将所有元素排序，然后左右夹逼。但本题要求返回下标，故要记录若干辅助信息，比较麻烦，略。

  [1]: https://leetcode.com/problems/two-sum/