#include<iostream>
#include<cstring>
#include<cstdio>
#include<cstdlib>
#include<ctime>
#define N 5
int multiply(const char* str1,const char* str2)/*字符数组实现两个比较大的数的乘法*/
{
    int data_len=strlen(str1)+strlen(str2);
    int* bite_data=new int[data_len]();
    for(int index_i=0;str1[index_i]!='\0';index_i++)
    {
        for(int index_j=0;str2[index_j]!='\0';index_j++)
        {
            bite_data[index_i+index_j+1]+=(str1[index_i]-'0')*(str2[index_j]-'0');
        }
    }
    for(int index=0;index!=data_len;index++)
    {
        std::cout<<bite_data[index]<<" ";
    }
    std::cout<<std::endl;
    char* result=new char[data_len]();/*整理整型数组的数,依次存入字符串数组*/
    for(int index_k=data_len-1;index_k!=0;index_k--)
    {
        if(bite_data[index_k]>10)
        {
            bite_data[index_k-1]+=bite_data[index_k]/10;
            bite_data[index_k]%=10;
        }
        result[index_k]=bite_data[index_k]+'0';
    }
    result[0]=bite_data[0];
    while(*result++=='0');
    return atoi(result);
}
struct node
{
    int data;
    struct node *next;
};
typedef struct node Node;
typedef struct node *PNode;
void list_out(PNode head)
{
    while(head)
    {
        std::cout<<head->data<<" ";
        head=head->next;
    }
    std::cout<<std::endl;
}
void list_reverse(Node* head)/*带头节点的链表逆置*/
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
/*不带头节点的链表逆置,head指针在操作过程中产生了移动,所以必须传Node**参数*/
void list_reverse(Node** head)
{
    Node* old=(*head)->next;
    Node* temp=NULL;
    (*head)->next=NULL;
    while(old)
    {
        temp=old->next;
        old->next=NULL;
        old->next=*head;
        *head=old;
        old=temp;
    }
}
bool get_long_list(Node* head1,Node* head2)/*获取比较长的链表*/
{
    Node* temp1=head1;
    Node* temp2=head2;
    int head1_len=0,head2_len=0;
    while(temp1)
    {
        head1_len++;
        temp1=temp1->next;
    }
    while(temp2)
    {
        head2_len++;
        temp2=temp2->next;
    }
    return head1_len>=head2_len;
}
int add(Node* head1,Node* head2)/*利用链表实现两个大数相加*/
{
    Node* temp1=head1;
    Node* temp2=head2;
    if(get_long_list(temp1,temp2))
    {
        Node* temp3=temp1;
        while(temp3->next)
        {
            temp3=temp3->next;
        }
        Node* inode=new Node();
        inode->data=0;
        temp3->next=inode;
        while(temp2)
        {
            temp1->data=temp1->data+temp2->data;
            if(temp1->data>=10)
            {
               temp1->next->data++;
               temp1->data%=10;
            }
            temp2=temp2->next;
            temp1=temp1->next;
        }
        list_reverse(&head1);
        int num=0;
        while(head1)
        {
            num=num*10+head1->data;
            head1=head1->next;
        }
        return num;
    }
    else
    {
        Node* temp3=temp2;
        while(temp3->next)
        {
            temp3=temp3->next;
        }
        Node* inode=new Node();
        inode->data=0;
        temp3->next=inode;
        while(temp1)
        {
            temp2->data=temp1->data+temp2->data;
            if(temp2->data>10)
            {
               temp2->next->data++;
               temp2->data%=10;
            }
            temp2=temp2->next;
            temp1=temp1->next;
        }
        list_reverse(&head2);
        int num=0;
        while(head2)
        {
            num=num*10+head2->data;
            head1=head2->next;
        }
        return num;
    }
}
void make_two_list(Node** head1,Node** head2)
{
    PNode tail1=NULL;
    PNode tail2=NULL;
    srand(time(NULL));
    int index=0;
    while(index<N)
    {
        Node* inode1=new Node();
        inode1->data=rand()%9+1;
        Node* inode2=new Node();
        inode2->data=rand()%9+1;
        if(*head1==NULL&&*head2==NULL)
        {
            *head1=inode1;
            *head2=inode2;
        }
        else
        {
            tail1->next=inode1;
            tail2->next=inode2;
        }
        tail1=inode1;
        tail2=inode2;
        index++;
    }
    Node* inode=new Node();
    inode->data=rand()%9+1;
    tail1->next=inode;
    tail1=inode;
}

