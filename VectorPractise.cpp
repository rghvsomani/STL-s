#include <iostream>
using namespace std;
class Vector{
    private:
    int* arr;
    int size;
    int capacity;

    void resize()
    {
        capacity= capacity*2;
        int* temp=new int(capacity);
        for(int i=0;i<size;i++)
        {
            temp[i]=arr[i];
        }
        delete arr;
        arr=temp;
    }
    public:

     Vector(int initialCapacity=10): capacity(initialCapacity){
        arr=new int(capacity);
    }
    ~Vector()
    {
        delete[] arr;
        size=0;
        capacity=0;
    }
    Vector(const Vector &temp)
    {
        capacity= temp.capacity;
        arr= new int(capacity);
        size=temp.size;
        for(int i=0;i<size;i++)
        {
            arr[i]=temp.arr[i];
        }
    }
    Vector& operator=(const Vector &temp)
    {
        if(this==&temp) return *this;
        delete [] arr;
        capacity= temp.capacity;
        size=temp.size;
        arr=new int(capacity);
        for(int i=0;i<size;i++)
        {
            arr[i]=temp.arr[i];
        }
    }

    void push_back(const int& val)
    {
        if(size==capacity)
        {
            resize();
        }
        arr[size++]=val;
    }

    void pop_back()
    {
        if(size>0)
        {
            size--;
        }
    }
    int& operator[](const int index)
    {
        if(index<size)
        {
            return arr[index];
        }
    }

    int get_size() const{
        return size;
    }

    int get_capacity() const{
        return capacity;
    }
};

int main()
{
    Vector v;
    v.push_back(5);
    v.push_back(10);
    cout<<v.get_size()<<endl;

    v[0]=4;
    Vector v1=v;
    Vector v2;
    v2=v;



}