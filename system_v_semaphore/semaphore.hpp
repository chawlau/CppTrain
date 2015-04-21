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
            sem_id=semget((key_t)atoi(value),1,0666|IPC_CREAT);
        }
        void sem_init(struct sembuf& sem)
        {
            arg.val=0;
            if(semctl(sem_id,sem.sem_num,SETVAL,arg.val)==-1)
            {
                perror("sem ctl");
                _exit(1);
            }
        }
        void sem_del()
        {
            if(semctl(sem_id,0,IPC_RMID,arg)==-1)
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
            return semctl(sem_id,sem.sem_num,GETVAL);
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

