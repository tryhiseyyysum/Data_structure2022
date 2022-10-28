#include<iostream>
using namespace std;
#include<queue>
#include<ctime>
#include<cstdlib>
#include<cmath>
//初始化一棵空的二叉查找树，随机插入n个元素，使用统一的随机数产生器得到待插入的值

template<class K,class E>
struct BSTNode
{
    pair<K,E> data;
    BSTNode<K,E> *leftChild;
    BSTNode<K,E> *rightChild;
    BSTNode(pair<K,E> d,BSTNode<K,E> *l=0,BSTNode<K,E> *r=0):data(d),leftChild(l),rightChild(r){}
};

template<class K,class E>
class BST               //二叉查找树ADT
{
    public:
    BST():root(0){}     //初始化空的二叉查找树
    bool IsEmpty() const;
    int GetHeight(BSTNode<K,E> *t);
    void Insert(const pair<K,E>& x);    //插入
    void ConstructTree(int n);
    void Levelorder();
    BSTNode<K,E>* Getroot();
    private:
    BSTNode<K,E> *root;
    queue<BSTNode<K,E>*> q;
};

template<class K,class E>
bool BST<K,E>::IsEmpty() const
{
    return root==0;
}

template<class K,class E>
int BST<K,E>::GetHeight(BSTNode<K,E> *t)
{
    if(t==0)
        return 0;
    else
    {
        int l=GetHeight(t->leftChild);
        int r=GetHeight(t->rightChild);
        return (l>r)?(l+1):(r+1);
    }
}

template<class K,class E>
BSTNode<K,E>* BST<K,E>::Getroot()
{
    return root;
} 

template<class K,class E>
void BST<K,E>::Insert(const pair<K,E>& x)
{
    BSTNode<K,E> *p=root,*pp=0;
    while(p)
    {
        pp=p;
        if(x.first<p->data.first)
            p=p->leftChild;
        else if(x.first>p->data.first)
            p=p->rightChild;
        else
        {
            p->data.second=x.second;
            return;
        }
    }
    p=new BSTNode<K,E>(x);
    if(root)
    {
        if(x.first<pp->data.first)
            pp->leftChild=p;
        else
            pp->rightChild=p;
    }
    else
        root=p;
}

template<class K,class E>
void BST<K,E>::ConstructTree(int n)
{
    for(int i=0;i<n;i++)
    {
        pair<K,E> x;
        x.first=rand()%10000;     //随机产生一个1000以内的整数
        x.second=x.first;       //将该整数作为关键字和值
        Insert(x);
    }
}

template<class K,class E>
void BST<K,E>::Levelorder()
{
    BSTNode<K,E> *p=root;
    q.push(p);
    while(!q.empty())
    {
        p=q.front();
        q.pop();
        cout<<p->data.first<<" ";
        if(p->leftChild)
            q.push(p->leftChild);
        if(p->rightChild)
            q.push(p->rightChild);
    }
}

int main()
{
    srand((unsigned)time(0));
    BST<int,int> bst;
    int n=100;
    bst.ConstructTree(n);
    cout<<"n="<<n<<":  ";
    cout<<"height："<<bst.GetHeight(bst.Getroot())<<"   ";
    cout<<"height/log2(n)的值为："<<bst.GetHeight(bst.Getroot())/log2(n)<<endl;
    int n2=500;
    bst.ConstructTree(n2);
    cout<<"n="<<n2<<":  ";
    cout<<"height："<<bst.GetHeight(bst.Getroot())<<"   ";
    cout<<"height/log2(n)的值为："<<bst.GetHeight(bst.Getroot())/log2(n2)<<endl;

    for(int i=1000;i<=10000;i+=1000)
    {
        bst.ConstructTree(i);
        cout<<"n="<<i<<":  ";
        cout<<"height："<<bst.GetHeight(bst.Getroot())<<"   ";
        cout<<"height/log2(n)的值为："<<bst.GetHeight(bst.Getroot())/log2(i)<<endl;
    }
    // cout<<"层次遍历二叉查找树：";
    // bst.Levelorder();
    cout<<endl;
    return 0;
}