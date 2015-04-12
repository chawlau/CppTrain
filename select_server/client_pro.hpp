#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/select.h>
#include <sys/time.h>
#include <json/json.h>
#include <stdexcept>
#include <iostream>
#include <sstream>
namespace CLIENT
{
    class Client
    {
        public:
            Client(const std::string& server_path,const std::string& pipe_rpath,const std::string& pipe_wpath,const std::string& name):m_pipe_rpath(pipe_rpath),m_pipe_wpath(pipe_wpath),m_name(name)
        {
            fd_server=open(server_path.c_str(),O_WRONLY);//打开服务器端描述符
            if(fd_server==-1)
            {
                perror("open fd_server");
            }
        }
            void connect()
            {
                std::cout<<"connect server"<<std::endl;
                Json::Value info;
                info["name"]=m_name;
                info["pid"]=getpid();
                info["pipe_r"]=m_pipe_rpath;
                info["pipe_w"]=m_pipe_wpath;
                info["type"]="on";
                std::string jsonfile=writer.write(info);
                int con_len=write(fd_server,jsonfile.c_str(),jsonfile.size());
            }
            void chat()
            {
                fd_write=open(m_pipe_wpath.c_str(),O_WRONLY);
                fd_read=open(m_pipe_rpath.c_str(),O_RDONLY);
                if(fork()==0)
                {
                    close(fd_server);
                    close(fd_write);
                    while(bzero(msg,1024),read(fd_read,msg,1024)!=0)
                    {
                        std::cout<<msg<<std::endl;
                    }
                    close(fd_read);
                    exit(0);
                }
                close(fd_read);
                while(bzero(msg,1024),fgets(msg,1024,stdin)!=NULL)
                {
                    Json::Value msginfo;
                    msginfo["name"]=m_name;
                    msginfo["pid"]=getpid();
                    msginfo["msg"]=msg;
                    std::string jsonfile=writer.write(msginfo);
                    write(fd_write,jsonfile.c_str(),jsonfile.size());
                }
            }
            void offline()
            {
                Json::Value info;
                info["pid"]=getpid();
                info["type"]="off";
                std::string jsonfile=writer.write(info);
                write(fd_write,jsonfile.c_str(),jsonfile.size());
                std::cout<<"waiting........"<<std::endl;
                wait(NULL);
                std::cout<<"waited !"<<std::endl;
                close(fd_server);
                close(fd_write);
            }
        private:
            int fd_write;
            int fd_read;
            int fd_server;
            std::string m_name;
            std::string m_pipe_rpath;
            std::string m_pipe_wpath;
            Json::FastWriter writer;
            Json::Reader reader;
            char msg[1024];
    };
}
