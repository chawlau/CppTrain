#include<iostream>
template <typename T>
T add(int num,...)
{
    T sum=0;
    T* p=((T*)&num+1);
    for(int index=0;index!=num;index++)
    {
        sum+=*p++;
    }
    return sum;
}
int main(int argc,char** argv)
{
    int i=1,j=2,k=3;
    std::cout<<add<int>(3,i,j,k);
    return 0;
}

