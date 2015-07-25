#include"queue.hpp"
int get_value(char& c_left,char& c_right,char& ope)
{
    int left=(int)(c_left-'0');
    int right=(int)(c_right-'0');
    switch(ope)
    {
        case '+':
            return left+right;
        case '-':
            return left-right;
        case '*':
            return left*right;
        case '/':
            return left/right;
    }
}
void get(Stack<char>* stack)
{
    char right;
    char ope;
    char left;
    right=stack->top();
    stack->pop();
    ope=stack->top();
    stack->pop();
    left=stack->top();
    stack->pop();
    char result=get_value(left,right,ope)+'0';
    stack->push(result);
}
void calculate(char* exp,int& sum)
{
    Stack<char>* stack=new Stack<char>();
    char* num=exp;
    while(*num++!='\0')
    {
        if(*num==')')
        {
            get(stack);
            stack->pop();
        }
        stack->push(*num);
    }
    while(stack->top()=='*'||stack->top()=='/')
    {
        get(stack);
    }
    while(stack->size()!=1)
    {
        get(stack);
    }
    sum=stack->top()-'0';
    stack->destroy();
}
int main(int argc,char** argv)
{
    char exp[]="1+(2+3)*5";
    int sum=0;
    calculate(exp,sum);
    std::cout<<sum<<std::endl;
}
