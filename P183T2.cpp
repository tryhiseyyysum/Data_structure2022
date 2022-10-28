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
    int length();
    void Delete_oneNode(ChainNode *x);
    void print();
    ChainNode *getfirst();

    private:
    int *chain;
    //int length;     //链的长度
    ChainNode *first;

};

int Chain::length()
{
    int length=0;
    ChainNode *current=first;
    while(current!=NULL)
    {
        length++;
        current=current->link;
    }
    return length;

    //时间复杂度为O(n)



}

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

void Chain::Delete_oneNode(ChainNode *x)
{
    if(first==0) return;         //链表为空
    if(x==first)
    {
        first=first->link;
        delete x;
    }
    else
    {
        ChainNode *current=first;
        while(current->link!=x)
        {
            current=current->link;
        }
        current->link=x->link;
        delete x;

    }

    //时间复杂度为O(n)


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


int main()
{
    int n=5;
    Chain chain(n);
    cout<<chain.length()<<endl;
    chain.print();
    cout<<"After delete:"<<endl;
    ChainNode *x=chain.getfirst()->getlink()->getlink();    //删除第三个节点 3
    chain.Delete_oneNode(x);
    chain.print();
    

    return 0;
}
