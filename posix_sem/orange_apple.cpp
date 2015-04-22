#include<unistd.h>
#include<semaphore.h>
#include<pthread.h>
#include<signal.h>
#include<cstring>
#include<cstdlib>
#include<cstdio>
#include<iostream>
struct Syn_info
{
    Syn_info()
    {
        sem_init(&plate,0,1);
        sem_init(&orange,0,0);
        sem_init(&apple,0,0);
    }
    sem_t plate;
    sem_t orange;
    sem_t apple;
};
void* father(void* arg)
{
    Syn_info* info=(Syn_info*)arg;
    while(1)
    {
        sleep(1);
        sem_wait(&info->plate);
        std::cout<<"father put apple in the plate"<<std::endl;
        sem_post(&info->apple);
    }
}
void* monther(void* arg)
{
    Syn_info* info=(Syn_info*)arg;
    while(1)
    {
        sleep(1);
        sem_wait(&info->plate);
        std::cout<<"monther put orange in the plate"<<std::endl;
        sem_post(&info->orange);
    }
}
void* son(void* arg)
{
    Syn_info* info=(Syn_info*)arg;
    while(1)
    {
        sleep(1);
        sem_wait(&info->apple);
        std::cout<<"son get apple from plate"<<std::endl;
        sem_post(&info->plate);
    }
}
void* daughter(void* arg)
{
    Syn_info* info=(Syn_info*)arg;
    while(1)
    {
        sleep(1);
        sem_wait(&info->orange);
        std::cout<<"daughter get orange from plate"<<std::endl;
        sem_post(&info->plate);
    }
}
Syn_info* temp;
void handle(int signum)
{
    std::cout<<"quit"<<std::endl;
    sem_destroy(&temp->plate);
    sem_destroy(&temp->apple);
    sem_destroy(&temp->orange);
    _exit(1);
}
int main(int argc,char** argv)
{
    struct sigaction act;
    act.sa_handler=handle;
    act.sa_flags=0;
    sigaction(SIGINT,&act,NULL);
    pthread_t* tid=new pthread_t[10]();
    Syn_info* info=new Syn_info();
    temp=info;
    pthread_create(tid+1,NULL,father,(void*)info);
    pthread_create(tid+2,NULL,monther,(void*)info);
    pthread_create(tid+3,NULL,son,(void*)info);
    pthread_create(tid+4,NULL,daughter,(void*)info);
    while(1);
}
