#include<iostream>
#include<ctime>
#include<cstdlib>
#include<cstdio>
#include<queue>
#include<stack>
#define N 10
#define max(first,second,third)  (first>second?first:second)>third?(first>second?first:second):third
template<typename T> struct Result
{
    T distance,depth;
    Result(T dis=0,T dep=0):distance(dis),depth(dep){}
};
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
    /*插入节点*/
    void insert(const T& data)
    {
        BNode<T>* inode=new BNode<T>(data);
        insert_node(&m_root,inode);
    }
    /*递归中序遍历*/
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
    /*非递归中序遍历*/
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
    /*递归先序遍历*/
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
    /*非递归先序遍历*/
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
    /*递归后序遍历*/
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
    /*非递归后序遍历*/
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
    /*层次遍历*/
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

    /*二叉树高度*/
    int tree_height(BNode<T>* root)
    {
        int right=0,left=0;
        if(root==NULL)
        {
            return 0;
        }
        else
        {
            left=tree_height(root->lchild)+1;
            right=tree_height(root->rchild)+1;
            return left>right?left:right;
        }
    }
    /*比较两个二叉树是否相等*/
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
    /*错误解法
      Result<T> max_distance(BNode<T>* root)
      {
      if(!root)
      {
      Result<T> init;
      return init;
      }
      Result<T> left=max_distance(root->lchild);
      Result<T> right=max_distance(root->rchild);
      T depth=max(left.depth+1,right.depth+1);
      T distance=max(max(left.distance,right.distance),left.depth+right.depth+2);
      Result<T> result(depth,distance);
      return result;
      }*/
    /*先求子树的高度,然后计算距离*/
    int max_distance(BNode<T>* root)
    {
        int distance=0;
        if(!root)
        {
            return -1;
        }
        distance=tree_height(root->lchild)+tree_height(root->rchild);
        int left_dis=max_distance(root->lchild);
        int right_dis=max_distance(root->rchild);
        return max(left_dis,right_dis,distance);
    }
    /*计算节点间的最大距离*/
    int max_distance(BNode<T>* root, int& max_d)  
    {  
        //每碰到一个子节点，高度自增1，可以设空节点高度为-1，  
        //避免计算高度时对空节点的判断。  
        if (!root) return -1;  
        int left = max_distance(root->lchild, max_d) + 1;     
        int right = max_distance(root->rchild, max_d) + 1;   
        int distance= left+right;  
        if (max_d < distance) max_d = distance;  
        return  left>right ? left : right;  
    }  
    void rebuild(char* pre_order,char* in_order,int tree_len,BNode<T>** root)
    {
        BNode<T>* inode=new BNode<T>(*pre_order);
        if(*root==NULL)
        {
            *root=inode;
        }
        if(tree_len==1)
        {
            return;
        }
        char* start=pre_order;
        int left_len=0;
        while(*start!=*in_order)
        {
            left_len++;
            start++;
            if(left_len>tree_len)
            {
                break;
            }
        }
        int right_len=tree_len-left_len-1;
        if(left_len>0)
        {
            rebuild(pre_order+1,in_order,left_len,&((*root)->lchild));
        }
        if(right_len>0)
        {
            rebuild(pre_order+left_len+1,in_order+left_len+1,right_len,&((*root)->rchild));
        }
    }
};
