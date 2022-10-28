/*模拟飞机场的着陆和起飞管理模式。设飞机场有3条跑道，有4
种着陆等待模式。前两条跑道分别具有两种着陆等待模式，第3条跑道不用作正常着陆。
到达的飞机进入某个等待模式队列，并分配给该飞机一个整数id（身份号）和另一个整数t,t
是飞机必须降落前（出于油批的原因）在队列中允许停留的时间单位数，称为剩余时间。3
个跑逍中的每一个均有一个起飞队列。在起飞队列中的飞机也分配有一个id值。各起飞
队列的长度应大致相同。
在每个时间单位中，可允许最多有3架飞机进入着陆队列以及最多3架飞机进入起飞
队列。每条跑道在一个时间单位中，允许一次起飞或降落。第3条跑道仅用作起飞（除非飞
机须紧急降落）。在每个时间单位中，任何一个着陆队列里剩余时间接近千0的飞机必须给
予高于其他飞机（不论是着陆还是起飞）的优先级。如果仅有一架飞机出现这种情况，则使
用第3条跑道。如果多于一架飞机（最多3架）发生此情况，则其他跑道也被使用。
用连续偶数（奇数）表示飞机在起飞（着陆）队列中的id值。在每个单位时间中，假设进
人队列的操作先于起飞或降落的操作。设计一个算法用千模拟上述管理模式。要求队列不
会过于增大，而到来的飞机又必须放到适当队列的尾部。队列不允许重新安排。
算法的输出应该清楚地显示出每个时间单位中所发生的事情。每次输出应包括： （a)
每个队列的内容；（b）起飞的平均等待时间；（c）着陆的平均等待时间；（d）着陆的平均剩余时
间；（e）紧急降落（无油料）的飞机数。(b)和(c)分别对应于已经起飞或降落的飞机。输出应
该是自说明的并易千理解（并且不混乱）。
算法的输入可以来自键盘、文件或随机数产生器。在每个时间单位中，输入包括： 到达
起飞队列的飞机数、到达着陆队列的飞机数，以及到达着陆队列的飞机所具有的剩余时间。*/


#include <iostream>
#include<ctime>
#include<cstdlib>
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
    bool IsFull() const;            //判断队列是否已满
    int Size() const;               //返回队列中元素的个数
    int QueueCount() const;        //返回队列中元素的个数

    private:
    T*queue;
    int front;
    int rear;
    int capacity;
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
    if((rear+1)%capacity==front)     //队满
    {
        T*newQueue=new T[2*capacity];   //扩容
        int start=(front+1)%capacity;
        if(start<2)     //不需要拷贝
            copy(queue+start,queue+start+capacity-1,newQueue);
        else    //需要拷贝两段
        {
            copy(queue+start,queue+capacity,newQueue);
            copy(queue,queue+rear+1,newQueue+capacity-start);
        }
        front=2*capacity-1;
        rear=capacity-2;
        capacity*=2;
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
    queue[front].~T();  //析构
}

template<class T>
inline bool Queue<T>::IsFull() const
{
    return (rear+2)%capacity==front;
}

template<class T>
inline int Queue<T>::Size() const
{
    return ((rear-front+capacity)%capacity);
}

// struct plane
// {
//     int id;     //飞机编号
//     int t;      //飞机剩余时间
// };

class plane
{
    public:
    plane(int id=0,int t=0):id(id),t(t){}
    void Fly(int time);     //飞行




    int id;     //飞机编号
    int t;      //飞机剩余时间
    bool emergency;     //是否为紧急降落
    int wait;           //等待时间
    int land;           //降落时间
    int takeoff;        //起飞时间
    int landwait;       //降落等待时间
    int takeoffwait;    //起飞等待时间
    int fuel;           //油量
    int runway;        //跑道
    int clock;          //时间
    int wait_time;       //等待时间
    int start;          //开始时间
    int arrive;         //到达时间


};

