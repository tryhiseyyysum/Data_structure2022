#include<iostream>
using namespace std;
#include<ctime>
#include<windows.h>

int BinarySearch(int *a,const int x,const int n)  //x是要查找的元素,n是数组长度
{
    //cout<<"BinarySearch"<<endl;
    int left=0,right=n-1;
    while(left<=right)
    {
        int middle=(left+right)/2;
        if(x<a[middle]) right=middle-1;
        else if(x>a[middle]) left=middle+1;
        else return middle;
    }
    return -1;  //not found
}


//计时程序
void TimeSearch()
{
    int a[1001],n[20];
    const long r[20]={300000,300000,200000,200000,100000,100000,100000,80000,
    80000,50000,50000,25000,15000,15000,10000,7500,7000,
    6000,5000,5000};

    for(int j=1;j<=1000;j++) a[j]=j;

    for(int j=0;j<10;j++)
    {
        n[j]=10*j;
        n[j+10]=100*(j+1);
    }

    cout<<"n  totalTime  runtime"<<endl;
    for(int j=0;j<20;j++)
    {
        
        double start= clock()/(double)CLOCKS_PER_SEC;

        for(long b=1;b<=r[j];b++)
        {
            int k=BinarySearch(a,0,n[j]);
        }
        

        double stop = clock()/(double)CLOCKS_PER_SEC;
      
        //程序从开始到现在总的运行时间
        double totalTime = clock()/(double)CLOCKS_PER_SEC;
        //程序段执行时间
        //double runtime=stop-start;
        double runtime=(double)totalTime/(double)(r[j]);

        cout<<n[j]<<"   "<<totalTime<<"s"<<"    "<<runtime<<"s"<<endl;
    }
    //cout<<"Times are in hundredths of a second."<<endl;

}

int main()
{
    int a[10]={1,2,3,4,5,6,7,8,9,10};
    int x=6;
    //cin>>x;
    int n=10;
    int result=BinarySearch(a,x,n);
    if(result==-1) cout<<"Not found"<<endl;
    else cout<<"Found at index: "<<result<<endl;
    TimeSearch();
    return 0;
}