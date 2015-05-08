#include<iostream>
#include<set>
#include<cstring>
#define max(a,b)  a>b?a:b
std::string result;
int LCS(const char* str1,const char* str2)
{
    if(!str1||!str2)
    {
        return 0;
    }
    int m=strlen(str1);
    int n=strlen(str2);
    int** data=new int*[m+1]();
    for(int index=0;index!=m+1;index++)
    {
        data[index]=new int[n];
    }
    for(int index=0;index!=m+1;index++)
    {
        data[index][0]=0;
    }
    for(int index=0;index!=n+1;index++)
    {
        data[0][index]=0;
    }
    for(int index=1;index!=m+1;index++)
    {
        for(int index_t=1;index_t!=n+1;index_t++)
        {
            if(str1[index-1]==str2[index_t-1])
            {
                result+=str2[index_t-1];
                data[index][index_t]=data[index-1][index_t-1]+1;
            }
            else
            {
                data[index][index_t]=max(data[index-1][index_t],data[index][index_t-1]);
            }
        }
    }
    return data[m][n];
}
int main(int argc,char** argv)
{
    std::cout<<LCS("hello1","hello")<<std::endl;
    std::cout<<result<<std::endl;
}
