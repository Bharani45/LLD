#include <bits/stdc++.h>
using namespace std;

/* ---------------- HOTEL ---------------- */
class Hotel {
public:
    vector<string> menu;
    string name;
    bool open;
    int id;
    Hotel(string n, vector<string> m, bool o,int i)
        : name(n), menu(m), open(o) ,id(i){}

    void add(string item) {
        menu.push_back(item);
    }

    void display() {
        cout << name<<"\n"<<"Menu:\n";
        for (auto &i : menu) cout << i << endl;
    }
};

/* ---------------- STATE PATTERN ---------------- */
class Order;

class State {
public:
    virtual void placed(Order* o) = 0;
    virtual void preparing(Order* o) = 0;
    virtual void delivered(Order* o) = 0;
    virtual ~State() {}
};

/* ---------------- ORDER ---------------- */
class Order {
public:
    static int nextId;
    int orderId;
    State* state;

    Order() {
        orderId = ++nextId;
        state = nullptr;
    }

    void setState(State* newState) {
        delete state;
        state = newState;
    }

    void placed() {
        state->placed(this);
    }

    void preparing() {
        state->preparing(this);
    }

    void delivered() {
        state->delivered(this);
    }

    ~Order() {
        delete state;
    }
};

int Order::nextId = 0;

/* ---------------- STATES ---------------- */

class PlacedState : public State {
public:
    void placed(Order* o) override {
        cout << "Order " << o->orderId << " is already placed\n";
    }

    void preparing(Order* o) override;

    void delivered(Order* o) override {
        cout << "Order not prepared yet\n";
    }
};

class PreparingState : public State {
public:
    void placed(Order* o) override {
        cout << "Order " << o->orderId << " already placed\n";
    }

    void preparing(Order* o) override {
        cout << "Order " << o->orderId << " already being prepared\n";
    }

    void delivered(Order* o) override;
};

class DeliveredState : public State {
public:
    void placed(Order* o) override {
        cout << "Order already delivered\n";
    }

    void preparing(Order* o) override {
        cout << "Order already delivered\n";
    }

    void delivered(Order* o) override {
        cout << "Order " << o->orderId << " already delivered\n";
    }
};

void PlacedState::preparing(Order* o){
    cout << "Preparing Order " << o->orderId << endl;
    o->setState(new class PreparingState());
}
void PreparingState::delivered(Order* o){
    cout << "Delivering Order " << o->orderId << endl;
    o->setState(new class DeliveredState());
}
class App{
    unordered_map<int,Hotel*>store;
    queue<pair<int,Order*>>q;
    public:
        App(){
        }
        void add(Hotel* h){
            store[h->id]=h;
        }
        void show(){
            for(auto i:store){
                i.second->display();
            }
        }
        void place(Order* o,int h_id){
            q.push({h_id,o});
            process();
        }
        void process(){
            while(!q.empty()){
                cout<<"Order for hotel "<<q.front().first<<" is initiated"<<endl;
                q.front().second->setState(new PlacedState());
                q.front().second->placed();
                q.front().second->preparing();
                q.front().second->delivered();
                q.pop();
            }
        }

};

/* ---------------- MAIN ---------------- */
int main() {
    vector<string> menu = {"Idly", "Dosa"};
    Hotel* a2b=new Hotel("A2B", menu, true,1);
    App* zomato=new App();
    zomato->add(a2b);
    Hotel* rr=new Hotel("RR",menu,true,2);
    zomato->add(rr);
    zomato->show();
    Order* o=new Order();
    zomato->place(o,1);

    return 0;
}
