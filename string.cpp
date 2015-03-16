#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<cstring>
#include<ctime>
#define N 10
void substr(char* dest,const char* src,const int& pos,const int& length)
{
    for(int index=0;index!=length;index++)
    {
        dest[index]=src[pos+index];
    }
    dest[length]='\0';
}
const char* contain(const char* src1,const char* src2)/*字符串包含*/
{
    if(strstr(src1,src2)!=NULL)
    {
        return src2;
    }
    char* dest=new char[100]();
    for(int len=strlen(src2);len!=0;len--)
    {
        for(int index=0;index!=strlen(src2)-len+1;index++)
        {
            substr(dest,src2,index,len);//自己编写的函数
            //memcpy(dest,src2+index,len);//系统内存拷贝函数
            //dest[len]='\0';
            if(strstr(src1,dest)!=NULL)
            {
                return dest;
            }
            bzero(dest,100);
        }
    }
    return NULL;
}
void common(const char* src1,const char* src2)
{
    if(strlen(src1)>=strlen(src2))
    {
        const char* value=contain(src1,src2);
        if(value!=NULL)
        {
            std::cout<<value<<std::endl;
            return;
        }
        std::cout<<"no common string"<<std::endl;
    }
    else
    {
        const char* value=contain(src1,src2);
        if(value!=NULL)
        {
            std::cout<<value<<std::endl;
            return;
        }
        std::cout<<"no common string "<<std::endl;
    }
}
struct node
{
    int data;
    struct node* next;
};
typedef struct node Node;
typedef struct node *PNode;
void list_out(Node* list)
{
    for(int index=0;index!=N;index++)
    {
        std::cout<<list[index].data<<" ";
    }
    std::cout<<std::endl;
}
void count_char(const char* word)/*统计单词个数*/
{
    int* hash=new int[26]();
    for(int index=0;word[index]!='\0';index++)
    {
        hash[word[index]-'a']++;
    }
    for(int index_i=0;index_i!=26;index_i++)
    {
        if(hash[index_i]==1)
        {
            std::cout<<(char)(index_i+'a')<<std::endl;
        }
    }
}
void reverse(char* word)
{
    char* head=word;
    char* tail=word+strlen(word)-1;
    std::cout<<*head<<std::endl;
    std::cout<<*tail<<std::endl;
    while(head!=tail)
    {
        char temp=*head;
        *head=*tail;
        *tail=temp;
        std::cout<<*head<<std::endl;
        std::cout<<*tail<<std::endl;
        head++;
        tail--;
    }
}
int main(int argc,char** argv)
{
    char* word="xiaonongyue";
    reverse(word);
    std::cout<<word<<std::endl;
}
