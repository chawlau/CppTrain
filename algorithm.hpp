#include<iostream>
#include<cstring>
#include<cstdio>
#include<cstdlib>
#include<ctime>
#include<vector>
#define N 10
    template<typename T>
void swap(T* a,T* b)
{
    T temp=*a;
    *a=*b;
    *b=temp;
}
    template<typename T>
void arr_out(T* data,T num)
{
    for(T index=0;index!=num;index++)
    {
        std::cout<<data[index]<<" ";
    }
    std::cout<<std::endl;
}
/*快慢指针法*/
int fast_slow_split(int* a,int num)
{
    int index_i=0;
    for(int index_j=1;index_j!=num;index_j++)
    {
        if(a[index_j]<=a[0])
        {
            int temp_data=a[index_i+1];
            a[++index_i]=a[index_j];
            a[index_j]=temp_data;
            //swap(&a[index_i++],&a[index_j]);
        }
    }
    swap(&a[index_i],&a[0]);
    return index_i;
}
/*前后指针分割法*/
int  pivot_split(int* a,int num)
{
    int pivot=a[0];
    int pre=0;
    int post=num-1;
    while(pre<post)
    {
        while(pre<post)
        {
            if(a[post]<=pivot)
            {
                a[pre]=a[post];
                break;
            }
            post--;
        }
        while(pre<post)
        {
            if(a[pre]>pivot)
            {
                a[post]=a[pre];
                break;
            }
            pre++;
        }
    }
    a[pre]=pivot;
    return pre;
}
/*快速排序*/
void quick_sort(int* a,int num)
{
    if(num<=1)
        return ;
    int k=fast_slow_split(a,num);
    //int k=pivot_split(a,num);
    quick_sort(a,k);
    quick_sort(a+k+1,num-k-1);
}
/*求一个数组中除自己外所有数的乘积*/
void multiple(int*a,int num)
{
    int* result=new int[num]();
    for(int index_i=0;index_i!=num;index_i++)
    {
        int left=1,right=1;
        int index_j=0;
        for(index_j;index_j!=index_i;index_j++)
        {
            left*=a[index_j];
        }
        for(index_j=index_i+1;index_j!=num;index_j++)
        {
            right*=a[index_j];
        }
        std::cout<<"left is"<<left<<std::endl;
        std::cout<<"right is"<<right<<std::endl;
        result[index_i]=left*right;
    }
    arr_out(result,num);
    delete [] result;
}
/*找出一个数组中最大数和最小数*/
void get_Max_Min(int* a,int num,int& Max,int& Min)
{

    if(num/2==0)
    {
        Max=a[0]>a[1]?a[0]:a[1];
        Min=a[0]<a[1]?a[0]:a[1];
        for(int index=2;index<num&&index+1<num;index+=2)
        {
            if(a[index]<a[index+1])
            {
                Max=Max>a[index+1]?Max:a[index+1];
                Min=Min<a[index]?Min:a[index];
            }
            else
            {
                Max=Max>a[index]?Max:a[index];
                Min=Min<a[index+1]?Min:a[index+1];
            }
            std::cout<<"Max is "<<Max<<std::endl;
            std::cout<<"Min is "<<Min<<std::endl;
        }
    }
    else
    {
        Max=a[0];
        Min=a[0];
        for(int index=1;index<num&&index+1<num;index+=2)
        {
            if(a[index]<a[index+1])
            {
                Max=Max>a[index+1]?Max:a[index+1];
                Min=Min<a[index]?Min:a[index];
            }
            else
            {
                Max=Max>a[index]?Max:a[index];
                Min=Min<a[index+1]?Min:a[index+1];
            }
            std::cout<<"Max is "<<Max<<std::endl;
            std::cout<<"Min is "<<Min<<std::endl;
        }
    }
    std::cout<<"Max is "<<Max<<std::endl;
    std::cout<<"Min is "<<Min<<std::endl;
}
/*找去一个数组中占一半数的数*/
int half_data(int* a,int num)
{
    int axis_cnt=0;
    int axis_data=0;
    for(int index=0;index!=num;index++)
    {
        if(axis_cnt==0)
        {
            axis_data=a[index];   
            axis_cnt=1;
        }
        else
        {
            if(axis_data==a[index])
            {
                axis_cnt++;
            }
            else
            {
                axis_cnt--;
            }
        }
    }
    return axis_data;
}
/*找出专门是最小值的数组集合*/
int* small_large(int* a,int num)
{
    int* small=new int[num]();
    small[num-1]=a[num-1];
    for(int index=num-2;index!=-1;index--)
    {
        if(a[index]<small[index+1])
        {
            small[index]=a[index];
        }
        else
        {
            small[index]=small[index+1];
        }
    }
    return small;
}
/*从头到尾逐步推进*/
void lsrb(int* a,int num)
{
    int* small=small_large(a,num);
    int left_max=0;
    for(int index=0;index!=num;index++)
    {
        if(a[index]>left_max)
        {
            left_max=a[index];//最大值是逐渐向右推进的
            if(a[index]==small[index])
            {
                std::cout<<a[index]<<" ";
            }
        }
    }
    std::cout<<std::endl;
    delete [] small;
}
/*数组法解决约瑟夫环的问题*/
int& yesef(int* a,int num,int mod)
{
    int flag=0;
    for(int index=0,value=num;value!=1;index=(index+1)%num)
    {
        if(flag!=mod&&a[index]!=0)
        {
            flag++;
        }
        if(flag==mod)
        {
            std::cout<<"delete : "<<a[index]<<std::endl;
            a[index]=0;
            flag=0;
            value--;
        }
    }
    for(int index_j=0;index_j!=num;index_j++)
    {
        if(a[index_j]!=0)
        {
            return a[index_j];
        }
    }
}
struct node
{
    int data;
    struct node *next;
};
typedef struct node Node;
typedef struct node *PNode;
int& yeseflist(Node* head,int mod)
{
    PNode pnew=head;
    int cnt=1;
    while(pnew->next!=pnew)
    {
        if(cnt!=mod)
        {
            cnt++;
            pnew=pnew->next;
        }
        if(cnt==mod)
        {
            std::cout<<"delete : "<<pnew->data<<std::endl;
            pnew->data=pnew->next->data;
            pnew->next=pnew->next->next;
            cnt=1;
        }
    }
    return pnew->data;
}
