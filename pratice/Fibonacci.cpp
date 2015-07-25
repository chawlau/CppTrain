#include<iostream>
#define N 10
template<typename T> T recurse(T num)
{
    if(num==0) return 0;
    if(num==1) return 1;
    return recurse(num-1)+recurse(num-2);
}
int data[100];
int Fun(int num)
{
    int index=0;
    data[0]=1;
    data[1]=2;
    for(index=2;index!=num;index++)
    {
        data[index]=data[index-1]+data[index-2];
    }
    std::cout<<data[index-1]<<std::endl;
}
int main(int argc,char** argv)
{
    Fun(4);
}
/*
int main(int argc,char** argv)
{
    int** result=new int*[N+1]();
    for(int index=0;index!=N+1;index++)
    {
        result[index]=new int[N+1];
    }
    result[0][0]=0;
    result[1][1]=1;
    for(int index_i=2;index_i!=N+1;index_i++)
    {
        for(int index_j=2;index_j!=N+1;index_j++)
        {
            if(index_i==index_j)
            {
                result[index_i][index_j]=result[index_i-1][index_j-1]+result[index_i-2][index_j-2];
            }
            else
            {
                result[index_i][index_j]=0;
            }
        }
    }
    std::cout<<result[N][N]<<std::endl;
}
*/
