#include<iostream>
using namespace std;
class Chain;

class ChainNode
{
    friend class Chain;
    public:
    ChainNode(int element=0,ChainNode *next=0):data(element),link(next){}
    ChainNode *getlink();
    private:
    int data;
    ChainNode *link;
};

ChainNode *ChainNode::getlink()
{
    return link;
}

class Chain
{
    public:
    Chain(int n);
    void print();
    ChainNode *getfirst();
    void move_right(ChainNode *l,ChainNode *r,int n);
    void move_left(ChainNode *l,ChainNode *r,int n);
    void set_l(ChainNode *l);
    void set_r(ChainNode *r);

    private:
    int *chain;
    //int length;     //链的长度
    ChainNode *first;
    ChainNode *l,*r;

};



Chain::Chain(int n)
{
    first=new ChainNode;
    first->data=1;
    first->link=NULL;
    ChainNode *current=first;
    for(int i=2;i<=n;i++)
    {
        ChainNode *newNode=new ChainNode;
        newNode->data=i;
        newNode->link=NULL;
        current->link=newNode;
        current=newNode;
    }
    current->link=0;    


    
}

void Chain::print()
{
    ChainNode *current=first;
    while(current!=NULL)
    {
        cout<<current->data<<" ";
        current=current->link;
    }
    cout<<endl;
}

ChainNode* Chain::getfirst()
{
    return first;
}

void Chain::move_right(ChainNode *l,ChainNode *r,int n)
{   
    //p为当前指针，pp为前指针，ppp为前前指针
    this->l=l;
    this->r=r;
    
    int i=0;

    while(i<n)     //移动指针r
    {

        if(r==0)
        {
            r=0;
            break;
        }
        l=r;
        r=r->link;
        i++;
    }
   
    //翻转指针r前面的所有指针
    ChainNode *p,*pp;
    p=first,pp=0;
    while(p!=r)
    {

        ChainNode *ppp=pp;
        pp=p;
        p=p->link;
        pp->link=ppp;

    }
    first=pp;

    cout<<"l="<<l->data<<" r="<<r->data<<endl;
}

void Chain::set_l(ChainNode *l)
{
    this->l=l;
}

void Chain::set_r(ChainNode *r)
{
    this->r=r;
}

void Chain::move_left(ChainNode *l,ChainNode *r,int n)
{
    //p为当前指针，pp为前指针，ppp为前前指针
    this->l=l;
    this->r=r;
    int i=0;

    //翻转指针r前面的所有指针
    ChainNode *p,*pp;
    p=first,pp=0;
    while(p!=r)
    {

        ChainNode *ppp=pp;
        pp=p;
        p=p->link;
        pp->link=ppp;

    }

    while(i<n)     //移动指针r
    {

        if(r==0)
        {
            r=0;
            break;
        }
        r=l;        //因为r前面的所有指针都被翻转了，故这里l相当于当前结点，r相当于前结点
        l=l->link;
        i++;
    }
    first=l;
   

    cout<<"l="<<l->data<<" r="<<r->data<<endl;
}

int main()
{
    int n,m1,m2;
    n=10;
    m1=2;
    m2=12;
    Chain chain(n);
    chain.print();
    ChainNode *l,*r;
    l=chain.getfirst()->getlink()->getlink()->getlink();       //l指向第四个节点
    r=chain.getfirst()->getlink()->getlink()->getlink()->getlink();  //r指向第五个节点  
    chain.move_right(l,r,m1);
    chain.print();


    cout<<"-----------------"<<endl;
    Chain chain2(n);
    chain2.print();
    l=chain2.getfirst()->getlink()->getlink()->getlink();       //l指向第四个节点
    r=chain2.getfirst()->getlink()->getlink()->getlink()->getlink();  //r指向第五个节点  
    chain2.move_left(l,r,m1);
    chain2.print();
    return 0;
}