#include "dir_scan.hpp"
int main(int argc,char** argv)
{
    FACTORY::Factory* str_search=new FACTORY::Factory(argv[1],argv[2]);
    str_search->on();
}
