#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<ctime>
#include"stack.hpp"
#define N 10
/*
   template<typename T> struct Node
   {
   T m_data;
   Node* m_next;
   Node(T data=0,Node* next=NULL):m_data(data),m_next(next){}
   };*/
template<typename T> struct Queue
{
    int m_size;
    Node<T>* m_front;
    Node<T>* m_rear;
    Queue(int size=0,Node<T>* front=NULL,Node<T>* rear=NULL):m_size(size),m_front(front),m_rear(rear){}
    void insert(const T& data)
    {
        Node<T>* inode=new Node<T>(data);
        if(m_front==NULL)
        {
            m_front=inode;
        }
        else
        {
            m_rear->m_next=inode;
        }
        m_rear=inode;
        m_size++;
    }
    void Delete()
    {
        if(m_size==0)
            return;
        Node<T>* temp=m_front;
        m_front=temp->m_next;
        delete temp;
        m_size--;
    }
    T& front()
    {
        if(m_size==0)
        {
            return 0;
        }
        return m_front->m_data;
    }
    void destroy()
    {
        while(m_front)
        {
            Delete();
        }
        m_rear=NULL;
    }
    void show()
    {
        Node<T>* temp=m_front;
        while(temp)
        {
            std::cout<<temp->m_data<<" ";
            temp=temp->m_next;
        }
        std::cout<<std::endl;
    }
    bool empty()
    {
        return m_size==0;
    }
};
template<typename T> struct Conbine_queue
{
    Stack<T> s1,s2;
    Conbine_queue(){} 
    int size()
    {
        return s1.m_size+s2.m_size;
    }
    bool empty()
    {
        return size()==0;
    }
    void insert(const T& data)
    {
        s1.push(data);
    }
    void Delete()
    {
        if(empty())
        {
            return ;
        }
        if(!s2.empty())
        {
            s2.pop();
        }
        else
        {
            while(!s1.empty())
            {
                T data=s1.top();
                s1.pop();
                s2.push(data);
            }
            s2.pop();
        }
    }
    T& front()
    {
        if(!empty())
        {
            if(!s2.empty())
            {
                return s2.top();
            }
            else
            {
                T data;
                while(!s1.empty())
                {
                    data=s1.top();
                    s1.pop();
                    s2.push(data);
                }
                return s2.top();
            }
        }
    }
    void show()
    {
        T data;
        while(!s1.empty())
        {
            T data=s1.top();
            s1.pop();
            s2.push(data);
        }
        s2.show();
    }
    void destroy()
    {
        s1.destroy();
        s2.destroy();
    }
};
