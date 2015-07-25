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
        printf("%d \n" ,shmid);
        struct text* ptext = (struct text *)shmat(shmid , NULL , 0);
//      ptext->useful = 0 ;
        while(1)
        {
                if(ptext -> useful == 0)
		{
                        int iret = read(STDIN_FILENO , ptext->buf , 1024);
                        ptext->useful = 1;
                        if(strncmp("end" , ptext->buf,3)==0)
                        {
                                break ;
                        }
                        //ptext ->useful = 0 ;
                }
                sleep(1);
        }
                shmdt((void *)ptext);
                return 0 ;
}
