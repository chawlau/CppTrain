#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/stat.h>
#include <unistd.h>
#include <iostream>
#define   BUFFER  255
struct msgtype 
{									//重新定义该结构体
    long mtype;				//第一个参数不变
    std::string buffer;
};

int main(int argc,char **argv)
{
    int msgid = msgget((key_t)1234,0666 | IPC_CREAT); //获取消息队列
    if(msgid == -1)
    {
        fprintf(stderr,"Creat Message  Error:%s\a\n",strerror(errno));
        exit(1);
    }
    msgtype msg;
    std::string word;
    while(bzero(&msg,sizeof(msg)),std::cin>>word)
    {
        msg.mtype = 1;								//给结构体的成员赋值
        msg.buffer=word;
        msgsnd(msgid,&msg,sizeof(msgtype),0);   	//发送信号
        bzero(&msg,sizeof(msg));
        msgrcv(msgid,&msg,sizeof(msgtype),2,0); 	//接收信号
        std::cout<<"Client receive: "<<msg.buffer<<std::endl;
    }
    exit(0);
}
