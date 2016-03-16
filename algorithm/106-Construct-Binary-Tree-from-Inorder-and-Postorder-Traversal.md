题目链接: [106.Construct Binary Tree from Inorder and Postorder Traversal][1]
难度: Medium


# 递归

https://leetcode.com/discuss/10961/my-recursive-java-code-with-o-n-time-and-o-n-space

java代码
```java
public TreeNode buildTreePostIn(int[] inorder, int[] postorder) {
    if (inorder == null || postorder == null || inorder.length != postorder.length)
        return null;
    HashMap<Integer, Integer> hm = new HashMap<Integer,Integer>(); // 牺牲O(N)空间来快速实现原本需要O(N)的查找操作
    for (int i=0;i<inorder.length;++i)
        hm.put(inorder[i], i);
    return buildTreePostIn(inorder, 0, inorder.length-1, postorder, 0, 
                          postorder.length-1,hm);
}

private TreeNode buildTreePostIn(int[] inorder, int is, int ie, int[] postorder, int ps, int pe, 
                                 HashMap<Integer,Integer> hm){
    if (ps>pe || is>ie) return null;
    TreeNode root = new TreeNode(postorder[pe]);
    int ri = hm.get(postorder[pe]);
    TreeNode leftchild = buildTreePostIn(inorder, is, ri-1, postorder, ps, ps+ri-is-1, hm);
    TreeNode rightchild = buildTreePostIn(inorder,ri+1, ie, postorder, ps+ri-is, pe-1, hm);
    root.left = leftchild;
    root.right = rightchild;
    return root;
}
```

# 非递归

https://leetcode.com/discuss/15115/my-comprehension-of-o-n-solution-from-%40hongzhi


与P105的非递归版本思想一致，同样难以理解

```cpp
class Solution {
public:
    TreeNode *buildTree(vector<int> &inorder, vector<int> &postorder) {
        if(inorder.size() == 0)return NULL;
        TreeNode *p;
        TreeNode *root;
        stack<TreeNode *> stn;

        root = new TreeNode(postorder.back()); 
        stn.push(root); 
        postorder.pop_back(); 

        while(true)
        {
            if(inorder.back() == stn.top()->val) 
            {
                p = stn.top();
                stn.pop(); 
                inorder.pop_back(); 
                if(inorder.size() == 0) break;
                if(stn.size() && inorder.back() == stn.top()->val)
                    continue;
                p->left = new TreeNode(postorder.back()); 
                postorder.pop_back();
                stn.push(p->left);
            }
            else 
            {
                p = new TreeNode(postorder.back());
                postorder.pop_back();
                stn.top()->right = p; 
                stn.push(p); 
            }
        }
        return root;
    }
};
```

[1]: https://leetcode.com/problems/construct-binary-tree-from-inorder-and-postorder-traversal/