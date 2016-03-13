题目链接: [99.Recover Binary Search Tree][1]
难度: Hard

二叉查找树中有两个元素被对调了，将其调回来。要求常数额外空间。


# 递归中序遍历

https://leetcode.com/discuss/13034/no-fancy-algorithm-just-simple-and-powerful-order-traversal


巧妙利用了递归，但是有人提出栈空间占用是O（log n），所以并不是常数额外空间方法
```cpp
class Solution {
public:
    void recoverTree(TreeNode* root) {
        TreeNode* firstElem = nullptr;
        TreeNode* secondElem = nullptr;
        TreeNode* prevElem = new TreeNode(INT_MIN);
        
        traverse(root, firstElem, secondElem, prevElem);
        swap(firstElem->val, secondElem->val);
    }
    
    void traverse(TreeNode* root, TreeNode* &firstElem, TreeNode* &secondElem, TreeNode* &prevElem) {
        if (root == nullptr) return;
        
        traverse(root->left, firstElem, secondElem, prevElem);
        
        // start of doing something
        if (firstElem == nullptr && prevElem->val >= root->val) firstElem = prevElem;
        if (firstElem != nullptr && prevElem->val >= root->val) secondElem = root;
        // firstElem比中序遍历后一个元素大，secondElem比前一个元素小。注意secondElem的赋值条件
        // 例如623451,2和1都比前面元素小，6和5都比后面元素大，但124356只有4和3满足firstElem和secondElem的条件
        // firstElem指向第一个“比下一个元素小”的元素，secondElem指向最后一个（有时第一有时第二）“比上一个元素大”的元素
        
        prevElem = root;
        traverse(root->right, firstElem, secondElem, prevElem); 
    }
};
```

# Morris 中序遍历

https://leetcode.com/discuss/26310/detail-explain-about-morris-traversal-finds-incorrect-pointer

```java
public void recoverTree(TreeNode root) {
	TreeNode pre = null;
	TreeNode first = null, second = null;
	// Morris Traversal
	TreeNode temp = null;
	while(root!=null){
		if(root.left!=null){
			// connect threading for root
			temp = root.left;
			while(temp.right!=null && temp.right != root)
				temp = temp.right;
			// the threading already exists
			if(temp.right!=null){
				if(pre!=null && pre.val > root.val){
					if(first==null){first = pre;second = root;}
					else{second = root;}
				}
				pre = root;

				temp.right = null;
				root = root.right;
			}else{
				// construct the threading
				temp.right = root;
				root = root.left;
			}
		}else{
			if(pre!=null && pre.val > root.val){
				if(first==null){first = pre;second = root;}
				else{second = root;}
			}
			pre = root;
			root = root.right;
		}
	}
	// swap two node values;
	if(first!= null && second != null){
		int t = first.val;
		first.val = second.val;
		second.val = t;
	}
}
```

[1]: https://leetcode.com/problems/recover-binary-search-tree/