#include<iostream>
#include<vector>
int get_max_sum(const std::vector<int>& data)//全是负数直接排序就好了
{
    int maxsum=0;
    int sum=0;
    for(int index=0;index!=data.size();index++)
    {
        sum+=data[index];
        if(maxsum<sum)
        {
            maxsum=sum;
        }
        else if(sum<0)
        {
            sum=0;
        }
    }
    std::cout<<maxsum<<std::endl;
    return maxsum;
}
int main(int argc,char** argv)
{
    std::vector<int> data;
    data.push_back(-2);
    data.push_back(-5);
    data.push_back(-3);
    data.push_back(-6);
    data.push_back(-4);
    data.push_back(-8);
    data.push_back(-6);
    get_max_sum(data);
}

