#include <iostream>

enum Color { RED, BLACK };

// Node structure for the Red-Black Tree
template <typename K, typename V>
struct Node {
    K key;
    V value;
    Color color;
    Node* left;
    Node* right;
    Node* parent;
    
    Node(K k, V v) : key(k), value(v), color(RED), left(nullptr), right(nullptr), parent(nullptr) {}
};

// Simple map implementation using Red-Black Tree
template <typename K, typename V>
class MyMap {
private:
    Node<K, V>* root;
    int node_count;

    void rotateLeft(Node<K, V>*& root, Node<K, V>*& node) {
        Node<K, V>* rightChild = node->right;
        node->right = rightChild->left;
        if (rightChild->left) rightChild->left->parent = node;
        rightChild->parent = node->parent;
        if (!node->parent) root = rightChild;
        else if (node == node->parent->left) node->parent->left = rightChild;
        else node->parent->right = rightChild;
        rightChild->left = node;
        node->parent = rightChild;
    }
    
    void rotateRight(Node<K, V>*& root, Node<K, V>*& node) {
        Node<K, V>* leftChild = node->left;
        node->left = leftChild->right;
        if (leftChild->right) leftChild->right->parent = node;
        leftChild->parent = node->parent;
        if (!node->parent) root = leftChild;
        else if (node == node->parent->right) node->parent->right = leftChild;
        else node->parent->left = leftChild;
        leftChild->right = node;
        node->parent = leftChild;
    }
    
    void fixInsert(Node<K, V>*& root, Node<K, V>*& node) {
        while (node->parent && node->parent->color == RED) {
            Node<K, V>* grandparent = node->parent->parent;
            if (node->parent == grandparent->left) {
                Node<K, V>* uncle = grandparent->right;
                if (uncle && uncle->color == RED) {
                    node->parent->color = BLACK;
                    uncle->color = BLACK;
                    grandparent->color = RED;
                    node = grandparent;
                } else {
                    if (node == node->parent->right) {
                        node = node->parent;
                        rotateLeft(root, node);
                    }
                    node->parent->color = BLACK;
                    grandparent->color = RED;
                    rotateRight(root, grandparent);
                }
            } else {
                Node<K, V>* uncle = grandparent->left;
                if (uncle && uncle->color == RED) {
                    node->parent->color = BLACK;
                    uncle->color = BLACK;
                    grandparent->color = RED;
                    node = grandparent;
                } else {
                    if (node == node->parent->left) {
                        node = node->parent;
                        rotateRight(root, node);
                    }
                    node->parent->color = BLACK;
                    grandparent->color = RED;
                    rotateLeft(root, grandparent);
                }
            }
        }
        root->color = BLACK;
    }
    
    Node<K, V>* insert(Node<K, V>* root, Node<K, V>* node) {
        if (!root) return node;
        
        if (node->key < root->key) {
            root->left = insert(root->left, node);
            root->left->parent = root;
        } else if (node->key > root->key) {
            root->right = insert(root->right, node);
            root->right->parent = root;
        } else {
            root->value = node->value; // Update value if key exists
        }
        return root;
    }
    
    Node<K, V>* search(Node<K, V>* node, K key) {
        if (!node || node->key == key)
            return node;
        if (key < node->key)
            return search(node->left, key);
        return search(node->right);
    }
    
    void inorder(Node<K, V>* node) {
        if (!node) return;
        inorder(node->left);
        std::cout << node->key << ": " << node->value << std::endl;
        inorder(node->right);
    }
    
public:
    MyMap() : root(nullptr), node_count(0) {}
    
    void insert(K key, V value) {
        Node<K, V>* node = new Node<K, V>(key, value);
        root = insert(root, node);
        fixInsert(root, node);
        node_count++;
    }
    
    V get(K key) {
        Node<K, V>* node = search(root, key);
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
    MyMap<int, std::string> myMap;
    myMap.insert(1, "Apple");
    myMap.insert(2, "Banana");
    myMap.insert(3, "Cherry");
    
    std::cout << "Key 2: " << myMap.get(2) << std::endl;
    
    std::cout << "\nMap Contents:" << std::endl;
    myMap.print();
    
    std::cout << "\nMap Size: " << myMap.size() << std::endl;
    
    return 0;
}
