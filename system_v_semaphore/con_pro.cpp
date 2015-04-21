#include"con_pro.hpp"
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
        struct sembuf sem[2];
        sem[0].sem_num=0;
        sem[0].sem_op=1;
        sem[0].sem_flg=0;
        sem[1].sem_num=1;
        sem[1].sem_op=-1;
        sem[1].sem_flg=0;
        sem_num_t=sem[0].sem_num;
        sema->sem_init(sem[0]);
        while(1)
        {
            std::cout<<"produce number is "<<sema->sem_ctl(sem[0])<<std::endl;
            std::cout<<"produce space number is "<<sema->sem_ctl(sem[1])<<std::endl;
            sema->sem_op(sem[0]);
            std::cout<<"produce + 1"<<std::endl;
            sema->sem_op(sem[1]);
            std::cout<<"produce space number is "<<sema->sem_ctl(sem[1])<<std::endl;
            std::cout<<"produce number is "<<sema->sem_ctl(sem[0])<<std::endl;
            sleep(2);
        }
    }
    else
    {
        sleep(5);
        struct sembuf sem_f[2];
        sem_f[0].sem_num=0;
        sem_f[0].sem_op=-1;
        sem_f[0].sem_flg=0;
        sem_f[1].sem_num=1;
        sem_f[1].sem_op=1;
        sem_f[1].sem_flg=0;
        std::cout<<"this is consumer"<<std::endl;
        while(1)
        {
            std::cout<<"consume number is "<<sema->sem_ctl(sem_f[0])<<std::endl;
            std::cout<<"consume space number is "<<sema->sem_ctl(sem_f[1])<<std::endl;
            sema->sem_op(sem_f[1]);
            std::cout<<"consume + 1 "<<std::endl;
            sema->sem_op(sem_f[0]);
            std::cout<<"consume space number is "<<sema->sem_ctl(sem_f[1])<<std::endl;
            std::cout<<"consume number is "<<sema->sem_ctl(sem_f[0])<<std::endl;
            sleep(2);
        }
    }
}
