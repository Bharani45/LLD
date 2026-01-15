#include <bits/stdc++.h>
using namespace std;
class Notification{
    public:
        virtual void notify(){
            cout<<"Notification App"<<endl;
        }
};
class Email:public Notification{
    public:
        void notify() override{
            cout<<"Email sent"<<endl;
        }
};
class SMS:public Notification{
    public:
        void notify() override{
            cout<<"SMS sent"<<endl;
        }
};
class NotificationFactory{
    public:
        Notification* create(string type){
            if(type=="Email"){
                return new Email();
            }else if(type == "SMS"){
                return new SMS();
            }
        }
};
int main(){
    string type;
    cout<<"EMAIL"<<endl;
    cout<<"SMS"<<endl;
    cin>>type;
    NotificationFactory* factory=new NotificationFactory();
    Notification* mode=factory->create(type);
    mode->notify();
    return 0;
}