#include<iostream>
using namespace std;

//A mazing problem
template<class T>
class Stack
{
    public:
    Stack(int stackCapacity=10);    //构造函数
    bool IsEmpty() const;           //判断栈是否为空
    T& Top() const;                 //返回栈顶元素
    void Push(const T& item);       //将元素插入栈顶
    void Pop();                     //删除栈顶元素
    friend ostream &operator<<(ostream &os, const Stack<T> &s);

    private:
    T*stack;
    int top;
    int capacity;
};

template<class T>
Stack<T>::Stack(int stackCapacity):capacity(stackCapacity)
{
    if(capacity<1) throw "Stack capacity must be >0";
    stack=new T[capacity];
    top=-1;
}

template<class T>
inline bool Stack<T>::IsEmpty() const
{
    return top==-1;
}

template<class T>
inline T& Stack<T>::Top() const
{
    if(IsEmpty()) throw "Stack is empty. No top element.";
    return stack[top];
}

template<class T>
void Stack<T>::Push(const T& x)
{
    if(top==capacity-1)     //栈满
    {
        T*newStack=new T[2*capacity];   //扩容
        copy(stack,stack+capacity,newStack); //复制到新数组
        capacity*=2;
        delete []stack;
        stack=newStack;
    }
    stack[++top]=x;
}

template<class T>
void Stack<T>::Pop()
{
    if(IsEmpty()) throw "Stack is empty. Cannot delete.";
    stack[top--].~T();  //析构
}

template<class T>
ostream &operator<<(ostream &os, const Stack<T> &s)
    {
        for(int i=0; i<s.top; i++)
            os << s.stack[i] << " ";
        return os;
    }

struct offsets
{
    int a,b;
    offsets(int a,int b):a(a),b(b){}
};
enum directions {N,NE,E,SE,S,SW,W,NW};
//offsets move[8];    //移动方向

class Items
{
    public:
    int x,y;
    int dir;
    Items(int x,int y,int dir);
};

Items::Items(int x,int y,int dir):x(x),y(y),dir(dir){}

class Maze
{
    public:
    Maze();
    //void PrintMaze();
    void InitMaze();

    void MazePath1(const int m,const int p,int d);
    void Path(const int m,const int p);
    int maze[10][10];   //迷宫
    int mark[10][10];   //标记数组
    offsets move[8]={offsets(-1,0),offsets(-1,1),offsets(0,1),offsets(1,1),offsets(1,0),offsets(1,-1),offsets(0,-1),offsets(-1,-1)};
    int x,y;    //起点坐标
    int x1,y1;  //终点坐标
};




Maze::Maze()
{
    // {1,1,1,1,1,1,1,1,1,1,
    // 1,0,0,1,0,0,0,1,0,1,
    // 1,0,0,1,0,0,0,1,0,1,
    // 1,0,0,0,0,1,1,0,0,1,
    // 1,0,1,1,1,0,0,0,0,1,
    // 1,0,0,0,1,0,0,0,0,1,
    
}



//初始化迷宫
void Maze::InitMaze()
{
    x1=8,y1=8;  //终点坐标
    move[N].a=-1;move[N].b=0;
    move[NE].a=-1;move[NE].b=1;
    move[E].a=0;move[E].b=1;
    move[SE].a=1;move[SE].b=1;
    move[S].a=1;move[S].b=0;
    move[SW].a=1;move[SW].b=-1;
    move[W].a=0;move[W].b=-1;
    move[NW].a=-1;move[NW].b=-1;
    
    int t[10][10]=
    {1,1,1,1,1,1,1,1,1,1,
    1,0,0,1,0,0,0,1,0,1,
    1,0,0,1,0,0,0,1,0,1,
    1,0,0,0,0,1,1,0,0,1,
    1,0,1,1,1,0,0,0,0,1,
    1,0,0,0,1,0,0,0,0,1,
    1,0,1,0,0,0,1,0,0,1,
    1,0,1,1,1,0,1,1,0,1,
    1,1,0,0,0,0,0,0,0,1,
    1,1,1,1,1,1,1,1,1,1};

    for(int i=0;i<10;i++)
        for(int j=0;j<10;j++)
            maze[i][j]=t[i][j];

}

//递归实现迷宫寻路，输出所有路径坐标
void Maze::MazePath1(const int m,const int p,int d)
{
    if(m==x1&&p==y1)
    {
        cout<<"("<<m<<","<<p<<")"<<endl;
        return;
    }
    for(int i=0;i<8;i++)
    {
        int m1=m+move[i].a;
        int p1=p+move[i].b;
        if(maze[m1][p1]==0&&mark[m1][p1]==0)
        {
            mark[m1][p1]=1;
            cout<<"("<<m1<<","<<p1<<")"<<endl;
            MazePath1(m1,p1,i);
            mark[m1][p1]=0;
        }
    }
}


//迭代实现
// void Maze::Path(const int m,const int p)
// {
//     mark[1][1]=1;
//     Stack<Items> stack(m*p);
//     Items temp(1,1,E);
//     stack.Push(temp);
    
//     while(!stack.IsEmpty())
//     {
//         Items temp=stack.Top();
//         stack.Pop();
//         int i=temp.x;
//         int j=temp.y;
//         int d=temp.dir;
//         while(d<8)
//         {
//             int g=i+move[d].a;
//             int h=j+move[d].b;
//             if(g==m&&h==p)
//             {
//                 cout<<stack;
//                 cout<<"("<<i<<","<<j<<")"<<"->"<<"("<<g<<","<<h<<")"<<endl;
//                 cout<<m<<","<<p<<endl;
//                 return;
//             }
//             if(!maze[g][h]&&!mark[g][h])
//             {
//                 mark[g][h]=1;
//                 temp.x=i;
//                 temp.y=j;
//                 temp.dir=d+1;
//                 stack.Push(temp);
//                 i=g;
//                 j=h;
//                 d=N;
//             }
//             else
//                 d++;
//         }
//         cout<<"No path!"<<endl;

//      }
// }


int main()
{
    Maze maze;
    maze.MazePath1(5,5,1);
    //maze.PrintPath();
    //maze.Path(6,4);
    return 0;
    
}