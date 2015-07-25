#include<iostream>
#include<cstring>
#include<cstdio>
#include<ctime>
#include<cstdlib>
#define N 20
struct node
{
    int data;
    struct node *next;
};
typedef struct node Node;
typedef struct node *PNode;
void list_reverse(Node* head)/*链表逆置*/
{
    PNode pnew=head->next->next;
    head->next->next=NULL;
    while(pnew)
    {
        PNode temp=pnew->next;
        pnew->next=NULL;
        pnew->next=head->next;
        head->next=pnew;
        pnew=temp;
    }
}
void list_out(PNode head)/*链表输出*/
{
    PNode pnew=head->next;
    while(pnew)
    {
        std::cout<<pnew->data<<" ";
        pnew=pnew->next;
    }
    std::cout<<std::endl;
}
void list_add(Node* head,Node* node)/*将一个数有序的插入链表中*/
{
    PNode pre=head;
    PNode pnew=head->next;
    if(pnew==NULL)
    {
        node->next=pre->next;
        pre->next=node;
    }
    while(pnew)
    {
        if(pnew->data>node->data)
        {
            node->next=pnew;
            pre->next=node;
            break;
        }
        if(pnew->data==node->data)
        {
            break;
        }
        if(pnew->next==NULL)
        {
            node->next=pnew->next;
            pnew->next=node;
            break;
        }
        pre=pnew;
        pnew=pnew->next;
    }
}
void list_create_sort(Node* head)/*创建有序链表*/
{
    int index=0;
    while(index<N)
    {
        PNode node=(PNode)calloc(1,sizeof(Node));
        node->data=rand()%100+1;
        node->next=NULL;
        list_add(head,node);
        index++;
    }
}
void list_sort(Node* head)/*将无序链表排序*/
{
    PNode insert=head->next->next;
    head->next->next=NULL;
    PNode pnew=head->next;
    PNode pre=head;
    while(insert)
    {
        PNode temp=insert->next;
        insert->next=NULL;
        pnew=head->next;
        pre=head;
        while(pnew)
        {
            if(pnew->data>insert->data)/*每次只插入一个值*/
            {
                insert->next=pre->next;
                pre->next=insert;
                break;
            }
            if(pnew->next==NULL)/*找不到所以插在末尾的位置*/
            {
                insert->next=pnew->next;
                pnew->next=insert;
                break;
            }
            pnew=pnew->next;
            pre=pre->next;
        }
        insert=temp;
    }
}
void list_unique(Node* head)/*去除链表中重复元素*/
{
    PNode pnew=head->next;
    while(pnew)
    {
        if(pnew->next==NULL)
        {
            return;
        }
        PNode pnew1=pnew->next;
        PNode pre=NULL;
        while(pnew1)
        {
            if(pnew1->data==pnew->data)
            {
                if(pre==NULL)
                {
                    PNode temp=pnew->next;
                    pnew->next=pnew1->next;
                    pnew1=temp;
                }
                else
                {
                    PNode temp=pnew->next;
                    pre->next=pnew1->next;
                    pnew1=temp;
                }
            }
            else
            {
                pre=pnew1;
                pnew1=pnew1->next;
            }
        }
        pnew=pnew->next;
    }
}
void list_merge(Node* head1,Node* head2)/*两个链表合并*/
{
    while(head2->next)
    {
        PNode node=head2->next;
        head2->next=head2->next->next;
        list_add(head1,node);
    }
}
