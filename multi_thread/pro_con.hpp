#include <unistd.h>
#include <pthread.h>
#include <queue>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#define CAPACITY 100
#define PRODUCE 30
#define CONSUME 10
#define THREADNUM 60
namespace FACTORY
{
    struct Control
    {
        Control()
        {
            pthread_mutex_init(&mutex,NULL);
            pthread_cond_init(&pro_cond,NULL);
            pthread_cond_init(&con_cond,NULL);
        }
        void lock()
        {
            pthread_mutex_lock(&mutex);    
        }
        void unlock()
        {
            pthread_mutex_unlock(&mutex);
        }
        void wait(pthread_cond_t* cond)
        {
            pthread_cond_wait(cond,&mutex);
        }
        void notify(pthread_cond_t* cond)
        {
           pthread_cond_broadcast(cond); 
        }
        pthread_mutex_t mutex;
        pthread_cond_t pro_cond;
        pthread_cond_t con_cond;
        std::queue<int> work_queue;
    };
    class Factory
    {
        public:
            Factory():start_flag(0),stop_flag(0){}
            void start(Control* m_info)
            {
                if(start_flag==1)
                {
                    return;
                }
                start_flag=1;
                for(int index=0;index!=THREADNUM;index++)
                {
                    if(index<PRODUCE)
                    {
                        pthread_create(tid+index,NULL,produce,(void*)m_info);
                        continue;
                    }
                    pthread_create(tid+index,NULL,consume,(void*)m_info);
                }
            }
            void stop()
            {
                if(stop_flag==1)
                {
                    return;
                }
                stop_flag=1;
                for(int index=0;index!=THREADNUM;index++)
                {
                    if(index<PRODUCE)
                    {
                        pthread_join(tid[index],NULL);
                        continue;
                    }
                    pthread_join(tid[index],NULL);
                }
            }
            static void* produce(void* arg)
            {
                Control* info=(Control*)arg;
                while(1)
                {
                    pthread_mutex_lock(&info->mutex);
                    while((info->work_queue).size()==CAPACITY)
                    {
                        std::cout<<"work queue is full"<<std::endl;
                        pthread_cond_wait(&info->con_cond,&info->mutex);
                    }
                    int value=rand()%100+1;
                    (info->work_queue).push(value);
                    std::cout<<"put data int work line :  "<<pthread_self()<<std::endl;
                    pthread_cond_broadcast(&info->con_cond);
                    pthread_mutex_unlock(&info->mutex);
                    sleep(rand()%3+1);
                }
            }
            static void* consume(void* arg)
            {
                Control* info=(Control*)arg;
                while(1)
                {
                    pthread_mutex_lock(&info->mutex);
                    while((info->work_queue).empty())
                    {
                        std::cout<<"work queue is empty"<<std::endl;
                        pthread_cond_wait(&info->pro_cond,&info->mutex);
                    }
                    int value=(info->work_queue).front();
                    (info->work_queue).pop();
                    std::cout<<"get data :"<<value<<" from work line :  "<<pthread_self()<<std::endl;
                    pthread_cond_broadcast(&info->pro_cond);
                    pthread_mutex_unlock(&info->mutex);
                    sleep(rand()%3+1);
                }
            }
        private:
            pthread_t tid[THREADNUM];
            int start_flag;
            int stop_flag;
    };
}
