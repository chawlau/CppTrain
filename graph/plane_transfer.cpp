#include<iostream>
#include<vector>
#define N 100
struct Note
{
    int city_id;
    int times;
    int pre;
};
std::vector<int> list;
Note queue[100];
int book[100]={0};
int start=0;
int end=4;
int e[100][100];
int flag=0;
int city_num=5;
void transfer()
{
    int head=0,tail=0;
    queue[head].city_id=start;
    queue[head].times=0;
    queue[head].pre=-1;
    list.push_back(start);
    tail++;
    book[start]=1;
    int cur;
    while(head<tail)
    {
        cur=queue[head].city_id;
        for(int index=0;index!=city_num;index++)
        {
            if(e[cur][index]!=N&&book[index]==0)
            {
                list.push_back(index);
                queue[tail].city_id=index;
                queue[tail].times=queue[head].times+1;
                queue[tail].pre=cur;
                tail++;
                book[index]=1;
            }
            if(queue[tail-1].city_id==end)
            {
                flag=1;
                break;
            }
        }
        if(flag)
        {
            break;
        }
        head++;
    }
    std::cout<<queue[tail-1].times<<std::endl;
}
int main(int argc,char** argv)
{
    for(int index=0;index!=city_num;index++)
    {
        for(int index_t=0;index_t!=city_num;index_t++)
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
    int city1,city2;
    for(int index=0;index!=7;index++)
    {
        std::cin>>city1>>city2;
        e[city1][city2]=1;
        e[city2][city1]=1;
    }
    for(int index=0;index!=city_num;index++)
    {
        for(int index_t=0;index_t!=city_num;index_t++)
        {
            std::cout<<"  "<<e[index][index_t]<<" ";
        }
        std::cout<<std::endl;
    }
    std::cout<<std::endl;
    transfer();
}
