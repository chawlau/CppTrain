#include<unistd.h>
#include<pthread.h>
#include<cstdio>
#include<cstdlib>
#include<iostream>
struct Data
{
    Data(const int& data):value(data)
    {
        pthread_mutex_init(&mutex,NULL);
        pthread_cond_init(&cond1,NULL);
        pthread_cond_init(&cond2,NULL);
    }
    pthread_mutex_t mutex;
    pthread_cond_t cond1;
    pthread_cond_t cond2;
    int value;
};
void* sell(void* arg)
{
    Data* info=(Data*)arg;
    while(1)
    {
        pthread_mutex_lock(&info->mutex);
        while(info->value!=0)
        {
            std::cout<<"wait for add tickets....."<<std::endl;
            pthread_cond_wait(&info->cond1,&info->mutex);
            std::cout<<"ticket empty"<<std::endl;
        }
        info->value++;
        std::cout<<"add ticket......"<<pthread_self()<<std::endl;
        pthread_cond_broadcast(&info->cond2);
        pthread_mutex_unlock(&info->mutex);
        sleep(3);
    }
}
void* buy(void* arg)
{
    Data* info=(Data*)arg;
    while(1)
    {
        pthread_mutex_lock(&info->mutex);
        while(info->value==0)
        {
            pthread_cond_broadcast(&info->cond1);
            std::cout<<"wait for ticket "<<std::endl;
            pthread_cond_wait(&info->cond2,&info->mutex);
        }
        info->value--;
        std::cout<<"get tickets : "<<pthread_self()<<std::endl;
        pthread_mutex_unlock(&info->mutex);
        sleep(3);
    }
}
int main(int argc,char** argv)
{
    Data* info=new Data(0);
    pthread_t tid[20];
    for(int index=0;index!=20;index++)
    {
        if(index<10)
        {
            pthread_create(tid+index,NULL,sell,(void*)info);
            continue;
        }
        pthread_create(tid+index,NULL,buy,(void*)info);
    }
    while(1);
    for(int index=0;index!=20;index++)
    {
        pthread_join(tid[index],NULL);
    }
    pthread_mutex_destroy(&info->mutex);
    pthread_cond_destroy(&info->cond1);
    pthread_cond_destroy(&info->cond2);
}

