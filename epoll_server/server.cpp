#include"socket.hpp"
int main(int argc,char** argv)
{
    SOCKET::Socket* server=new SOCKET::Socket(argv[1]);
    server->socket_init();
    server->socket_bind();
    server->socket_listen();
    int fd_client=server->socket_accept();
    char recv_buf[1024];
    if(fork()==0)
    {
        while(bzero(recv_buf,1024),server->socket_recv(fd_client,recv_buf)>0)
        {
            std::cout<<recv_buf;
        }
        exit(1);
    }
    std::string msg;
    while(std::cout<<"服务器输入"<<std::endl,std::cin>>msg)
    {
        server->socket_send(fd_client,msg.c_str());
    }
}
