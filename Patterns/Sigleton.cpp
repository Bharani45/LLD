#include <bits/stdc++.h>
using namespace std;
class Db{
    static Db* instance;
    Db(){
        cout<<"Db created"<<endl;
    }
    Db operator=(const Db& ls)=delete;
    Db (const Db& ls)=delete;
    public:
        static Db* getinstance(){
            if(instance==nullptr){
                instance=new Db();
            }
            return instance;
        }
};
Db* Db::instance=nullptr;
int main(){
    Db* d1=Db::getinstance();
    Db* d2=Db::getinstance();
    if(d1==d2){
        cout<<"Same table"<<endl;
    }
    return 0;
}