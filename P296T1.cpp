#include<iostream>
using namespace std;
#include<queue>

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
    BST():root(0){}
    BST(const BST<K,E> &t);
    ~BST();
    bool IsEmpty() const;
    BSTNode<K,E>* Copy(BSTNode<K,E> *t);
    pair<K,E>* Get(const K& k);    //查找
    void Insert(const pair<K,E>& x);    //插入
    //BSTNode<K,E>* GetMaxKey(BSTNode<K,E>* t);
    void Delete(const K& k);    //删除
    void DeleteTree(BSTNode<K,E> *&t);
    void ConstructTree();
    void Levelorder();
    private:
    BSTNode<K,E> *root;
    queue<BSTNode<K,E>*> q;
};

template<class K,class E>
BST<K,E>::BST(const BST<K,E> &t)
{
    root=Copy(t.root);
}

template<class K,class E>
void BST<K,E>::DeleteTree(BSTNode<K,E> *&t)
{
    if(t)
    {
        DeleteTree(t->leftChild);
        DeleteTree(t->rightChild);
        delete t;
        t=0;
    }
}


template<class K,class E>
BST<K,E>::~BST()
{
    DeleteTree(root);
}

template<class K,class E>
bool BST<K,E>::IsEmpty() const
{
    return root==0;
}

template<class K,class E>
BSTNode<K,E>* BST<K,E>::Copy(BSTNode<K,E> *t)
{
    if(t==0)
        return 0;
    else
        return new BSTNode<K,E>(t->data,Copy(t->leftChild),Copy(t->rightChild));
}

template<class K,class E>
pair<K,E>* BST<K,E>::Get(const K& k)
{
    BSTNode<K,E> *current=root;
    while(current!=0)
    {
        if(k<current->data.first)
            current=current->leftChild;
        else if(k>current->data.first)
            current=current->rightChild;
        else
            return &current->data;
    }
    return 0;
}

template<class K,class E>
void BST<K,E>::Insert(const pair<K,E>& x)
{
    BSTNode<K,E> *p=root,*pp=0;
    while(p!=0)
    {
        pp=p;
        if(x.first<p->data.first)
            p=p->leftChild;
        else if(x.first>p->data.first)
            p=p->rightChild;
        else
        {
            p->data.second=x.second;    //修改已有元素的值
            return;   //退出
        }
    }
    if(root==0)
        root=new BSTNode<K,E>(x);
    else if(x.first<pp->data.first)
        pp->leftChild=new BSTNode<K,E>(x);
    else
        pp->rightChild=new BSTNode<K,E>(x);
}

// template<class K,class E>
// BSTNode<K,E>* BST<K,E>::GetMaxKey(BSTNode<K,E>* t)     //返回以t为根的左子树中键最大的结点
// {
//     if(t==0)
//         return 0;
//     t=t->leftChild;
//     while(t->rightChild!=0)
//         t=t->rightChild;
//     return t;
// }




template<class K,class E>
void BST<K,E>::Delete(const K& k)   
{
    BSTNode<K,E> *p=root,*pp=0;
    while(p!=0&&p->data.first!=k)
    {
        pp=p;
        if(k<p->data.first)
            p=p->leftChild;
        else
            p=p->rightChild;
    }
    if(p==0)
        return;
    if(p->leftChild!=0&&p->rightChild!=0)   //p的度为2,找到p的左子树中键最大的结点,用它替换p
    {
        BSTNode<K,E> *s=p->leftChild,*ps=p;
        while(s->rightChild!=0)
        {
            ps=s;
            s=s->rightChild;
        }
        p->data=s->data;
        //p=s;
        //pp=ps;
        if(s->leftChild)    //由于s是左子树中最大的结点，故它没有右孩子，这个判断恒为真
        {
            if(ps==p)
                ps->leftChild=s->leftChild;
            else
                ps->rightChild=s->leftChild;
        }
        delete s;
    }
    else if(p->leftChild==0&&p->rightChild==0)  //p的度为0
    {
        if(p==root)   //p是根结点
            root=0;
        else if(pp->leftChild==p)   //p是左孩子
            pp->leftChild=0;
        else    //p是右孩子
            pp->rightChild=0;
        delete p;
    }
    
    else        //p的度为1
    {
        BSTNode<K, E> *c;
        if (p->leftChild != 0) // p的左孩子不为空
            c = p->leftChild;
        else // p的右孩子不为空
            c = p->rightChild;
        if (p == root) // p为根结点
            root = c;
        else if (p == pp->leftChild) // p为左孩子
            pp->leftChild = c;
        else // p为右孩子
            pp->rightChild = c;
        delete p;
    }
    
}

template<class K,class E>
void BST<K,E>::ConstructTree()
{
    pair<K,E> x;
    cout<<"输入结点的键值和数据，以0结束"<<endl;
    cin>>x.first>>x.second;
    while(x.first!=0)
    {
        Insert(x);
        cin>>x.first>>x.second;
    }
}

template<class K,class E>
void BST<K,E>::Levelorder()
{
    BSTNode<K,E> *current=root;
    if(current!=0)
        q.push(current);
    while(!q.empty())
    {
        current=q.front();
        q.pop();
        cout<<current->data.first<<" "<<current->data.second<<endl;
        if(current->leftChild!=0)
            q.push(current->leftChild);
        if(current->rightChild!=0)
            q.push(current->rightChild);
    }
}

int main()
{
    int k=10;        //键值
    BST<int,int> t;
    t.ConstructTree();
    cout<<"层次遍历"<<endl;
    t.Levelorder();
    t.Delete(k);    //删除键值为k的元素
    cout<<"删除键值为"<<k<<"的元素后的二叉排序树的层次遍历序列为："<<endl;
    t.Levelorder();
    return 0;
}




