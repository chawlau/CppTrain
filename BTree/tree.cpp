#include"BTree.hpp"
int main(int argc,char** argv)
{
    int num=0;
    //srand(time(NULL));
    BTree<int>* btree=new BTree<int>();
    BTree<int>* btree1=new BTree<int>();
    BTree<int>* btree2=new BTree<int>();
    btree2->insert(8);
    btree2->insert(6);
    btree2->insert(10);
    btree2->insert(5);
    btree2->insert(7);
    btree2->insert(9);
    btree2->insert(12);
    btree2->insert(11);
    while(num++!=N)/*建立二叉树*/
    {
        int data=rand()%20+1;
        btree->insert(data);
        btree1->insert_t(data);
    }
    if(btree->search(btree->m_root,7))/*查找二叉树一个特定的值*/
    {
        std::cout<<"find"<<std::endl;
    }
    BNode<int>* ret;
    if(ret=btree->search_min(btree->m_root))/*查找二叉树最小的值*/
    {
        std::cout<<"min:"<<ret->m_data<<std::endl;
    }
    if(ret=btree->search_max(btree->m_root))/*查找二叉树最大的值*/
    {
        std::cout<<"max:"<<ret->m_data<<std::endl;
    }
    if(btree->judge_BST())/**/
    {
        std::cout<<"btree is  BST"<<std::endl;
    }
    if(!btree1->judge_BST())/**/
    {
        std::cout<<"btree1 is not BST"<<std::endl;
    }
    if(btree2->judge_BST())/**/
    {
        std::cout<<"btree2 is  BST"<<std::endl;
    }
    int max_d=0;
    std::cout<<"tree height :"<<btree2->tree_height(btree2->m_root)<<std::endl;
    btree2->max_distance(btree2->m_root,max_d);
    std::cout<<"max distance : "<<max_d<<std::endl;
    std::cout<<"get height first :"<<btree2->max_distance(btree2->m_root)<<std::endl;
    btree2->print_inline();
    std::cout<<"pre order -------------------"<<std::endl;
    btree2->pre_order();
    std::cout<<"in order -------------------"<<std::endl;
    btree2->in_order();
    std::cout<<"postorder -------------------"<<std::endl;
    btree2->post_order();
    std::cout<<std::endl;
}
