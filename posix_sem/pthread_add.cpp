#include<iostream>
#include<pthread.h>
#include<cstdlib>
#include<cstdio>
#include<ctime>
void* add(void* arg)
{
    int* sum=new int();
    int* temp=(int*)arg;
    for(int index=0;index!=50;index++)
    {
        *sum+=temp[index];
    }
    std::cout<<"sum is :"<<*sum<<std::endl;
    pthread_exit((void*)sum);
}
void* add2(void* arg)
{
    long long sum=0;
    for(int index=0;index!=50;index++)
    {
        sum+=((int*)arg)[index];
    }
    std::cout<<"sum is :"<<sum<<std::endl;
    pthread_exit((void*)sum);
}
int main(int argc,char** argv)
{
    int* data=new int[100]();
    int sum=0;
    for(int index=0;index!=100;index++)
    {
        data[index]=rand()%100+1;
        sum+=data[index];
        if(index==49)
        {
            std::cout<<"first 50 sum "<<sum<<std::endl;
        }
    }
    std::cout<<"result :"<<sum<<std::endl;
    //int* sum1=NULL;
    //int* sum2=NULL;
    long long sum1=0;/*64位机器必须8个字节来存储*/
    long long sum2=0;
    pthread_t tid1,tid2;
    pthread_create(&tid1,NULL,add2,(void*)&data[0]);
    pthread_create(&tid2,NULL,add2,(void*)&data[50]);
    pthread_join(tid1,(void**)&sum1);
    pthread_join(tid2,(void**)&sum2);
    std::cout<<"sum1:"<<sum1<<" sum2:"<<sum2<<std::endl;
    //delete sum1;
    //delete sum2;
    //std::cout<<"sum is :"<<sum1+sum2<<std::endl;
}