void plane::Fly(int time)
{
    t-=time;
}

enum action{ARRIVE,DEPART};     //飞机动作
//3个跑道，每个跑道有一个起飞队列，在起飞队列中的飞机也分配有一个id值；前两条跑道可以起飞和降落，第三个跑道只能起飞或紧急降落
class Runway
{
    public:
    Runway(int limit);
    bool CanLand(const plane& current) const;     //判断是否可以降落
    bool CanDepart(const plane& current) const;   //判断是否可以起飞
    void Land(plane& current);      //降落
    void Takeoff(plane& current);    //起飞
    void Refuse(plane& current) const;  //拒绝
    void Idle() const;      //空闲
    // int RunwayCount() const;    //返回跑道中飞机的个数
    // int RunwayCount(int i) const;    //返回跑道中飞机的个数
    int LandCount() const;      //返回降落的飞机个数
    int DepartCount() const;    //返回起飞的飞机个数
    int LandWait() const;       //返回降落的飞机的等待时间
    int DepartWait() const;     //返回起飞的飞机的等待时间
    int LandLeft() const;       //返回降落的飞机的剩余时间
    int EmergencyCount() const;     //返回紧急降落的飞机个数
    void Run();     //运行
    void RunIdle(int time);    //空闲运行
    void Refuse(const plane& current) const;      //拒绝
    void ShutDown(int time) const;      //关闭
    int RunwayCount(int i) const;      //返回跑道中飞机的个数
    void ServiceRunway(int i);      //服务跑道
    void ServiceEmergency(int time);        //服务紧急降落


    private:
    Queue<plane> landing;       //降落队列
    Queue<plane> takeoff;       //起飞队列
    int queue_limit;        //队列的最大长度
    int num_land_requests;      //降落请求的个数
    int num_takeoff_requests;   //起飞请求的个数
    int num_land;       //降落的飞机个数
    int num_takeoff;        //起飞的飞机个数
    int num_land_accepted;      //降落的飞机个数
    int num_takeoff_accepted;   //起飞的飞机个数
    int num_land_refused;       //拒绝降落的飞机个数
    int num_takeoff_refused;    //拒绝起飞的飞机个数
    int num_emergency;      //紧急降落的飞机个数
    int land_wait;      //降落的飞机的等待时间
    int takeoff_wait;       //起飞的飞机的等待时间
    int idle_time;      //空闲时间
    int emergency_time;     //紧急降落的飞机的等待时间
    int emergency_wait;     //紧急降落的飞机的等待时间
    int emergency_left;     //紧急降落的飞机的剩余时间
    int emergency_count;    //紧急降落的飞机个数
    int emergency_id;       //紧急降落的飞机编号
    int emergency_t;        //紧急降落的飞机剩余时间
    int emergency_runway;       //紧急降落的飞机所在的跑道
    int emergency_runway_count;     //紧急降落的飞机所在的跑道中的飞机个数

    
};

Runway::Runway(int limit):queue_limit(limit),num_land_requests(0),num_takeoff_requests(0),num_land(0),num_takeoff(0),num_land_accepted(0),num_takeoff_accepted(0),num_land_refused(0),num_takeoff_refused(0),num_emergency(0),land_wait(0),takeoff_wait(0),idle_time(0),emergency_time(0),emergency_wait(0),emergency_left(0),emergency_count(0),emergency_id(0),emergency_t(0),emergency_runway(0),emergency_runway_count(0)
{
}

bool Runway::CanLand(const plane& current) const
{
    if(landing.Size()<queue_limit)
        return true;
    else
        return false;
}

bool Runway::CanDepart(const plane& current) const
{
    if(takeoff.Size()<queue_limit)
        return true;
    else
        return false;
}

int Runway::RunwayCount(int i) const
{
    if(i==1)
        return landing.Size();
    else if(i==2)
        return takeoff.Size();
    else
        return 0;
}

