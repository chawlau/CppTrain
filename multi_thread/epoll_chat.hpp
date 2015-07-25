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
#include "thread_chat.hpp"
#include <vector>
#include <json/json.h>
#include <sstream>
#define MAXSIZE 1024
namespace EPOLL
{
    class Epoll
    {
        public:
            Epoll(const std::string port):socket(new SOCKET::Socket(port))
        {
            chat=new FACTORY::Factory(socket);   
        }
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
                        chat->info->online_client.push_back(fd_client);
                        chat->handle->put_sockfd(fd_client);
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
                chat->on();
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
            FACTORY::Factory* chat;
    };
}

