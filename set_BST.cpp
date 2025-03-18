#include <iostream>

// Node structure for the BST
template <typename K>
struct BSTNode {
    K key;
    BSTNode* left;
    BSTNode* right;
    
    BSTNode(K k) : key(k), left(nullptr), right(nullptr) {}
};

// Simple set implementation using BST
template <typename K>
class BSTSet {
private:
    BSTNode<K>* root;
    int node_count;
    
    BSTNode<K>* insert(BSTNode<K>* node, K key) {
        if (!node) {
            node_count++;
            return new BSTNode<K>(key);
        }
        
        if (key < node->key)
            node->left = insert(node->left, key);
        else if (key > node->key)
            node->right = insert(node->right, key);
        
        return node;
    }
    
    bool search(BSTNode<K>* node, K key) {
        if (!node) return false;
        if (node->key == key) return true;
        
        if (key < node->key)
            return search(node->left, key);
        return search(node->right, key);
    }
    
    void inorder(BSTNode<K>* node) {
        if (!node) return;
        inorder(node->left);
        std::cout << node->key << " ";
        inorder(node->right);
    }
    
public:
    BSTSet() : root(nullptr), node_count(0) {}
    
    void insert(K key) {
        root = insert(root, key);
    }
    
    bool contains(K key) {
        return search(root, key);
    }
    
    int size() {
        return node_count;
    }
    
    void print() {
        inorder(root);
        std::cout << std::endl;
    }
};

int main() {
    std::cout << "BSTSet Example:\n";
    BSTSet<int> bstSet;
    bstSet.insert(1);
    bstSet.insert(2);
    bstSet.insert(3);
    bstSet.print();
    std::cout << "BSTSet Size: " << bstSet.size() << "\n";
    
    return 0;
}