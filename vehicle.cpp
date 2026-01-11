#include <bits/stdc++.h>
using namespace std;

class Parking{
    public:
    Parking* ptr;
    Parking():ptr(nullptr){}
    void setnext(Parking* ls){
        ptr=ls;
    }
    virtual void func(int k)=0;
};
class Ground:public Parking{
    public:
    void func(int k){
        if(k==0){
            cout<<"Ground Parking"<<endl;
        }else if(ptr){
            ptr->func(k);
        }
    }
};

class Firstfloor:public Parking{
    public:
    void func(int k){
        if(k==1){
            cout<<"1st floor Parking"<<endl;
        }else if(ptr){
            ptr->func(k);
        }
    }
};

int main(){
    Parking* gnd=new Ground();
    Parking* first=new Firstfloor();
    gnd->setnext(first);
    gnd->func(0);
    gnd->func(1);
    return 0;
}