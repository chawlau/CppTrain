#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <queue>
#include <iostream>
#include <sstream>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <string.h>
#define CAPACITY 100
#define PRODUCE 30
#define CONSUME 10
#define THREADNUM 300
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
        std::queue<std::string> work_queue;
        int unfinished;
        std::string search;
    };
    class Thread_run
    {
        public:
            void set_info(Control* m_info)
            {
                info=m_info;
            }
            int in_file(const char* file)/*查询词是否包含在文件中*/
            {
                std::ifstream fin(file);
                std::string line;
                while(getline(fin,line))
                {
                    if(line.find(info->search)!=std::string::npos)
                    {
                        return 1;
                    }
                }
                fin.close();
                return 0;
            }
            void put_dir(const char* task)/*将解析的目录放入工作队列*/
            {
                std::string p_task(task);
                info->lock();
                (info->work_queue).push(p_task);
                info->unfinished++;
                info->unlock();
            }
            void get_dir(std::string& task)/*从工作队列取出目录*/
            {
                info->lock();
                while((info->work_queue).empty())
                {
                    info->wait();
                }
                task=(info->work_queue).front();
                (info->work_queue).pop();
                info->notify();
                info->unlock();
            }
            void mod_unfinished()//解析任务完成,unfinished减1
            {
                info->lock();
                if(--info->unfinished==0)
                {
                    std::cout<<"task is over !"<<std::endl;
                    _exit(0);
                }
                info->unlock();
                info->notify();
            }
            void handle_reg(std::string& task)
            {
                if(in_file(task.c_str()))
                {
                    //std::cout<<dirname(task.c_str())<<std::endl;
                    std::cout<<basename(task.c_str())<<std::endl;
                }
                mod_unfinished();
            }
            void handle_dir(const std::string& task)
            {
                DIR* dir;
                struct dirent* pent;
                dir=opendir(task.c_str());
                while((pent=readdir(dir))!=NULL)
                {
                    if(strcmp(".",pent->d_name)==0||strcmp("..",pent->d_name)==0)
                    {
                        continue;
                    }
                    std::stringstream ss;
                    ss<<task<<"/"<<pent->d_name;
                    put_dir(ss.str().c_str());
                }
                mod_unfinished();
            }
            void handle_other(const std::string& task)
            {
                mod_unfinished();
            }
            void dir_analysis(std::string& task)
            {
                struct stat my_stat;
                bzero(&my_stat,sizeof(my_stat));
                if(lstat(task.c_str(),&my_stat)==-1)//对取到的目录进行解析,解析失败任务unfinished也要减1
                {
                    perror("lstat");
                    mod_unfinished();
                    return;
                }
                if(S_ISREG(my_stat.st_mode))//如果是普通文件查找是否包含查询词
                {
                    handle_reg(task);
                }
                else if(S_ISDIR(my_stat.st_mode))//目录,解析后重新将目录流中的目录放入工作队列
                {
                    handle_dir(task);
                }
                else
                {
                    handle_other(task);//直接将unfinished减掉1
                }
            }
            void run()
            { 
                while(1)
                {
                    std::string task;
                    get_dir(task);
                    dir_analysis(task);
                }
            }
        private:
            Control* info;    
    };
    class Factory
    {
        public:
            Factory(std::string m_search,std::string src_path):info(new Control()),handle()
        {
            start_flag=0;
            info->search=m_search;
            (info->work_queue).push(src_path);
        }
            void on()
            {
                if(start_flag==1)
                {
                    return;
                }
                start_flag==1;
                pthread_t recover[THREADNUM];
                for(int index=0;index!=THREADNUM;index++)
                {
                    recover[index]=start(&handle);
                }
                for(int index=0;index!=THREADNUM;index++)
                {
                    pthread_join(recover[index],NULL);
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
            Thread_run handle;
    };
}
