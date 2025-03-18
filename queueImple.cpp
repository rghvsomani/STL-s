#include <iostream>
using namespace std;

struct Node{
    int data;
    Node* next;
    Node(int value):data(value),next(nullptr){}
};

class Queue{
    private:
    Node *start,*end;
    int size=0;

    public:
        Queue():start(nullptr),end(nullptr)
        {
        }

        void push(int value)
        {
            Node* newNode=new Node(value);
            if(end==nullptr)
            {
                
                start=end=newNode;
            }
            end->next=newNode;
            end=newNode;
            size++;
        }

        void pop()
        {
            Node* temp=start;
            if(start!=nullptr)
            {
                start=start->next;
            }
            size--;
            delete temp;
        }

        int getfirst()
        {
            if(start!=nullptr)
            {
                return start->data;
            }
        }

        int getLast()
        {
            if(end!=nullptr)
            {
                return end->data;
            }
        }

        void Print()
        {
            Node * temp= start;
            while(temp!=nullptr)
            {
                cout<<temp->data<<endl;
                temp=temp->next;
            }
        }

        ~Queue()
        {
            while(start!=nullptr)
            {
                Node * temp=start->next;
                delete start;
                start=temp;
            }
            end=nullptr;
        }
};