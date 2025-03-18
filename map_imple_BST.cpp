#include <iostream>

// Node structure for the BST
template <typename K, typename V>
struct BSTNode {
    K key;
    V value;
    BSTNode* left;
    BSTNode* right;
    
    BSTNode(K k, V v) : key(k), value(v), left(nullptr), right(nullptr) {}
};

// Simple map implementation using BST
template <typename K, typename V>
class BSTMap {
private:
    BSTNode<K, V>* root;
    int node_count;
    
    BSTNode<K, V>* insert(BSTNode<K, V>* node, K key, V value) {
        if (!node) {
            node_count++;
            return new BSTNode<K, V>(key, value);
        }
        
        if (key < node->key)
            node->left = insert(node->left, key, value);
        else if (key > node->key)
            node->right = insert(node->right, key, value);
        else
            node->value = value; // Update value if key exists
        
        return node;
    }
    
    BSTNode<K, V>* search(BSTNode<K, V>* node, K key) {
        if (!node || node->key == key)
            return node;
        
        if (key < node->key)
            return search(node->left, key);
        return search(node->right);
    }
    
    void inorder(BSTNode<K, V>* node) {
        if (!node) return;
        inorder(node->left);
        std::cout << node->key << ": " << node->value << std::endl;
        inorder(node->right);
    }
    
public:
    BSTMap() : root(nullptr), node_count(0) {}
    
    void insert(K key, V value) {
        root = insert(root, key, value);
    }
    
    V get(K key) {
        BSTNode<K, V>* node = search(root, key);
        if (!node) throw std::runtime_error("Key not found");
        return node->value;
    }
    
    int size() {
        return node_count;
    }
    
    void print() {
        inorder(root);
    }
};

int main() {
    std::cout << "BSTMap Example:\n";
    BSTMap<int, std::string> bstMap;
    bstMap.insert(1, "Apple");
    bstMap.insert(2, "Banana");
    bstMap.insert(3, "Cherry");
    bstMap.print();
    std::cout << "BSTMap Size: " << bstMap.size() << "\n\n";
    return 0;
}