#include<iostream>
int main(int argc,char** argv)
{
    int inf=100;
    int vertex_num,edge_num;
    std::cin>>vertex_num>>edge_num;
    int* left=new int[edge_num]();
    int* right=new int[edge_num]();
    int* weight=new int[edge_num]();
    for(int index=0;index!=edge_num;index++)//初始化边和顶点
    {
        std::cin>>left[index]>>right[index]>>weight[index];
    }
    int* dis=new int[vertex_num]();//初始化点纪录路径的数组
    for(int index=0;index!=vertex_num;index++)
    {
        dis[index]=inf;
    }
    dis[0]=0;
    int check;//检测是否发生边的松弛
    for(int times=0;times!=edge_num-1;times++)
    {
        check=0;
        for(int index=0;index!=edge_num;index++)
        {
            if(dis[right[index]]>dis[left[index]]+weight[index])
            {
                dis[right[index]]=dis[left[index]]+weight[index];
                check=1;
            }
        }
        if(check==0)
        {
            break;
        }
    }
    int flag=0;
    for(int index=0;index!=edge_num;index++)
    {
        if(dis[right[index]]>dis[left[index]]+weight[index])
        {
            flag=1;
        }
    }
    if(flag)
    {
        std::cout<<" this graph has loop"<<std::endl;
    }
    else
    {
        std::cout<<"result is :";
        for(int index=0;index!=edge_num;index++)
        {
            std::cout<<" "<<dis[index]<<" ";
        }
        std::cout<<std::endl;
    }
    delete [] left;
    delete [] right;
    delete [] dis;
    delete [] weight;
}
