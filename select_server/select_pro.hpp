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
#define FD_MAX 1023
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
            fd_max=fd_server;//可以避免扫描整个集合
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
                if(inode->m_read>fd_max)
                    fd_max=inode->m_read;
                inode->m_next=m_head;
                m_head=inode;
                FD_SET(inode->m_read,&read_set);//将读描述符放入监听集合
                std::stringstream ss;
                ss<<inode->m_name<<" is on line !"<<std::endl;
                std::string onmsg=ss.str();
                std::cout<<onmsg;
                dispatch(onmsg,inode->m_pid);/*群发客户端上线消息*/
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
                dispatch(offmsg,search->m_pid);/*群发该客户端下线的消息*/
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
            }
            void dropoff(const int& read)
            {
                Client_info* search=m_head;
                Client_info* pre=NULL;
                while(search)
                {
                    if(search->m_read==read)//找到掉线的客户端
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
                dispatch(offmsg,search->m_pid);/*群发该客户端掉线的消息*/
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
            }
            void handle_task(const int& index)
            {
                char recv_buf[1024]="";
                int recv_len=read(index,recv_buf,1024);
                if(recv_len==0)
                {
                    dropoff(index);       //处理掉线
                }
                else if(recv_len>0)
                {
                    std::string msg(recv_buf);
                    if(msg.find("off")!=std::string::npos)//客户端正常下线
                    {
                        offline(msg);        
                    }
                    else                                    
                    {
                        sendmsg(msg);      //客户端正常发消息
                    }
                }
            }
            void sendmsg(const std::string& msg)
            {
                Json::Value msginfo;
                reader.parse(msg,msginfo,false);    
                int msg_pid=msginfo["pid"].asInt();
                std::string clientname=msginfo["name"].asString();
                std::string clientmsg=msginfo["msg"].asString();
                std::stringstream ss;
                ss<<clientmsg<<"from client :"<<clientname<<std::endl;
                std::string msgmsg=ss.str();
                dispatch(msgmsg,msg_pid);
            }
            void dispatch(const std::string& msg,const int& pid)
            {
                Client_info* broadcast=m_head;
                while(broadcast)
                {
                    if(broadcast->m_pid!=pid)//不能加入FD_ISSET来判断,否则未活动的描述符就收不到消息了
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
                    timeout.tv_sec=30;//设置系统延迟等待时间30s
                    timeout.tv_usec=0; 
                    temp_set=read_set;
                    result=select(fd_max+1,&temp_set,NULL,NULL,&timeout);
                    if(result==-1)
                    {
                        std::cout<<"select error!"<<std::endl;
                        break;
                    }
                    if(result==0)
                    {
                        std::cout<<"server waiting time out!"<<std::endl;
                        continue;
                    }
                    for(int index=0;index!=fd_max+1;index++)
                    {
                        if(FD_ISSET(index,&temp_set))
                        {
                            if(index==fd_server)//处理上线
                            {
                                handle_on(); 
                            }
                            else
                            {
                                handle_task(index);//处理客户端上线以外其他的业务
                            }
                        }
                    }
                }
            }
        private:
            Client_info* m_head;
            fd_set read_set;
            fd_set temp_set;
            struct timeval timeout;
            int result;
            int fd_server;
            int fd_max;
            Json::FastWriter writer;
            Json::Reader reader;
    };
}
