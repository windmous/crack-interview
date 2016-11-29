题目链接: [272.Closest Binary Search Tree Value II][1]
难度: Hard

Given a non-empty binary search tree and a target value, find k values in the BST that are closest to the target.

Note:
Given target value is a floating point.
You may assume k is always valid, that is: k ≤ total nodes.
You are guaranteed to have only one unique set of k values in the BST that are closest to the target.
Follow up:
Assume that the BST is balanced, could you solve it in less than O(n) runtime (where n = total nodes)?

Hint:

Consider implement these two helper functions:
getPredecessor(N), which returns the next smaller node to N.
getSuccessor(N), which returns the next larger node to N.
Try to assume that each node has a parent pointer, it makes the problem much easier.
Without parent pointer we just need to keep track of the path from the root to the current node using a stack.
You would need two stacks to track the path in finding predecessor and successor node separately.

实际是道水题

# 中序遍历 + 队列(16ms)
```cpp
class Solution {
public:
    vector<int> closestKValues(TreeNode* root, double target, int k) {
        vector<int> result;
        double sum = 0.;
        queue<int> q;
        solve(root, q, k, sum, target);
        
        while (!q.empty()) {
            result.push_back(q.front());
            q.pop();
        }
        
        return result;
    }
    
    bool solve(TreeNode *root, queue<int> &q, const int k, double &sum, const double target) {
        if (!root) return true;
        if (!solve(root->left, q, k, sum, target)) return false;
        
        if (q.size() < k) {
            q.push(root->val);
            sum += abs(target - root->val);
        } else {
            double temp_sum = sum - (abs(q.front() - target)) + abs(root->val - target);
            if (temp_sum <= sum) {
                q.pop();
                q.push(root->val);
            } else {
                return false;
            }
        }
        
        return solve(root->right, q, k, sum, target);
    }
};
```
[1]: https://leetcode.com/problems/closest-binary-search-tree-value-ii/