题目链接: [60.Permutation Sequence][1]
难度: Medium

寻找[123..n]的第k个permutation

say n = 4, you have {1, 2, 3, 4}

If you were to list out all the permutations you have

```
1 + (permutations of 2, 3, 4) 
2 + (permutations of 1, 3, 4) 
3 + (permutations of 1, 2, 4) 
4 + (permutations of 1, 2, 3)
```

# 0ms

```cpp
class Solution {
public:
	string getPermutation(int n, int k) {
		int pTable[10] = {1};
		for(int i = 1; i <= 9; i++){
			pTable[i] = i * pTable[i - 1];
		}
		string result;
		vector<char> numSet = {'1', '2','3','4','5','6','7','8','9'};
		while(n > 0){
			int temp = (k - 1) / pTable[n - 1];
			result += numSet[temp];
			numSet.erase(numSet.begin() + temp);
			k = k - temp * pTable[n - 1];
			n--;
		}
		return result;
	}
};
```

[1]: https://leetcode.com/problems/permutation-sequence/