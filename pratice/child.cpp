#include<unistd.h>
#include<sys/wait.h>
#include<iostream>
void pr_exit(int& status)
{
    if(WIFEXITED(status))
    {
        std::cout<<"normal child process exit,status is"<<WEXITSTATUS(status)<<std::endl;
    }
    else if(WIFSIGNALED(status))
    {
        std::cout<<"abnormal termination,signal num is "<<WTERMSIG(status)<<std::endl;
    }
    else if(WIFSTOPPED(status))
    {
        std::cout<<"child stopped ,sig num ="<<WSTOPSIG(status)<<std::endl;
    }
}
int main(int argc,char** argv)
{
    pid_t pid;
    int status;
    if((pid=fork())==0)
    {
        exit(1);
    }
    pr_exit(status);
}