void Runway::Land(plane& current)
{
    if(current.emergency==true)
    {
        emergency_count++;
        emergency_id=current.id;
        emergency_t=current.fuel;
        emergency_runway=current.runway;
        emergency_runway_count=RunwayCount(emergency_runway);
        emergency_time=current.clock;
        emergency_wait=emergency_time-emergency_t;
        emergency_left=emergency_t-emergency_wait;
        cout<<"紧急降落的飞机编号为："<<emergency_id<<endl;
        cout<<"紧急降落的飞机所在的跑道为："<<emergency_runway<<endl;
        cout<<"紧急降落的飞机所在的跑道中的飞机个数为："<<emergency_runway_count<<endl;
        cout<<"紧急降落的飞机的等待时间为："<<emergency_wait<<endl;
        cout<<"紧急降落的飞机的剩余时间为："<<emergency_left<<endl;
        cout<<"紧急降落的飞机的总时间为："<<emergency_time<<endl;
        cout<<"紧急降落的飞机个数为："<<emergency_count<<endl;
    }
    else
    {
        num_land_requests++;
        if(CanLand(current))
        {
            landing.Push(current);
            num_land++;
            land_wait+=current.wait_time;
        }
        else
        {
            num_land_refused++;
            Refuse(current);
        }
    }
}

void Runway::Takeoff(plane& current)
{
    num_takeoff_requests++;
    if(CanDepart(current))
    {
        takeoff.Push(current);
        num_takeoff++;
        takeoff_wait+=current.wait_time;
    }
    else
    {
        num_takeoff_refused++;
        Refuse(current);
    }
}

void Runway::RunIdle(int time)
{
    idle_time+=time;
}

void Runway::Refuse(const plane& current) const
{
    cout<<"飞机"<<current.id<<"被拒绝"<<endl;
}

void Runway::ShutDown(int time) const
{
    cout<<"模拟结束"<<endl;
    cout<<"模拟时间为："<<time<<"分钟"<<endl;
    cout<<"降落的飞机个数为："<<num_land<<endl;
    cout<<"起飞的飞机个数为："<<num_takeoff<<endl;
    cout<<"降落的飞机个数为："<<num_land_accepted<<endl;
    cout<<"起飞的飞机个数为："<<num_takeoff_accepted<<endl;
    cout<<"拒绝降落的飞机个数为："<<num_land_refused<<endl;
    cout<<"拒绝起飞的飞机个数为："<<num_takeoff_refused<<endl;
    cout<<"紧急降落的飞机个数为："<<num_emergency<<endl;
    cout<<"降落的飞机的等待时间为："<<land_wait<<endl;
    cout<<"起飞的飞机的等待时间为："<<takeoff_wait<<endl;
    cout<<"空闲时间为："<<idle_time<<endl;
    cout<<"紧急降落的飞机的等待时间为："<<emergency_wait<<endl;
    cout<<"紧急降落的飞机的剩余时间为："<<emergency_left<<endl;
    cout<<"紧急降落的飞机的总时间为："<<emergency_time<<endl;
    cout<<"紧急降落的飞机个数为："<<emergency_count<<endl;
    cout<<"紧急降落的飞机编号为："<<emergency_id<<endl;
    cout<<"紧急降落的飞机所在的跑道为："<<emergency_runway<<endl;
    cout<<"紧急降落的飞机所在的跑道中的飞机个数为："<<emergency_runway_count<<endl;
}

void Runway::ServiceRunway(int time)        
{
    if(!landing.IsEmpty())
    {
        plane current=landing.Front();
        landing.Pop();
        current.wait_time=time-current.arrive;
        land_wait+=current.wait_time;
        num_land_accepted++;
        RunIdle(time-current.start);
        current.Fly(time);
    }
    else if(!takeoff.IsEmpty())
    {
        plane current=takeoff.Front();
        takeoff.Pop();
        current.wait_time=time-current.arrive;
        takeoff_wait+=current.wait_time;
        num_takeoff_accepted++;
        RunIdle(time-current.start);
        current.Fly(time);
    }
    else
        RunIdle(time);
}

