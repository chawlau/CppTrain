#include<iostream>
#include<cstdio>
#include<unistd.h>
void start()
{
    char *cmd[]={"hello",NULL};
    execv("hello",cmd);
}
int main(int argc,char** argv)
{
    for(int index=0;index!=100;index++)
    {
        if(fork()==0)
        {
           start(); 
        }
    }
}
