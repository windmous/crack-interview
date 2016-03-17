题目链接: [117.Populating Next Right Pointers in Each Node II][1]
难度: Hard

树的节点多了一个next指针，任务是将每个节点的next指针指向其右边的节点，每层最右节点的next设为null。要求只用常数额外空间。

P116树保证是完全二叉树。P117取消此条件。


# 同样是用next指针层次遍历，但是增加了一些指针

和P116解法的想法大致相同，除了有一个指向下一层开头的指针之外，P117增加了一个prev指针，指向待修改next的节点。

```java
public class Solution {

    //based on level order traversal
    public void connect(TreeLinkNode root) {

        TreeLinkNode head = null; //head of the next level
        TreeLinkNode prev = null; //the leading node on the next level
        TreeLinkNode cur = root;  //current node of current level

        while (cur != null) {

            while (cur != null) { //iterate on the current level
                //left child
                if (cur.left != null) {
                    if (prev != null) {
                        prev.next = cur.left;
                    } else {
                        head = cur.left;
                    }
                    prev = cur.left;
                }
                //right child
                if (cur.right != null) {
                    if (prev != null) {
                        prev.next = cur.right;
                    } else {
                        head = cur.right;
                    }
                    prev = cur.right;
                }
                //move to next node
                cur = cur.next;
            }

            //move to next level
            cur = head;
            head = null;
            prev = null;
        }

    }
}
```

[1]: https://leetcode.com/problems/populating-next-right-pointers-in-each-node-ii/