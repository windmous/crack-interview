题目链接: [112.Path Sum][1]
难度: Easy

树的节点附带一个值，判断树从根到叶子是否有一条路径，各个节点和为目标值。因为只要bool返回，所以不用记录路径。

P113需要打印所有路径。

```cpp
bool hasPathSum(TreeNode *root, int sum) {
	if (root == NULL) return false;
	if (root->val == sum && root->left ==  NULL && root->right == NULL) return true;
	return hasPathSum(root->left, sum-root->val) || hasPathSum(root->right, sum-root->val);
}
```

[1]: https://leetcode.com/problems/path-sum/