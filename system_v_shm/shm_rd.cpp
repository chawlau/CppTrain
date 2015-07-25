#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
struct Text
{
    int useful;
    char buf[1024];
};
int main(int argc,char** argv)
{
    int shmid=shmget((key_t)5080,sizeof(struct Text),IPC_CREAT);
    Text* text=(Text*)shmat(shmid,NULL,0);
    text->useful=0;
    while(1)
    {
        if(text->useful==1)
        {
            write(1,text->buf,strlen(text->buf));
            text->useful=0;
            if(strncmp("end",text->buf,3)==0)
            {
                break;
            }
            sleep(1);
        }
        shmdt((void*)text);
        shmctl(shmid,IPC_RMID,0);
    }
}
