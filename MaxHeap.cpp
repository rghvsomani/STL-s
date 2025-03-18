#include <iostream>
#include  <vector>
#include <algorithm> 
using namespace std;
class MaxHeap{
    private:
    int size{};
    vector<int> vect={-1};

    int parent(int i){return i>>1;}
    int left(int i){ return i<<1;}
    int right(int i){return (i<<1)+1;}

    public:

    bool isEmpty() const{return size==0;}
    int getMax() const{return vect[1];}
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
        if(vect[i]>vect[parent(i)])
        {
            swap(vect[i],vect[parent(i)]);
            
        }
        shiftUP(parent(i));
    }

    void shiftDown(int i)
    {
        if(i>size) return;
        int minimumIndex=i;
        if(left(i)<=size&&vect[i]<vect[left(i)])
        {
            minimumIndex=left(i);
        }
        if(right(i)<=size&&vect[minimumIndex]<vect[right(i)])
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

    int extractMax()
    {
        int maxNum=vect[1];
        swap(vect[1],vect[size--]);
        shiftDown(1);
        return maxNum;
    }
};

int main()
{
    MaxHeap* PriorityQueue=new MaxHeap();
    PriorityQueue->insertItem(10);
    PriorityQueue->insertItem(113);
    PriorityQueue->insertItem(10);
    PriorityQueue->insertItem(424);
    PriorityQueue->insertItem(5);
    cout<<PriorityQueue->getMax()<<endl;
    PriorityQueue->extractMax();
    cout<<PriorityQueue->getMax()<<endl;
    return 0;
}