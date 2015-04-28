#include "socket.hpp"
#include <sys/wait.h>
#include <json/json.h>
SOCKET::Socket* ex_client;
std::string ex_name;
Json::FastWriter writer;
pid_t ch_pid;
void handle(int signum)
{
    Json::Value drop;
    drop["msg"]="is drop off line!";
    drop["name"]=ex_name;
    std::string dropjson=writer.write(drop);
    ex_client->socket_send(ex_client->server_sock,dropjson.c_str());
    waitpid(-1,NULL,WNOHANG);
    kill(ch_pid,9);
    close(ex_client->server_sock);
    _exit(1);
}
void signal_register()
{
    struct sigaction act;
    bzero(&act,sizeof(act));
    act.sa_handler=handle;
    act.sa_flags=0;
    sigaction(SIGCHLD,&act,NULL);
    sigaction(SIGINT,&act,NULL);
    sigaction(SIGQUIT,&act,NULL);
    sigaction(SIGALRM,&act,NULL);
}
int main(int argc,char** argv)
{
    alarm(100);
    signal_register();
    Json::Reader reader;
    SOCKET::Socket* client=new SOCKET::Socket(argv[2]);
    std::string name(argv[1]);
    client->socket_init();
    client->socket_connect();
    ex_client=client;
    ex_name=name;
    Json::Value onvalue;
    onvalue["msg"]="is on line!";
    onvalue["name"]=name;
    std::string onjson=writer.write(onvalue);
    client->socket_send(client->server_sock,onjson.c_str());
    char recv_buf[1024];
    if(fork()==0)
    {
        ch_pid=getpid();
        while(bzero(recv_buf,1024),client->socket_recv(client->server_sock,recv_buf)>0)
        {
            Json::Value value;
            reader.parse(recv_buf,value,false);
            std::string client_name=value["name"].asString();
            std::string client_msg=value["msg"].asString();
            std::cout<<client_name<<": "<<client_msg<<std::endl;
        }
        _exit(1);
    }
    std::string msg;
    int off_flag=0;
    while(std::cout<<"客户端输入"<<std::endl,std::cin>>msg)
    {
        Json::Value value;
        value["msg"]=msg;
        value["name"]=name;
        if(msg.find("off")!=std::string::npos)
        {
            value["msg"]="is off line";    
            off_flag=1;
        }
        std::string jsonfile=writer.write(value);
        client->socket_send(client->server_sock,jsonfile.c_str());
        if(off_flag)
        {
            client->socket_send(client->server_sock,"");
            _exit(0);
        }
    }
    waitpid(-1,NULL,WNOHANG);
}
