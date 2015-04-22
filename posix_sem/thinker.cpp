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
        sem_init(&mutex,0,1);
        for(int index=0;index!=5;index++)
        {
            sem_init(chop+index,0,1);
        }
        count=0;
    }
    sem_t chop[5];
    sem_t mutex;
    int count;
    int id;
};
/*哲学家进餐问题*/
void* thinker(void* arg)
{
    Syn_info* info=(Syn_info*)arg;
    while(1)
    {
        sem_wait(&info->mutex);
        sem_wait(&info->chop[info->id]);
        sem_post(&info->chop[(info->id+1)%5]);
        sem_post(&info->mutex);
        std::cout<<info->id<<" th thinker eating ......"<<std::endl;
        sem_post(&info->chop[info->id]);
        sem_post(&info->chop[(info->id+1)%5]);
        std::cout<<info->id<<"th thinker thinking ......."<<std::endl;
    }
}
int main(int argc,char** argv)
{
    pthread_t* tid=new pthread_t[10]();
    Syn_info* info=new Syn_info();
    for(int index=0;index!=5;index++)
    {
        info->id=index;
        pthread_create(tid+index,NULL,thinker,(void*)info);
    }
    while(1);
}
