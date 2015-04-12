#include"select_pro.hpp"
//#include"select.hpp"
int main(int argc,char** argv)
{
    SELECT::Select* server=new SELECT::Select(argv[1]);
    server->init();
    server->wait();
}
