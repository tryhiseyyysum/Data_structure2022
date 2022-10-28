#pragma once
#include<iostream>
using namespace std;

template <class T>
class Queue
{
	int front, rear;
	T* queue;
	int Maxsize;
public:
	Queue(int Maxqueuesize = 7);
	bool isempty();
	bool isfull();
	void Add(const T& item);
	T* Delete(T& x);
	T& Front();
	int size();
	int QueueCount();
};
template <class T>
Queue<T>::Queue(int Maxqueuesize):Maxsize(Maxqueuesize)
{
	queue = new T[Maxqueuesize];
	front = rear = 0;
}
template <class T>
bool Queue<T>::isempty()
{
	return front == rear;
}
template <class T>
bool Queue<T>::isfull()
{
	return ((rear + 1) % Maxsize == front);
}
template <class T>
void Queue<T>::Add(const T& x)
{
	if (this->isfull())
	{
		cout << "队列已满" << endl;
	}
	else
	{
		rear = (rear + 1) % Maxsize;
		queue[rear] = x;
	}
}
template <class T>
T* Queue<T>::Delete(T& x)
{
	if (this->isempty())
	{
		cout << "队列为空"<<endl;
	}
	x = queue[++front %= Maxsize];
	return &x;
}
template <class T>
T& Queue<T>::Front()
{
	//if (this->isempty())
	return queue[front + 1];
}
template<class T>
int Queue<T>::size()
{
	if (this->isempty())
		return 0;
	else if (front < rear)
		return rear - front + 1;
	else
		return Maxsize - front + rear;
}

template<class T>
int Queue<T>::QueueCount()
{
	return size();
}