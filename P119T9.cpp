#include<iostream>
using namespace std;

class String
{
    public:
    String(const char *init,int m);   //构造函数,初始化字符串
    int FastFind(String &p);    //KMP算法
    int Length();               //返回字符串长度
    void FailFunction();

    private:
    const char *str;  //字符串
    int length; //字符串长度
    int *f;     //前缀函数值(失配函数)

};

String::String(const char *init,int m)
{
    str=new char[m];
    f=new int[m];
    str=init;
    length=m;
}

int String::Length()
{
    return length;
}

int String::FastFind(String &p)
{
    p.FailFunction();
    int PosP=0,PosS=0;
    int LengthP=p.Length(),LengthS=Length();
    while((PosP<LengthP)&&(PosS<LengthS))
    {
        if(p.str[PosP]==str[PosS])      //如果当前字符匹配
        {
            PosP++;
            PosS++;
        }
        else                //如果当前字符不匹配
        {
            if(PosP==0)
                PosS++;
            else PosP=p.f[PosP-1]+1;    //失配函数值+1
         
        }
    }
    if(PosP<LengthP)
        return -1;
    else return PosS-LengthP;
}

void String::FailFunction()
{
    int lengthP=Length();
    f[0]=-1;            //第0个前缀函数值
    for(int j=1;j<lengthP;j++)
    {
        int i=f[j-1];       //前一个前缀函数值
        while((str[j]!=str[i+1])&&(i>=0))       //如果当前字符不匹配
            i=f[i];         //失配函数值

        //修改处：增加了一个判断，如果当前字符匹配，但是下一个字符不匹配，那么前缀函数值+1
        if(str[j]==str[i+1] && str[i+1]!=str[j+1])         //如果当前字符匹配
            f[j]=i+1;               //前缀函数值+1

        //i=-1 时，即当前失配函数值为-1
        else f[j]=-1;               //前缀函数值置为-1
        
    }
}



int main()
{
    String s("dghabcabcajkabcabcacabdsd",26);
    String p("abcabcacab",10);
    cout<<s.FastFind(p)<<endl;
    return 0;
}