//每条跑道在一个时间单位内只能有一个飞机起飞或降落

//用连续偶数编号表示起飞飞机，奇数编号表示降落飞机





   





// Queue<plane> runway1,runway2,runway3;

// //每条跑道在一个时间单位内只能有一个飞机起飞或降落
// bool runway1_busy=false,runway2_busy=false,runway3_busy=false;

// int id=0;

// //统计
// int takeoff=0,landing=0,emergency=0;     //起飞、降落、紧急降落的飞机数
// int takeoff_wait=0,landing_wait=0;       //起飞、降落等待的时间
// int takeoff_emergency=0,landing_emergency=0;     //紧急起飞、紧急降落的飞机数

// //飞机到达
// void arrive(int time)
// {
//     plane p;
//     p.id=++id;
//     p.t=rand()%20+1;    //随机生成剩余时间
//     if(p.id%2==0)   //起飞飞机
//     {
//         if(runway1_busy==false)     //跑道1空闲
//         {
//             runway1.Push(p);
//             runway1_busy=true;
//         }
//         else if(runway2_busy==false)    //跑道2空闲
//         {
//             runway2.Push(p);
//             runway2_busy=true;
//         }
//         else if(runway3_busy==false)    //跑道3空闲
//         {
//             runway3.Push(p);
//             runway3_busy=true;
//         }
//         else    //所有跑道都忙
//         {
//             takeoff_wait+=time;
//             landing_wait+=time;
//             takeoff_emergency++;
//             landing_emergency++;
//             cout<<"Time "<<time<<": Plane "<<p.id<<" emergency takeoff."<<endl;
//         }
//     }
//     else    //降落飞机
//     {
//         if(runway1_busy==false)     //跑道1空闲
//         {
//             runway1.Push(p);
//             runway1_busy=true;
//         }
//         else if(runway2_busy==false)    //跑道2空闲
//         {
//             runway2.Push(p);
//             runway2_busy=true;
//         }
//         else if(runway3_busy==false)    //跑道3空闲
//         {
//             runway3.Push(p);
//             runway3_busy=true;
//         }
//         else    //所有跑道都忙
//         {
//             takeoff_wait+=time;
//             landing_wait+=time;
//             takeoff_emergency++;
//             landing_emergency++;
//             cout<<"Time "<<time<<": Plane "<<p.id<<" emergency landing."<<endl;
//         }
//     }
// }

// //飞机起飞或降落
// void depart(int time)
// {
//     if(runway1_busy==true)  //跑道1忙
//     {
//         plane p=runway1.Front();
//         runway1.Pop();
//         if(p.id%2==0)   //起飞飞机
//         {
//             takeoff++;
//             cout<<"Time "<<time<<": Plane "<<p.id<<" takeoff."<<endl;
//         }
//         else    //降落飞机
//         {
//             landing++;
//             cout<<"Time "<<time<<": Plane "<<p.id<<" landing."<<endl;
//         }
//         if(runway1.IsEmpty())   //跑道1空闲
//             runway1_busy=false;
//     }
//     else if(runway2_busy==true) //跑道2忙
//     {
//         plane p=runway2.Front();
//         runway2.Pop();
//         if(p.id%2==0)   //起飞飞机
//         {
//             takeoff++;
//             cout<<"Time "<<time<<": Plane "<<p.id<<" takeoff."<<endl;
//         }
//         else    //降落飞机
//         {
//             landing++;
//             cout<<"Time "<<time<<": Plane "<<p.id<<" landing."<<endl;
//         }
//         if(runway2.IsEmpty())   //跑道2空闲
//             runway2_busy=false;
//     }
//     else if(runway3_busy==true) //跑道3忙
//     {
//         plane p=runway3.Front();
//         runway3.Pop();
//         if(p.id%2==0)   //起飞飞机
//         {
//             takeoff++;
//             cout<<"Time "<<time<<": Plane "<<p.id<<" takeoff."<<endl;
//         }
//         else    //降落飞机
//         {
//             landing++;
//             cout<<"Time "<<time<<": Plane "<<p.id<<" landing."<<endl;
//         }
//         if(runway3.IsEmpty())   //跑道3空闲
//             runway3_busy=false;
//     }
// }

