#include<iostream>
#include<vector>
#define N 100
int ans[N];
int data[10]={1,2,3,4,5};
int number=5;
void com(int depth)
{
    if(depth==number)
    {
        for(int index=0;index!=N;index++)
        {
            if(ans[index]!=0)
            {
                std::cout<<index+1;
            }
        }
        std::cout<<std::endl;
        return;
    }
    ans[depth]=0;
    com(depth+1);
    ans[depth]=1;
    com(depth+1);
}
int main(int argc,char** argv)
{
    com(0);
}
