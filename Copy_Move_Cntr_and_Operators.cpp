#include <iostream>
using namespace std;

class Test {
    int* data;
public:
    // Constructor
    Test(int value) : data(new int(value)) {
        cout << "default constructor" << endl;
    }

    // Copy Constructor
    Test(const Test& obj) : data(new int(*obj.data)) {
        cout << "copy constructor" << endl;
    }

    // Copy Assignment Operator
    Test& operator=(const Test& obj) {
        cout << "copy assignment operator" << endl;
        if (this != &obj) {
            delete data;
            data = new int(*obj.data);
        }
        return *this;
    }

    // Move Constructor
    Test(Test&& obj) noexcept : data(nullptr) {
        cout << "move constructor" << endl;
        if (this != &obj) { // Self-move check (rare, but for completeness)
            data = obj.data;
            obj.data = nullptr;
        }
    }

    // Move Assignment Operator
    Test& operator=(Test&& obj) noexcept {
        cout << "move assignment operator" << endl;
        if (this != &obj) {
            delete data;
            data = obj.data;
            obj.data = nullptr;
        }
        // Self-move: data will be nullptr
        return *this;
    }

    // Destructor
    ~Test() {
        delete data;
        data = nullptr; // For clarity
    }
};
