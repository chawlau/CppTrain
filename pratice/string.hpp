#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<cstring>
#include<ctime>
#include<cctype>
#include<cassert>
#define N 10
void substr(char* dest,const char* src,const int& pos,const int& length)/*截取一段字符串*/
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
void count_char(const char* word)/*hash表统计单词个数*/
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
void reverse(char* word,int& length)/*将一个字符串逆转*/
{
    char* head=word;
    char* tail=word+length-1;
    for(int index=0;index!=length/2;index++)
    {
        //std::cout<<"head: "<<*head<<" "<<"tail: "<<*tail<<std::endl;
        char temp=*head;
        *head=*tail;
        *tail=temp;
        head++;
        tail--;
    }
}
void reverse_phrase(char* word)/*将一句话的单词顺序逆转,单词本身不逆转*/
{
    int length=strlen(word);
    reverse(word,length);
    int begin=0,end=0,flag=0;
    for(int index=0;index!=strlen(word)+1;index++)
    {
        if(isalpha(word[index])&&!flag)
        {
            begin=index;
            flag=1;
        }
        if((isspace(word[index])||word[index]=='\0')&&flag)
        {
            end=index;
            int len=end-begin;
            reverse(word+begin,len);
            flag=0;
        }
    }
}
void trim_redunt(char* word)/*利用哈希表来去重*/
{
    int* hash=new int[26]();
    int  index_i=0;
    for(int index=0;word[index]!='\0';index++)
    {
        if(!hash[word[index]-'a'])
        {
            word[index_i++]=word[index];
            hash[word[index]-'a']=1;
        }
    }
    word[index_i]='\0';
}
char* str_cpy(char* dest,const char* src)
{
    assert((dest!=NULL)&&(src!=NULL));/*断言必须加*/
    char* address=dest;
    while((*dest++=*src++)!='\0');
    return address;
}
void once_char(char* word)/*查找出现一次的字符*/
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
void trim_space(char* word)/*去除字符串的多余空格只保留一个*/
{
    assert(word!=NULL);
    int index_i=0;
    for(int index=0;word[index]!='\0';index++)
    {
        if(isspace(word[index]))
        {
            if(index==0||isalpha(word[index_i-1]))
            {
                word[index_i++]=word[index];
            }
        }
        if(isalpha(word[index]))
        {
            word[index_i++]=word[index];
        }
    }
    std::cout<<word<<std::endl;
}
void trim_pattern(char* word)
{
    char pattern[6]="aeiou";
    int index_i=0;
    for(int index=0;word[index]!='\0';index++)
    {
        if(!(word[index]=='a'||word[index]=='e'||word[index]=='i'\
                    ||word[index]=='o'||word[index]=='u'))
        {
            word[index_i++]=word[index];
        }
    }
    word[index_i]='\0';
    std::cout<<word<<std::endl;
}
bool char_contain(const char* str1,const char* str2)/*str2中的字符串是否都出现在str1中*/
{
    int* hash=new int[26]();
    for(int index=0;str1[index]!='\0';index++)
    {
        hash[str1[index]-'a']++;
    }
    for(int index=0;str2[index]!='\0';index++)
    {
        if(hash[str2[index]-'a']==0)
        {
            return false;
        }
    }
    return true;
}
long long strtoint(char* str)/*将字符串转换成整数*/
{
    assert(str!=NULL);
    int flag=0;
    if(*str=='-')
    {
        flag=1;
    }
    str++;
    long long num=0;
    while(*str!='\0')
    {
        if(!(*str>='0'&&*str<='9'))
        {
            return 0;
        }
        num=num*10+(*str-'0');
        if(num>100000000000)
        {
            return 0;
        }
        str++;
    }
    if(flag)
    {
        return -num;
    }
    return num;
}
bool cir_contain(char* str1,const char* str2)/*循环数组是否包含子串*/
{
    strcat(str1,str1);
    for(int index=0;index!=strlen(str1)-strlen(str2)+1;index++)
    {
        for(int index_i=0;str2[index_i]!='\0';index_i++)
        {
            if(str2[index_i]!=str1[index])
            {
                break;
            }
        }
        return true;
    }
}
char* replace(char* word)
{
    int space_cnt=0;
    for(int index=0;word[index]!='\0';index++)
    {
        if(isspace(word[index]))
        {
            space_cnt++;
        }
    }
    int index_i=strlen(word)+2*space_cnt-1;
    word[index_i+1]='\0';
    for(int index_j=strlen(word)-1;index_j!=-1;index_j--)
    {
        if(isspace(word[index_j])) 
        {
            index_i=index_i-3;
            memcpy(word+index_i+1,"%20",3);
            continue;
        }
        word[index_i--]=word[index_j];
    }
    return word;
}
