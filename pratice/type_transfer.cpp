#include<iostream>
class base{};
class child: public base{};
int main(int argc,char** argv)
{
    int* ip=new int[1]();
    *ip=4;
    char* ip1=reinterpret_cast<char*>(ip);
    const char* pc_str="hello word";
    std::string str="hello world";
    char* const pc=const_cast<char*>(str.c_str());
    std::cout<<pc<<std::endl;
    base father;
    child son;
    son=static_cast<child&>(father);
    char* st1=NULL;
    int* st2=reinterpret_cast<int*>(st1);
}
