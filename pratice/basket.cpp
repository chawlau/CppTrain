#include"shopping_basket.hpp"
int main(int argc,char** argv)
{
    Phone iphone5s("apple","IOS8");
    Phone mi4("xiaomi","MIUIV6");
    Pad ipadair("ipad",9.7);
    Pad mipad("mPad",7.9);
    Book b1("C++ prime",59);
    Book b2("Unix",68);
    Basket basket;
    basket.push_back(&iphone5s);
    basket.push_back(&mi4);
    basket.push_back(&ipadair);
    basket.push_back(&mipad);
    basket.push_back(&b1);
    basket.push_back(&b2);
    curse iter=basket.begin();
    for(iter;iter!=basket.end();iter++)
    {
        //(*iter).operator->()->show();
        (*iter)->show();
    }
}