// //飞机离开
// void leave(int time)
// {
//     if(runway1_busy==true)  //跑道1忙
//     {
//         plane p=runway1.Front();
//         runway1.Pop();
//         p.t--;
//         if(p.t==0)  //飞机离开
//         {
//             if(p.id%2==0)   //起飞飞机
//             {
//                 takeoff++;
//                 cout<<"Time "<<time<<": Plane "<<p.id<<" takeoff."<<endl;
//             }
//             else    //降落飞机
//             {
//                 landing++;
//                 cout<<"Time "<<time<<": Plane "<<p.id<<" landing."<<endl;
//             }
//             if(runway1.IsEmpty())   //跑道1空闲
//                 runway1_busy=false;
//         }
//         else    //飞机未离开
//         {
//             runway1.Push(p);
//         }
//     }
//     if(runway2_busy==true)  //跑道2忙
//     {
//         plane p=runway2.Front();
//         runway2.Pop();
//         p.t--;
//         if(p.t==0)  //飞机离开
//         {
//             if(p.id%2==0)   //起飞飞机
//             {
//                 takeoff++;
//                 cout<<"Time "<<time<<": Plane "<<p.id<<" takeoff."<<endl;
//             }
//             else    //降落飞机
//             {
//                 landing++;
//                 cout<<"Time "<<time<<": Plane "<<p.id<<" landing."<<endl;
//             }
//             if(runway2.IsEmpty())   //跑道2空闲
//                 runway2_busy=false;
//         }
//         else    //飞机未离开
//         {
//             runway2.Push(p);
//         }
//     }
//     if(runway3_busy==true)  //跑道3忙
//     {
//         plane p=runway3.Front();
//         runway3.Pop();
//         p.t--;
//         if(p.t==0)  //飞机离开
//         {
//             if(p.id%2==0)   //起飞飞机
//             {
//                 takeoff++;
//                 cout<<"Time "<<time<<": Plane "<<p.id<<" takeoff."<<endl;
//             }
//             else    //降落飞机
//             {
//                 landing++;
//                 cout<<"Time "<<time<<": Plane "<<p.id<<" landing."<<endl;
//             }
//             if(runway3.IsEmpty())   //跑道3空闲
//                 runway3_busy=false;
//         }
//         else    //飞机未离开
//         {
//             runway3.Push(p);
//         }
//     }
// }

// //飞机等待
// void wait(int time)
// {
//     if(runway1_busy==false) //跑道1空闲
//     {
//         if(runway2_busy==true)  //跑道2忙
//         {
//             plane p=runway2.Front();
//             runway2.Pop();
//             if(p.id%2==0)   //起飞飞机
//             {
//                 takeoff++;
//                 takeoff_wait+=time;
//                 cout<<"Time "<<time<<": Plane "<<p.id<<" takeoff."<<endl;
//             }
//             else    //降落飞机
//             {
//                 landing++;
//                 landing_wait+=time;
//                 cout<<"Time "<<time<<": Plane "<<p.id<<" landing."<<endl;
//             }
//             if(runway2.IsEmpty())   //跑道2空闲
//                 runway2_busy=false;
//         }
//         else if(runway3_busy==true) //跑道3忙
//         {
//             plane p=runway3.Front();
//             runway3.Pop();
//             if(p.id%2==0)   //起飞飞机
//             {
//                 takeoff++;
//                 takeoff_wait+=time;
//                 cout<<"Time "<<time<<": Plane "<<p.id<<" takeoff."<<endl;
//             }
//             else    //降落飞机
//             {
//                 landing++;
//                 landing_wait+=time;
//                 cout<<"Time "<<time<<": Plane "<<p.id<<" landing."<<endl;
//             }
//             if(runway3.IsEmpty())   //跑道3空闲
//                 runway3_busy=false;
//         }
//     }
//     if(runway2_busy==false) //跑道2空闲
//     {
//         if(runway3_busy==true)  //跑道3忙
//         {
//             plane p=runway3.Front();
//             runway3.Pop();
//             if(p.id%2==0)   //起飞飞机
//             {
//                 takeoff++;
//                 takeoff_wait+=time;
//                 cout<<"Time "<<time<<": Plane "<<p.id<<" takeoff."<<endl;
//             }
//             else    //降落飞机
//             {
//                 landing++;
//                 landing_wait+=time;
//                 cout<<"Time "<<time<<": Plane "<<p.id<<" landing."<<endl;
//             }
//             if(runway3.IsEmpty())   //跑道3空闲
//                 runway3_busy=false;
//         }
//     }
// }

