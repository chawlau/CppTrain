#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<ctime>
#define N 10
template<typename T> struct Node
{
    T m_data;
    struct Node* m_next;
    Node(T data=0,Node* next=NULL):m_data(data),m_next(next){};
};
template<typename T> struct Stack
{
    int m_size;
    Node<T>* m_head;
    Stack(int size=0,Node<T>* head=NULL):m_size(size),m_head(head){}
    void init()
    {
        m_head=NULL;
        m_size=0;
    }
    void push(const T& data)
    {
        Node<T>* inode=new Node<T>(data);
        inode->m_next=m_head;
        m_head=inode;
        m_size++;
    }
    int& size()
    {
        return m_size;
    }
    void pop()
    {
        if(m_size==0)
            return;
        Node<T>* temp=m_head;
        m_head=temp->m_next;
        delete temp;
        m_size--;
    }
    T& top()
    {
        if(m_size!=0)
        {
           return m_head->m_data;
        }
    }
    void destroy()
    {
        while(m_head)
        {
            pop();
        }
    }
    bool empty()
    {
        return m_size==0;
    }
    void show()
    {
        Node<T>* temp=m_head;
        while(temp)
        {
            std::cout<<temp->m_data<<" ";
            temp=temp->m_next;
        }
        std::cout<<std::endl;
    }
};

