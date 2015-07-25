#include"BTree.hpp"
#include<cstring>
int main(int argc,char** argv)
{
    //char pre_order[]="abdcef";
    char post_order[]="dbefca";
    char in_order[]="dbaecf";
    int treelen=strlen(in_order);
    BTree<char>* tree=new BTree<char>();
    tree->post_build(post_order,in_order,treelen,&(tree->m_root));
    //tree->pre_build(pre_order,in_order,treelen,&(tree->m_root));
    //tree->post_order();
    std::cout<<tree->tree_height(tree->m_root)<<std::endl;
    tree->pre_order();
    tree->post_order();
    tree->in_order();
    tree->level_order();
}
