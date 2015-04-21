#include"semaphore.hpp"
#include<signal.h>
static int sem_id_t=0;
static int sem_num_t=0;
static void handle(int signum)
{
    semctl(sem_id_t,sem_num_t,IPC_RMID);
    _exit(1);
}
int main(int argc,char** argv)
{
    struct sigaction st;
    st.sa_handler=handle;
    st.sa_flags=0;
    sigaction(SIGINT,&st,NULL);
    SEMAPHORE::Semaphore* sema=new SEMAPHORE::Semaphore(argv[1]);
    sem_id_t=sema->sem_get();
    if(fork()==0)
    {
        struct sembuf sem;
        sem.sem_num=0;
        sem.sem_op=1;
        sem.sem_flg=0;
        sem_num_t=sem.sem_num;
        sema->sem_init(sem);
        while(1)
        {
            sema->sem_op(sem);    
            std::cout<<"produce total number "<<sema->sem_ctl(sem)<<std::endl;
            sleep(1);
        }
    }
    else
    {
        sleep(2);
        struct sembuf sem_f;
        sem_f.sem_num=0;
        sem_f.sem_op=-1;
        sem_f.sem_flg=0;
        while(1)
        {
            sema->sem_op(sem_f);
            std::cout<<"consume total numner "<<sema->sem_ctl(sem_f)<<std::endl;
            sleep(2);
        }
    }
}
