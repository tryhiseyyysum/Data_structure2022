#include<iostream>
using namespace std;
#include<stack>
//树的中序遍历迭代器

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
    class InorderIterator
    {
        public:
        InorderIterator(TreeNode<T> *t=0):currentNode(t){}
        T *Next();

        private:
        stack<TreeNode<T>*> s;
        TreeNode<T> *currentNode;
    };

    private:
    TreeNode<T> *root;

    public:
    Tree():root(0){}
    void InOrder();
    void ConstructTree();

};

template <class T>
T *Tree<T>::InorderIterator::Next()
{
    while (currentNode)
    {
        s.push(currentNode);
        currentNode = currentNode->leftChild;
    }
    if (s.empty())
        return 0;
    currentNode = s.top();
    s.pop();
    T &temp = currentNode->data;
    currentNode = currentNode->rightChild;
    return &temp;
}

template<class T>
void Tree<T>::InOrder()
{
    InorderIterator it(root);
    T *temp;
    temp=it.Next();
    while(temp!=0)
    {
        cout<<*temp<<" ";
        temp=it.Next();
    }
    
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

int main()
{
    Tree<int> t;
    t.ConstructTree();
    t.InOrder();
    return 0;
}




