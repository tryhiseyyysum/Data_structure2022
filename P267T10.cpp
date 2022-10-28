#include<iostream>
using namespace std;
#include<stack>
#include<queue>     //实验：完整二叉树类的实现
//迭代版先序遍历实现

template<class T> class Tree;

template<class T>
class TreeNode
{
    friend class Tree<T>;
    public:
    TreeNode(T element=0,TreeNode *left=0,TreeNode *right=0):data(element),leftChild(left),rightChild(right){}
    private:
    T data;
    TreeNode<T> *leftChild;
    TreeNode<T> *rightChild;
};


template<class T>
class Tree
{
    public:
    class Iterator
    {
        public:
        Iterator(TreeNode<T> *t=0):currentNode(t){}
        void Preorder();     //前序遍历
        void Inorder();      //中序遍历
        void Postorder();    //后序遍历
        void Levelorder();  //层次遍历

        private:
        stack<TreeNode<T>*> s;
        queue<TreeNode<T>*> q;
        TreeNode<T> *currentNode;
    };

    private:
    TreeNode<T> *root;
    public:
    Tree():root(0){}
    Tree(const Tree<T> &t);
    Tree(Tree<T>& bt1,T&item,Tree<T> &bt2);
    ~Tree();
    TreeNode<T>* Copy(TreeNode<T> *origNode);
    bool IsEmpty();
    Tree<T> LeftSubtree();
    Tree<T> RightSubtree();
    T RootData();
    void Judge();   
    void NonrecPreorder();
    void ConstructTree();
    void DeleteTree(TreeNode<T> *&t);
    TreeNode<T>* Getroot();


};

//前序遍历
template <class T>
void Tree<T>::Iterator::Preorder()
{
    TreeNode<T> *p=currentNode;
    while(p!=0||!s.empty())
    {
        if(p!=0)
        {
            cout<<p->data<<" ";
            s.push(p);
            p=p->leftChild;
        }
        else
        {
            p=s.top();
            s.pop();
            p=p->rightChild;
        }
    }

}

//中序遍历
template <class T>
void Tree<T>::Iterator::Inorder()
{
    TreeNode<T> *p=currentNode;
    while(p!=0||!s.empty())
    {
        if(p!=0)
        {
            s.push(p);
            p=p->leftChild;
        }
        else
        {
            p=s.top();
            s.pop();
            cout<<p->data<<" ";
            p=p->rightChild;
        }
    }

}

//后序遍历，迭代实现
template <class T>
void Tree<T>::Iterator::Postorder()
{
    TreeNode<T> *p=currentNode; //当前结点指针
    TreeNode<T> *q=0;           //上一次访问的结点指针
    //栈非空或当前结点非空时迭代处理
    while(!s.empty() || p!=0)
    {   
        //当前结点非空，沿左子树方向入栈
        if(p!=0)
        {
            s.push(p);
            p=p->leftChild;
        }
        //如果当前结点为空，说明已到达左子树最下方，此时应该访问栈顶结点
        else
        {
            p=s.top();
            if(p->rightChild!=0 && p->rightChild!=q)  //如果栈顶有右子树，且未被访问，则要访问右子树
            {
                p=p->rightChild;    //转向右子树
                s.push(p);  //右子树根结点入栈
                p=p->leftChild; //沿左子树方向下行
            }
            else
            {
                p=s.top();
                cout<<p->data<<" ";
                s.pop();
                q=p;    //记录上一次访问的结点
                p=0;    //目的是防止再次沿左路下降，造成左路子树的重复遍历
            }
        }
    }
}

//层次遍历
template <class T>
void Tree<T>::Iterator::Levelorder()
{
    TreeNode<T> *p=currentNode;
    if(p!=0)
    {
        q.push(p);
        while(!q.empty())
        {
            p=q.front();
            q.pop();
            cout<<p->data<<" ";
            if(p->leftChild!=0)
                q.push(p->leftChild);
            if(p->rightChild!=0)
                q.push(p->rightChild);
        }
    }
    
}

template <class T>
TreeNode<T>* Tree<T>::Getroot()
{
    return root;
}


template<class T>
Tree<T>::Tree(const Tree<T> &t)
{
    root=Copy(t.root);
}

template<class T>
TreeNode<T>* Tree<T>::Copy(TreeNode<T> *origNode)
{
    if(!origNode) return 0;
    return new TreeNode<T>(origNode->data,Copy(origNode->leftChild),Copy(origNode->rightChild));
}

template<class T>
bool Tree<T>::IsEmpty()
{
    return root==0;
}

template<class T>
T Tree<T>::RootData()
{
    return root;
}

template<class T>
Tree<T> Tree<T>::LeftSubtree()
{
    Tree<T> t;
    t.root=root->leftChild;
    return t;
}

template<class T>
Tree<T> Tree<T>::RightSubtree()
{
    Tree<T> t;
    t.root=root->rightChild;
    return t;
}

template<class T>
Tree<T>::Tree(Tree<T>& bt1,T&item,Tree<T> &bt2)
{
    root->data=item;
    root->leftChild=bt1;
    root->rightChild=bt2;
}

template<class T>
void Tree<T>::ConstructTree()
{
    root=new TreeNode<T>;
    root->data=1;
    root->leftChild=new TreeNode<T>;
    root->leftChild->data=2;
    root->rightChild=new TreeNode<T>;
    root->rightChild->data=3;
    root->leftChild->leftChild=new TreeNode<T>;
    root->leftChild->leftChild->data=4;
    root->leftChild->rightChild=new TreeNode<T>;
    root->leftChild->rightChild->data=5;
    root->rightChild->leftChild=new TreeNode<T>;
    root->rightChild->leftChild->data=6;
    root->rightChild->rightChild=new TreeNode<T>;
    root->rightChild->rightChild->data=7;

}

template<class T>
void Tree<T>::DeleteTree(TreeNode<T> *&t)
{
    if(t)
    {
        DeleteTree(t->leftChild);       //递归删除左子树
        DeleteTree(t->rightChild);      //递归删除右子树
        delete t;                       //删除根结点
        t=0;                            //置空根节点指针
    }
    
}

template<class T>
Tree<T>::~Tree()
{
    cout<<"Destructor is called!"<<endl;
    DeleteTree(root);
}


template<class T>
void Tree<T>::Judge()
{
    if(root)
        cout<<"The tree is not empty!"<<endl;
    else
    {
        cout<<"The tree is empty!"<<endl;
    }
}

int main()
{
    Tree<int> t;
    t.ConstructTree();
    Tree<int>::Iterator it(t.Getroot());
    t.Judge();
    cout<<"Preorder:"<<endl;
    it.Preorder();
    cout<<endl;
    cout<<"Inorder:"<<endl;
    it.Inorder();
    cout<<endl;
    cout<<"Postorder:"<<endl;
    it.Postorder();
    cout<<endl;
    cout<<"Levelorder:"<<endl;
    it.Levelorder();
    cout<<endl;

    t.~Tree();
    t.Judge();
    
    return 0;
}