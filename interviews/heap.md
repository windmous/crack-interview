/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Codec {
public:

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        stringstream out;
        serialize(root, out);
        return out.str();
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        stringstream in(data);
        vector<string> elements;
        copy(istream_iterator<string>(in), istream_iterator<string>(),
            back_inserter(elements));
            
        int idx = 0;
        return deserialize(elements, idx);
    }
    
private:
    void serialize(TreeNode *root, stringstream& out) {
        if (root == nullptr) {
            out << "# ";
        } else {
            out << root->val << " ";
            serialize(root->left, out);
            serialize(root->right, out);
        }
    }
    
    TreeNode* deserialize(vector<string> &elements, int &idx) {
        if (idx >= elements.size() || elements[idx] == "#") {
            idx ++;
            return nullptr;
        }
        
        TreeNode *root = new TreeNode(stoi(elements[idx++]));
        root->left = deserialize(elements, idx);
        root->right = deserialize(elements, idx);
        
        return root;
    }

};

// Your Codec object will be instantiated and called as such:
// Codec codec;
// codec.deserialize(codec.serialize(root));