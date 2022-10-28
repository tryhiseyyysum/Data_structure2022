#include<iostream>
using namespace std;
#include<cmath>

//数据类
struct Term
{
    int coef;
    int exp;
    Term Set(int c = 0, int e = 0) { coef = c; exp = e; return *this; }
};

template<class T>
class Chain;

//链表结点类
template<class T>
class ChainNode
{
    friend class Chain<T>;
public:
    int Getcoef() { return t.coef; }
    int& Getexp() { return t.exp; }
    ChainNode<T>*& Getlink();
    Term& GetTerm() { return t; }
private:
    Term t;
    ChainNode<T>* link;
};

template<class T>
ChainNode<T>*& ChainNode<T>::Getlink()
{
    return link;
}


class Polynomial;
//带头结点的循环链表类
template<class T>
class Chain
{
    friend class Polynomial;
public:
    //嵌套类  //链表迭代器类
    template<class T>
    class ChainIterator
    {
    public:
        ChainIterator(ChainNode<T>*& startNode) { current = startNode; }
        T& operator*() { return &current->t; }
        T* operator->() { return &current->t; }
        ChainIterator& operator++() { current = current->Getlink(); return *this; }
        ChainIterator operator++(int)
        {
            ChainIterator old = *this;
            current = current->Getlink();
            return old;
        }
        bool operator!=(const ChainIterator right) const
        {
            return current != right.current;
        }
        bool operator==(const ChainIterator right) const
        {
            return current == right.current;
        }
        //private:
        ChainNode<T>* current;
    };

public:
    Chain();
    Chain(int n);
    ~Chain();
    //void print();
    ChainNode<T>* Getlast();
    ChainNode<T>* GetNode();
    void RetNode(ChainNode<T>*& x);
    void InsertBack(ChainNode<T>*& x);
    ChainNode<T>*& Gethead();
    ChainIterator<T> begin() { return ChainIterator<T>(head->link); }
    ChainIterator<T> end() { return ChainIterator<T>(head); }

private:
    ChainNode<T>* head;
    ChainNode<T>* last;
    ChainNode<T>* av;   //av list的头指针

};

template<class T>
Chain<T>::Chain()
{
    head = GetNode();
    head->t.Set(-1, -1);
    head->link = head;
    last = 0;
    av = 0;
}

template<class T>
Chain<T>::Chain(int n)
{
    av = 0;
    //dummy head node
    head = GetNode();
    head->link = head;
    head->t.exp = -1;

    last = GetNode();
    last->link = head;

    ChainNode<T>* current = last;
    for (int i = 0; i < n; i++)
    {
        current->link = GetNode();
        current = current->link;
        current->link = head;
    }
    last = current;
}

template<class T>
Chain<T>::~Chain()
{
    if (last)
    {
        ChainNode<T>* first = last->Getlink();
        last->link = av;
        av = first;
        last = 0;
    }
}

template<class T>
ChainNode<T>* Chain<T>::Getlast()
{
    return last;
}

template<class T>
ChainNode<T>*& Chain<T>::Gethead()
{
    return head;
}

//从头部插入一个结点
template<class T>
void Chain<T>::InsertBack(ChainNode<T>*& x)
{
    if (last)
    {
        x->link = last->link;
        last->link = x;
        last = x;
    }
    else
    {
        //cout << "链表为空" << endl;
        head->link = x;
        x->link = head;
        last = x;

    }

}



//从av list 中获得一个新的结点
template<class T>
ChainNode<T>* Chain<T>::GetNode()
{
    ChainNode<T>* x;
    if (av) { x = av; av = av->link; }
    else x = new ChainNode<T>;
    return x;
}

//原链表删除一个结点，交给 av list 去保存
template<class T>
void Chain<T>::RetNode(ChainNode<T>*& x)
{
    x->link = av;
    av = x;
    x = 0;
}


//多项式类
class Polynomial
{
public:
    Polynomial();
    Polynomial(int n);
    ~Polynomial();
    friend istream& operator>>(istream& is, Polynomial& x);
    friend ostream& operator<<(ostream& os, Polynomial& x);
    Polynomial(const Polynomial& a);    //拷贝构造函数
    Polynomial& operator=(Polynomial& a);    //赋值运算符重载
    Polynomial& operator+(Polynomial& b);  //加法运算符重载
    Polynomial& operator-(Polynomial& b);  //减法运算符重载
    Polynomial& operator*(Polynomial& b);  //乘法运算符重载
    float Evaluate(float x);    //求当自变量等于x时多项式的值

private:
    Chain<Term> poly;

};

Polynomial::Polynomial()
{

}

