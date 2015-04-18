#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/epoll.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/epoll.h>
#include "socket.hpp"
#include <vector>
#include <json/json.h>
#include <sstream>
#define MAXSIZE 1024
namespace EPOLL
{
    class Epoll
    {
        public:
            Epoll(const std::string port):socket(new SOCKET::Socket(port)){};
            void epoll_init()
            {
                epoll_fd=epoll_create(MAXSIZE);
            }
            void event_add(const int& sockfd,const int& state)
            {
                struct epoll_event ev;
                ev.events=state;
                ev.data.fd=sockfd;
                epoll_ctl(epoll_fd,EPOLL_CTL_ADD,sockfd,&ev);
            }
            void event_delete(const int& sockfd)
            {
                epoll_ctl(epoll_fd,EPOLL_CTL_DEL,sockfd,NULL);
            }
            void event_mod(const int& sockfd,const int& state)
            {
                struct epoll_event ev;
                ev.events=state;
                ev.data.fd=sockfd;
                epoll_ctl(epoll_fd,EPOLL_CTL_MOD,sockfd,&ev);
            }
            void handle_request(const int& active)
            {
                if(active==0)
                {
                    std::cout<<"epoll listen system timeout !"<<std::endl;
                }
                for(int index=0;index<active;index++)
                {
                    if(socket->server_sock==events[index].data.fd)
                    {
                        int fd_client=socket->socket_accept();
                        socket->set_nonblock(fd_client);
                        event_add(fd_client,EPOLLIN|EPOLLET);
                        online.push_back(fd_client);
                    }
                    else if(events[index].events&EPOLLIN)
                    {
                        char recv_buf[MAXSIZE]="";
                        int read_ret=socket->socket_recv(events[index].data.fd,recv_buf);
                        //int read_ret=read(events[index].data.fd,recv_buf,MAXSIZE);
                        if(read_ret==-1&&errno!=EAGAIN)
                        {
                            perror("client closed");
                            close(events[index].data.fd);
                        }
                        else if(read_ret==0)
                        {
                            std::cout<<events[index].data.fd<<"has been closed"<<std::endl;
                            event_delete(events[index].data.fd);
                            close(events[index].data.fd);
                            for(size_t index_t=0;index!=online.size();index++)
                            {
                                if(online[index_t]=events[index].data.fd)
                                {
                                    online[index_t]==0;
                                }
                            }
                        }
                        else if(read_ret>0)
                        {
                            Json::Value value;
                            reader.parse(recv_buf,value,false);
                            std::string msg=value["msg"].asString();
                            std::string name=value["name"].asString();
                            std::stringstream ss;
                            ss<<msg<<" from client:"<<name;
                            std::string msgmsg=ss.str();
                            std::cout<<msgmsg<<std::endl;
                            for(size_t index_t=0;index_t!=online.size();index_t++)
                            {
                                if(online[index_t]!=events[index].data.fd&&online[index_t]!=0)
                                {
                                    //write(online[index_t],msgmsg.c_str(),msgmsg.size());
                                    int send_len=socket->socket_send(online[index_t],msgmsg.c_str());
                                }
                            }
                        }
                    }
                }
            }
            void server_init()
            {
                socket->socket_init();
                socket->set_nonblock(socket->server_sock);
                event_add(socket->server_sock,EPOLLIN|EPOLLET);
                socket->socket_bind();
                socket->socket_listen();
            }
            void epoll_listen()
            {
                epoll_init();
                server_init();
                int active=0;
                std::cout<<"waiting for connecting......."<<std::endl;
                while(1)
                {
                    active=epoll_wait(epoll_fd,events,MAXSIZE,50000); 
                    handle_request(active);
                }
            }
        private:
            SOCKET::Socket* socket;
            int epoll_fd;
            struct epoll_event events[MAXSIZE];
            std::vector<int> online;
            Json::Reader reader;
    };
}

