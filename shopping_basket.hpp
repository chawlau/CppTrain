#include<iostream>
#include<vector>
class Object
{
    public:
        ~Object(){}
    virtual void show()=0;
    virtual Object* clone()=0;
};
class Handle
{
    public:
        Handle(Object* obj=NULL):m_ptr(obj){}
        Object* operator->()
        {
            return m_ptr->clone();
        }
        Object& operator*()
        {
            return *(m_ptr->clone());
        }
    private:
        Object* m_ptr;
};
class Phone:public Object
{
    public:
        Phone(std::string brand="",std::string system=""):m_brand(brand),m_system(system){}
        void show()
        {
            std::cout<<"brand: "<<m_brand<<" m_system:"<<m_system<<std::endl;
        }
        Object* clone()
        {
            return this;
        }
    private:
        std::string m_brand;
        std::string m_system;
};
class Pad:public Object
{
    public:
        Pad(std::string brand="",double size=0):m_brand(brand),m_size(size){}
        void show()
        {
            std::cout<<"brand: "<<m_brand<<" m_size: "<<m_size<<std::endl;
        }
        Object* clone()
        {
            return this;
        }
    private:
        std::string m_brand;
        double m_size;
};
class Book:public Object
{
    public:
    Book(std::string name="",int price=0):m_name(name),m_price(price){}
    void show()
    {
        std::cout<<"book_name : "<<m_name<<" price :"<<m_price<<std::endl;
    }
    Object* clone()
    {
        return this;
    }
    private:
    std::string m_name;
    int m_price;
};
typedef std::vector<Handle> Basket;
typedef std::vector<Handle>::iterator curse;
