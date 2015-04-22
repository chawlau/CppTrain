#include<unistd.h>
#include<semaphore.h>
#include<pthread.h>
#include<signal.h>
#include<cstdlib>
#include<cstdio>
#include<ctime>
#include<iostream>
struct Syn_info
{
    Syn_info()
    {
        sem_init(&mutex_1,0,1);
        sem_init(&mutex_2,0,1);
        sem_init(&mutex_3,0,1);
        count=0;
    }
    sem_t mutex_1;
    sem_t mutex_2;
    sem_t mutex_3;
    sem_t finish;
    int count;
};
/*读者写者问题*/
void* offer(void* arg)
{
    Syn_info* info=(Syn_info*)arg;
    int random=0;
    while(1)
    {
        random=rand()%3+1;
        if(random==1)
        {
            std::cout<<"off offer 1"<<std::endl;
            sem_post(&info->mutex_1);
        }
        else if(random==2)
        {
            std::cout<<"off offer 2"<<std::endl;
            sem_post(&info->mutex_2);
        }
        else
        {
            std::cout<<"off offer 3"<<std::endl;
            sem_post(&info->mutex_3);
        }
        sem_wait(&info->finish);
    }
}
void* smoke1(void* arg)
{
    Syn_info* info=(Syn_info*)arg;
    while(1)
    {
        sem_wait(&info->mutex_1);
        std::cout<<"offer 1 smoke"<<std::endl;
        sem_post(&info->finish);
    }
}
void* smoke2(void* arg)
{
    Syn_info* info=(Syn_info*)arg;
    while(1)
    {
        sem_wait(&info->mutex_2);
        std::cout<<"offer 2 smoke"<<std::endl;
        sem_post(&info->finish);
    }
}
void* smoke3(void* arg)
{
    Syn_info* info=(Syn_info*)arg;
    while(1)
    {
        sem_wait(&info->mutex_3);
        std::cout<<"offer 3 smoke"<<std::endl;
        sem_post(&info->finish);
    }
}
int main(int argc,char** argv)
{
    pthread_t* tid=new pthread_t[10]();
    Syn_info* info=new Syn_info();
    pthread_create(tid+1,NULL,offer,(void*)info);
    pthread_create(tid+2,NULL,smoke1,(void*)info);
    pthread_create(tid+3,NULL,smoke2,(void*)info);
    pthread_create(tid+4,NULL,smoke3,(void*)info);
    while(1);
}
