#include<iostream>
using namespace std;
#include<list>

int Compute(list<int> &a)
{
    list<int>::iterator it1,it2;
    it1=it2=a.begin();
    for(int i=0;i<5;i++)
    {
        it2++;
    }
    int sum=0;
    for(it2;it2!=a.end();it2++)
    {
        sum+=*it1 * *it2;
        it1++;
    }
    return sum;
}

int main()
{
    list<int> L;
    for(int i=1;i<11;i++)
    {
        L.push_back(i);
    }

    cout<<Compute(L)<<endl;
}
