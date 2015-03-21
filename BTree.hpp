#include<iostream>
#include<ctime>
#include<cstdlib>
#include<cstdio>
#include<queue>
#include<stack>
#define N 10
template<typename T> struct BNode
{
    T m_data;
    BNode<T>* rchild;
    BNode<T>* lchild;
    BNode(T data=0):m_data(data),rchild(NULL),lchild(NULL){}
};
template<typename T> struct BTree
{
    BNode<T>* m_root;
    T m_data;
    BTree(BNode<T>* root=NULL,T data=0):m_root(root),m_data(data){}
    void insert_node(BNode<T>** root,BNode<T>* p)
    {
        if(*root==NULL)
        {
            *root=p;
            return;
        }
        if(p->m_data<(*root)->m_data)
        {
            insert_node(&((*root)->lchild),p);
        }
        else
        {
            insert_node(&((*root)->rchild),p);
        }
    }
    void insert(const T& data)
    {
        BNode<T>* inode=new BNode<T>(data);
        insert_node(&m_root,inode);
    }
    void in_order(BNode<T>* node)
    {
        if(node==NULL)
        {
            return;
        }
        in_order(node->lchild);
        std::cout<<node->m_data<<" ";
        in_order(node->rchild);
    }
    void in_order()
    {
        if(m_root==NULL)
        {
            return;
        }
        std::stack<BNode<T>*> s;
        BNode<T>* start=m_root;
        std::cout<<__func__<<":"<<__LINE__<<std::endl;
        while(start||!s.empty())
        {
            while(start)
            {
                s.push(start);
                start=start->lchild;
            }
            if(!s.empty())
            {
                start=s.top();
                std::cout<<start->m_data<<" ";
                s.pop();
                start=start->rchild;
            }
        }
        std::cout<<std::endl;
    }
    void pre_order(BNode<T>* node)
    {
        if(node==NULL)
        {
            return;
        }
        std::cout<<node->m_data<<" ";
        pre_order(node->lchild);
        pre_order(node->rchild);
    }
    void pre_order()
    {
        if(m_root==NULL)
        {
            return;
        }
        std::stack<BNode<T>*> s;
        BNode<T>* start=m_root;
        std::cout<<__func__<<":"<<__LINE__<<std::endl;
        while(start||!s.empty())
        {
            while(start)
            {
                std::cout<<start->m_data<<" ";
                s.push(start);
                start=start->lchild;
            }
            if(!s.empty())
            {
                start=s.top();
                s.pop();
                start=start->rchild;
            }
        }
        std::cout<<std::endl;
    }
    void post_order(BNode<T>* node)
    {
        if(node==NULL)
        {
            return;
        }
        post_order(node->lchild);
        post_order(node->rchild);
        std::cout<<node->m_data<<" ";
    }
    void level_order()
    {
        std::queue<BNode<T>*> restore;
        if(m_root==NULL)
        {
            return;
        }
        restore.push(m_root);
        while(!restore.empty())
        {
            BNode<T>* p=restore.front();
            restore.pop();
            if(p->lchild)
            {
                restore.push(p->lchild);
            }
            if(p->rchild)
            {
                restore.push(p->rchild);
            }
            std::cout<<p->m_data<<" ";
        }
        std::cout<<std::endl;
    }
    void post_order()
    {
        if(m_root==NULL)
        {
            return;
        }
        std::stack<BNode<T>*> s;
        BNode<T>* start=m_root;
        BNode<T>* visit=NULL;
        std::cout<<__func__<<":"<<__LINE__<<std::endl;
        while(start||!s.empty())
        {
            if(start)
            {
                s.push(start);
                start=start->lchild;
            }
            else
            {
                start=s.top();
                if(start->rchild&&(start->rchild)!=visit)
                {
                    start=start->rchild;
                    s.push(start);
                    start=start->lchild;
                }
                else
                {
                    start=s.top();
                    s.pop();
                    visit=start;
                    std::cout<<start->m_data<<" ";
                    start=NULL;
                }
            }
        }
        std::cout<<std::endl;
    }
    int tree_height(BNode<T>* root)
    {
        if(root==NULL)
        {
            return -1;
        }
        int right=0,left=0;
        left=tree_height(root->lchild)+1;
        right=tree_height(root->rchild)+1;
        return left>right?left:right;
    }
    bool is_equal(BNode<T>* node1,BNode<T>* node2)
    {
        if(node1==NULL&&node2==NULL)
        {
            return true;
        }
        if(!node1||!node2)
        {
            return false;
        }
        if(node1->m_data==node2->m_data)
        {
            return is_equal(node1->rchild,node2->rchild)&&is_equal(node1->lchild,node2->lchild);
        }
        else
        {
            return false;
        }
    }
};