// int main()
// {
//     srand(time(0));
//     int time=0;
//     int n;
//     cin>>n;
//     for(int i=0;i<n;i++)
//     {
//         plane p;
//         cin>>p.id>>p.t;
//         if(p.id%2==0)   //起飞飞机
//         {
//             if(runway1_busy==false) //跑道1空闲
//             {
//                 runway1.Push(p);
//                 runway1_busy=true;
//             }
//             else if(runway2_busy==false) //跑道2空闲
//             {
//                 runway2.Push(p);
//                 runway2_busy=true;
//             }
//             else if(runway3_busy==false) //跑道3空闲
//             {
//                 runway3.Push(p);
//                 runway3_busy=true;
//             }
//             else    //跑道1、2、3都忙
//             {
//                 wait(time);
//                 runway1.Push(p);
//                 runway1_busy=true;
//             }
//         }
//         else    //降落飞机
//         {
//             if(runway1_busy==false) //跑道1空闲
//             {
//                 runway1.Push(p);
//                 runway1_busy=true;
//             }
//             else if(runway2_busy==false) //跑道2空闲
//             {
//                 runway2.Push(p);
//                 runway2_busy=true;
//             }
//             else if(runway3_busy==false) //跑道3空闲
//             {
//                 runway3.Push(p);
//                 runway3_busy=true;
//             }
//             else    //跑道1、2、3都忙
//             {
//                 wait(time);
//                 runway1.Push(p);
//                 runway1_busy=true;
//             }
//         }
//         time++;
//         leave(time);
//     }
//     cout<<"Takeoff: "<<takeoff<<endl;
//     cout<<"Landing: "<<landing<<endl;
//     cout<<"Takeoff wait: "<<takeoff_wait<<endl;
//     cout<<"Landing wait: "<<landing_wait<<endl;
//     return 0;
// }

// class AirportSimulation
// {
//     public:
//     AirportSimulation(int landingTime,int takeoffTime,int totalTime,int landingNum,int takeoffNum,int emergencyNum);
//     void Run();         //运行模拟
//     void Output();      //输出结果
//     private:
//     int landingTime;        //着陆时间
//     int takeoffTime;        //起飞时间
//     int totalTime;          //总时间
//     int landingNum;         //着陆队列长度
//     int takeoffNum;         //起飞队列长度
//     int emergencyNum;       //紧急降落队列长度
//     int landingCount;       //着陆队列中飞机数
//     int takeoffCount;       //起飞队列中飞机数
//     int emergencyCount;     //紧急降落队列中飞机数
//     int landingWait;        //着陆队列中飞机等待时间
//     int takeoffWait;        //起飞队列中飞机等待时间
//     int emergencyWait;      //紧急降落队列中飞机等待时间
//     int landingRemain;      //着陆队列中飞机剩余时间
//     int takeoffRemain;      //起飞队列中飞机剩余时间
//     int emergencyRemain;    //紧急降落队列中飞机剩余时间
//     int landingPlane;       //着陆队列中飞机编号
//     int takeoffPlane;       //起飞队列中飞机编号
//     int emergencyPlane;     //紧急降落队列中飞机编号
//     Queue<plane>landingQueue;       //着陆队列
//     Queue<plane>takeoffQueue;       //起飞队列
//     Queue<plane>emergencyQueue;     //紧急降落队列
// };

