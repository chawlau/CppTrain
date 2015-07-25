#include<iostream>
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/wait.h>
#include<unistd.h>
#include<signal.h>
#include<ctime>
#include<cstdlib>
#include<cstdio>
void timeout(int sig)
{
    if(sig==SIGALRM)
    {
        std::cout<<"timeout"<<std::endl;
        alarm(2);
    }
}
int main(int argc,char** argv)
{
    struct sigaction act;
    act.sa_handler=timeout;
    sigemptyset(&act.sa_mask);
    act.sa_flags=0;
    sigaction(SIGALRM,&act,NULL);
    alarm(1);
    for(int index=0;index!=3;index++)
    {
        std::cout<<"wait "<<std::endl;
        sleep(100);
        
    }
    return 0;
}
