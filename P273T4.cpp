#include<iostream>
using namespace std;
#include<queue>
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
    private:
    TreeNode<T> *root;
    public:
    Tree():root(0){}
    TreeNode<T> *&Getroot();
    void ConstructTree();
    void LevelOrder();  //层次遍历
    void PrintTree();
    //递归删除树的所有结点
    void DeleteTree(TreeNode<T> *&t);
    ~Tree();

};

template<class T>
TreeNode<T> *&Tree<T>::Getroot()
{
    return root;
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
void Tree<T>::LevelOrder()
{
    queue<TreeNode<T>*> q;
    TreeNode<T> *currentNode=root;
    q.push(currentNode);
    while(!q.empty())
    {
        currentNode=q.front();
        q.pop();
        cout<<currentNode->data<<" ";
        if(currentNode->leftChild)
            q.push(currentNode->leftChild);
        if(currentNode->rightChild)
            q.push(currentNode->rightChild);
    }
}

template<class T>
void Tree<T>::PrintTree()
{
    if(root)
        LevelOrder();
    else
    {
        cout<<"The tree is empty!"<<endl;
    }
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
    DeleteTree(root);
}

int main()
{
    Tree<int> tree;
    tree.ConstructTree();
    tree.PrintTree();
    cout<<endl;
    //tree.DeleteTree(tree.Getroot());
    tree.~Tree();
    tree.PrintTree();
    return 0;
}
