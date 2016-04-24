题目链接: [297.Serialize and Deserialize Binary Tree][1]
难度: Medium

# 空格法(44ms)
时间复杂度：O(N)
空间复杂度：O(N)

使用空格间隔每个每个元素，同时用`#`表示NULL。

```cpp
class Codec {
public:
    string serialize(TreeNode* root) {
        ostringstream out;
        serialize(root, out);
        return out.str();
    }

    TreeNode* deserialize(string data) {
        istringstream in(data);
        return deserialize(in);
    }

private:
    void serialize(TreeNode* root, ostringstream& out) {
        if (root) {
            out << root->val << ' ';
            serialize(root->left, out);
            serialize(root->right, out);
        } else {
            out << "# ";
        }
    }

    TreeNode* deserialize(istringstream& in) {
        string val;
        in >> val;
        if (val == "#")
            return nullptr;
        TreeNode* root = new TreeNode(stoi(val));
        root->left = deserialize(in);
        root->right = deserialize(in);
        return root;
    }
};
```

[1]: https://leetcode.com/problems/serialize-and-deserialize-binary-tree/