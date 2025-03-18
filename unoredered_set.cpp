#include <iostream>
#include <vector>

// Hash table node structure for unordered_set
template <typename K>
struct HashNode {
    K key;
    HashNode* next;
    
    HashNode(K k) : key(k), next(nullptr) {}
};

// Simple unordered_set implementation using separate chaining for collision handling
template <typename K>
class UnorderedSet {
private:
    std::vector<HashNode<K>*> table;
    int capacity;
    int size_count;
    
    int hashFunction(K key) {
        return std::hash<K>{}(key) % capacity;
    }
    
public:
    UnorderedSet(int cap = 10) : capacity(cap), size_count(0) {
        table.resize(capacity, nullptr);
    }
    
    void insert(K key) {
        int hashIndex = hashFunction(key);
        HashNode<K>* newNode = new HashNode<K>(key);
        
        if (!table[hashIndex]) {
            table[hashIndex] = newNode;
        } else {
            HashNode<K>* temp = table[hashIndex];
            while (temp) {
                if (temp->key == key) {
                    delete newNode; // Avoid duplicates
                    return;
                }
                if (!temp->next) break;
                temp = temp->next;
            }
            temp->next = newNode;
        }
        size_count++;
    }
    
    bool contains(K key) {
        int hashIndex = hashFunction(key);
        HashNode<K>* temp = table[hashIndex];
        while (temp) {
            if (temp->key == key)
                return true;
            temp = temp->next;
        }
        return false;
    }
    
    int size() {
        return size_count;
    }
};

int main() {
    std::cout << "UnorderedSet Example:\n";
    UnorderedSet<int> uset;
    uset.insert(1);
    uset.insert(2);
    uset.insert(3);
    
    std::cout << "Contains key 2: " << (uset.contains(2) ? "Yes" : "No") << "\n";
    std::cout << "Contains key 4: " << (uset.contains(4) ? "Yes" : "No") << "\n";
    std::cout << "UnorderedSet Size: " << uset.size() << "\n";
    
    return 0;
}
