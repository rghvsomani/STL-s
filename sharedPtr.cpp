#include <iostream>
#include <memory>
using namespace std;

template <typename T>
class SharedPtr{
    private:
        T* res;
        int* counter;

        void incrementCounter()
        {
            if(counter)
            {
                (*counter)++;
            }
        }

        void decrementCounter()
        {
            if(counter)
            {
                (*counter)--;
                if(*counter==0)
                {
                    if(res){
                    delete res;
                    delete counter;
                    res=nullptr;
                    counter=nullptr;
                    }
                }
            }
        }




    public:
    SharedPtr(T* ptr=nullptr): res(ptr),counter(new int(1))
    {
        cout<<"ctor called"<<endl;
    }
    SharedPtr(const SharedPtr<T>& ptr)
    {
            res=ptr.res;
            counter=ptr.counter;
            incrementCounter();
            cout<<"copy constructor called"<<endl;
    }

    SharedPtr& operator=(const SharedPtr<T>& ptr)
    {
        if(this!=&ptr)
        {
        decrementCounter();
        res=ptr.res;
        counter=ptr.counter;
        incrementCounter();
        }
        return *this;
    }

    SharedPtr(SharedPtr<T>&& ptr)
    {
        if(this!=&ptr)
        {
            res=ptr.res;
            counter=ptr.counter;
            ptr.res=nullptr;
            ptr.counter=nullptr;
            cout<<"move ctor called"<<endl;
        }
    }

    SharedPtr& operator=(SharedPtr<T>&& ptr)
    {
        if(this!=&ptr)
        {
        decrementCounter();
        res=ptr.res;
        count=ptr.counter;
        ptr.res=nullptr;
        ptr.counter=nullptr;
        }

        return *this;
    }

    int getCount()
    {   if(counter)
        {
        return (*counter);
        }
        return -1;
    }

    T& operator*()
    {
        return *res;
    }

    void reset(T* obj=nullptr)
    {
        decrementCounter();
        res=obj;
        counter=new int(1);
    }

    ~SharedPtr()
    {
        if(res)
        {
            decrementCounter();
        }
    }

    
};

int main()
{
    SharedPtr<int> ptr1(new int(10));
    SharedPtr<int> ptr2=ptr1;
    SharedPtr<int> ptr3;
    ptr3 = ptr2;

    SharedPtr<int> ptr4=std::move(ptr1);

    cout<<"current count of share pointer resource: "<<ptr4.getCount()<<endl;
    cout<<"Value of pointer: "<<*ptr2<<endl;

}

***************************************************************************************************

#include <cstddef> // for std::size_t

template<typename T>
class SharedPtr {
    T* ptr;
    std::size_t* ref_count;
public:
    // Constructor
    explicit SharedPtr(T* p = nullptr) : ptr(p), ref_count(new std::size_t(1)) {}

    // Copy constructor
    SharedPtr(const SharedPtr& other) : ptr(other.ptr), ref_count(other.ref_count) {
        ++(*ref_count);
    }

    // Copy assignment
    SharedPtr& operator=(const SharedPtr& other) {
        if (this != &other) {
            release();
            ptr = other.ptr;
            ref_count = other.ref_count;
            ++(*ref_count);
        }
        return *this;
    }

    // Destructor
    ~SharedPtr() {
        release();
    }

    void release() {
        if (ref_count && --(*ref_count) == 0) {
            delete ptr;
            delete ref_count;
        }
    }

    // Move constructor
    SharedPtr(SharedPtr&& other) : ptr(other.ptr), ref_count(other.ref_count) {
        other.ptr = nullptr;
        other.ref_count = nullptr;
    }

    // Move assignment
    SharedPtr& operator=(SharedPtr&& other) {
        if (this != &other) {
            release();
            ptr = other.ptr;
            ref_count = other.ref_count;
            other.ptr = nullptr;
            other.ref_count = nullptr;
        }
        return *this;
    }

    // Access
    T& operator*() const { return *ptr; }
    T* operator->() const { return ptr; }
    T* get() const { return ptr; }
    std::size_t use_count() const { return ref_count ? *ref_count : 0; }
};
