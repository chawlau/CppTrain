#include<iostream>
#include<unistd.h>
#include<cstring>
#include<cstdio>
#include<cstdlib>
int main(int argc,char** argv)
{
    int n;
    int num1,num2;
    char line[1024];
    while((n=read(0,line,1024)!=0))
    {
        sscanf(line,"%d%d",&num1,&num2);
        sprintf(line,"%d\n",num1+num2);
        write(1,line,strlen(line));
    }
}
