#include<iostream>
#include<unistd.h>
#include<cstring>
#include<cstdio>
#include<cstdlib>
int main(int argc,char** argv)
{
    int n;
    int fd[2];
    pid_t pid;
    char line[1024];
    pipe(fd);
    char str[]="hello";
    char str1[100];
    write(fd[1],str,strlen(str));
    read(fd[0],str1,1024);
    std::cout<<str1<<std::endl;
    /*
    if(fork()==0)
    {
        close(fd[1]);
        while((n=read(fd[0],line,1024))!=0)
        {
            write(1,line,n);
            std::cout<<"child :";
            std::cout<<std::endl;
        }
    }
    close(fd[0]);
    while((n=read(0,line,1024))!=0)
    {
        write(fd[1],line,n);
    }*/
}
