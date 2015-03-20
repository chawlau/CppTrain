#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
void right_move(char* str)/*向右移动*/
{
    char* temp=str+strlen(str)-1;
    char data=*temp;
    while(temp!=str)
    {
        *temp=*(temp-1);
        temp--;
    }
    *str=data;
    std::cout<<str<<std::endl;
}
void cycle_right_move(char* str,int num)
{
    num=num%strlen(str);
    while(num--)
    {
        right_move(str);
    }
}
void left_move(char* str)/*向左移动*/
{
    char* temp=str;
    char data=*temp;
    while(*(temp+1)!='\0')
    {
        *temp=*(temp+1);
        temp++;
    }
    *(str+strlen(str)-1)=data;
    std::cout<<str<<std::endl;
}
void cycle_left_move(char* str,int num)
{
    num=num%strlen(str);
    while(num--)
    {
        left_move(str);
    }
}
