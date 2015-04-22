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
    Syn_info(const int& m_value):value(m_value)
    {
        sem_init(&mutex,0,1);
        sem_init(&cond,0,0);
    }
    sem_t mutex;
    sem_t cond;
    int value;
};
void* sell(void* arg)
{
    Syn_info* info=(Syn_info*)arg;
    while(1)
    {
        sem_wait(&info->cond);
        info->value+=30;
        sem_post(&info->mutex);
    }
}
void* buy(void* arg)
{
    Syn_info* info=(Syn_info*)arg;
    while(1)
    {
        sem_wait(&info->mutex);
        if(info->value>0)
        {
            info->value--;
            std::cout<<"left tickets "<<info->value<<" "<<pthread_self()<<std::endl;
            sem_post(&info->mutex);
        }
        else
        {
            sem_post(&info->cond);
        }
    }
}
Syn_info* temp;
void handle(int signum)
{
    std::cout<<"quit"<<std::endl;
    sem_destroy(&temp->mutex);
    sem_destroy(&temp->cond);
    _exit(1);
}
int main(int argc,char** argv)
{
    struct sigaction act;
    act.sa_handler=handle;
    act.sa_flags=0;
    sigaction(SIGINT,&act,NULL);
    pthread_t* tid=new pthread_t[10]();
    Syn_info* info=new Syn_info(30);
    temp=info;
    pthread_create(tid,NULL,sell,(void*)info);
    for(int index=1;index!=10;index++)
    {
        pthread_create(tid+index,NULL,buy,(void*)info);
    }
    while(1);
}
