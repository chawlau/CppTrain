#include<unistd.h>
#include<semaphore.h>
#include<pthread.h>
#include<signal.h>
#include<cstring>
#include<cstdlib>
#include<cstdio>
#include<ctime>
#include<iostream>
struct Syn_info
{
    Syn_info()
    {
        sem_init(&mutex,0,1);
        sem_init(&customer,0,0);
        sem_init(&barber,0,0);
        count=10;
        wait=0;
    }
    sem_t mutex;
    sem_t customer;
    sem_t barber;
    int count;
    int wait;
};
/*理发师问题*/
void* barber(void* arg)
{
    Syn_info* info=(Syn_info*)arg;
    while(1)
    {
        sem_wait(&info->customer);
        sem_wait(&info->mutex);
        info->wait--;
        sem_post(&info->barber);
        sem_post(&info->mutex);
        std::cout<<"hair cuting....."<<std::endl;
    }
}
void* customer(void* arg)
{
    Syn_info* info=(Syn_info*)arg;
    while(1)
    {
        sem_wait(&info->mutex);
        if(info->wait<info->count)
        {
            info->wait++;
            std::cout<<info->wait<<" customer waiting for haircut"<<std::endl;
            sem_post(&info->customer);
            sem_post(&info->mutex);
            sem_wait(&info->barber);
            std::cout<<"waiting for hair cut"<<std::endl;
        }
        else
        {
            sem_post(&info->mutex);
        }
    }
}
int main(int argc,char** argv)
{
    pthread_t* tid=new pthread_t[10]();
    Syn_info* info=new Syn_info();
    pthread_create(tid,NULL,barber,(void*)info);
    for(int index=1;index!=10;index++)
    {
        pthread_create(tid+index,NULL,customer,(void*)info);
    }
    while(1);
}
