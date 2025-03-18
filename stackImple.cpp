#include <iostream>
using namespace std;


struct Node{
    int data;

    Node * next;
    Node(int value):data(value),next(nullptr)
    {
    }
};

class Stack{
    private:

    Node* start;
    int size=0;

    public:
    Stack():start(nullptr){}

    void push(int value)
    {
        Node * newNode=new Node(value);
        if(start==nullptr)
        {
            start=newNode;
            size++;
        }
        else{
        newNode->next=start;
        start=newNode;
        size++;
        }
    }

    void pop()
    {
        if(size>0)
        {
        Node * temp=start;
        start=start->next;
        size--;
        delete temp;
        }
    }

    int top()
    {
        if(size>0)
        {
            return start->data;
        }
        return -1;
    }

    bool isEmpty()
    {
        return start==nullptr;
    }

    void display()
    
    {
        if(isEmpty()==false)
        {
            Node * begin=start;
            while(begin!=nullptr)
            {
                cout<<begin->data<<endl;
                begin=begin->next;
            }
        }
    }

    int get_size()
    {
        return size;
    }

    ~Stack()
    {
        while(!isEmpty())
        {
            pop();
        }
        // Node * temp=start;
        // while(temp!=nullptr)
        // {
        //     start=start->next;
        //     delete temp;
        //     temp=start;
        // }
    }
};

int main()
{
    Stack st;
    st.push(1);
    st.push(344);
    st.push(13);
    st.display();
    st.pop();
    st.display();
    int top=st.top();
    cout<<top<<endl;
}