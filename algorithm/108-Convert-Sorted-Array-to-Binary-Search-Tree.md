题目链接: [108.Convert Sorted Array to Binary Search Tree][1]
难度: Medium

将有序数组转为“height balanced BST”，这题不是很好，因为同一组数组可能有很多合法的“height balanced BST”

这种完全二叉树就难以实现二分法，但是他也是“height balanced BST”
```
3
|  \
1   4
|\  | \ 
0 2 #  #
```

这种则较好实现
```
2
| \
1   4
|\  | \
0 # 3  #
```

# 二分法 (16ms)
```cpp
class Solution {
public:
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        return solve(nums.begin(), nums.end());
    }
    
    template <typename Iterator>    
    TreeNode *solve(Iterator start, Iterator end) {
        if (start == end) return nullptr;
        
        auto mid = start + distance(start, end) / 2;
        TreeNode *root = new TreeNode(*mid);
        root->left = solve(start, mid);
        root->right = solve(mid+1, end);
        
        return root;
    }   
};
```
[1]: https://leetcode.com/problems/convert-sorted-array-to-binary-search-tree/