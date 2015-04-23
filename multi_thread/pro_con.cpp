#include "pro_con.hpp"
int main(int argc,char** argv)
{
    FACTORY::Control* info=new FACTORY::Control();
    FACTORY::Factory* factory=new FACTORY::Factory();
    factory->start(info);
    factory->stop();
}
