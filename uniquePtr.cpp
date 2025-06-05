#include <iostream>
#include <memory>


using namespace std;

template<typename T>
class UniquePtr{
    private:
     T* ptr;
    
    public:

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
