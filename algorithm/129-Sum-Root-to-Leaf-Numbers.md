题目链接: [129.Sum Root to Leaf Numbers][1]
难度: Medium

树的每个节点是0-9的任意一个数字，根到叶子的路径组成一个数。求所有路径的数的和。

# dfs

https://leetcode.com/discuss/73014/super-simple-dfs-solution

```cpp
public class Solution {
    public int sumNumbers(TreeNode root) {
        return sumNumbers(root, 0);
    }

    private int sumNumbers(TreeNode root, int sum){
        if(root == null) return 0;
        if(root.left == null && root.right == null)
            return sum + root.val;

        return sumNumbers(root.left, (sum + root.val) * 10) + sumNumbers(root.right, (sum + root.val) * 10);

    }
}
```

[1]: https://leetcode.com/problems/sum-root-to-leaf-numbers/