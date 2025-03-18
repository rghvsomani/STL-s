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