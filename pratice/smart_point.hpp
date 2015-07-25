#include<iostream>
#include<cstring>
#include<stdexcept>
//class String;
//std::ostream& operator<<(std::ostream& out,String& obj);
class Ref_cnt
{
    friend class String;
    int m_cnt;
    int m_size;
    char* m_ptr;
    Ref_cnt(int size=0,int cnt=1):m_ptr(new char[size]()),m_size(size),m_cnt(cnt)
    {
    }
    int& get_cnt()
    {
        return m_cnt;
    }
    int get_size()
    {
        return m_size;
    }
    char* get_str()
    {
        return m_ptr;
    }
    void decrement()
    {
        if(m_cnt==0)
        {
            return;
        }
        m_cnt--;
    }
    void increment()
    {
        m_cnt++;
    }
    ~Ref_cnt()
    {
        delete [] m_ptr;
    }
};
class String
{
    public:
        //friend std::ostream& ::operator<<(std::ostream& out,const String& obj);
        String():m_use(NULL){}
        String(const char* data):m_use(new Ref_cnt(strlen(data)+1))
    {
        strcpy(m_use->get_str(),data);
        std::cout<<__func__<<":"<<__LINE__<<std::endl;
    }
        String(const String& obj)
        {
            m_use=obj.m_use;
            m_use->increment();
            std::cout<<"current ref_cnt is "<<m_use->get_cnt()<<std::endl;
        }
        String& operator=(const String& obj)
        {
            if(this==&obj)
            {
                return *this;
            }
            if(m_use!=NULL)
            {
                m_use->decrement();
                if(m_use->get_cnt()==0)
                {
                    delete m_use;
                }
            }
            m_use=obj.m_use;
            m_use->increment();
            std::cout<<__func__<<":"<<__LINE__<<std::endl;
        }
        char* get_str()
        {
            return m_use->get_str();
        }
        int& get_cnt()
        {
            return m_use->get_cnt();
        }
        bool operator<(String& right)
        {
            return strcmp(this->get_str(),right.get_str())<0;
        }
        bool operator>(String& right)
        {
            return !(*this<right);
        }
        char& operator[](int pos)//写时复制
        {
            if(!(pos>=0&&pos<strlen(m_use->m_ptr)))
            {
                throw std::runtime_error("out of range");
            }
            if(m_use->m_cnt==1)
            {
                return (m_use->get_str())[pos];
            }
            /*将这块空间的指针赋值给temp由temp来判断引用计数*/
            Ref_cnt* temp=m_use;
            /*单独开辟一块新的空间来存放原来的内容*/
            m_use=new Ref_cnt(temp->m_size);
            strcpy(m_use->m_ptr,temp->m_ptr);
            temp->decrement();
            if(temp->m_cnt==0)
            {
                delete temp;
            }
            return m_use->m_ptr[pos];
        }
        void set_str(const char* data)/*可以和operaor[]参照对比比较*/
        {
            if(m_use==NULL)
            {
                m_use=new Ref_cnt(strlen(data)+1);
                strcpy(m_use->get_str(),data);
            }
            if(m_use->get_cnt()==1)
            {
                if(m_use->m_size>=strlen(data)+1)
                {
                    strcpy(m_use->get_str(),data);
                }
                else
                {
                    delete m_use;
                    m_use=new Ref_cnt(strlen(data)+1);
                    strcpy(m_use->m_ptr,data);
                }
            }
            else
            {
                m_use->decrement();
                m_use=new Ref_cnt(strlen(data)+1);
                strcpy(m_use->m_ptr,data);
            }
        }
        String operator+(String& right)/*直接创建一个String对象，存放两个对象相加之和*/
        {
            if(m_use==NULL)
            {
                return right;
            }
            char* m_temp=new char(m_use->m_size+(right.m_use)->m_size-1);
            strcpy(m_temp,m_use->m_ptr);
            strcat(m_temp,(right.m_use)->m_ptr);
            //String str_temp(m_temp);
            return m_temp;/*返回时同样执行了operator=(const String& obj)方法*/
            //return str_temp;/*返回时执行了operator=(const String& obj)方法*/
            std::cout<<__func__<<":"<<__LINE__<<std::endl;
        }
        String& operator+=(String& right)
        {
            *this= (*this)+right;/*从这里可以很容易看出operator+返回执行了operator=*/
            return *this;
        }
        ~String()
        {
            if(m_use==NULL)
            {
                return;
            }
            /*析构函数记得释放空间*/
            m_use->decrement();
            if(m_use->get_cnt()==0)
            {
                delete m_use;
            }
            std::cout<<__func__<<":"<<__LINE__<<std::endl;
        }
    private:
        Ref_cnt* m_use;
};
std::ostream& operator<<(std::ostream& out,String& obj)
{
    out<<obj.get_str();
    return out;
}

