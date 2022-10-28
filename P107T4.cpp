#include<iostream>
using namespace std;
class SparseMatrix;
class MatrixTerm
{
    friend class SparseMatrix;
    private:
        int row;
        int col;
        int value;

};

class SparseMatrix
{
    public:
    SparseMatrix()=default;
    SparseMatrix(int r,int c,int t);
    SparseMatrix FastTranspose();
    void Print();
    private:
    int rows,cols,terms,capacity;
    MatrixTerm *smArray;

};

SparseMatrix::SparseMatrix(int r,int c,int t)
{
    rows=r;
    cols=c;
    terms=t;
    capacity=2*terms;
    smArray=new MatrixTerm[capacity];
    smArray[0].row=0;
    smArray[0].col=0;
    smArray[0].value=1;
    smArray[1].row=0;
    smArray[1].col=2;
    smArray[1].value=2;
    smArray[2].row=1;
    smArray[2].col=1;
    smArray[2].value=3;
    smArray[3].row=1;
    smArray[3].col=3;
    smArray[3].value=4;
    smArray[4].row=2;
    smArray[4].col=2;
    smArray[4].value=5;
    
}

SparseMatrix SparseMatrix::FastTranspose()
{
    SparseMatrix b(cols,rows,terms);
    if(terms>0)
    {
        int *rowSize_rowStart=new int[2*cols];
        fill(rowSize_rowStart,rowSize_rowStart+2*cols,0);
        for(int i=0;i<terms;i++)
            rowSize_rowStart[smArray[i].col]++;
            
        rowSize_rowStart[terms]=0;
        for(int i=1;i<cols;i++)
            rowSize_rowStart[i+terms]=rowSize_rowStart[i+terms-1]+rowSize_rowStart[i-1];
            
            
        for(int i=0;i<terms;i++)
        {
            int j=rowSize_rowStart[smArray[i].col+terms];
            b.smArray[j].row=smArray[i].col;
            b.smArray[j].col=smArray[i].row;
            b.smArray[j].value=smArray[i].value;
            rowSize_rowStart[smArray[i].col+terms]++;
        }
        delete []rowSize_rowStart;
     
    }
    return b;
}

void SparseMatrix::Print()
{
    //打印稀疏矩阵的三元组
    for(int i=0;i<terms;i++)
        cout<<smArray[i].row<<"  "<<smArray[i].col<<"  "<<smArray[i].value<<endl;
}


int main()
{
    SparseMatrix a(3,4,5);
    cout<<"转置前："<<endl;
    a.Print();
    cout<<endl;
    SparseMatrix b=a.FastTranspose();
     cout<<"转置后："<<endl;
    b.Print();
    return 0;
    
}




