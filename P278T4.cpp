#include<iostream>
using namespace std;
//前序遍历线索二叉树

template<class T>
class ThreadedTree;

template<class T>
class ThreadedNode
{
    friend class ThreadedTree<T>;
    public:
    ThreadedNode(T element=0,ThreadedNode *left=0,ThreadedNode *right=0,bool ltag=0,bool rtag=0):data(element),leftChild(left),rightChild(right),leftThread(ltag),rightThread(rtag){}
    private:
    T data;
    ThreadedNode<T> *leftChild;
    ThreadedNode<T> *rightChild;
    bool leftThread;
    bool rightThread;
};

template<class T>
class ThreadedTree
{
    public:
    class Iterator
    {
        public:
        Iterator(ThreadedNode<T> *t=0):currentNode(t){}
        T* PreorderNext();      //前序遍历
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
    void preThread(ThreadedNode<T> *p, ThreadedNode<T>*&pre);
    void createPreThread(ThreadedTree<T> &tree);
    void Preorder();
};

//算法：前序遍历线索二叉树：
// 如果该结点有左孩子，那么该结点的先序后继就是该结点的左孩子；
// 如果该结点没有左孩子，那么该结点的先序后继就是该结点的右孩子
// (右孩子存在，那么返回一个实在的结点；右孩子不存在，那么返回NULL)

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

//建立前序线索
template<class T>
void ThreadedTree<T>::preThread(ThreadedNode<T> *p, ThreadedNode<T>*&pre)
{
	if (p != NULL)
	{
		if (p->leftChild == NULL)//建立当前结点的前驱线索
		{
			p->leftChild = pre;
			p->leftThread = true;
		}
		if (pre != NULL && pre->rightChild == NULL) 
        {//建立当前结点的后继线索
			pre->rightChild = p;
			pre->rightThread = true;
		}
		pre = p;
		/*左右指针不是线索才能继续递归*/
		if(p->leftThread==0)
			preThread(p->leftChild, pre);//递归，左子树线索化
		if (p->rightThread == 0)
			preThread(p->rightChild, pre);//递归，右子树线索化
	}
}

template<class T>
void ThreadedTree<T>::createPreThread(ThreadedTree<T> &tree)
{
    ThreadedNode<T> *pre = NULL;
    tree.preThread(tree.Getroot(), pre);
    pre->rightChild = NULL;
    pre->rightThread = true;
}


template<class T>
void ThreadedTree<T>::Preorder()
{
    if (root != NULL)
    {
        ThreadedNode<T> *p = root;
        while (p != NULL)
        {
            while (p->leftThread == 0)
            { //左指针不是线索，则边访问边左移
                cout << p->data<<"  ";
                p = p->leftChild;
            }
            cout << p->data<<"  ";
            /*此时p左孩子不存在，则右指针若非空，则不论是否为线索都指向其后继*/
            p = p->rightChild;
        }
    }
}



int main()
{
    ThreadedTree<char> tree;
    tree.ConstructTree();
    tree.createPreThread(tree);
    tree.Preorder();
    //输出前序序列为：A C D G E H B F I
    //树的结构为：
    //        A
    //      /   \
    //     C     B
    //    / \   / \
    //   D   E    F
    //  /     \  /
    // G       H I

    return 0;
}