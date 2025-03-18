#include <iostream>
#include  <vector>
#include <algorithm> 
using namespace std;
class MinHeap{
    private:
    int size{};
    vector<int> vect={-1};

    int parent(int i){return i>>1;}
    int left(int i){ return i<<1;}
    int right(int i){return (i<<1)+1;}

    public:

    bool isEmpty() const{return size==0;}
    int getMin() const{return vect[1];}
    void insertItem(int val)
    {
        if(size+1>=vect.size())
        {
            vect.push_back(0);
        }
        vect[++size]=val;
        shiftUP(size);
        return;
    }

    void shiftUP(int i)
    {
        if(i>size) return;
        if(i==1) return;
        if(vect[i]<vect[parent(i)])
        {
            swap(vect[i],vect[parent(i)]);
            
        }
        shiftUP(parent(i));
    }

    void shiftDown(int i)
    {
        if(i>size) return;
        int minimumIndex=i;
        if(left(i)<=size&&vect[i]>vect[left(i)])
        {
            minimumIndex=left(i);
        }
        if(right(i)<=size&&vect[minimumIndex]>vect[right(i)])
        {
            minimumIndex=right(i);
        }
        if(minimumIndex!=i)
        {
            swap(vect[i],vect[minimumIndex]);
            shiftDown(minimumIndex);
        }
        return;
    }

    int extractMin()
    {
        int maxNum=vect[1];
        swap(vect[1],vect[size--]);
        shiftDown(1);
        return maxNum;
    }
};

int main()
{
    MinHeap* PriorityQueue=new MinHeap();
    PriorityQueue->insertItem(10);
    PriorityQueue->insertItem(113);
    PriorityQueue->insertItem(10);
    PriorityQueue->insertItem(424);
    PriorityQueue->insertItem(5);
    cout<<PriorityQueue->getMin()<<endl;
    PriorityQueue->extractMin();
    cout<<PriorityQueue->getMin()<<endl;
    return 0;
}