#include<iostream>
using namespace std;
//线索二叉树中插入把l作为s的左结点插入
template<class T>
class ThreadedTree;

template<class T>
class ThreadedNode
{
    friend class ThreadedTree<T>;
    public:
    ThreadedNode(T element=0,ThreadedNode *left=0,ThreadedNode *right=0,bool ltag=0,bool rtag=0):data(element),leftChild(left),rightChild(right),leftThread(ltag),rightThread(rtag){}
    T *&Getdata();
    private:
    T data;
    ThreadedNode<T> *leftChild;
    ThreadedNode<T> *rightChild;
    bool leftThread;
    bool rightThread;
};

template<class T>
T *&ThreadedNode<T>::Getdata()
{
    return data;
}

template<class T>
class ThreadedTree
{
    public:
    class Iterator
    {
        public:
        Iterator(ThreadedNode<T> *t=0):currentNode(t){}
        T* Next();      //中序遍历
        private:
        ThreadedNode<T> *currentNode;
    };

    private:
    ThreadedNode<T> * root;
    ThreadedNode<T> * head;
    public:
    ThreadedTree():root(0){}
    ThreadedNode<T> *&Getroot();

    void ConstructTree();
    void InThread(ThreadedNode<T> *p, ThreadedNode<T>*&pre);
    void createInThread(ThreadedTree<T> &tree);

    ThreadedNode<T> *First(ThreadedNode<T> *p);
    ThreadedNode<T> *Next(ThreadedNode<T> *p);
    void Inorder(ThreadedNode<T> *root);

    ThreadedNode<T>* InorderSucc(ThreadedNode<T> *currentNode);  //返回currentNode的中序遍历后继节点指针
    void InsertLeft(ThreadedNode<T> *&s,ThreadedNode<T> *&l);
};

template<class T>
T* ThreadedTree<T>::Iterator::Next()
{
        ThreadedNode<T> *temp = currentNode->rightChild;
        if (!currentNode->rightThread)
        {
            while (!currentNode->leftThread)
                temp = temp->leftChild;
        }
        currentNode = temp;
        // No next node
        //if (currentNode == root)
            //return 0;
        return &currentNode->data;
    

}


//插入一个结点，作为左结点插入
template<class T>
void ThreadedTree<T>::InsertLeft(ThreadedNode<T> *&s,ThreadedNode<T> *&l)
{
    // l->leftChild=s->leftChild;
    // l->leftThread=s->leftThread;

    // l->rightChild=s;
    // l->rightThread=true;

    // s->leftChild=l;
    // s->leftThread=false;

    // if(!l->leftThread)  //l有左孩子
    // {
    //     ThreadedNode<T>* temp=InorderSucc(l);
    //     temp->leftChild=l;
    // }



    l->leftChild = s->leftChild;
    l->leftThread = s->leftThread;
    l->rightChild = s;
    l->rightThread = 1;
    s->leftChild = l;
    s->leftThread = 0;
    if (!l->leftThread)
    {
        ThreadedNode<T> *temp = l->leftChild;
        while (!temp->rightThread)
            temp = temp->rightChild;
        temp->rightChild = l;
    }
}

template<class T>
ThreadedNode<T>* ThreadedTree<T>::InorderSucc(ThreadedNode<T> *currentNode)
{
    ThreadedNode<T>* temp=currentNode->rightChild;
    if(!currentNode->rightThread)
    {
        while(!currentNode->leftThread)
            temp=temp->leftChild;
    }
    currentNode=temp;
    if(currentNode==root) return root;
    else
        return currentNode;
}

template<class T>
ThreadedNode<T> *&ThreadedTree<T>::Getroot()
{
    return root;
}

template<class T>
void ThreadedTree<T>::ConstructTree()
{
    ThreadedNode<T>* pA,*pB,*pC,*pD,*pE,*pF,*pG,*pH,*pI;
    pA=new ThreadedNode<T>;
    pB=new ThreadedNode<T>;
    pC=new ThreadedNode<T>;
    pD=new ThreadedNode<T>;
    pE=new ThreadedNode<T>;
    pF=new ThreadedNode<T>;
    pG=new ThreadedNode<T>;
    pH=new ThreadedNode<T>;
    pI=new ThreadedNode<T>;

    pA->data = 'A';
	pB->data = 'B';
	pC->data = 'C';
	pD->data = 'D';
	pE->data = 'E';
	pF->data = 'F';
	pG->data = 'G';
	pH->data = 'H';
	pI->data = 'I';
 
	pA->leftChild = pC;
	pA->rightChild = pB;
	pC->leftChild = pD;
	pC->rightChild = pE;
	pB->rightChild = pF;
	pB->leftChild = NULL;
	pD->leftChild = pG;
	pD->rightChild = NULL;
	pE->leftChild = NULL;
	pE->rightChild = pH;
	pF->leftChild = pI;
	pF->rightChild = NULL;
	pG->leftChild = pG->rightChild = NULL;  //pG是叶子结点
	pH->leftChild = pH->rightChild = NULL;  //pH是叶子结点
	pI->leftChild = pI->rightChild = NULL;  //pI是叶子结点
 
 
	pA->leftThread = pA->rightThread = 0;
    pB->leftThread = pB->rightThread = 0;
    pC->leftThread = pC->rightThread = 0;
    pD->leftThread = pD->rightThread = 0;
    pE->leftThread = pE->rightThread = 0;
    pF->leftThread = pF->rightThread = 0;
    pG->leftThread = pG->rightThread = 0;
    pH->leftThread = pH->rightThread = 0;
    pI->leftThread = pI->rightThread = 0;

    root=pA;

}

//构造中序线索，结点线索化
template<class T>
void ThreadedTree<T>::InThread(ThreadedNode<T> *p, ThreadedNode<T>*&pre) //pre是前一个结点
{
    if (p)
    {
        InThread(p->leftChild,pre); //递归，左子树线索化
        if (!p->leftChild)
        {
            p->leftThread = true;
            p->leftChild = pre;
        }
        if(pre && !pre->rightChild)
        {
            pre->rightThread = true;
            pre->rightChild = p;
        }
        pre = p;

        InThread(p->rightChild,pre);    //递归，右子树线索化
    }

}

template<class T>
void ThreadedTree<T>::createInThread(ThreadedTree<T> &tree)
{
    ThreadedNode<T> *pre =0;
   if(root!=0)
   {
         InThread(root,pre);
         pre->rightChild=0;
         pre->rightThread=1;
   }    

}


template<class T>
ThreadedNode<T> *ThreadedTree<T>::First(ThreadedNode<T> *p)
{
    while (p->leftThread == 0)
        p = p->leftChild; //最左下结点
    return p;
}

template<class T>
ThreadedNode<T> *ThreadedTree<T>::Next(ThreadedNode<T> *p)
{
    if (p->rightThread == 0)
        return First(p->rightChild);
    else
        return p->rightChild; // rtag==1,直接返回后继线索
}

template<class T>
void ThreadedTree<T>::Inorder(ThreadedNode<T> *root)
{
    for (ThreadedNode<T> *p = First(root); p != NULL; p = Next(p))
        cout << p->data<<"  ";
}

int main()
{
    ThreadedTree<char> tree;
    ThreadedNode<char> *p=new ThreadedNode<char>('Z');
    tree.ConstructTree();
    tree.createInThread(tree);
    tree.Inorder(tree.Getroot());
    tree.InsertLeft(tree.Getroot(), p);
    cout<<endl;
    tree.Inorder(tree.Getroot());


    return 0;
}