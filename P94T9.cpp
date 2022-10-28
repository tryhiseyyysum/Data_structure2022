#include<iostream>
using namespace std;

class Polynomial;

class Term
{
public:
    friend class Polynomial;

    float coef;
    int exp;

};

class Polynomial
{
    friend Term;
public:
    Polynomial()=default;
    Polynomial(int n);
    ~Polynomial();
    Polynomial &Add(Polynomial b);
    Polynomial &Mul(Polynomial b);
    void NewTerm(const float theCoeff, const int theExp);
    friend ostream &operator<<(ostream &out,const Polynomial &p);
    friend istream &operator>>(istream &in,Polynomial &p);


private:
    static Term* termArray;
    static int capacity;
    static int free;
    int start,finish;


};

int Polynomial::capacity=100;
Term* Polynomial::termArray=new Term[100];
int Polynomial::free=0;     //free指向termArray中下一个空闲的位置

Polynomial::Polynomial(int n)
{
    start=free;
    finish=free+n-1;
    free+=n;
}



Polynomial::~Polynomial()
{
    //free=start;
}

void Polynomial::NewTerm(const float theCoeff, const int theExp)
{
    if(free==capacity)
    {
        capacity*=2;   //扩容
        Term* temp=new Term[capacity];
        for(int i=0;i<free;i++)
            temp[i]=termArray[i];
        delete []termArray;
        termArray=temp;
    }
    termArray[free].coef=theCoeff;
    termArray[free++].exp=theExp;
}

//注意：要返回Polynomial类型的引用，否则会调用拷贝构造函数
Polynomial &Polynomial::Add(Polynomial b)
{
    Polynomial c;
    c.start=free;
    int i=start,j=b.start;
    while(i<=finish && j<=b.finish)
    {
        if(termArray[i].exp==b.termArray[j].exp)
        {
            if(termArray[i].coef+b.termArray[j].coef)
            {
                {
                    //NewTerm里面自带了free++，所以这里不用free++
                    c.NewTerm(termArray[i].coef+b.termArray[j].coef,termArray[i].exp);
                }
                
            }
            i++;
            j++;

        } 
        else if(termArray[i].exp>b.termArray[j].exp)
        {
            c.NewTerm(termArray[i].coef,termArray[i].exp);
            i++;
        }
        else if(termArray[i].exp<b.termArray[j].exp)
        {
            c.NewTerm(b.termArray[j].coef,b.termArray[j].exp);
            j++;
        }
    }
    while(i<=finish)
    {
        c.NewTerm(termArray[i].coef,termArray[i].exp);
        i++;
    }
    while(j<=b.finish)
    {
        c.NewTerm(b.termArray[j].coef,b.termArray[j].exp);
        j++;
    }

    c.finish=c.free-1;
    return c;
}

Polynomial &Polynomial::Mul(Polynomial b)
{
    Polynomial d;
    d.start=free;

    for(int i=start;i<=finish;i++)
    {
        for(int j=b.start;j<=b.finish;j++)
        {
            float t=termArray[i].coef*b.termArray[j].coef;
            if(t)
            {
                d.NewTerm(t,termArray[i].exp+b.termArray[j].exp);
            }

        }
    }

    d.finish=d.free-1;
    return d;
}



ostream &operator<<(ostream &out,const Polynomial &p)
{
    for(int i=p.start;i<=p.finish;i++)
    {
        if(p.termArray[i].exp==0)
            out<<p.termArray[i].coef;
        else
        {
            if(p.termArray[i].coef==1)
                out<<"x^"<<p.termArray[i].exp;
            else if(p.termArray[i].coef==-1)
                out<<"-x^"<<p.termArray[i].exp;
            else
                out<<p.termArray[i].coef<<"x^"<<p.termArray[i].exp;
        }
            
        if(i<p.finish) out<<"+";

    }
        
    out<<endl;
    return out;
}

istream &operator>>(istream &in,Polynomial &p)
{
    for(int i=p.start;i<=p.finish;i++)
        in>>p.termArray[i].coef>>p.termArray[i].exp;
    return in;
}



int main()
{
    Polynomial a(2),b(4),c,d;
    cin>>a>>b;
    cout<<"多项式a为："<<endl;
    cout<<a<<endl;
    cout<<"多项式b为："<<endl;
    cout<<b<<endl;
    cout<<"------------------"<<endl;
    c=a.Add(b);
    cout<<"多项式a+b为："<<endl;
    cout<<c<<endl;
    cout<<"------------------"<<endl;
    cout<<"多项式a*b为："<<endl;
    d=a.Mul(b);
    cout<<d<<endl;
    return 0;
}


