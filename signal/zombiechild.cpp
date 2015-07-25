#include<iostream>
#include<sys/wait.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<cstdio>
#include<cstdlib>
#include<cstring>
void handle(int signum)
{
    sleep(100);
    int status;
    pid_t pid=waitpid(-1,&status,WNOHANG);
    //pid_t pid=waitpid(-1,NULL,WNOHANG);就可以回收全部僵尸进程
    if(WIFEXITED(status))
    {
        std::cout<<"recover child id "<<pid<<std::endl;/*回收的僵尸进程ID*/
        std::cout<<"child send:"<<WEXITSTATUS(status)<<std::endl;/*僵尸进程退出的值*/
    }
}
int main(int argc,char** argv)
{
    pid_t ch_id;
    struct sigaction act;
    bzero(&act,sizeof(act));
    act.sa_handler=handle;
    sigemptyset(&act.sa_mask);
    act.sa_flags=0;
    sigaction(SIGCHLD,&act,NULL);
    int num=10;
    while(num)
    {
        if(fork()==0)
        {
            std::cout<<"I'm zombie child process"<<std::endl;
            _exit(num);
        }
        std::cout<<"wait!"<<std::endl;
        sleep(2);
        num--;
    }
}

