#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/select.h>
#include <sys/time.h>
#include <signal.h>
#include <json/json.h>
#include <stdexcept>
#include <iostream>
#include <sstream>
namespace SELECT
{
    struct Client_info
    {
        Client_info():m_next(NULL){}
        int m_pid;
        int m_read;
        int m_write;
        std::string m_name;
        Client_info* m_next;
    };
    void sighandle(int signum)
    {
         std::cout<<"Capture signal is "<<signum<<std::endl;
    }
    class Select
    {
        public:
            Select(const std::string pipe_path):m_head(NULL)
        {
            fd_server=open(pipe_path.c_str(),O_RDONLY);
            if(fd_server==-1)
            {
                throw std::runtime_error("open pipe failed");
            }
            signal(SIGPIPE,sighandle);
        }
            void init()
            {
                FD_ZERO(&read_set);
                FD_ZERO(&temp_set);
                FD_SET(fd_server,&read_set);
            }
            void handle_on()//处理上线消息
            {
                char recv_msg[1024];
                read(fd_server,recv_msg,1024);
                std::string msg(recv_msg);
                if(msg.find("on")!=std::string::npos)
                {
                    online(msg);
                }
            }
            void online(const std::string& msg)
            {
                Json::Value value;
                reader.parse(msg,value,false);//解析客户端上线消息
                Client_info* inode=new Client_info();
                inode->m_pid=value["pid"].asInt();//进程ID
                inode->m_name=value["name"].asString();//客户端名字
                inode->m_read=open(value["pipe_w"].asString().c_str(),O_RDONLY);//打开读写管道
                inode->m_write=open(value["pipe_r"].asString().c_str(),O_WRONLY);
                inode->m_next=m_head;
                m_head=inode;
                FD_SET(inode->m_read,&read_set);//将读描述符放入监听集合
                std::stringstream ss;
                ss<<inode->m_name<<" is on line !"<<std::endl;
                std::string onmsg=ss.str();
                std::cout<<onmsg;
                dispatch(onmsg,inode);/*群发客户端上线消息*/
            }
            void offline(const std::string& msg)
            {
                Json::Value value;
                reader.parse(msg,value,false);//解析客户端的下线消息,提取客户端的进程ID
                Client_info* search=m_head;
                Client_info* pre=NULL;
                while(search)
                {
                    if(search->m_pid==value["pid"].asInt())//找到下线的客户端
                    {
                        break;
                    }
                    pre=search;
                    search=search->m_next;
                }
                FD_CLR(search->m_read,&read_set);//将下线客户端描述符从监听集删除
                std::stringstream ss;
                ss<<search->m_name<<" off line normal"<<std::endl;
                std::string offmsg=ss.str();
                std::cout<<offmsg;
                dispatch(offmsg,search);/*群发该客户端下线的消息*/
                close(search->m_read);
                close(search->m_write);//关闭下线客户端的读写描述符
                if(pre==NULL)/*将下线的客户端从链表中移除同时释放空间*/
                {
                    m_head=search->m_next;
                    search->m_next=NULL;
                    delete search;
                }
                else
                {
                    pre->m_next=search->m_next;
                    delete search;
                }
                temp_set=read_set;
            }
            void dropoff(const int& pid)
            {
                Client_info* search=m_head;
                Client_info* pre=NULL;
                while(search)
                {
                    if(search->m_pid==pid)//找到掉线的客户端
                    {
                        break;
                    }
                    pre=search;
                    search=search->m_next;
                }
                FD_CLR(search->m_read,&read_set);//将掉线客户端描述符从监听集删除
                std::stringstream ss;
                ss<<search->m_name<<" drop off line !"<<std::endl;
                std::string offmsg=ss.str();
                std::cout<<offmsg;
                dispatch(offmsg,search);/*群发该客户端掉线的消息*/
                close(search->m_read);
                close(search->m_write);//关闭掉线客户端的读写描述符
                if(pre==NULL)/*将线的客户端从链表中移除同时释放空间*/
                {
                    m_head=search->m_next;
                    search->m_next=NULL;
                    delete search;
                }
                else
                {
                    pre->m_next=search->m_next;
                    delete search;
                }
                temp_set=read_set;
            }
            void broadcast()
            {
                Client_info* cur=m_head;
                char recv_buf[1024]="";
                while(cur)
                {
                    if(FD_ISSET(cur->m_read,&temp_set))
                    {
                        bzero(recv_buf,1024);
                        if(read(cur->m_read,recv_buf,1024)!=0)
                        {
                            std::string offmsg(recv_buf);
                            if(offmsg.find("off")!=std::string::npos)//客户端正常下线
                            {
                                offline(offmsg);        
                            }
                            else                                    //客户端发送消息
                            {
                                std::stringstream ss;
                                ss<<recv_buf<<"from <<"<<cur->m_name<<std::endl;
                                std::string msg=ss.str();
                                dispatch(msg,cur);
                            }
                        }
                        else  //客户端掉线
                        {
                            dropoff(cur->m_pid);
                        }
                    }
                    cur=cur->m_next;
                }
            }
            void dispatch(const std::string& msg,Client_info* current)
            {
                Client_info* broadcast=m_head;
                while(broadcast)
                {
                    //if(broadcast!=current&&FD_ISSET(broadcast->m_read,&temp_set))
                    if(broadcast!=current)
                    {
                        write(broadcast->m_write,msg.c_str(),msg.size());
                    }
                    broadcast=broadcast->m_next;
                }
            }
            void wait()
            {
                init();
                std::cout<<"server waiting for connecting"<<std::endl;
                while(1)
                {
                    temp_set=read_set;
                    select(1024,&temp_set,NULL,NULL,NULL);
                    if(FD_ISSET(fd_server,&temp_set))
                    {
                        handle_on(); 
                    }
                    broadcast();
                }
            }
        private:
            Client_info* m_head;
            fd_set read_set;
            fd_set temp_set;
            int fd_server;
            Json::FastWriter writer;
            Json::Reader reader;
    };
}
