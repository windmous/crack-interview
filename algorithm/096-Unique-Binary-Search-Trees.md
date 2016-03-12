题目链接: [96.Unique Binary Search Trees][1]
难度: Medium

给定n，判断1..n能组成多少不同的二叉查找树

# 动态规划

```cpp
int numTrees(int n) {
    vector<int> G(n+1, 0);
    G[0] = G[1] = 1;

    for(int i=2; i<=n; ++i) { // 元素个数为i的树
        for(int j=1; j<=i; ++j) { // 分配给左边j-1个元素，给右边i-j个元素
            G[i] += G[j-1] * G[i-j];
        }
    }

    return G[n];
}
```

[1]: https://leetcode.com/problems/unique-binary-search-trees/