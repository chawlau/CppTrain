#include<iostream>
#define N 100
int min=100;
int book[100],e[100][100];
void dfs(int cur,int dis)
{
    if(dis>min)//还没遍历到终点城市距离已经大于最小的距离，则不需要比了
    {
        return;
    }
    if(cur==4)
    {
        if(dis<min)
        {
            min=dis;
        }
        return;
    }
    for(int index=0;index!=5;index++)
    {
        if(e[cur][index]!=N&&book[index]!=1)
        {
            book[index]=1;
            dfs(index,dis+e[cur][index]);
            book[index]=0;
        }
    }
    return;
}
int main(int argc,char** argv)
{
    int m,n;
    std::cin>>m>>n;
    for(int index=0;index!=m;index++)
    {
        for(int index_t=0;index_t!=m;index_t++)
        {
            if(index==index_t)
            {
                e[index][index_t]=0;
            }
            else
            {
                e[index][index_t]=N;
            }
        }
    }
    int arr,row,data;
    for(int index=0;index!=n;index++)
    {
        std::cin>>arr>>row>>data;
        e[arr][row]=data;
    }
    for(int index=0;index!=m;index++)
    {
        for(int index_t=0;index_t!=m;index_t++)
        {
            std::cout<<" "<<e[index][index_t]<<" ";
        }
        std::cout<<std::endl;
    }
    std::cout<<std::endl;
    book[0]=1;
    dfs(0,0);
    std::cout<<"min distance: "<<min<<std::endl;
}
