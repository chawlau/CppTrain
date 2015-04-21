#include<iostream>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<sys/sem.h>
#include<cstdio>
#include<cstdlib>
#include<cstring>
namespace SEMAPHORE
{
    union semun
    {
        int val;
        struct semid_ds *buf;
        unsigned short *array;
    };
    class Semaphore
    {
        public:
            Semaphore(const char* value)
            {
                sem_id=semget((key_t)atoi(value),2,0666|IPC_CREAT);
            }
            Semaphore()
            {
                sem_id=semget((key_t)1234,2,0666|IPC_CREAT);
            }
            void sem_init(struct sembuf& sem)
            {
                unsigned short sem_array[2];
                sem_array[0]=0;
                sem_array[1]=10;
                arg.array=sem_array;
                if(semctl(sem_id,sem.sem_num,SETALL,arg.array)==-1)
                {
                    perror("sem ctl");
                    _exit(1);
                }
            }
            void sem_del(struct sembuf& sem)
            {
                if(semctl(sem_id,sem.sem_num,IPC_RMID)==-1)
                {
                    perror("sem del failed");
                    _exit(1);
                }
            }
            int sem_op(struct sembuf& sem)
            {
                if(semop(sem_id,&sem,1)==-1)
                {
                    perror("semphore P failed");
                    _exit(1);
                }
            }
            int sem_ctl(struct sembuf& sem)
            {
                int ret=semctl(sem_id,sem.sem_num,GETVAL);
                if(ret==-1)
                {
                    perror("sem ctl");
                    _exit(1);
                }
                return ret;
            }
            int sem_get()
            {
                return sem_id;
            }
        private:
            int sem_id;
            union semun arg;
    };
}

