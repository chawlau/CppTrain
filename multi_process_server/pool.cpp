//#include "pool.hpp"
#include "mempool.hpp"
int main(int argc,char** argv)
{
    PROCESSPOOL::Process_pool* pool=new PROCESSPOOL::Process_pool(argv[1]);
    pool->child_pool();
    //pool->handle();
}
