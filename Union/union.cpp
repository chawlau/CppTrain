#include<iostream>
#include<cstdio>
#include<cstdlib>
namespace UNION
{
    struct Union
    {
        Union(int num,int pair):m_num(num),m_pair(pair)
        {
            set=new int[num+1]();
            init();
        }
        void init()
        {
            for(int index=1;index!=m_num+1;index++)
            {
                set[index]=index;
                std::cout<<index<<":"<<set[index]<<std::endl;
            } 
        }
        int get_leader(int index)
        {
            if(set[index]==index)
            {
                return index;
            }
            else
            {
                return  get_leader(set[index]);
            }
        }
        int get_leader_t(int index)
        {
            int leader=index;
            while(set[leader]!=leader)//找出节点的代表
            {
                leader=set[leader];
            }
            return leader;
        }
        void merge(int left,int right)
        {
            int leader1,leader2;
            leader1=get_leader(left);
            leader2=get_leader(right);
            if(leader1!=leader2)
            {
                set[leader2]=leader1;
            }
            /*
            for(int index=0;index!=m_num+1;index++)
            {
                std::cout<<" "<<index<<":"<<set[index]<<"";
            }
            std::cout<<std::endl;
            */
            return;
        }
        int* set;
        int m_num;
        int m_pair;
    };
}
int main(int argc,char** argv)
{
    UNION::Union* test=new UNION::Union(atoi(argv[1]),atoi(argv[2]));
    int count=0;
    std::cout<<"input relation "<<std::endl;
    for(int index=0;index!=test->m_pair;index++)
    {
        int left=0;
        int right=0;
        std::cin>>left>>right;
        test->merge(left,right);
    }
    for(int index_t=1;index_t!=test->m_num+1;index_t++)
    {
        if(test->set[index_t]==index_t)
        {
            count++;
        }
        std::cout<<index_t<<":"<<test->set[index_t]<<" ";
    }
    std::cout<<std::endl;
    std::cout<<"group num :"<<count<<std::endl;
}
