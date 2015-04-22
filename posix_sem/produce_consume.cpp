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
        sem_init(&mutex_full,0,0);
        sem_init(&mutex_empty,0,10);
        sem_init(&mutex,0,1);
        count=0;
    }
    sem_t mutex_full;
    sem_t mutex_empty;
    sem_t mutex;
    int count;
};
/*多个生产者消费者问题*/
void* producen(void* arg)
{
    Syn_info* info=(Syn_info*)arg;
    while(1)
    {
        std::cout<<"produe product "<<std::endl;
        sem_wait(&info->mutex_empty);
        sem_wait(&info->mutex);
        if(info->count<10)
        {
            info->count++;
            std::cout<<"producer put product in work line"<<std::endl;
            std::cout<<"free product num for produce: "<<10-info->count<<std::endl;
            sem_post(&info->mutex);
            sem_post(&info->mutex_full);
        }
        else
        {
            std::cout<<"no free space for producer to put product"<<std::endl;
            sem_post(&info->mutex);
        }
        sleep(1);
    }
}
void* consumen(void* arg)
{
    Syn_info* info=(Syn_info*)arg;
    while(1)
    {
        sem_wait(&info->mutex_full);
        sem_wait(&info->mutex);
        if(info->count>0)
        {
            info->count--;
            std::cout<<"consumer get product from work line"<<std::endl;
            std::cout<<"product on the work line num: "<<info->count<<std::endl;
            sem_post(&info->mutex);
            sem_post(&info->mutex_empty);
        }
        else
        {
            std::cout<<"no product on work line"<<std::endl;
            sem_post(&info->mutex);
        }
        sleep(1);
    }
}
/*一个生产者消费者问题*/
void* produce(void* arg)
{
    Syn_info* info=(Syn_info*)arg;
    while(1)
    {
        std::cout<<"produe product "<<std::endl;
        sem_wait(&info->mutex_empty);
        sem_wait(&info->mutex);
        std::cout<<"put product in work line"<<std::endl;
        sem_post(&info->mutex);
        sem_post(&info->mutex_full);
        sleep(1);
    }
}
void* consume(void* arg)
{
    Syn_info* info=(Syn_info*)arg;
    while(1)
    {
        sem_wait(&info->mutex_full);
        sem_wait(&info->mutex);
        std::cout<<"product on the work line num: "<<std::endl;
        sem_post(&info->mutex);
        sem_post(&info->mutex_empty);
        std::cout<<"consume the product"<<std::endl;
        sleep(1);
    }
}
int main(int argc,char** argv)
{
    pthread_t* tid=new pthread_t[10]();
    Syn_info* info=new Syn_info();
    for(int index=0;index!=20;index++)
    {
        if(index<10)
        {
            pthread_create(tid+index,NULL,produce,(void*)info);
        }
        else
        {
            pthread_create(tid+index,NULL,consume,(void*)info);
        }
    }
    while(1);
}
