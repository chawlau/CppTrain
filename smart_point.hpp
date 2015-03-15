#include<iostream>
#include<cstring>
#include<stdexcept>
class Ref_cnt
{
    friend class Str;
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
class Str
{
    public:
        Str():m_use(NULL){}
        Str(const char* data):m_use(new Ref_cnt(strlen(data)+1))
    {
        strcpy(m_use->get_str(),data);
        std::cout<<"init cnt is :"<<m_use->get_cnt()<<std::endl;
    }
        Str(const Str& obj)
        {
            m_use=obj.m_use;
            m_use->increment();
            std::cout<<"current ref_cnt is "<<m_use->get_cnt()<<std::endl;
        }
        Str& operator=(const Str& obj)
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
        }
         char* get_str()
        {
            return m_use->get_str();
        }
        ~Str()
        {
            if(m_use==NULL)
            {
                return;
            }
            m_use->decrement();
            if(m_use->get_cnt()==0)
            {
                delete m_use;
            }
        }
        bool operator<(Str& right)
        {
            return strcmp(this->get_str(),right.get_str())<0;
        }
        bool operator>(Str& right)
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
            Ref_cnt* temp=m_use;
            m_use->decrement();
            m_use=new Ref_cnt(temp->m_size);
            strcpy(m_use->m_ptr,temp->m_ptr);
            if(temp->m_cnt==0)
            {
                delete temp;
            }
            return m_use->m_ptr[pos];
        }
        Str operator+(Str& right)
        {
            if(m_use==NULL)
            {
                return right;
            }
            char* m_temp=new char(m_use->m_size+(right.m_use)->m_size-1);
            strcat(m_temp,m_use->m_ptr);
            strcat(m_temp,(right.m_use)->m_ptr);
            Str str_temp(m_temp);
            return str_temp;
        }
        Str& operator+=(Str& right)
        {
            *this= (*this)+right;
            return *this;
        }
        void set_str(const char* data)
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
    private:
        Ref_cnt* m_use;
};
