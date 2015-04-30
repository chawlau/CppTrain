#include<iostream>
#include<ctime>
#include<cstdlib>
#include<cstdio>
#include<queue>
#include<stack>
#define N 10
#define max(first,second,third)  (first>second?first:second)>third?(first>second?first:second):third
#define max_dp(first,second)   (first>second?first:second)
#define min(first,second)   (first<second?first:second)
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
    BNode<T>* parent;
    int ltag;
    int rtag;
    BNode(T data=0):m_data(data),rchild(NULL),lchild(NULL),parent(NULL),ltag(0),rtag(0){}
};
template<typename T> struct BTree
{
    BNode<T>* m_root;
    BNode<T>* index;
    BNode<T>* pre;
    T m_data;
    BTree(BNode<T>* root=NULL,T data=0):m_root(root),m_data(data),pre(NULL){}
    void insert_node(BNode<T>** root,BNode<T>* p)
    {
        if(*root==NULL)
        {
            *root=p;
            return;
        }
        if(p->m_data<(*root)->m_data&&(*root)->lchild==NULL)
        {
            p->parent=*root;
            (*root)->lchild=p;
            return;
        }
        else if(p->m_data>(*root)->m_data&&(*root)->rchild==NULL)
        {
            p->parent=*root;
            (*root)->rchild=p;
            return ;
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
    void insert_node_t(BNode<T>** root,BNode<T>* p)
    {
        if(*root==NULL)
        {
            *root=p;
            return;
        }
        if(p->m_data>(*root)->m_data)
        {
            insert_node(&((*root)->lchild),p);
        }
        else
        {
            insert_node(&((*root)->rchild),p);
        }
    }
    /*插入节点*/
    void insert_t(const T& data)
    {
        BNode<T>* inode=new BNode<T>(data);
        insert_node_t(&m_root,inode);
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
                std::cout<<"current data: "<<start->m_data;
                std::cout<<"pre: "<<get_pre_pre(start)<<"post: "<<get_pre_suc(start);
                if(start->parent)
                {
                    std::cout<<"-->father node data: "<<start->parent->m_data;
                }
                std::cout<<std::endl;
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
    T get_pre_pre(BNode<T>* root)//先序遍历的前驱节点修正版本，待修改
    {
        if(root==NULL)
        {
            return 0;
        }
        BNode<T>* father=root->parent;
        if(!father)
        {
            return 0;
        }
        if(root==father->lchild)
        {
            return father->m_data;
        }
        else if(root==father->rchild)
        {
            if(!father->lchild)
            {
                return 0;
            }
            BNode<T>* child=father->lchild;
            while(child->rchild||child->lchild)
            {
                while(child->rchild)
                {
                    child=child->rchild;
                }
                while(child->lchild)
                {
                    child=child->lchild;
                }
            }
            return child->m_data;
        }
    }
    T get_pre_suc(BNode<T>* root)// 先序遍历的后继节点,比较特殊四种情况都可以
    {
        if(root==NULL)
        {
            return 0;
        }
        if(root->lchild)
        {
            return root->lchild->m_data;
        }
        else if(root->rchild)
        {
            return root->rchild->m_data;
        }
        else if(root->parent&&root==root->parent->lchild)
        {
            BNode<T>* father=root->parent;
            if(!father->rchild)
            {
                return 0;
            }
            return father->rchild->m_data;
        }
        else if(root->parent&&root==root->parent->rchild)
        {
            BNode<T>* father=root->parent;
            BNode<T>* current=root;
            while(father&&current==father->rchild)
            {
                current=father;
                father=father->parent;
            }
            if(!father->rchild)
            {
                return 0;
            }
            return father->rchild->m_data;
        }
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
                s.pop();
                std::cout<<"current data: "<<start->m_data;
                if(start->parent)
                {
                    std::cout<<"-->father node data: "<<start->parent->m_data;
                }
                if(T suc=get_suc(start))
                {
                    std::cout<<"-->succed node data: "<<suc;
                }
                else
                {
                    std::cout<<"--> no succed node data: ";
                }
                if(T pre=get_pre(start))
                {
                    std::cout<<"-->preval node data: "<<pre;
                }
                else
                {
                    std::cout<<"--> no preval node data: ";
                }
                std::cout<<std::endl;
                start=start->rchild;
            }
        }
        std::cout<<std::endl;
    }
    T get_pre(BNode<T>* root)/*查找一个中序遍历二叉树节点的前驱节点*/
    {
        if(root==NULL)
        {
            return 0;
        }
        if(root->lchild)
        {
            BNode<T>* start=root->lchild;
            while(start->rchild)
            {
                start=start->rchild;
            }
            return start->m_data;
        }
        else if(root->parent)
        {
            BNode<T>* father=root->parent;
            BNode<T>* current=root;
            while(father&&father->lchild==current)
            {
                current=father;
                father=father->parent;
            }
            if(father)
            {
                return father->m_data;
            }
            return 0;
        }
    }
    T get_suc(BNode<T>* root)/*查找一个中序遍历二叉树节点的后继节点*/
    {
        if(root==NULL)
        {
            return 0;
        }
        if(root->rchild)
        {
            BNode<T>* right=root->rchild;
            while(right->lchild)
            {
                right=right->lchild;
            }
            return right->m_data;
        }
        else if(root->parent)
        {
            BNode<T>* father=root->parent;
            BNode<T>* current=root;
            while(father&&father->rchild==current)
            {
                current=father;
                father=father->parent;
            }
            if(father)
            {
                return father->m_data;
            }
            return 0;
        }
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
            while(start)
            {
                s.push(start);
                start=start->lchild;
            }
            if(!s.empty())
            {
                start=s.top();
                if(start->rchild&&(start->rchild)!=visit)//有右孩子先不弹栈,将右孩子压栈然后再遍历才弹栈
                {
                    start=start->rchild;
                    s.push(start);
                    start=start->lchild;
                }
                else              //没有右孩子才开始弹栈
                {
                    start=s.top();
                    s.pop();
                    visit=start;
                    std::cout<<"current data: "<<start->m_data;
                    std::cout<<"pre: "<<get_post_pre(start)<<"post: "<<get_post_suc(start);
                    if(start->parent)
                    {
                        std::cout<<"-->father node data: "<<start->parent->m_data;
                    }
                    std::cout<<std::endl;
                    start=NULL;
                }
            }
        }
        std::cout<<std::endl;
    }
    T get_post_pre(BNode<T>* root)//获取后序遍历的前驱节点
    {
        if(!root)
        {
            return 0;
        }
        if(root->rchild)
        {
            return root->rchild->m_data;
        }
        else if(root->lchild)
        {
            return root->lchild->m_data;
        }
        else if(root->parent)
        {
            BNode<T>* father=root->parent;
            BNode<T>* current=root;
            while(father&&current==father->lchild)
            {
                current=father;
                father=father->parent;
            }
            if(father&&father->lchild)
            {
                return father->lchild->m_data;
            }
            return 0;
        }
        return 0;
    }
    T get_post_suc(BNode<T>* root)// 获取后序遍历的后继节点
    {
        if(!root||!root->parent)
        {
            return 0;
        }
        if(root==root->parent->rchild)
        {
            return root->parent->m_data;
        }
        else if(root==root->parent->lchild&&!root->parent->rchild)
        {
            return root->parent->m_data;
        }
        else if(root==root->parent->lchild&&root->parent->rchild)
        {
            BNode<T>* start=root->parent->rchild;
            while(start->lchild||start->rchild)
            {
                while(start->lchild)
                {
                    start=start->lchild;
                }
                while(start->rchild)
                {
                    start=start->rchild;
                }
            }
            return start->m_data;
        }
        return 0;
    }
    /*层次遍历*/
    void level_order()
    {
        std::cout<<__func__<<":"<<__LINE__<<std::endl;
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
            std::cout<<p->m_data<<" ";
            if(p->lchild)
            {
                restore.push(p->lchild);
            }
            if(p->rchild)
            {
                restore.push(p->rchild);
            }
        }
    }
    /*按行打印二叉树*/
    void print_inline()
    {
        std::cout<<__func__<<":"<<__LINE__<<std::endl;
        std::queue<BNode<T>*> restore;
        if(m_root==NULL)
        {
            return;
        }
        restore.push(m_root);
        int nextLevel=0;
        int toBePrinted=1;
        while(!restore.empty())
        {
            BNode<T>* p=restore.front();
            std::cout<<p->m_data<<" ";
            if(p->lchild)
            {
                restore.push(p->lchild);
                nextLevel++;
            }
            if(p->rchild)
            {
                restore.push(p->rchild);
                nextLevel++;
            }
            restore.pop();
            if(--toBePrinted==0)
            {
                std::cout<<std::endl;
                toBePrinted=nextLevel;
                nextLevel=0;
            }
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
    void pre_build(char* pre_order,char* in_order,int tree_len,BNode<T>** root)
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
        char* start=in_order;
        int left_len=0;
        while(*start!=*pre_order)
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
            pre_build(pre_order+1,in_order,left_len,&((*root)->lchild));
        }
        if(right_len>0)
        {
            pre_build(pre_order+left_len+1,in_order+left_len+1,right_len,&((*root)->rchild));
        }
    }
    void post_build(char* post_order,char* in_order,int tree_len,BNode<T>** root)
    {
        BNode<T>* inode=new BNode<T>(*(post_order+tree_len-1));
        if(*root==NULL)
        {
            *root=inode;
        }
        if(tree_len==1)
        {
            return;
        }
        char* start=in_order;
        int left_len=0;
        while(*start!=*(post_order+tree_len-1))
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
            post_build(post_order,in_order,left_len,&((*root)->lchild));
        }
        if(right_len>0)
        {
            post_build(post_order+left_len,in_order+left_len+1,right_len,&((*root)->rchild));
        }
    }
    BNode<T>* search(BNode<T>*root,T key)/*二叉树的查找*/
    {
        if(root==NULL)
        {
            return NULL;
        }
        if(root->m_data==key)
        {
            return root; 
        }
        else if(root->m_data>key)
        {
            search(root->lchild,key);
        }
        else
        {
            search(root->rchild,key);
        }
    }
    BNode<T>* search_min(BNode<T>* root)
    {
        if(root==NULL)
        {
            return NULL;
        }
        if(root->lchild==NULL)
        {
            return root;
        }
        else
        {
            return search_min(root->lchild);
        }
    }
    BNode<T>* search_max(BNode<T>* root)
    {
        if(root==NULL)
        {
            return NULL;
        }
        if(root->rchild==NULL)
        {
            return root;
        }
        else
        {
            return search_max(root->rchild);
        }
    }
    bool judge_BST(BNode<T>* root,T lowbound)/*判定一棵二叉树是不是排序二叉树*/
    {
        if(root==NULL)
        {
            return true;
        }
        else
        {
            if(!judge_BST(root->lchild,lowbound)||lowbound>root->m_data)
            {
                return false;
            }
            lowbound=root->m_data;
            return judge_BST(root->rchild,lowbound);
        }
    }
    bool judge_BST()//非递归判断一棵树是不是排序树
    {
        if(m_root==NULL)
        {
            return true;
        }
        std::stack<BNode<T>*> s;
        BNode<T>* start=m_root;
        BNode<T>* temp;
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
                s.pop();//有没有右孩子该节点都要弹栈
                if(start->rchild)//如果有右孩子则和右孩子比较
                {
                    temp=start->rchild;
                }
                else if(!s.empty())//如果没有右孩子直接和栈顶元素比较
                {
                    temp=s.top() ;
                }
                else
                {
                    break;
                }
                if(start->m_data>temp->m_data)
                {
                    return false;
                }
                start=start->rchild;
            }
        }
        return true;
    }
    void thread(BNode<T>* root)//将一个二叉树节点添加线索
    {
        if(root==NULL)
        {
            return;
        }
        thread(root->lchild);
        if(root->lchild==NULL)
        {
            root->lchild=pre;
            root->ltag=1;
        }
        if(pre->rchild==NULL)
        {
            pre->rchild=root;
            pre->rtag=1;
        }
        pre=root;
        thread(root->rchild);
    }
    void create_thread()//将一个二叉树线索化
    {
        index=new BNode<T>();
        index->rtag=1;
        index->ltag=0;
        if(m_root==NULL)
        {
            index->lchild=index;
            return;
        }
        index->lchild=m_root;
        pre=index;
        thread(m_root);
        pre->rchild=index;
        pre->rtag=1;
        index->rchild=pre;
        std::cout<<"index tree create"<<std::endl;
        std::cout<<"index lchild--> root"<<index->lchild->m_data<<std::endl;
        std::cout<<"index rchild--> tree last node"<<index->rchild->m_data<<std::endl;
    }
    void index_visit()//中序顺序线索遍历二叉树
    {
        BNode<T>* start=index->lchild;
        while(start!=index)
        {
            while(start->ltag==0)
            {
                start=start->lchild;
            }
            std::cout<<start->m_data<<" ";
            while(start->rtag==1&&start->rchild!=index)
            {
                start=start->rchild;
                std::cout<<start->m_data<<" ";
            }
            start=start->rchild;// 有右孩子的节点
        }
        std::cout<<std::endl;
    }
    void index_rvisit()//中序逆序线索遍历二叉树
    {
        BNode<T>* end=index->rchild;
        while(end!=index)
        {
            while(end->rtag==0)
            {
                end=end->rchild;
            }
            std::cout<<end->m_data<<" ";
            while(end->ltag==1&&end->lchild!=index)//有前驱的节点
            {
                end=end->lchild;
                std::cout<<end->m_data<<" ";
            }
            end=end->lchild;//有左孩子的节点
        }
        std::cout<<std::endl;
    }
    void serialize(BNode<T>* root)//序列化二叉树
    {
        if(root==NULL)
        {
            std::cout<<"$,";
            return;
        }
        std::cout<<root->m_data<<",";
        serialize(root->lchild);
        serialize(root->rchild);
    }
    T kthnode(int k)// 求一个二叉树中第K大的数
    {
        if(m_root==NULL||k==0)
        {
            return -1;
        }
        return kthnode(m_root,k);
    }
    T  kthnode(BNode<T>* root,int& k)
    {
        T target=0;
        if(root->lchild)
        {
            target=kthnode(root->lchild,k);
        }
        if(!target)
        {
            if(k==1)
            {
                target=root->m_data;
            }
            k--;
        }
        if(!target&&root->rchild)
        {
            target=kthnode(root->rchild,k);
        }
        return target;
    }
    int max_depth(BNode<T>* root)
    {
        if(root==NULL)
        {
            return 0;
        }
        return  1+max_dp(max_depth(root->lchild),max_depth(root->rchild)); 
    }
    int min_depth(BNode<T>* root)
    {
        if(root==NULL)
        {
            return 0;
        }
        return 1+min(min_depth(root->lchild),min_depth(root->rchild));
    }
    bool isbanlance()//判定一棵树是不是平衡二叉树
    {
        return max_depth(m_root)-min_depth(m_root)<=1;
    }
};
