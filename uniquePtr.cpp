#include <iostream>
#include <memory>


using namespace std;

template<typename T>
class UniquePtr{
    private:
     T* ptr;
    
    public:

/*
    Constructor	What happens with foo(ptr)?	What happens with foo(5)?	Safe?
    explicit	Only works with explicit cast	Error (won’t compile)	YES
    non-explicit	Implicitly converts	Implicitly converts	NO
*/
    // Constructor
    explicit UniquePtr(T* p = nullptr) : ptr(p) {}
    {
        cout<<"Ctor called"<<endl;
    };

    UniquePtr (const UniquePtr<T>& obj) =delete;
    UniquePtr& operator=(const UniquePtr<T>& obj)=delete;
    UniquePtr (UniquePtr<T> && obj)
    {
        ptr= obj.ptr;
        obj.ptr=nullptr;
    }

    UniquePtr& operator=(UniquePtr<T>&& obj)
    {
        if(this!=&obj)
        {
            if(!ptr)
            {
                delete ptr;
            }
            ptr=obj.ptr;
            obj.ptr=nullptr;
        }

        return *this;
    }

    T* operator->()
    {
        return ptr;
    }

    T& operator*()
    {
        return *ptr;
    }

    T* get()
    {
        return ptr;
    }

    void reset(T *obj=nullptr)
    {
        if(ptr)
        {
            delete ptr;
        }
        ptr=obj;
    }

    ~UniquePtr()
    {
        if(ptr)
        {
            delete ptr;
            ptr=nullptr;
            cout<<"destructor called"<<endl;
        }
    }
    
        

};

int main()
{
    UniquePtr<int> ptr1(new int(10));
    //UniquePtr ptr2=ptr1;//Compilation error
    //UniquePtr ptr3(ptr1);
    UniquePtr<int> ptr4;
    ptr4 = std::move(ptr1);
    UniquePtr<int> ptr5(std::move(ptr4));
    cout<<"Value at ptr5: "<<*ptr5<<endl;
    ptr5.reset(new int(10));
    cout<<"Value at ptr5: "<<*ptr5<<endl;


}

*******************************************************************************************************************

template<typename T>
class UniquePtr {
    T* ptr;
public:
    // Constructor
    explicit UniquePtr(T* p = nullptr) : ptr(p) {}

    // Destructor
    ~UniquePtr() { delete ptr; }

    // Disable copy semantics
    UniquePtr(const UniquePtr&) = delete;
    UniquePtr& operator=(const UniquePtr&) = delete;

    // Move semantics
    UniquePtr(UniquePtr&& other) : ptr(other.ptr) {
        other.ptr = nullptr;
    }
    UniquePtr& operator=(UniquePtr&& other) {
        if (this != &other) {
            delete ptr;
            ptr = other.ptr;
            other.ptr = nullptr;
        }
        return *this;
    }

    // Access
    T& operator*() const { return *ptr; }
    T* operator->() const { return ptr; }
    T* get() const { return ptr; }
    void reset(T* p = nullptr) {
        delete ptr;
        ptr = p;
    }
    T* release() {
        T* old = ptr;
        ptr = nullptr;
        return old;
    }
};
