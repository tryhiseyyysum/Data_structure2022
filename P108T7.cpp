#include<iostream>
using namespace std;       //稀疏矩阵的另一种表示方法
class SparseMatrix1;
class MatrixTerm
{
    friend class SparseMatrix1;
    private:
        int row;
        int col;
        int value;

};
class SparseMatrix2;

//用三元组法表示稀疏矩阵
class SparseMatrix1
{
    public:
    SparseMatrix1()=default;
    SparseMatrix1(int rows,int cols);
    SparseMatrix1(int r,int c,int t);
    SparseMatrix1& Add(SparseMatrix2 b);
    void Print1();

    private:
    int rows,cols,terms,capacity;
    MatrixTerm *smArray;

};


//用P108T7所给方法表示稀疏矩阵
class SparseMatrix2
{
    friend class SparseMatrix1;

    public:
    SparseMatrix2()=default;
    SparseMatrix2(int r,int c,int t);
    private:
    int rows,cols,terms;
    int **bits;
    int *v;
    

};



SparseMatrix1::SparseMatrix1(int r,int c,int t)
{
    rows=r;
    cols=c;
    terms=t;
    capacity=2*terms;
    smArray=new MatrixTerm[capacity];
    smArray[0].row=0;
    smArray[0].col=0;
    smArray[0].value=15;
    smArray[1].row=0;
    smArray[1].col=4;
    smArray[1].value=91;
    smArray[2].row=1;
    smArray[2].col=1;
    smArray[2].value=11;
    smArray[3].row=2;
    smArray[3].col=1;
    smArray[3].value=3;
    smArray[4].row=2;
    smArray[4].col=5;
    smArray[4].value=28;
    smArray[5].row=3;
    smArray[5].col=0;
    smArray[5].value=22;
    smArray[6].row=3;
    smArray[6].col=2;
    smArray[6].value=-6;
    smArray[7].row=4;
    smArray[7].col=0;
    smArray[7].value=-15;

    
}

SparseMatrix2::SparseMatrix2(int rows,int cols,int terms)
{
    v=new int[terms];           //一维数组按顺序存储非零项的值
    v[0]=15,v[1]=22,v[2]=-15,v[3]=11,v[4]=3,v[5]=-6,v[6]=91,v[7]=28;

    bits=new int*[rows];
    for(int i=0;i<rows;i++)
    {
        bits[i]=new int[cols];
    }
    
    
    for(int i=0;i<rows;i++)
    {
        for(int j=0;j<cols;j++)
        {
            //把bits二维数组中的非零元素置为1，其他元素置为0
            if(i==0&&j==0||i==0&&j==3&&i==0,j==5||i==1&&j==1||i==1&&j==2||i==2&&j==3||i==4&&j==0||i==5&&j==2)
            {
                bits[i][j]=1;
            }
            else
            {
                bits[i][j]=0;
            }
            
        }
    }

}

SparseMatrix1& SparseMatrix1::Add(SparseMatrix2 b)
{
   int i=0;
   for(int j=0;j<terms;j++)
   {
      smArray[i++].value+=b.v[j];
   }

    
    return *this;
    
    
    
}

void SparseMatrix1::Print1()
{
    for(int i=0;i<terms;i++)
    {
        cout<<smArray[i].row<<" "<<smArray[i].col<<" "<<smArray[i].value<<endl;
    }
}


int main()
{
    SparseMatrix1 a(6,6,8);         //a为三元组表示的稀疏矩阵
    cout<<"a矩阵为："<<endl;
    a.Print1();
    cout<<"----------------------"<<endl;
    SparseMatrix2 b(6,6,8);         //b为P108T7所给方法表示的稀疏矩阵
    SparseMatrix1 c(6,6,8);
    cout<<"a+b矩阵为："<<endl;
    c=a.Add(b);
    c.Print1();
    return 0;
}
    
