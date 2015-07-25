#include<iostream>
int func(int m,int n)
{
    if(m%n==0)
    {
        return n;
    }
    else 
    {
        return func(n,m%n);
    }
}
template<typename T> class stack
{
    stack(){}
};
void fi(stack<char>)
{}
class Ex
{
    stack<double> &rs;
    stack<int> si;
};
int main(int argc,char** argv)
{
    stack<char> *sc;
    fi(*sc);
    int i=sizeof(stack<std::string>);
    return 0;
}
