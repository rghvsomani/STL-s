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
    /*
    * Move semantics :- 
    * Standard containers (like std::vector) rely on move operations being noexcept for optimal performance and exception safety.
    * If move operations can throw, containers may fall back to copy operations, which are slower.
    */
    // Move Constructor --> steel the data not copy the data
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

int main(){
    //This will give error
    // Test obj;
    
    //Para Constructore 
    Test obj(10);
    
    //All form of copy constructor
    Test obj2 = obj;
    Test obj3(obj);
    Test obj4 = Test(obj);
    
    //All form of Move constructor
    Test move1 = std::move(obj);
    Test move2(std::move(obj));
    Test move3 = Test(10);  // para constructor //However, in some cases, compilers may use move constructor for 
                            // optimization (copy elision or return value optimization), but strictly speaking, 
                            // this line only calls the constructor with int parameter.
                            
    //Move operator
    obj = std::move(obj2);      // Self-move assignment
    obj2 = std::move(obj2);      // Invokes: operator=(Test&& obj)
    
}
