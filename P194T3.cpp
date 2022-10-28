#include<iostream>
using namespace std;
#include<list>
#include<vector>

void copy(list<int> &a,vector<int> &b)
{
    list<int>::iterator it;
    for(it=a.begin();it!=a.end();it++)
    {
        b.push_back(*it);
    }
}


int main()
{
    list<int> a;
    vector<int> b;
    int n=10;
    for(int i=0;i<n;i++)
    {
        a.push_back(i);
    }

    cout<<"a:"<<endl;
    for(list<int>::iterator it=a.begin();it!=a.end();it++)
    {
        
        cout<<*it<<" ";
    }
    cout<<endl;

    copy(a,b);
    cout<<"b:"<<endl;
    for(vector<int>::iterator it=b.begin();it!=b.end();it++)
    {
        cout<<*it<<" ";
    }
    cout<<endl;
    return 0;
}