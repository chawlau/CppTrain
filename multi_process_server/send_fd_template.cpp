#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>
#include<sys/wait.h>
#include<sys/socket.h>
#include<iostream>
void send_fd(const int& sockfd,const int& src_fd);
void recv_fd(const int& sockfd,int& des_fd);
int main(int argc,char** argv)
{
    int fds[2];
    if(-1==socketpair(AF_LOCAL,SOCK_STREAM,0,fds))
    {
        perror("socket pair");
    }
    std::cout<<"fds[0]: "<<fds[0]<<"  fds[1]:"<<fds[1]<<std::endl;
    if(fork()==0)
    {
        close(fds[0]);
        std::cout<<"child process"<<std::endl;
        int fd_client;
        recv_fd(fds[1],fd_client);
        std::cout<<" child recv fd is"<<fd_client<<std::endl;
        char buf[1024]="";
        std::cout<<"begin....."<<std::endl;
        read(fd_client,buf,1024);
        std::cout<<buf<<std::endl;
        std::cout<<"end......."<<std::endl;
    }
    close(fds[1]);
    int fd_rd=open(argv[1],O_RDONLY);
    std::cout<<"parent fd is"<<fd_rd<<std::endl;
    send_fd(fds[0],fd_rd);
    wait(NULL);
    return 0;
}
void send_fd(const int& sockfd,const int& fd)
{
    struct msghdr my_msg;
    bzero(&my_msg,sizeof(my_msg));
    my_msg.msg_name=NULL;
    my_msg.msg_namelen=0;
    int val=100;
    char str[100]="hello world";
    struct iovec data[2];
    data[0].iov_base=&val;
    data[0].iov_len=sizeof(val);
    data[1].iov_base=str;
    data[1].iov_len=strlen(str);
    my_msg.msg_iov=data;
    my_msg.msg_iovlen=2;
    struct cmsghdr* pcmsg=(struct cmsghdr*)calloc(1,sizeof(struct cmsghdr));
    int cmsglen=CMSG_LEN(sizeof(int));
    pcmsg->cmsg_len=CMSG_LEN(sizeof(int));
    pcmsg->cmsg_level=SOL_SOCKET;
    pcmsg->cmsg_type=SCM_RIGHTS;
    *(int*)CMSG_DATA(pcmsg)=fd;
    my_msg.msg_control=pcmsg;
    my_msg.msg_controllen=pcmsg->cmsg_len;
    my_msg.msg_flags=0;
    int ret=sendmsg(sockfd,&my_msg,0);
    std::cout<<ret<<std::endl;
}
void recv_fd(const int& sockfd,int& fd)
{
    struct msghdr my_msg;
    bzero(&my_msg,sizeof(my_msg));
    my_msg.msg_name=NULL;
    my_msg.msg_namelen=0;
    int val=0;
    char str[100]="";
    struct iovec data[2];
    data[0].iov_base=&val;
    data[0].iov_len=sizeof(int);
    data[1].iov_base=str;
    data[1].iov_len=99;
    my_msg.msg_iov=data;
    my_msg.msg_iovlen=2;
    my_msg.msg_flags=0;
    struct cmsghdr* pcmsg=(struct cmsghdr*)calloc(1,sizeof(struct cmsghdr));
    my_msg.msg_control=pcmsg;
    my_msg.msg_controllen=CMSG_LEN(sizeof(int));
    recvmsg(sockfd,&my_msg,0);
    fd=*(int*)CMSG_DATA(pcmsg);
    std::cout<<"fd :"<<fd<<std::endl;
    std::cout<<val<<std::endl;
    std::cout<<str;
}
