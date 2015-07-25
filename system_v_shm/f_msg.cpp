#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <iostream>
struct Msg
{
    long mtype;
    char buf[64];
};
int main()
{
    int msgid = msgget((key_t)1234, 0666 | IPC_CREAT);
    if(msgid == -1)
    {
        perror("msgget error");
        exit(-1);
    }
    Msg msg;
    memset(&msg,0,sizeof(msg));
    if(fork() > 0)
    {
        msg.mtype = 1;
        strcpy(msg.buf,"mingzongyue");
        msgsnd(msgid,&msg,sizeof(msg),0);
        wait(NULL);
		msgctl(msgid, IPC_RMID, NULL);
        exit(0);
    }
    else
    {
        msgrcv(msgid, &msg, sizeof(msg), 1, 0);
        puts(msg.buf);
        exit(0);
    }
}
