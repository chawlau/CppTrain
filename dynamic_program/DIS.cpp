#include<iostream>
#include<string>
#include<cstdio>
#include<cstdlib>
#define min(first,second,third)  (first<second?first:second)<third?(first<second?first:second):third
//int distance(const char* str1,const char* str2)
int distance(const std::string& str1,const std::string& str2)
{
    int m=str1.size();
    int n=str2.size();
    std::cout<<m<<" "<<n<<std::endl;
    int** data=new int*[m+1]();
    for(int index=0;index!=m+1;index++)
    {
        data[index]=new int[n+1]();
    }
    for(int index=0;index!=m+1;index++)
    {
        data[index][0]=index;
    }
    for(int index=0;index!=n+1;index++)
    {
        data[0][index]=index;
    }
    for(int index=1;index!=m+1;index++)
    {
        for(int index_t=1;index_t!=n+1;index_t++)
        {
            if(str1[index-1]==str2[index_t-1])
            {
                data[index][index_t]=data[index-1][index_t-1];
            }
            else
            {
                int minvalue=min(data[index-1][index_t],data[index][index_t-1],data[index-1][index_t-1]);
                data[index][index_t]=minvalue+1;
            }
        }
    }
    int dis= data[m][n];
    for(int index=0;index!=m+1;index++)
    {
        delete []data[index];
    }
    delete [] data;
    return dis;
}
int main(int argc,char** argv)
{
    std::string str1(argv[1]);
    std::string str2(argv[2]);
    std::cout<<distance(str2.c_str(),str1.c_str())<<std::endl;
    //std::cout<<distance(str1,str2)<<std::endl;
}
