#include <bits/stdc++.h>
using namespace std;
class Order{
    string main;
    string dessert;
    string side;
    Order(string m,string d,string s):main(m),dessert(d),side(s){
        cout<<main<<" "<<dessert<<" "<<side<<endl;
    }
    public:
    class Builder{
    string main="";
    string dessert="";
    string side=""; 
    public:
        Builder& setmain(string dish){
            this->main=dish;
            return *this;
        }
        Builder& setdessert(string dish){
            this->dessert=dish;
            return *this;
        }
        Builder& setside(string dish){
            this->side=dish;
            return *this;
        }
        Order* build(){
            return new Order(main,dessert,side);
        }
    };

};

int main(){
    Order* b=Order::Builder().setmain("Biriyani").setdessert("Ice cream").build();
    return 0;
}