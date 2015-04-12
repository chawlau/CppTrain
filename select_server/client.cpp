#include"client_pro.hpp"
//#include"client.hpp" 
int main(int argc,char** argv)
{
    CLIENT::Client* client=new CLIENT::Client(argv[1],argv[2],argv[3],argv[4]);
    client->connect();
    client->chat();
    client->offline();
}
