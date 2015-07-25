#include<iostream>
#include<cassert>
struct Node
{
    Node(int m_data):data(m_data){}
    int data;
    Node* next;
};
void create_list(Node** head)
{
    for(int index=0;index!=10;index++)
    {
        Node* inode=new Node(index);
        inode->next=*head;
        *head=inode;
    }
}
void list_out(Node* head)
{
    while(head)
    {
        std::cout<<head->data<<" ";
        head=head->next;
    }
    std::cout<<std::endl;
}
void printlist(Node* head)
{
    if(head->next)
    {
        printlist(head->next);
    }
    std::cout<<" "<<head->data;
}
int main(int argc,char** argv)
{
    Node* head=NULL;
    create_list(&head);
    list_out(head);
    printlist(head);
}

