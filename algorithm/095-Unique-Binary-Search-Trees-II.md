题目链接: [95.Unique Binary Search Trees II][1]
难度: Medium

给定n，判断1..n能组成多少不同的二叉查找树，返回所有的这些树

# 递归 24ms

```cpp
class Solution {
public:
    vector<TreeNode*> generateTrees(int n) {
        if (n == 0) return {};
        return generate(1, n);
    }
private:
    vector<TreeNode*> generate(int start, int end) {
        if (start > end) {
            return vector<TreeNode*>(1, nullptr); 
        } 
        vector<TreeNode*> subTree;
        for (int k = start; k <= end; ++k) {
            vector<TreeNode*> leftSubs = generate(start, k - 1);
            vector<TreeNode*> rightSubs = generate(k + 1, end);
            for (auto i : leftSubs) {
                for (auto j : rightSubs) {
                    TreeNode* node = new TreeNode(k);
                    node->left = i; 
                    node->right = j;
                    subTree.push_back(node);
                }
            }
        }
        return subTree;
    }
};
```

[1]: https://leetcode.com/problems/unique-binary-search-trees-ii/