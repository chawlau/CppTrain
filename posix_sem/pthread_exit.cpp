#include<unistd.h>
#include<pthread.h>
#include<iostream>
/*线程退出时，将线程中的一个变量的值传出来*/
struct foo
{
    foo(const std::string& m_name,const int& m_id):name(m_name),id(m_id){}
    std::string name;
    int id;
};
void cout_foo(const std::string& th_id,const foo* fp)
{
    std::cout<<th_id<<":"<<" name :"<<fp->name<<" id :"<<fp->id<<std::endl;
}
void* th_handle1(void* arg)
{
    foo* f1=new foo("mingzongyue",50);
    cout_foo("th_handle1",f1);
    pthread_exit((void*)f1);
}
void* th_handle2(void* arg)
{
    int data=5;
    std::cout<<"arg is : "<<(char*)arg<<std::endl;
    pthread_exit((void*)data);
}
void* th_handle3(void* arg)
{
    std::cout<<"thread 2 ID: "<<(unsigned long)pthread_self()<<std::endl;
    pthread_exit((void*)0);
}
int main(int argc,char** argv)
{
    pthread_t tid1,tid2,tid3;
    foo* fp;
    pthread_create(&tid1,NULL,th_handle1,NULL);
    pthread_join(tid1,(void**)&fp);/*如果是空指针，注意传地址的地址*/
    std::cout<<"name :"<<fp->name<<" id: "<<fp->id<<std::endl;
    pthread_create(&tid2,NULL,th_handle3,NULL);
    cout_foo("parent: ",fp);
    int data=0;
    int* data2=(int*)data;
    char* msg="xiaonongyue";
    pthread_create(&tid3,NULL,th_handle2,msg);
    pthread_join(tid3,(void**)&data2);
    std::cout<<data2<<std::endl;
    _exit(0);
}
