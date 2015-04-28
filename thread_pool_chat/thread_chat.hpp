#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <queue>
#include <list>
#include <iostream>
#include <sstream>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <string.h>
#define CAPACITY 100
#define PRODUCE 30
#define CONSUME 10
#define THREADNUM 10
namespace EPOLL
{
    class Epoll;
}
namespace FACTORY
{
    struct Control
    {
        Control()
        {
            pthread_mutex_init(&mutex,NULL);
            pthread_cond_init(&cond,NULL);
        }
        void lock()
        {
            pthread_mutex_lock(&mutex);    
        }
        void unlock()
        {
            pthread_mutex_unlock(&mutex);
        }
        void wait()
        {
            pthread_cond_wait(&cond,&mutex);
        }
        void notify()
        {
            pthread_cond_broadcast(&cond); 
        }
        pthread_mutex_t mutex;
        pthread_cond_t cond;
        std::queue<int> work_queue;
        std::list<int> online_client;
    };
    class Thread_run
    {
        public:
            friend class EPOLL::Epoll;
            Thread_run(SOCKET::Socket* m_socket):socket(m_socket){}
            void set_info(Control* m_info)
            {
                info=m_info;
            }
            void put_sockfd(int sockfd)/*client sockfd放入工作队列*/
            {
                info->lock();
                (info->work_queue).push(sockfd);
                info->notify();
                info->unlock();
            }
            void get_sockfd(int& sockfd)/*从工作队列取出client sockfd*/
            {
                info->lock();
                while((info->work_queue).empty())
                {
                    info->wait();
                }
                sockfd=(info->work_queue).front();
                (info->work_queue).pop();
                info->notify();
                info->unlock();
            }
            void handle_chat(int& sockfd)
            {
                char recv_buf[1024]="";
                int read_ret;
                while((read_ret=socket->socket_recv(sockfd,recv_buf))!=0)
                {
                    if(read_ret==-1&&errno!=EAGAIN)
                    {
                        perror("client closed");
                        break;
                    }
                    else if(read_ret>0)
                    {
                        std::string msgmsg(recv_buf);
                        std::list<int>::iterator iter=info->online_client.begin();
                        for(iter;iter!=info->online_client.end();iter++)
                        {
                            if(*iter==sockfd)
                            {
                                continue;                        
                            }
                            socket->socket_send(*iter,msgmsg.c_str());
                        }
                        if(msgmsg.find("off")!=std::string::npos)
                        {
                            break;
                        }
                    }
                }
                info->online_client.remove(sockfd);
                std::cout<<sockfd<<" has been closed "<<std::endl;
                close(sockfd);
            }
            void run()
            { 
                while(1)
                {
                    int fd_client;
                    get_sockfd(fd_client);
                    handle_chat(fd_client);
                }
            }
        private:
                Control* info;    
                SOCKET::Socket* socket;
    };
    class Factory
    {
        public:
            friend class EPOLL::Epoll;
            Factory(SOCKET::Socket* socket):info(new Control()),handle(new Thread_run(socket))
        {
            start_flag=0;
        }
            void on()
            {
                if(start_flag==1)
                {
                    return;
                }
                start_flag==1;
                for(int index=0;index!=THREADNUM;index++)
                {
                    start(handle);
                }
            }
            pthread_t start(Thread_run* arg)
            {
                arg->set_info(info);
                pthread_create(&tid,NULL,thread_func,(void*)arg);
                return tid;
            }
            static void* thread_func(void* obj)
            {
                pthread_detach(pthread_self());
                Thread_run* obj1=(Thread_run*)obj;
                obj1->run();
            }
        private:
            pthread_t tid;
            int start_flag;
            Control* info;
            Thread_run* handle;
    };
}
