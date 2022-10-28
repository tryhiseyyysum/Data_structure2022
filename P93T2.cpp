#include<iostream>
using namespace std;

int Compare_Arr(int *a,int n,int *b,int m)
{
    int aPos=0,bPos=0;
    while(aPos<n && bPos<m)
    {
        if(a[aPos]==b[bPos])
        {
            aPos++;
            bPos++;
        }
        else if(a[aPos]<b[bPos])
        {
            return -1;      //a<b
        }
        else if(a[aPos]>b[bPos])
        {
            return +1;      //a>b
        }
    }

    //退出循环，表示a或b中的某一个已经遍历完
    if(n<m)   //a遍历完
    {
        return -1;      //a<b
    }
    else if(n>m)
    {
        return +1;      //a>b
    }
    else
    {
        return 0;       //a=b
    }

}

int main()
{
    int a[10]={1,2,3,4,5,6,7,8,9,10};
    int b[10]={1,2,3,4,5,6,7};
    int result1=Compare_Arr(a,10,b,7);
    cout<<result1<<endl;        //1   表示a>b

    int c[10]={14,15,16,17,18,19,20,21,22,23};
    int d[10]={14,15,17,20,44};
    int result2=Compare_Arr(c,5,d,10);
    cout<<result2<<endl;        //-1  表示c<d

    int e[10]={1,2,3,4,5,6,7,8,9,10};
    int f[10]={1,2,3,4,5,6,7,8,9,10};
    int result3=Compare_Arr(e,10,f,10);
    cout<<result3<<endl;        //0   表示e=f



}