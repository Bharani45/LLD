#include <bits/stdc++.h>
using namespace std;

class Observer{
    public:
        virtual void notify(string name,int price)=0;
};
class Mode:public Observer{
    public:
        string name;
        Mode(string name){
            this->name=name;
        }
        void notify(string name,int price){
            cout<<this->name<<": Stock "<<name<<" "<<"Price is "<<price<<endl;
        }
};
class Subject{
    public:
        virtual void add(Observer* s)=0;
        virtual void remove(Observer* s)=0;
        virtual void notify()=0;
};
class Stock:public Subject{
    public:
        string name;
        int price;
        Stock(string name,int price){
            this->name=name;
            this->price=price;
        }
        vector<Observer*>store;
        void add(Observer* s){
            store.push_back(s);
            cout<<"User added"<<endl;
        }
        void changePrice(int p){
            this->price=p;
            notify();
        }
        void remove(Observer* s){
            store.erase(std::remove(store.begin(),store.end(),s),store.end());
        }
        void notify(){
            for(int i=0;i<store.size();i++){
                store[i]->notify(name,price);
            }
        }
};

int main(){
    Stock* apple=new Stock("apple",100);
    Mode* Email=new Mode("Email");
    Mode* SMS=new Mode("SMS");
    apple->add(Email);
    apple->add(SMS);
    apple->changePrice(200);
    apple->remove(Email);
    return 0;
}
