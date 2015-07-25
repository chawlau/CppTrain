#include"queue.hpp"
#include<stack>
void stack_sort(std::stack<int> s)
{
    std::stack<int> r;
    while(!s.empty())
    {
        int temp=s.top();
        s.pop();
        while(!r.empty()&&r.top()<temp)
        {
           s.push(r.top());
           r.pop();
        }
        r.push(temp);
    }
    while(!r.empty())
    {
        std::cout<<r.top()<<" ";
        r.pop();
    }
    std::cout<<std::endl;
}
/* Test Sample*/
/*
int main(int argc,char** argv)
{
    srand(time(NULL));
    std::stack<int>* queue=new std::stack<int>();
    int num=0;
    while(num++!=N)
    {
        queue->push(rand()%20+1);
    }
    stack_sort(*queue);
}
*/
