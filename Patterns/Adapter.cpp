#include <bits/stdc++.h>
using namespace std;
class BankPayment{
    public:
        virtual void pay(int rs){
            cout<<"Bank transcation of Rs"<<rs<<" completed"<<endl;
        }
};
class UpiPayment{
    public:
        void pay(int rs){
             cout<<"UPI transcation of Rs"<<rs<<" completed"<<endl;
        }
};
class Adapter:public BankPayment{
    UpiPayment* ptr;
    public:
    Adapter(UpiPayment* a){
        ptr=a;
    }
    void pay(int rs)override{
        cout<<"Via gateway"<<endl;
        ptr->pay(rs);
    }
};
int main(){
    BankPayment* bank=new Adapter(new UpiPayment());
    bank->pay(50);
    return 0;
}