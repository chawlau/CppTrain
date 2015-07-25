#include"queue.hpp"
int main(int argc,char** argv)
{
    Queue<int>* queue=new Queue<int>();    
    srand(time(NULL));
    int n=0;
    while(n++!=N)
    {
        queue->insert(rand()%26+1);
    }
    queue->show();
    std::cout<<queue->m_size<<std::endl;
    queue->Delete();
    queue->show();
    std::cout<<queue->m_size<<std::endl;
    std::cout<<queue->front()<<std::endl;
    std::cout<<queue->m_size<<std::endl;
    queue->destroy();
    std::cout<<queue->empty()<<std::endl;
}