// AirportSimulation::AirportSimulation(int landingTime,int takeoffTime,int totalTime,int landingNum,int takeoffNum,int emergencyNum)
// {
//     this->landingTime=landingTime;
//     this->takeoffTime=takeoffTime;
//     this->totalTime=totalTime;
//     this->landingNum=landingNum;
//     this->takeoffNum=takeoffNum;
//     this->emergencyNum=emergencyNum;
//     landingCount=takeoffCount=emergencyCount=0;
//     landingWait=takeoffWait=emergencyWait=0;
//     landingRemain=takeoffRemain=emergencyRemain=0;
//     landingPlane=takeoffPlane=emergencyPlane=0;
// }

// void AirportSimulation::Run()
// {
//     int currentPlane=0;     //当前飞机编号
//     int currentTime=0;      //当前时间
//     int emergency=0;        //紧急降落标志
//     while(currentTime<totalTime)
//     {
//         if(currentTime%landingTime==0)   //有飞机到达
//         {
//             currentPlane++;
//             plane newPlane;
//             newPlane.id=currentPlane;
//             newPlane.t=landingTime;
//             if(emergency)   //紧急降落
//             {
//                 if(emergencyQueue.IsFull())     //紧急降落队列满
//                 {
//                     cout<<"Emergency landing queue is full. Plane "<<currentPlane<<" is forced to land."<<endl;
//                     landingCount++;
//                     landingWait+=currentTime;
//                     landingRemain+=landingTime;
//                     landingPlane=currentPlane;
//                 }
//                 else
//                 {
//                     emergencyQueue.Push(newPlane);
//                     emergencyCount++;
//                     emergencyWait+=currentTime;
//                     emergencyRemain+=landingTime;
//                     emergencyPlane=currentPlane;
//                 }
//                 emergency=0;
//             }
//             else if(landingQueue.IsFull())  //着陆队列满
//             {
//                 cout<<"Landing queue is full. Plane "<<currentPlane<<" is forced to land."<<endl;
//                 landingCount++;
//                 landingWait+=currentTime;
//                 landingRemain+=landingTime;
//                 landingPlane=currentPlane;
//             }
//             else
//             {
//                 landingQueue.Push(newPlane);
//                 landingCount++;
//                 landingWait+=currentTime;
//                 landingRemain+=landingTime;
//                 landingPlane=currentPlane;
//             }
//         }
//         if(currentTime%takeoffTime==0)  //有飞机起飞
//         {
//             currentPlane++;
//             plane newPlane;
//             newPlane.id=currentPlane;
//             newPlane.t=takeoffTime;
//             if(takeoffQueue.IsFull())   //起飞队列满
//             {
//                 cout<<"Takeoff queue is full. Plane "<<currentPlane<<" is forced to take off."<<endl;
//                 takeoffCount++;
//                 takeoffWait+=currentTime;
//                 takeoffRemain+=takeoffTime;
//                 takeoffPlane=currentPlane;
//             }
//             else
//             {
//                 takeoffQueue.Push(newPlane);
//                 takeoffCount++;
//                 takeoffWait+=currentTime;
//                 takeoffRemain+=takeoffTime;
//                 takeoffPlane=currentPlane;
//             }
//         }
//         if(currentTime%emergencyNum==0)     //有紧急降落
//         {
//             emergency=1;
//         }
//         if(!landingQueue.IsEmpty())     //有飞机着陆
//         {
//             plane landingPlane=landingQueue.Front();
//             landingPlane.t--;
//             if(landingPlane.t==0)   //飞机着陆完成
//             {
//                 landingQueue.Pop();
//                 landingCount--;
//                 landingRemain-=landingTime;
//             }
//             else
//             {
//                 landingQueue.Pop();
//                 landingQueue.Push(landingPlane);
//             }
//         }
//         if(!takeoffQueue.IsEmpty())     //有飞机起飞
//         {
//             plane takeoffPlane=takeoffQueue.Front();
//             takeoffPlane.t--;
//             if(takeoffPlane.t==0)   //飞机起飞完成
//             {
//                 takeoffQueue.Pop();
//                 takeoffCount--;
//                 takeoffRemain-=takeoffTime;
//             }
//             else
//             {
//                 takeoffQueue.Pop();
//                 takeoffQueue.Push(takeoffPlane);
//             }
//         }
//         if(!emergencyQueue.IsEmpty())   //有飞机紧急降落
//         {
//             plane emergencyPlane=emergencyQueue.Front();
//             emergencyPlane.t--;
//             if(emergencyPlane.t==0)     //飞机紧急降落完成
//             {
//                 emergencyQueue.Pop();
//                 emergencyCount--;
//                 emergencyRemain-=landingTime;
//             }
//             else
//             {
//                 emergencyQueue.Pop();
//                 emergencyQueue.Push(emergencyPlane);
//             }
//         }
//         currentTime++;
//     }
//     cout<<"Landing queue: "<<landingCount<<" planes, average waiting time: "<<(double)landingWait/landingCount<<", average remaining time: "<<(double)landingRemain/landingCount<<", last plane: "<<landingPlane<<endl;
// }

