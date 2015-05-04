#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<vector>
int data[10];
int flag[10];
int n=0;
int total=0;
int target=100;
int count=0;
int coin[4]={1,2,5,10};
std::vector<int> answer;
void dfs(int step)
{
    int index=0;
    if(step==n)
    {
        /*数组中其实数值在不断变化，只有到第十个盒子的时候才打印出结果*/
        if(data[0]*100+data[1]*10+data[2]+data[3]*100+data[4]*10\
                +data[5]==data[6]*100+data[7]*10+data[8])
        {
            total++;
            std::cout<<data[0]<<data[1]<<data[2]\
                <<"+"<<data[3]<<data[4]<<data[5]<<"="<<data[6]<<data[7]<<data[8];
            std::cout<<std::endl;
        }//给定9个盒子任意填数,左边三个数相加等于右边
        /*
        for(index=0;index!=n;index++)
        {
            std::cout<<data[index];
        }
        std::cout<<std::endl;
        */
        return;
    }
    for(index=0;index!=n;index++)
    {
        if(flag[index]==0)
        {
            data[step]=index+1;
            flag[index]=1;
            dfs(step+1);
            flag[index]=0;
        }
    }
}
void dfs_coin(int step)//给定 1 2 5 10四种硬币 组合成任意数目的金额
{
    if(total==target)
    {
        count++;
        for(int index_t=0;index_t!=answer.size();index_t++)
        {
            std::cout<<answer[index_t]<<" ";
        }
        std::cout<<std::endl;
        return;
    }
    if(total>target)
    {
        return;
    }
    for(int index=step;index!=4;index++)
    {
        total+=coin[index];
        answer.push_back(coin[index]);
        dfs_coin(index);
        answer.pop_back();
        total-=coin[index];
    } 
}
int main(int argc,char** argv)
{
    std::cin>>n;
    dfs(0);
    std::cout<<"count :"<<count<<std::endl;
    return 0;
}
