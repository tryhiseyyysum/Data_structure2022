#include<iostream>
using namespace std;

class DblList;

class DblListNode
{
    friend class DblList;
    public:
    DblListNode(int element=0,DblListNode *left=0,DblListNode *right=0):data(element),left(left),right(right){}
    DblListNode *getright();
    private:
    int data;
    DblListNode *left,*right;
};

DblListNode *DblListNode::getright()
{
    return right;
}

class DblList
{
    public:
    DblList(int n);
    void Delete(DblListNode *x);
    void Insert(DblListNode *p,DblListNode *x);
    void print();
    void Clear();
    DblListNode *getfirst();
    DblListNode *getlast();
    void Concatenate(DblList m);
    
    private:
    DblListNode *first;
};

DblList::DblList(int n)
{
    first=new DblListNode;
    first->data=1;
    first->left=NULL;
    first->right=NULL;
    DblListNode *current=first;
    for(int i=2;i<=n;i++)
    {
        DblListNode *newNode=new DblListNode;
        newNode->data=i;
        newNode->left=current;
        newNode->right=NULL;
        current->right=newNode;
        current=newNode;
    }
}


void DblList::print()
{
    DblListNode *current=first;
    while(current!=NULL)
    {
        cout<<current->data<<" ";
        current=current->right;
    }
    cout<<endl;
}

DblListNode *DblList::getfirst()
{
    return first;
}

DblListNode *DblList::getlast()
{
    DblListNode *current=first;
    while(current->right!=NULL)
    {
        current=current->right;
    }
    return current;
}


void DblList::Delete(DblListNode *x)
{
    if(x==first) throw "Deletion of header node not permitted.";
    else
    {
        DblListNode *y=x->left;
        DblListNode *z=x->right;
        y->right=z;
        z->left=y;
    }
}

void DblList::Clear()   //清空链表
{
    DblListNode *current=first;
    while(current!=NULL)
    {
        DblListNode *next=current->right;
        delete current;
        current=next;
    }
    first=NULL;
}

void DblList::Insert(DblListNode *p,DblListNode *x)
{
    DblListNode *y=x->right;
    x->right=p;
    p->left=x;
    p->right=y;
    y->left=p;
}

//连接两个双向链表，并把m置为空
void DblList::Concatenate(DblList m)
{
//1.
    // this->getlast()->right=m->getfirst();
    // m->getfirst()->left=this->getlast();

    // //释放m链表的空间
    // DblListNode *current=m->getfirst();
    // while(current!=NULL)
    // {
    //     DblListNode *next=current->right;
    //     delete current;
    //     current=next;
    // }

//2.
    // DblListNode *last=getlast();
    // DblListNode *first=m->getfirst();
    // last->right=first;
    // first->left=last;

    DblListNode *last=getlast();
    DblListNode *first=m.getfirst();   
    last->right=first;
    first->left=last;

}

int main()
{
    DblList list(10);
    list.print();
//测试其他功能函数:
    // DblListNode *x=list.getfirst();
    // for(int i=0;i<5;i++)
    // {
    //     x=x->getright();
    // }
    // DblListNode *p=new DblListNode(100);    //把p插入到x的右边
    // list.Insert(p,x);
    // list.print();
    // list.Delete(x);
    // list.print();

    DblList list2(5);
    list.Concatenate(list2);
    list.print();
    list2.Clear();
    list2.print();
    return 0;
}
