#include<unistd.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>
#include<libgen.h>
#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<cstring>
#include<stack>
void create_file(char* path)
{
    std::stack<char*> temp;
    char* fdir=path;
    char* cdir=NULL;
    while(strcmp(".",fdir)!=0)
    {
        cdir=basename(fdir);
        fdir=dirname(fdir);
        temp.push(cdir);
    }
    while(!temp.empty())
    {
        if(temp.size()!=1)
        {
            mkdir(temp.top(),0777);
            chdir(temp.top());
            temp.pop();
            continue;
        }
        open(temp.top(),O_RDWR|O_CREAT);
        temp.pop();
    }
}
int main(int argc,char** argv)
{
    create_file(argv[1]);
}
