#include<iostream>
#define max(a,b) a>b?a:b
int N=4,V=6;
int weight[]={1,2,3,4};
int value[]={60,100,120,140};
void package()
{
    int** data=new int*[N+1]();
    for(int index=0;index!=N+1;index++)
    {
        data[index]=new int[V+1]();
        for(int index_t=0;index_t!=V+1;index_t++)
        {
            data[index][index_t]=0;
        }
    }
    for(int index=1;index!=N+1;index++)
    {
        for(int index_t=1;index_t!=V+1;index_t++)
        {
            if(index_t<weight[index-1])
            {
                data[index][index_t]=data[index-1][index_t];
            }
            else
            {
                int max1=data[index-1][index_t];
                int max2=data[index-1][index_t-weight[index-1]]+value[index-1];
                data[index][index_t]=max(max1,max2);
            }
        }
    }
    std::cout<<data[N][V]<<std::endl;
}
int main(int argc,char** argv)
{
    package();
}
