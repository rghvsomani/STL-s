#include <iostream>
#include <vector>

// Hash table node structure
template <typename K, typename V>
struct HashNode {
    K key;
    V value;
    HashNode* next;
    
    HashNode(K k, V v) : key(k), value(v), next(nullptr) {}
};

// Simple unordered_map implementation using separate chaining for collision handling
template <typename K, typename V>
class UnorderedMap {
private:
    std::vector<HashNode<K, V>*> table;
    int capacity;
    int size_count;
    
    int hashFunction(K key) {
        return std::hash<K>{}(key) % capacity;
    }
    
public:
    UnorderedMap(int cap = 10) : capacity(cap), size_count(0) {
        table.resize(capacity, nullptr);
    }
    
    void insert(K key, V value) {
        int hashIndex = hashFunction(key);
        HashNode<K, V>* newNode = new HashNode<K, V>(key, value);
        
        if (!table[hashIndex]) {
            table[hashIndex] = newNode;
        } else {
            HashNode<K, V>* temp = table[hashIndex];
            while (temp) {
                if (temp->key == key) {
                    temp->value = value; // Update value if key exists
                    delete newNode;
                    return;
                }
                if (!temp->next) break;
                temp = temp->next;
            }
            temp->next = newNode;
        }
        size_count++;
    }
    
    V get(K key) {
        int hashIndex = hashFunction(key);
        HashNode<K, V>* temp = table[hashIndex];
        while (temp) {
            if (temp->key == key)
                return temp->value;
            temp = temp->next;
        }
        throw std::runtime_error("Key not found");
    }
    
    bool contains(K key) {
        int hashIndex = hashFunction(key);
        HashNode<K, V>* temp = table[hashIndex];
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
    std::cout << "UnorderedMap Example:\n";
    UnorderedMap<int, std::string> umap;
    umap.insert(1, "Apple");
    umap.insert(2, "Banana");
    umap.insert(3, "Cherry");
    
    std::cout << "Value for key 2: " << umap.get(2) << "\n";
    std::cout << "Contains key 3: " << (umap.contains(3) ? "Yes" : "No") << "\n";
    std::cout << "UnorderedMap Size: " << umap.size() << "\n";
    
    return 0;
}
