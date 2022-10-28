#include<iostream>
using namespace std;
#include<stack>
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
    private:
    TreeNode<T> *root;
    public:
    Tree():root(0){}
    void NonrecPreorder();
    void ConstructTree();

};

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
void Tree<T>::NonrecPreorder()
{
    stack<TreeNode<T>*> s;
    TreeNode<T>* currentNode=root;
    while(1)
    {
        while(currentNode)
        {
            cout<<currentNode->data<<" ";
            s.push(currentNode);
            currentNode=currentNode->leftChild;
        }
        if(s.empty())
            return;
        currentNode=s.top();
        s.pop();
        currentNode=currentNode->rightChild;
    }
}

int main()
{
    Tree<int> t;
    t.ConstructTree();
    t.NonrecPreorder();
    return 0;
}