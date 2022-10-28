#include<iostream>
using namespace std;

template<class T>
class LinkedQueue;

template<class T>
class ChainNode
{
    friend class LinkedQueue<T>;
    private:
    T data;
    ChainNode<T> *link;
    public:
    ChainNode(T element=0,ChainNode *next=0):data(element),link(next){}
};


template<class T>
class LinkedQueue
{
    ChainNode<T> *front,*rear;

    public:
    LinkedQueue():front(0),rear(0){}
    void Push(const T &e);
    void Pop();
    bool IsEmpty();
    T Front();
    T Back();
    void Print();
    void Clear();    //清空队列
    ~LinkedQueue(); 
    void Reverse();
    void Insert(int n,const T &e);    //在第n个元素后插入元素e
    void Delete1(int n);         //删除第n个元素
    void Delete2(const T &e);    //删除所有值为e的元素
};



template<class T>
bool LinkedQueue<T>::IsEmpty()
{
    return front==0;
}

template<class T>
void LinkedQueue<T>::Push(const T &e)
{
    if(IsEmpty())
    {
        front=rear=new ChainNode<T>(e);
    }
    else
    {
        rear->link=new ChainNode<T>(e);
        rear=rear->link;
    }

}

template<class T>
void LinkedQueue<T>::Pop()
{
    if(IsEmpty())   throw "Queue is empty.Cannot delete.";
    ChainNode<T> *delNode=front;
    front=front->link;
    delete delNode;
}

template<class T>
T LinkedQueue<T>::Front()
{
    if(IsEmpty())   throw "Queue is empty.Cannot get front.";
    return front->data;
}

template<class T>
T LinkedQueue<T>::Back()
{
    if(IsEmpty())   throw "Queue is empty.Cannot get back.";
    return rear->data;
}

template<class T>
void LinkedQueue<T>::Print()
{
    ChainNode<T> *current=front;
    while(current!=0)
    {
        cout<<current->data<<" ";
        current=current->link;
    }
    cout<<endl;
}

template<class T>
void LinkedQueue<T>::Clear()
{
    while(!IsEmpty())   Pop();
}

template<class T>
LinkedQueue<T>::~LinkedQueue()
{
    Clear();
}

template<class T>
void LinkedQueue<T>::Reverse()
{
    ChainNode<T> *p=front,*pp=0;
    while(p)
    {
        ChainNode<T> *ppp=pp;
        pp=p;
        p=p->link;
        pp->link=ppp;
    }
    front=pp;
}

template<class T>
void LinkedQueue<T>::Insert(int n,const T &e)
{
    ChainNode<T> *current=front;
    for(int i=1;i<n;i++)
    {
        current=current->link;
    }
    ChainNode<T> *newNode=new ChainNode<T>(e,current->link);
    current->link=newNode;
}

template<class T>
void LinkedQueue<T>::Delete1(int n)
{
    ChainNode<T> *current=front;
    for(int i=0;i<n-1;i++)
    {
        current=current->link;
    }
    //退出循环后，current指向第n-1个元素
    ChainNode<T> *delNode=current->link;    //要删除的元素,第n个元素
    current->link=delNode->link;
    delete delNode;
}

template<class T>
void LinkedQueue<T>::Delete2(const T &e)
{
    ChainNode<T> *current=front,*pp=0;
    while(current)
    {
        if(current->data==e)
        {
            if(current==front)
            {
                front=front->link;
                delete current;
                current=front;
            }
            else
            {
                pp->link=current->link;
                delete current;
                current=pp->link;
            }
        }
        else
        {
            pp=current;
            current=current->link;
        }
    }
}

int main()
{
    LinkedQueue<int> L;
    for(int i=1;i<11;i++)
    {
        L.Push(i);
    }
    L.Print();
    L.Reverse();
    L.Print();
    L.Insert(5,100);
    L.Print();
    L.Delete1(4);       //删除4号下标的元素
    L.Print();
    L.Delete2(100);     //删除所有值为100的元素
    L.Print();
    return 0;
}
