#include<iostream>
#include<cstring>
void change(char*& p1,char*& p2)
{
    char* temp=p1;
    p1=p2;
    p2=temp;
}
int main(int argc,char** argv)
{
    char* str1="hello world";
    char* str2="world hello";
    change(str1,str2);
    std::cout<<str1<<std::endl;
    std::cout<<str2<<std::endl;
}

