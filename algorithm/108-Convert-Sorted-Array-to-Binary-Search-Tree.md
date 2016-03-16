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

# 二分法
```cpp
class Solution {
public:
    TreeNode *sortedArrayToBST(vector<int> &num) {
        if(num.size() == 0) return NULL;
        if(num.size() == 1)
        {
            return new TreeNode(num[0]);
        }

        int middle = num.size()/2;
        TreeNode* root = new TreeNode(num[middle]);

        vector<int> leftInts(num.begin(), num.begin()+middle);
        vector<int> rightInts(num.begin()+middle+1, num.end());

        root->left = sortedArrayToBST(leftInts);
        root->right = sortedArrayToBST(rightInts);

        return root;
    }
};
```
[1]: https://leetcode.com/problems/convert-sorted-array-to-binary-search-tree/