// int main()
// {
//     int landingTime,takeoffTime,totalTime,landingNum,takeoffNum,emergencyNum;
//     //landingTime:飞机到达时间间隔，takeoffTime:飞机起飞时间间隔，totalTime:模拟时间，landingNum:着陆队列长度，takeoffNum:起飞队列长度，emergencyNum:紧急降落时间间隔
//     cin>>landingTime>>takeoffTime>>totalTime>>landingNum>>takeoffNum>>emergencyNum;
//     AirportSimulation airportSimulation(landingTime,takeoffTime,totalTime,landingNum,takeoffNum,emergencyNum);
//     airportSimulation.Run();
//     return 0;
// }







////////////////
		if (flag1 == 1)
			goto label1;
		if(!landing.isempty() && takeoff.isempty())
		{
			p = *landing.Delete(p);
			land1(p);
		}
		else if(landing.isempty()&&!takeoff.isempty())
		{
			p = *takeoff.Delete(p);
			fly1(p);
		}
		else if(!landing.isempty() && !takeoff.isempty())
		{
			if (landing.Front().id < takeoff.Front().id)                 //优先降落
			{
				p = *landing.Delete(p);
				land1(p);
			}
			else if (landing.Front().id > takeoff.Front().id)             //优先起飞
			{
				p = *takeoff.Delete(p);
				fly1(p);
			}
		}
		label1:
		//考虑跑道2
		if (flag2 == 1)
			goto label2;
		if (!landing.isempty() && takeoff.isempty())
		{
			p = *landing.Delete(p);
			land2(p);
		}
		else if (landing.isempty() && !takeoff.isempty())
		{
			p = *takeoff.Delete(p);
			fly2(p);
		}
		else if (!landing.isempty() && !takeoff.isempty())
		{
			if (landing.Front().id < takeoff.Front().id)                 //优先降落
			{
				p = *landing.Delete(p);
				land2(p);
			}
			else if (landing.Front().id > takeoff.Front().id)             //优先起飞
			{
				p = *takeoff.Delete(p);
				fly2(p);
			}
		}


		else if(landing.isempty() && takeoff.isempty())
			idle();
		label2:
		cout << endl;
	}


