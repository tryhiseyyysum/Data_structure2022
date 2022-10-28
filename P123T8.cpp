#include<iostream>
using namespace std;
#include <cstdlib>
#include <ctime>
//random walk
 
//移动方向类
class Move
{
    friend class random_walk;
    public:
    void InitMove(int* imove,int* jmove);    //初始化移动方位数组
    private:
    int rmove[8],cmove[8];  //移动方位数组
    

};

void Move::InitMove(int* imove,int* jmove)    //初始化移动方位数组
{
    imove[0] = -1;
    jmove[0] = 1;   //东北方
 
    imove[1] = 0;
    jmove[1] = 1;   //正东方
 
    imove[2] = 1;
    jmove[2] = 1;   //东南方
 
    imove[3] = 1;
    jmove[3] = 0;   //正南方
 
    imove[4] = 1;
    jmove[4] = -1;  //西南方
 
    imove[5] = 0;
    jmove[5] = -1;  //正西方
 
    imove[6] = -1;
    jmove[6] = -1;  //西北方
 
    imove[7] = -1;
    jmove[7] = 1;   //正北方
}

//随机漫步类
class random_walk
{
    public:
    int Random(int m,int n);    //指定范围内随机数
    bool judgewalk(int**count,int n,int m); //判断是否访问完所有瓷砖
    void printwalk(int**count,int n,int m); //打印所有瓷砖访问次数
    void randomwalk_randomInitPoint(int** count,int n,int m);    
    void randomwalk_setInitPoint(int** count,int n,int m,int x,int y);   

    private:
    Move move; //移动方向类对象

};

int random_walk::Random(int m,int n) //指定范围内随机数
{
    int pos,range;    //pos表示随机数的起始位置，range表示随机数的范围
    if(m == n)  //表示范围内只有一个数字
        return m;
    else if(n < m)  //表示取区间[n,m]内的数字
    {
        pos = n;
        range = m - n + 1;
        return rand() % range + pos;
    }
    else    //表示取区间[m,n]内的数字
    {
        pos = m;
        range = n - m + 1;
        return rand() % range + pos;
    }
}
 

 
bool random_walk::judgewalk(int**count,int n,int m) //判断是否访问完所有瓷砖
{
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < m; j++)
        {
            if(!count[i][j]) //如果有一个没访问完的瓷砖，则退出
                return false;
        }
    }
    return true;
}
 
void random_walk::printwalk(int**count,int n,int m) //打印所有瓷砖访问次数
{
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < m; j++)
        {
            cout << count[i][j] << " ";
        }
        cout << endl;
    }
}

void random_walk::randomwalk_randomInitPoint(int** count,int n,int m)  //随机漫步
{

    count=new int*[n];  //记录每个瓷砖被访问的次数
    for(int i=0;i<n;i++)
    {
        count[i]=new int[m];
    }
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            count[i][j]=0;
        }
    }

    move.InitMove(move.rmove,move.cmove);  //初始化移动方位数组
    int ibug = Random(0,n - 1); //现在所在行
    int jbug = Random(0,m - 1); //现在所在列

    count[ibug][jbug]++;    //当前瓷砖访问次数＋1
    
    int NextR,NextC;    //下一位置所在行，下一位置所在列


    while(true)
    {
        int moving = Random(0,7);   //随机产生移动方向
        NextR = ibug + move.rmove[moving];   //下一位置所在行
        NextC = jbug + move.cmove[moving];   //下一位置所在列
        while(NextR < 0 || NextC < 0 || NextR >=n || NextC >= m)   //当碰到墙壁时
        {
            moving = Random(0,7);   //随机产生移动方向
            NextR = ibug + move.rmove[moving];   //下一位置所在行
            NextC = jbug + move.cmove[moving];   //下一位置所在列
        }

        count[ibug][jbug]++;    //当前瓷砖访问次数＋1
        ibug = NextR;
        jbug = NextC;   //下一位置等于当前位置
  
        int sum=0;
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<m;j++)
            {
                sum+=count[i][j];
            }
        }
        
        if(judgewalk(count,n,m)) //判断是否访问完所有瓷砖
        {
            cout << "Total move step:" << sum << endl;  //打印总步数
            printwalk(count,n,m);    //打印所有瓷砖访问次数
            return;
        }
        if(sum > 50000) //超出迭代上限次数
        {
            cout << "Cockroach don't visit all Tile." << endl;
            cout << "Total move step:" << sum << endl;  //打印总步数
            printwalk(count,n,m);
            return;
        }
 
    }
}
 

 void random_walk::randomwalk_setInitPoint(int** count,int n,int m,int x,int y)  //给定起始位置的随机漫步
{

    count=new int*[n];  //记录每个瓷砖被访问的次数
    for(int i=0;i<n;i++)
    {
        count[i]=new int[m];
    }
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            count[i][j]=0;
        }
    }

    move.InitMove(move.rmove,move.cmove);  //初始化移动方位数组
    int ibug = x; //现在所在行
    int jbug = y; //现在所在列

    count[ibug][jbug]++;    //当前瓷砖访问次数＋1
    
    int NextR,NextC;    //下一位置所在行，下一位置所在列


    while(true)
    {
        int moving = Random(0,7);   //随机产生移动方向
        NextR = ibug + move.rmove[moving];   //下一位置所在行
        NextC = jbug + move.cmove[moving];   //下一位置所在列
        while(NextR < 0 || NextC < 0 || NextR >=n || NextC >= m)   //当碰到墙壁时
        {
            moving = Random(0,7);   //随机产生移动方向
            NextR = ibug + move.rmove[moving];   //下一位置所在行
            NextC = jbug + move.cmove[moving];   //下一位置所在列
        }

        count[ibug][jbug]++;    //当前瓷砖访问次数＋1
        ibug = NextR;
        jbug = NextC;   //下一位置等于当前位置
  
        int sum=0;
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<m;j++)
            {
                sum+=count[i][j];
            }
        }
        if(judgewalk(count,n,m)) //判断是否访问完所有瓷砖
        {
            cout << "Total move steps:" << sum << endl;  //打印总步数
            printwalk(count,n,m);    //打印所有瓷砖访问次数
            return;
        }
        if(sum > 50000) //超出迭代上限次数
        {
            cout << "Cockroach don't visit all Tile." << endl;
            cout << "Total move steps:" << sum << endl;  //打印总步数
            printwalk(count,n,m);
            return;
        }
 
    }
}


int main()
{
    srand(time(0)); //根据时间产生相应种子值
    random_walk rw1,rw2,rw3;

    int n,m;  //行列
    int **count;

    //第a问：
    cout<<"第a问："<<endl;
    cout<<"请输入行数n: "<<endl;
    cin >> n;
    cout<<"请输入列数m: "<<endl;
    cin >> m;
    rw1.randomwalk_randomInitPoint(count,n,m);
    //delete
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            delete []count;
        }
    }
    
    cout<<"-------------------------------------"<<endl;


    //第b问(1)：
    cout<<"第b问(1)："<<endl;
    int n2=15,m2=15;
    rw2.randomwalk_setInitPoint(count,n2,m2,9,9);

    cout<<"-------------------------------------"<<endl;

    //第b问(2)：
    cout<<"第b问(2)："<<endl;
    int n3=39,m3=19;
    rw3.randomwalk_setInitPoint(count,n3,m3,0,0);

    cout<<"-------------------------------------"<<endl;

    return 0;
}
