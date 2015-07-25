#include "epoll_chat.hpp"
int main(int argc,char** argv)
{
    EPOLL::Epoll* epoll=new EPOLL::Epoll(argv[1]);
    epoll->epoll_listen();
}
