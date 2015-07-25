#include<iostream>
#include<cstdio>
#include<cstdlib>
int main(int argc,char** argv)
{
    int m=5,n=6;
    int **a= new int* [m]();//C++手法开辟
    for(int index=0;index!=m;index++)
    {
        a[index]=new int[n]();
    }
    std::cout<<"alloacte C++ memory"<<std::endl;
    for(int index=0;index!=m;index++)
    {
        delete []a[index];
    }
    delete []a;//C++手法释放
    std::cout<<"free C++ new memrory"<<std::endl;//C语言开辟和释放空间
    int** b=(int**)malloc(5*sizeof(int*));
    for(int index=0;index!=5;index++)
    {
        b[index]=(int*)malloc(6*sizeof(int));
    }
    std::cout<<"allocate C malloc memory"<<std::endl;
    for(int index=0;index!=5;index++)
    {
        free(b[index]);
    }
    free(b);
    std::cout<<"free C malloc memory"<<std::endl;
    int** c=(int**)calloc(5,sizeof(int*));
    for(int index=0;index!=5;index++)
    {
        c[index]=(int*)calloc(6,sizeof(int));
    }
    std::cout<<"allocate C calloc memory"<<std::endl;
    for(int index=0;index!=5;index++)
    {
        free(c[index]);
    }
    free(c);
    std::cout<<"free C calloc memory"<<std::endl;

}
