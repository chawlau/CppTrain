#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>
#include<sys/wait.h>
#include<sys/socket.h>
#include<sys/mman.h>
#include<vector>
#include<queue>
#include <iostream>
#include "socket.hpp"
#define CHILDNUM 2            
using namespace std;
namespace PROCESSPOOL
{
    struct Pchild
    {
        Pchild(const int& fd,const pid_t& pid,const int& busy):ch_fd(fd),ch_pid(pid),ch_busy(busy){}
        int ch_fd;
        pid_t ch_pid;
        int ch_busy;
    };
    class Process_pool
    {
        public:
            Process_pool(const std::string& port):server(new SOCKET::Socket(port))
        {
            if(-1==socketpair(AF_LOCAL,SOCK_STREAM,0,fds))//创建可以实现父子进程发送描述符的fds
            {
                perror("socket pair");
            }
        }
            void server_init()//初始化socket连接
            {
                server->socket_init();
                server->socket_bind();
                server->socket_listen();
                std::cout<<"server socket init"<<std::endl;
            }
            void fdset_init()//select监听初始化
            {
                FD_ZERO(&read_set);
                FD_ZERO(&ready_set);
                FD_SET(server->server_sock,&read_set);
                for(size_t index=0;index!=CHILDNUM;index++)
                {
                    FD_SET(child_info[index].ch_fd,&read_set);
                }
                std::cout<<"child local fd and server_sock has been add in read_set"<<std::endl;
            }
            void child_create()//创建CHILDNUM个子进程
            {
                int index=0;
                while(index<CHILDNUM)
                {
                    int fd_send[2];
                    if(-1==(socketpair(AF_LOCAL,SOCK_STREAM,0,fd_send)))
                    {
                        perror("socket pair");
                        exit(1);
                    }
                    pid_t pid=fork();
                    if(pid==0)
                    {
                        close(fd_send[1]);
                        child_handle(fd_send[0]);
                        exit(1);
                    }
                    close(fd_send[0]);
                    Pchild* child=new Pchild(fd_send[1],pid,0);//创建的子进程信息对象
                    child_info.push_back(*child);//放入child_info这个对象数组中
                    index++;
                }
                std::cout<<"child process has been create"<<std::endl;
            }
            void child_detect()//遍历child_info这个进程对象数组查看空闲子进程
            {
                char buf[16];
                for(int index=0;index!=CHILDNUM;index++)
                {
                    if(FD_ISSET(child_info[index].ch_fd,&ready_set))//有空闲进程
                    {
                        read(child_info[index].ch_fd, buf,16); //consume the descriptor
                        std::cout<<"child #"<<index<<"waiting for fd"<<endl;
                        if(!wait_client.empty())//如果客户端等待队列不为空，说明有客户端请求等待处理
                        {
                            std::cout<<"wait client #"<<wait_client.front()<<"in queue"<<endl;
                            server->socket_send(wait_client.front(),"now you can do!");
                            send_fd(child_info[index].ch_fd,wait_client.front());
                            wait_client.pop();
                            child_info[index].ch_busy=1;//让子进程出力客户端请求，同时将busy置为1
                        } 
                        else
                        {
                            std::cout<<"no waiting clients"<<endl;
                            child_info[index].ch_busy=0;
                        }
                    }
                }
            }
            void child_handle(const int& local_fd)//子进程处理客户端任务
            {
                int sockfd;
                int flag=1;
                while(1)
                {
                    recv_fd(local_fd,sockfd);
                    cout<< "child got fd"<<endl;
                    char msg[1024];
                    while(bzero(msg,1024),server->socket_recv(sockfd,msg)>0)
                    {
                        std::string offmsg(msg);
                        if(offmsg.find("off")!=std::string::npos)//子进程受到客户端约定的下线请求
                        {
                            break;
                        }
                        std::cout<<"pid:"<<getpid()<<' '<<msg<<std::endl;
                        int fd_read=open("ming.txt",O_RDONLY);//子进程的具体业务，此段就是将一个文本内容返回给客户端
                        char ming[1024];
                        bzero(ming,1024);
                        read(fd_read,ming,1024);
                        server->socket_send(sockfd,ming);
                    }
                    write(local_fd,&flag,sizeof(int));        
                    cout<<"offine"<<endl;
                    close(sockfd);
                }
            }
            void select_listen()//select监听
            {
                ready_set=read_set;
                timeout.tv_sec=100;
                timeout.tv_usec=0;
                int result=select(1024,&ready_set,NULL,NULL,&timeout);
                if(result==0)
                {
                    std::cout<<"system waiting time out!"<<std::endl;
                }
                for(int index=0;index!=1024;index++)
                {
                    if(FD_ISSET(index,&ready_set))
                    {
                        if(index==server->server_sock)//客户端上线请求
                        {
                            int fd_client=server->socket_accept();
                            int index_t;
                            for(index_t=0;index_t!=CHILDNUM;index_t++)//遍历子进程信息表
                            {
                                if(child_info[index_t].ch_busy==0)//发现空闲子进程
                                {
                                    std::cout<<child_info[index_t].ch_pid<<" is free,handle task  "<<index_t<<std::endl;
                                    send_fd(child_info[index_t].ch_fd,fd_client);//客户端socket发给子进程
                                    child_info[index_t].ch_busy=1;
                                    break;
                                }
                            }
                            if(index_t==CHILDNUM)//说明没有空闲子进程，通知客户端让其等待
                            {
                                std::string busy="no free child process, waiting....";
                                std::cout<<"no free child process, waiting...."<<std::endl;
                                server->socket_send(fd_client,busy.c_str());
                                wait_client.push(fd_client);
                                break;
                            }
                        }
                    }
                }
            }
            void child_pool()//监听系统执行的主函数
            {
                child_create();
                server_init();
                fdset_init();
                while(1)
                {
                    select_listen();
                    child_detect();
                }
            }
            void handle()//暂时用不着
            {
                server_init();
                if(fork()==0)
                {
                    close(fds[1]);
                    int sockfd;
                    recv_fd(fds[0],sockfd);
                    std::cout<<"recv ret is"<<sockfd<<std::endl;
                    char msg[1024];
                    while(bzero(msg,1024),server->socket_recv(sockfd,msg)>0)
                    {
                        std::cout<<msg<<std::endl;
                        int fd_read=open("ming.txt",O_RDONLY);
                        char ming[1024];
                        int len=read(fd_read,ming,1024);
                        ming[len]='\0';
                        server->socket_send(sockfd,ming);
                        close(fd_read);
                    }
                    std::cout<<"client has offline"<<std::endl;
                    close(fds[0]);
                    close(sockfd);
                    exit(1);
                }
                close(fds[0]);
                int fd_client=server->socket_accept();
                send_fd(fds[1],fd_client);
                wait(NULL);
            }
            void send_fd(const int& sockfd,const int& fd)//发送文件描述符
            {
                struct msghdr my_msg;
                bzero(&my_msg,sizeof(my_msg));
                my_msg.msg_name=NULL;
                my_msg.msg_namelen=0;
                int val=100;
                struct iovec data[1];
                data[0].iov_base=&val;
                data[0].iov_len=sizeof(int);
                my_msg.msg_iov=data;
                my_msg.msg_iovlen=1;
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
                //std::cout<<"sendmsg ret :"<<ret<<std::endl;
            }
            void recv_fd(const int& sockfd,int& fd)//接收文件描述符
            {
                struct msghdr my_msg;
                bzero(&my_msg,sizeof(my_msg));
                my_msg.msg_name=NULL;
                my_msg.msg_namelen=0;
                int val=0;
                struct iovec data[1];
                data[0].iov_base=&val;
                data[0].iov_len=sizeof(int);
                my_msg.msg_iov=data;
                my_msg.msg_iovlen=1;
                my_msg.msg_flags=0;
                struct cmsghdr* pcmsg=(struct cmsghdr*)calloc(1,sizeof(struct cmsghdr));
                my_msg.msg_control=pcmsg;
                my_msg.msg_controllen=CMSG_LEN(sizeof(int));
                int ret=recvmsg(sockfd,&my_msg,0);
                //std::cout<<"recv msg ret:"<<ret<<std::endl;
                fd=*(int*)CMSG_DATA(pcmsg);
            }
        private:
            int fds[2];
            SOCKET::Socket* server;//socket 对象指针
            fd_set read_set;
            fd_set ready_set;
            struct timeval timeout;
            std::vector<Pchild> child_info;//子进程对象数组
            std::queue<int> wait_client;//等待请求被处理的客户端
    };
}