Polynomial::Polynomial(int n)
{
    poly = Chain<Term>(n);
    ChainNode<Term>* current = poly.Getlast()->Getlink();
    for (int i = 0; i < n; i++)
    {
        current->GetTerm().Set(0, -1);
        current = current->Getlink();
    }
}

Polynomial::~Polynomial()
{
    poly.~Chain();
}

istream& operator>>(istream& is, Polynomial& x)
{
    int n;
    is >> n;

    for (int i = 0; i < n; i++)
    {
        ChainNode<Term>* current = new ChainNode<Term>;   //=x.poly.Getlast();
        int c, e;
        is >> c >> e;
        (current->GetTerm()).Set(c, e);
        x.poly.InsertBack(current);

    }
    return is;

}

ostream& operator<<(ostream& os, Polynomial& x)
{
    Chain<Term>::ChainIterator<Term> first((x.poly.Gethead())->Getlink());
    Chain<Term>::ChainIterator<Term> end(x.poly.Gethead());
    while (first != end)
    {
        if (first->coef == 1)
        {
            if (first->exp == 0)
            {
                os << "1";
                if ((++first)->exp != -1 && first->coef > 0)
                    os << "+";
            }
            else if (first->exp == 1 && first->coef > 0)
            {
                os << "x";
                if ((++first)->exp != -1)
                    os << "+";
            }
            else
            {
                os << "x^" << first->exp;
                if ((++first)->exp != -1 && first->coef > 0)
                    os << "+";
            }
        }
        else if (first->coef == -1)
        {
            if (first->exp == 0)
            {
                os << "-1";
                ++first;
            }
            else if (first->exp == 1)
            {
                os << "-x";
                ++first;
            }
            else
            {
                os << "-x^" << first->exp;
                ++first;
            }
        }
        else
        {
            if (first->coef < 0)       //系数小于0
            {
                if (first->exp == 0)
                {
                    os << first->coef;
                    ++first;
                }
                else if (first->exp == 1)
                {
                    os << first->coef << "x";
                    ++first;
                }
                else
                {
                    os << first->coef << "x^" << first->exp;
                    ++first;
                }

            }
            else if (first->coef > 0)       //系数大于0
            {
                if (first->exp == 0)
                {
                    os << first->coef;
                    if ((++first)->exp != -1 && first->coef > 0)
                        os << "+";
                }
                else if (first->exp == 1)
                {
                    os << first->coef << "x";
                    if ((++first)->exp != -1 && first->coef > 0)
                        os << "+";
                }
                else
                {
                    os << first->coef << "x^" << first->exp;
                    if ((++first)->exp != -1 && first->coef > 0)
                        os << "+";
                }
            }
            else      //系数等于0
            {
                if ((++first)->exp != -1 && first->coef > 0)
                    os << "+";
            }
        }

    }
    return os;
}

Polynomial::Polynomial(const Polynomial& a)
{
    poly = a.poly;

}

Polynomial& Polynomial::operator=(Polynomial& a)
{
    poly = a.poly;
    return *this;

}

Polynomial& Polynomial::operator+(Polynomial& b)
{
    Polynomial* c = new Polynomial;
    ChainNode<Term>* current1 = poly.Gethead()->Getlink();
    ChainNode<Term>* current2 = b.poly.Gethead()->Getlink();
    while (current1 != poly.Gethead() && current2 != b.poly.Gethead())
    {
        if (current1->GetTerm().exp > current2->GetTerm().exp)
        {
            ChainNode<Term>* newNode = c->poly.GetNode();
            newNode->GetTerm().Set(current1->GetTerm().coef, current1->GetTerm().exp);
            c->poly.InsertBack(newNode);
            current1 = current1->Getlink();
        }
        else if (current1->GetTerm().exp < current2->GetTerm().exp)
        {
            ChainNode<Term>* newNode = c->poly.GetNode();
            newNode->GetTerm().Set(current2->GetTerm().coef, current2->GetTerm().exp);
            c->poly.InsertBack(newNode);
            current2 = current2->Getlink();
        }
        else
        {
            ChainNode<Term>* newNode = c->poly.GetNode();
            newNode->GetTerm().Set(current1->GetTerm().coef + current2->GetTerm().coef, current1->GetTerm().exp);
            c->poly.InsertBack(newNode);
            current1 = current1->Getlink();
            current2 = current2->Getlink();
        }
    }
    while (current1 != poly.Gethead())
    {
        ChainNode<Term>* newNode = c->poly.GetNode();
        newNode->GetTerm().Set(current1->GetTerm().coef, current1->GetTerm().exp);
        c->poly.InsertBack(newNode);
        current1 = current1->Getlink();
    }
    while (current2 != b.poly.Gethead())
    {
        ChainNode<Term>* newNode = c->poly.GetNode();
        newNode->GetTerm().Set(current2->GetTerm().coef, current2->GetTerm().exp);
        c->poly.InsertBack(newNode);
        current2 = current2->Getlink();
    }
    return *c;
}


