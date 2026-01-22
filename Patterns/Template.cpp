#include <bits/stdc++.h>
using namespace std;
class Parser{
        void close(){
            cout<<"Closing the file"<<endl;
        }
        void open(){
            cout<<"Opening the file"<<endl;
        }
    public:
        void process(){
            open();
            parse();
            close();
        }
        virtual void parse()=0;
};
class Excel:public Parser{
        void parse()override{
            cout<<"Parsing Excel files"<<endl;
        }
};
class CSV:public Parser{
        void parse()override{
            cout<<"Parsing CSV files"<<endl;
        }
};
int main(){
    Parser* p=new Excel();
    p->process();
    p=new CSV();
    p->process();
    return 0;
}