#include <bits/stdc++.h>
using namespace std;
// -------------------- BOOK -----------------------------//
class Book;
class State{
    public:
        virtual void idle(Book* b)=0;
        virtual void borrowed(Book* b)=0;
        virtual void returned(Book* b)=0;
};
class Book{
    public:
        int id;
        string author;
        string title;
        State* next;
        Book(int id,string a,string t):id(id),author(a),title(t){}
        void setstate(State* ptr){
            next=ptr;
        }
        void idle(){
            next->idle(this);
        }
        void borrowed(){
            next->borrowed(this);
        }
        void returned(){
            next->returned(this);
        }
};
class Idle:public State{
    public:
        void idle(Book* b) override{
            cout<<"The bool is already idle"<<endl;
        }
        void borrowed(Book* b)override;
        void returned(Book* b)override{
            cout<<"Book is not borrowed"<<endl;
        }
};
class Borrow:public State{
    public:
        void idle(Book* b) override{
            cout<<"Book is borrowed"<<endl;
        }
        void borrowed(Book* b)override{
            cout<<"Book is aleady borrowed not available"<<endl;
        }
        void returned(Book* b)override;
};
class Returned:public State{
    public:
        void idle(Book* b) override{
            b->setstate(new Idle());
        }
        void borrowed(Book* b)override{
            b->setstate(new Borrow());
        }
        void returned(Book* b)override{
            cout<<"Book is already returned"<<endl;
        }
};
void Idle::borrowed(Book* b){
    cout<<"Book is borrowed"<<endl;
    b->setstate(new Borrow());
}
void Borrow::returned(Book* b){
    cout<<"Book is returned"<<endl;
    b->setstate(new Returned());
}
//-----------------------LIBRARIAN--------------------------//
class Librarian{
    public:
        string name;
        int id;
        Librarian(int id,string n):name(n),id(id){}
        void lend(Book* b){
            b->borrowed();
        }
        void returned(Book* b){
            b->returned();
        }
        void add(Book *b){
            b->setstate(new Idle());
        }
        
};
class Library{
    public:
        Librarian* lb;
        unordered_map<int,Book*>store;
        Library(Librarian* ptr){
            lb=ptr;
        }
        void addBook(int id,string author,string title){
            if(store.count(id)){
                cout<<"Book alreay exists"<<endl;
                return;
            }
            store[id]=new Book(id,author,title);
            lb->add(store[id]);
        }
        void removeBook(int id){
            if(store.count(id)){
                cout<<"No such book"<<endl;
                return;
            }
            delete store[id];
            store.erase(id);
        }
        void getBook(int id){
            if(!store.count(id)){
                cout<<"No such book"<<endl;
                return;
            }
            lb->lend(store[id]);
        }
        void returnBook(int id){
            lb->returned(store[id]);
        }
};
int main(){
    Librarian* kavi=new Librarian(35,"Kavi");
    Library* lib=new Library(kavi);
    lib->addBook(1,"Bharani","Adv of narnia");
    lib->getBook(2);
    lib->getBook(1);
    lib->returnBook(1);
    lib->returnBook(1);
    return 0;
}