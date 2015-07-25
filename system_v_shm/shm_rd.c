#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
struct text
{
    int useful;
    char buf[1024];
};
int main()
{
    int shmid = shmget((key_t)5080 , sizeof(struct text),IPC_CREAT);
    struct text* ptext = (struct text *)shmat(shmid , NULL , 0);
    ptext->useful = 0 ;
    while(1)
    {
        if(ptext -> useful == 1)
        {
            {
                write(STDOUT_FILENO,ptext -> buf , strlen(ptext -> buf));
                ptext ->useful = 0 ;
                if(strncmp("end" , ptext->buf,3)==0)
                {
                    break ;
                }
            }
            sleep(1);
        }
        shmdt((void *)ptext);
        shmctl(shmid , IPC_RMID,0);
        return 0 ;
    }
}
