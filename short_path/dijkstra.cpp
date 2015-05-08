#include<iostream>
int main(int argc,char** argv)
{
    int inf=100;
    int node_num,node_group;
    std::cin>>node_num>>node_group;
    int** data=new int*[node_num]();//开辟动态的二维数组
    for(int index=0;index!=node_num;index++)//初始化边的二维数组
    {
        data[index]=new int[node_num]();
        for(int index_t=0;index_t!=node_num;index_t++)
        {
            if(index==index_t)
            {
                data[index][index_t]=0;
            }
            else
            {
                data[index][index_t]=inf;
            }
        }
    }
    int start,end,value;
    for(int index=0;index!=node_group;index++)//输入边和定点的数组
    {
        std::cin>>start>>end>>value;
        data[start][end]=value;
    }
    int* dis=new int[node_num]();
    for(int index=0;index!=node_num;index++)//初始化0号顶点到其他点的距离
    {
        dis[index]=data[0][index];
    }
    int* book=new int[100]();
    for(int index=0;index!=100;index++)//初始化标记数组
    {
        book[index]=0;
    }
    book[0]=1;
    int min_index;//数组中最小的值的下标
    int min;
    for(int times=0;times!=node_num-1;times++)
    {
        min=inf;
        for(int index_t=0;index_t!=node_num;index_t++)
        {
            if(book[index_t]==0&&dis[index_t]<min)
            {
                min=dis[index_t];
                min_index=index_t;
            }
        }
        book[min_index]=1;//将中转节点加入标记数组表述已经添加到路径中
        for(int arrive=0;arrive!=node_num;arrive++)
        {
            if(data[min_index][arrive]<inf)
            {
                if(dis[arrive]>dis[min_index]+data[min_index][arrive])
                {
                    dis[arrive]=dis[min_index]+data[min_index][arrive];
                }
            }
        }
    }
    for(int index=0;index!=node_num;index++)
    {
        std::cout<<dis[index]<<" ";
    }
    std::cout<<std::endl;
    /*释放内存*/
    for(int index=0;index!=node_num;index++)
    {
        delete []data[index];
    }
    delete []data;
}
