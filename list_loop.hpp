#include<iostream>
#include<cstring>
#include<cstdlib>
#include<cstdio>
#include<ctime>
#define N 10
#define LOOP 5
struct node
{
    int pos;
    struct node *next;
};
typedef struct node Node;
typedef struct node *PNode;
bool list_is_loop(PNode head)
{
    PNode p=head;
    PNode q=head;
    PNode meet=NULL;
    int flag=0;
    while(1)
    {
        p=p->next->next;
        q=q->next;
        if(p==NULL||q==NULL)
        {
            return false;
        }
        std::cout<<"p data : --> "<<p->pos<<std::endl;
        if(p==q)
        {
            if(flag==1)
            {
                meet=p;
                std::cout<<"list is loop"<<std::endl;
                std::cout<<"meet address : --> "<<meet<<" meet pos : --> "<<meet->pos<<std::endl;
                return true;
            }
            else
            {
                flag=1;
                q=head;
            }
        }
    }
}
bool list_is_meet(PNode head1,PNode head2)
{

}
void list_out(PNode head)
{
    int index=0;
    while(head)
    {
        std::cout<<head->pos<<" ";
        //std::cout<<head<<" ";
        head=head->next;
    }
    std::cout<<std::endl;
}
void build_loop(Node** head)
{
    PNode tail=NULL;
    PNode loop=NULL;
    int index=0;
    while(index<N)
    {
        PNode inode=(PNode)calloc(1,sizeof(Node));
        inode->pos=index;
        if(*head==NULL)
        {
            *head=inode;
        }
        else
        {
            tail->next=inode;
            if(index==LOOP)
            {
                loop=inode;  
            }
        }
        tail=inode;
        if(index==N-1)
        {
            tail->next=loop;
        }
        index++;
    }
}
void list_head(Node* head)/*带头节点的头插法生成链表*/
{
    int index=0;
    while(index<N)
    {
        Node* inode=new Node();
        inode->pos=index;
        inode->next=head->next;
        head->next=inode;
        index++;
    }
}
void list_no_head(Node** head)/*不带头节点的头插法生成链表*/
{
    int index=0;
    while(index<N)
    {
        Node* inode=new Node();
        inode->pos=index;
        inode->next=*head;
        *head=inode;
        index++;
    }
}
void build_meet_list(Node** head1,Node** head2,Node** tail2)/*建立两个相交的链表*/
{
    PNode tail1=NULL;
    int index_i=0,index_j=0;
    srand(time(NULL));
    while(index_i<LOOP)
    {
        Node* inode=new Node();
        inode->pos=rand()%20+1;
        if(*head1==NULL)
        {
            *head1=inode;
        }
        else
        {
            tail1->next=inode;
        }
        tail1=inode;
        index_i++;
    }
    //list_out(*head1);
    while(index_j<N)
    {
        Node* inode=new Node();
        inode->pos=index_j;
        if(*head2==NULL)
        {
            *head2=inode;
        }
        else
        {
            (*tail2)->next=inode;
        }
        *tail2=inode;
        if(index_j==LOOP)
        {
            tail1->next=inode;
            tail1=inode;
        }
        index_j++;
    }
    Node* inew=new Node();
    /*
    inew->pos=rand()%100+1;
    inew->next=*head1;
    *head1=inew;*/
    list_out(*head1);
    list_out(*head2);
}
void list_delete(Node* head)
{
    PNode pnew=head->next;
    while(pnew)
    {
        if(pnew->pos==5)
        {
            pnew->pos=pnew->next->pos;
            pnew->next=pnew->next->next;
            break;
        }
        pnew=pnew->next;
    }
}
Node* find_loop_port(PNode head)/*要设置一个头节点*/
{
    Node* newhead=new Node();
    newhead->next=head;
    head=newhead;
    Node* slow=head;
    Node* fast=head;
    while(fast&&fast->next)
    {
       slow=slow->next;
       fast=fast->next->next;
       if(slow==fast)
       {
            break;
       }
    }
    if(fast==NULL||slow==NULL)
    {
        return NULL;
    }
    slow=head;/*第一次相遇后要将任意一个节点重新归位为头节点*/
    //fast=head;
    while(slow!=fast)
    {
        slow=slow->next;
        fast=fast->next;
    }
    return slow;
}
void two_list_meet(PNode head1,PNode head2)
{
    /*计算两个链表的长度差 */
    int head1_len=0,head2_len=0;
    PNode tmp1=head1,tmp2=head2;
    while(tmp1)
    {
        head1_len++;
        tmp1=tmp1->next;
    }
    while(tmp2)
    {
        head2_len++;
        tmp2=tmp2->next;
    }
    int len=head1_len>head2_len?head1_len-head2_len:head2_len-head1_len;
    int index=0;
    PNode data1=head1,data2=head2;
    if(head1_len>head2_len)/*比较长的指针先移动*/
    {
        while(index<len)
        {
            data1=data1->next;
            index++;
        }
    }
    else
    {
        while(index<len)
        {
            data2=data2->next;
            index++;
        }
    }
    /*两个指针同时遍历,第一个相遇点就是交点*/
    while(data1&&data2)
    {
        if(data1==NULL||data2==NULL)
        {
            break;
        }
        if(data1==data2)
        {
            std::cout<<"first meet node address : "<<data1<<" data :"<<data1->pos<<std::endl;
            break;
        }
        data1=data1->next;
        data2=data2->next;
    }
}


