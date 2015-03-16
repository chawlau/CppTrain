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
void build_meet_list(Node** head1,Node** head2,Node** tail2)
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
    list_out(*head1);
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
int main(int argc,char** argv)
{
    PNode head1=NULL;
    PNode head2=NULL;
    PNode tail2=NULL;
    build_meet_list(&head1,&head2,&tail2);
    tail2->next=head1;
    list_is_loop(head2);
}


