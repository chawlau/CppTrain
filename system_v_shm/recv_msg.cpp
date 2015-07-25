#include <stdio.h> 
#include <string.h> 
#include <stdlib.h> 
#include <errno.h> 
#include <unistd.h> 
#include <sys/types.h> 
#include <sys/ipc.h> 
#include <sys/stat.h> 
#include <sys/msg.h> 
#include <unistd.h>
#include <iostream>
#define   BUFFER  255

struct msgtype {										//重定义消息结构体
    long mtype;
    std::string buffer;
};

int main()
{   	
    int msgid = msgget((key_t)1234, 0666 | IPC_CREAT); 	//获得消息队列
    if(msgid == -1)
    {
        fprintf(stderr,"Creat Message  Error:%s\a\n",strerror(errno));
        exit(1);
    }
    msgtype msg;
    std::string word;
    while(bzero(&msg,sizeof(msg)),std::cin>>word)
    {
        msgrcv(msgid,&msg,sizeof(msg),1,0);   	//接收消息
        std::cout<<"Server Receive: "<<msg.buffer<<std::endl;
        msg.mtype = 2;
        msg.buffer=word;
        msgsnd(msgid,&msg,sizeof(msg),0);		//发送消息
    }
    exit(0);
}

