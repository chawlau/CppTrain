#include "socket.hpp"
#include <sys/wait.h>
#include <json/json.h>
int main(int argc,char** argv)
{
    alarm(100);
    Json::FastWriter writer;
    fd_set read_set,ready_set;
    FD_ZERO(&read_set);
    FD_ZERO(&ready_set);
    SOCKET::Socket* client=new SOCKET::Socket(argv[2]);
    std::string name(argv[1]);
    client->socket_init();
    client->socket_connect();
    FD_SET(client->server_sock,&read_set);
    FD_SET(0,&read_set);
    int fd_max=client->server_sock;
    char recv_buf[1024];
    std::string msg;
    int shutdown=0;
    while(1)
    {
        if(shutdown)
        {
            break;
        }
        ready_set=read_set;
        select(fd_max+1,&ready_set,NULL,NULL,NULL);
        for(int index=0;index!=fd_max+1;index++)
        {
            if(FD_ISSET(index,&ready_set))
            {
                if(index==0)
                {
                    std::cin>>msg;
                    Json::Value value;
                    value["msg"]=msg;
                    value["name"]=name;
                    std::string jsonfile=writer.write(value);
                    client->socket_send(client->server_sock,jsonfile.c_str());
                    if(msg.find("off")!=std::string::npos)
                    {
                        shutdown=1;
                        break;
                    }
                }
                else if(index==fd_max)
                {
                    bzero(recv_buf,1024);
                    int recv_len=client->socket_recv(client->server_sock,recv_buf);
                    recv_buf[recv_len]='\0';
                    std::cout<<recv_buf<<std::endl;
                }
            }
        }
    }
    close(client->server_sock);
}