Polynomial& Polynomial::operator-(Polynomial& b)
{
    Polynomial* c = new Polynomial;
    ChainNode<Term>* current1 = this->poly.Gethead()->Getlink();
    ChainNode<Term>* current2 = b.poly.Gethead()->Getlink();
    while (current1 != this->poly.Gethead() && current2 != b.poly.Gethead())
    {
        if (current1->Getexp() == current2->Getexp())
        {
            ChainNode<Term>* newNode = c->poly.GetNode();
            newNode->GetTerm().Set(current1->Getcoef() - current2->Getcoef(), current1->Getexp());
            c->poly.InsertBack(newNode);
            current1 = current1->Getlink();
            current2 = current2->Getlink();
        }
        else if (current1->Getexp() > current2->Getexp())
        {
            ChainNode<Term>* newNode = c->poly.GetNode();
            newNode->GetTerm().Set(current1->Getcoef(), current1->Getexp());
            c->poly.InsertBack(newNode);
            current1 = current1->Getlink();
        }
        else
        {
            ChainNode<Term>* newNode = c->poly.GetNode();
            newNode->GetTerm().Set(-current2->Getcoef(), current2->Getexp());
            c->poly.InsertBack(newNode);
            current2 = current2->Getlink();
        }
    }
    while (current1 != this->poly.Gethead())
    {
        ChainNode<Term>* newNode = c->poly.GetNode();
        newNode->GetTerm().Set(current1->Getcoef(), current1->Getexp());
        c->poly.InsertBack(newNode);
        current1 = current1->Getlink();
    }
    while (current2 != b.poly.Gethead())
    {
        ChainNode<Term>* newNode = c->poly.GetNode();
        newNode->GetTerm().Set(-current2->Getcoef(), current2->Getexp());
        c->poly.InsertBack(newNode);
        current2 = current2->Getlink();
    }
    return *c;
}


Polynomial& Polynomial::operator*(Polynomial& b)
{
    Polynomial* c = new Polynomial;
    ChainNode<Term>* current1 = this->poly.Gethead()->Getlink();
    ChainNode<Term>* current2 = b.poly.Gethead()->Getlink();
    while (current1 != this->poly.Gethead())
    {
        while (current2 != b.poly.Gethead())
        {
            ChainNode<Term>* newNode = c->poly.GetNode();
            newNode->GetTerm().Set(current1->Getcoef() * current2->Getcoef(), current1->Getexp() + current2->Getexp());
            c->poly.InsertBack(newNode);
            current2 = current2->Getlink();
        }
        current1 = current1->Getlink();
        current2 = b.poly.Gethead()->Getlink();
    }

    //再次遍历多项式c，将相同指数的项合并
    ChainNode<Term>* current3 = c->poly.Gethead()->Getlink();
    ChainNode<Term>* current4 = current3->Getlink();
    while (current3 != c->poly.Gethead())
    {
        while (current4 != c->poly.Gethead())
        {
            if (current3->Getexp() == current4->Getexp())
            {
                current3->GetTerm().coef += current4->Getcoef();
                ChainNode<Term>* temp = current4;
                current4 = current4->Getlink();
                c->poly.RetNode(temp);
                current3->Getlink() = current4;
            }
            else
            {
                current4 = current4->Getlink();
            }
        }
        current3 = current3->Getlink();
        current4 = current3->Getlink();
    }
    return *c;

}


float Polynomial::Evaluate(float x)
{
    float result = 0;
    ChainNode<Term>* current = this->poly.Gethead()->Getlink();
    while (current != this->poly.Gethead())
    {
        result += current->Getcoef() * pow(x, current->Getexp());
        current = current->Getlink();
    }
    return result;
}

int main()
{
    Polynomial a, b, c, d, e;
    cin >> a;
    cin >> b;
    cout << "a=" << a << endl;
    cout << "b=" << b << endl;

    c = a + b;
    cout << "c=a+b=" << c << endl;

    d = a - b;
    cout << "d=a-b=" << d << endl;

    e = a * b;
    cout << "e=a*b=" << e << endl;

    cout << "a(2)=" << a.Evaluate(2) << endl;
    cout << "b(3)=" << b.Evaluate(3) << endl;
    cout << "c(4)=" << c.Evaluate(4) << endl;
    cout << "d(5)=" << d.Evaluate(5) << endl;
    cout << "e(6)=" << e.Evaluate(6) << endl;


    return 0;
}

