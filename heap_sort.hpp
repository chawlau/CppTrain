#include<iostream>
#include<ctime>
#include<cstdlib>
#include<cstdio>
void swap(int& a,int &b)
{
    a=a^b;
    b=a^b;
    a=a^b;
}
void adjust(int* arr,int index,int end)/*自顶向下调整,保持堆顶是最大的元素*/
{
    int key=arr[index];
    int child=(index<<1)+1;
    while(child<=end)
    {
        if(child+1<=end)
        {
            if(arr[child]<arr[child+1])
            {
                child++;
            }
        }
        if(arr[child]<=key)
        {
            break;
        }
        arr[index]=arr[child];
        index=child;
        child=(index<<1)+1;
    }
    arr[index]=key;
}
void heap_sort(int* arr,int len)
{
    for(int index=(len-1-1)>>1;index>=0;index--)
    {
        adjust(arr,index,len-1);
    }
    for(int index=len-1;index>=0;index--)
    {
        swap(arr[0],arr[index]);
        adjust(arr,0,index-1);
    }
}
/*测试代码*/
/*
int main(int argc,char** argv)
{
    srand(time(NULL));
    int* arr= new int[10]();
    for(int index=0;index!=10;index++)
    {
        arr[index]=rand()%20+1;
        std::cout<<arr[index]<<" ";
    }
    std::cout<<std::endl;
    heap_sort(arr,10);
    for(int index=0;index!=10;index++)
    {
        std::cout<<arr[index]<<" ";
    }
    std::cout<<std::endl;
}*/
