C++版本二叉排序树

```cpp
#include <iostream>
#include <cassert>

using namespace std;

struct TreeNode {
    TreeNode(int x=-1) : val(x), left(nullptr), right(nullptr) {}

    int val;
    TreeNode *left, *right;
};

class BST {
public:
    BST() : _root(nullptr) {}

    int size() const {
        return size(_root);
    }

    TreeNode *get(int key) const {
        TreeNode *cur = _root;
        while (cur != nullptr) {
            if (key == cur->val) return cur;
            else if (key < cur->val) cur = cur->left;
            else cur = cur->right;
        }

        return nullptr;
    }

    void put(int key) {
        TreeNode *pre = nullptr, *cur = _root;
        while (cur) {
            pre = cur;
            if (key == cur->val) return ;
            else if (key < cur->val) cur = cur->left;
            else cur = cur->right;
        }

        if (pre == nullptr) _root = new TreeNode(key);
        else if (key < pre->val) pre->left = new TreeNode(key);
        else pre->right = new TreeNode(key);
    }

    TreeNode *min() const {
        return min(_root);
    }

    void delete_min() {
        _root = delete_min(_root);
    }

    void delete_node(int key) {
        // BST中删除节点一共有三种情况
        // 1. 待删除的节点没有孩子,那么直接删除该节点即可
        // 2. 待删除的节点只有1个孩子,那么删除该节点,并让原来指向本节点的指针指向这唯一一个孩子
        // 3. 待删除的节点有2个孩子,此时删除右子树中最小的节点,并将其值拷贝到当前节点
        _root = delete_node(key, _root);
    }

    template <typename Visitor>
    void preorder_traverse(Visitor visitor) const {
        preorder_traverse(_root, visitor);
    }

    template <typename Visitor>
    void inorder_traverse(Visitor visitor) const {
        inorder_traverse(_root, visitor);
    }

    template <typename Visitor>
    void postorder_traverse(Visitor visitor) const {
        postorder_traverse(_root, visitor);
    }

private:
    TreeNode *delete_node(int key, TreeNode *root) {
        if (root == nullptr) return nullptr;

        if (key < root->val) root->left = delete_node(key, root->left);
        else if (key > root->val) root->right = delete_node(key, root->right);
        else {
            if (root->left != nullptr && root->right != nullptr) {
                root->val = min(root->right)->val;
                root->right = delete_min(root->right);
            } else {
                TreeNode *to_delete = root;
                if (root->left == nullptr) root = root->right;
                else root = root->left;
                delete to_delete;
            }
        }

        return root;
    }

    TreeNode *min(TreeNode *root) const {
        if (root == nullptr) return nullptr;
        while (root->left) {
            root = root->left;
        }

        return root;
    }

    int size(TreeNode *root) const {
        if (root == nullptr) return 0;
        return 1 + size(root->left) + size(root->right);
    }

    TreeNode *delete_min(TreeNode *root) {
        if (root == nullptr) return nullptr;

        if (root->left == nullptr) {
            TreeNode *to_delete = root;
            root = root->right;
            delete to_delete;
        } else {
            root->left = delete_min(root->left);
        }

        return root;
    }

    template <typename Visitor>
    void inorder_traverse(TreeNode *root, Visitor &visitor) const {
        if (root == nullptr) return;
        inorder_traverse(root->left, visitor);
        visitor(root->val);
        inorder_traverse(root->right, visitor);
    }

    template <typename Visitor>
    void preorder_traverse(TreeNode *root, Visitor &visitor) const {
        if (root == nullptr) return;
        visitor(root->val);
        preorder_traverse(root->left, visitor);
        preorder_traverse(root->right, visitor);
    }

    template <typename Visitor>
    void postorder_traverse(TreeNode *root, Visitor &visitor) const {
        if (root == nullptr) return;
        postorder_traverse(root->left, visitor);
        postorder_traverse(root->right, visitor);
        visitor(root->val);
    }

    TreeNode *_root;
};

void print_tree(const BST& tree) {
    auto printer = [&](int x) {cout << x << " ";};

    tree.preorder_traverse(printer);
    cout << endl;
    tree.inorder_traverse(printer);
    cout << endl;
    tree.postorder_traverse(printer);
    cout << endl;
}

int main() {
    BST bst;
    for (int x : {4, 2, 1, 8, 10, 12, 3, 5, 9}) {
        bst.put(x);
    }
    print_tree(bst);

    TreeNode *ele = bst.get(8);
    assert(ele != nullptr && ele->val == 8);
    ele = bst.get(100);
    assert(ele == nullptr);

    cout << "After delete some elements" << endl;
    bst.delete_node(3);
    bst.delete_node(4);
    print_tree(bst);

    cout << "Delete the minimum element" << endl;
    bst.delete_min();
    print_tree(bst);

    const int size = bst.size();
    cout << "There are " << size << " elements left." << endl;
    for (int i = 0; i < size; ++ i) {
        bst.delete_min();
    }

    print_tree(bst);

    return 0;
}
```