#include<iostream>
int a1=0;
int a2;
void child()
{
    int a=5;
    std::cout<<a<<std::endl;
}
int main(int argc,char** argv)
{
    int a4=0;
    static int a5=6;
    int* p1=new int(5);
    child();
    while(1);
}
