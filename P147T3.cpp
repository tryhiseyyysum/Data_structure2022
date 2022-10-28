#include<iostream>
using namespace std;
template<class T>
class Queue
{
    public:
    Queue(int queueCapacity=10);    //构造函数
    bool IsEmpty() const;           //判断队列是否为空
    T& Front() const;               //返回队首元素
    T& Rear() const;                //返回队尾元素
    void Push(const T& item);       //将元素插入队尾
    void Pop();                     //删除队首元素
    void split(Queue<T>& q1,Queue<T>& q2);    //将队列分成两个队列

    private:
    T*queue;
    int front,rear,capacity;

};

template<class T>
Queue<T>::Queue(int queueCapacity):capacity(queueCapacity)
{
    if(capacity<1) throw "Queue capacity must be >0";
    queue=new T[capacity];
    front=rear=0;
}

template<class T>
inline bool Queue<T>::IsEmpty() const
{
    return front==rear;
}

template<class T>
inline T& Queue<T>::Front() const
{
    if(IsEmpty()) throw "Queue is empty. No front element.";
    return queue[(front+1)%capacity];
}

template<class T>
inline T& Queue<T>::Rear() const
{
    if(IsEmpty()) throw "Queue is empty. No rear element.";
    return queue[rear];
}

template<class T>
void Queue<T>::Push(const T& x)
{
    if((rear+1)%capacity==front)    //队列满
    {
        T*newQueue=new T[2*capacity];   //扩容
        int start=(front+1)%capacity;   //从队首开始复制
        if(start<2)         //若队首在数组前半段
            copy(queue+start,queue+start+capacity-1,newQueue);  //复制到新数组
        else        //若队首在数组后半段
        {
            copy(queue+start,queue+capacity,newQueue);   //复制到新数组
            copy(queue,queue+rear+1,newQueue+capacity-start);  //复制到新数组
        }
        front=2*capacity-1;     //更新队首
        rear=capacity-2;        //更新队尾
        capacity*=2;            //更新容量
        delete []queue;
        queue=newQueue;
    }
    rear=(rear+1)%capacity;
    queue[rear]=x;
}

template<class T>
void Queue<T>::Pop()
{
    if(IsEmpty()) throw "Queue is empty. Cannot delete.";
    front=(front+1)%capacity;
    queue[front].~T();  //析构函数
}

template<class T>
void Queue<T>::split(Queue<T>& q1,Queue<T>& q2) //将队列分成两个队列
{
    int i=0;
    while(!IsEmpty())
    {
        if(i%2==0)  //偶数放入q1
            q1.Push(Front());
        else        //奇数放入q2
            q2.Push(Front());
        Pop();
        i++;
    }
}

int main()
{
    Queue<int>q;
    for(int i=0;i<10;i++)
        q.Push(i);
    for(int i=0;i<10;i++)
    {
        cout<<q.Front()<<endl;
        q.Pop();
    }

//测试split函数
    cout<<"------------------------"<<endl;
    Queue<int>q1,q2;
    for(int i=0;i<10;i++)
        q.Push(i);
    q.split(q1,q2);
    cout<<"q1:"<<endl;
    for(int i=0;i<5;i++)
    {
        
        cout<<q1.Front()<<endl;
        q1.Pop();
    }
     cout<<"q2:"<<endl;
    for(int i=0;i<5;i++)
    {
       
        cout<<q2.Front()<<endl;
        q2.Pop();
    }

    return 0;
}