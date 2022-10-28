//地图染色问题 BackTracking回溯算法实现
//r:被染色的地图,N:城市数，c:各个城市的颜色
#include <iostream>
using namespace std;
int c[100],pr,color=4;  //4中颜色可选
const int N=7;    //城市数
int r[N][N]={0,1,1,0,0,0,0,
             1,0,1,1,0,0,0,
             1,1,0,1,1,0,0,
             0,1,1,0,1,1,0,
             0,0,1,1,0,1,1,
             0,0,0,1,1,0,1,
             0,0,0,0,1,1,0};  //邻接矩阵

void mapcolor(int (*r)[N],int *c)
{
    c[1]=1;     //第一个城市染色
    pr=2;       //从2号城市开始试探
    while(pr<=N)    //从2号城市开始涂色
    {
        for(int k=1;k<=color;k++)   //每个城市从1~color依次试探
        {
            for(int j=1;j<=N;j++)   //对城市pr，搜索其全部相邻城市的颜色
            {
                if(r[pr][j]==1&&c[j]==k)    //相邻城市同色
                {
                    break;
                }
                if(j>N)     //没有相邻城市同色
                {
                    c[pr]=k;    //pr号城市染色
                    pr++;
                    break;
                }
            }
            if(k>color)     //没有找到合适的颜色，即所有颜色都已经用过，以及无法填入了，则退回上一地区重新涂色，BackTracking
            {
                pr--;
                c[pr]++;    //回溯
            }
        }
    }

}

int main()
{
    mapcolor(r,c);
    for(int i=1;i<=N;i++)
    {
        cout<<c[i]<<" ";
    }
    cout<<endl;
    return 0;
}