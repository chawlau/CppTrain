#include<iostream>
int main(int argc,char** argv)
{
    int inf=100;
    int city_num,city_group;
    std::cin>>city_num>>city_group;
    int** data=new int*[10]();
    for(int index=0;index!=10;index++)
    {
        data[index]=new int[10]();
        for(int index_t=0;index_t!=10;index_t++)
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
    int city1,city2,dis;
    for(int index=0;index!=city_group;index++)
    {
        std::cin>>city1>>city2>>dis;
        data[city1][city2]=dis;
    }
    std::cout<<"----before-calculate----"<<std::endl;
    for(int index=0;index!=city_num;index++)
    {
        for(int index_t=0;index_t!=city_num;index_t++)
        {
            std::cout<<data[index][index_t]<<" ";
        }
        std::cout<<std::endl;
    }
    for(int index_k=0;index_k!=city_num;index_k++)
    {
        for(int index=0;index!=city_num;index++)
        {
            for(int index_t=0;index_t!=city_num;index_t++)
            {
                if(data[index][index_t]>data[index][index_k]+data[index_k][index_t])
                {
                    data[index][index_t]=data[index][index_k]+data[index_k][index_t];
                }
            }
        }
    }
    for(int index=0;index!=city_num;index++)
    {
        for(int index_t=0;index_t!=city_num;index_t++)
        {
            std::cout<<data[index][index_t]<<" ";
        }
        std::cout<<std::endl;
    }
}

