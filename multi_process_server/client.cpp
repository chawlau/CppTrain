#include "socket.hpp"
#include <sys/wait.h>
#include <json/json.h>
int main(int argc,char** argv)
{
    alarm(30);
    Json::FastWriter writer;
    SOCKET::Socket* client=new SOCKET::Socket(argv[2]);
    std::string name(argv[1]);
    client->socket_init();
    client->socket_connect();
    char recv_buf[1024];
    if(fork()==0)
    {
        while(bzero(recv_buf,1024),client->socket_recv(client->server_sock,recv_buf)>0)
        {
            std::cout<<recv_buf<<std::endl;
        }
        exit(1);
    }
    std::string msg;
    while(std::cout<<"客户端输入"<<std::endl,std::cin>>msg)
    {
        Json::Value value;
        value["msg"]=msg;
        value["name"]=name;
        std::string jsonfile=writer.write(value);
        client->socket_send(client->server_sock,jsonfile.c_str());
    }
    close(client->server_sock);
    waitpid(-1,NULL,WNOHANG);
}
