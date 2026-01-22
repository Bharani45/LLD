#include <bits/stdc++.h>
using namespace std;

/* ===================== HOTEL ===================== */

class Hotel {
public:
    int id;
    string name;
    bool open;
    unordered_map<string,int> menu; // item -> price

    Hotel(int id, string name, bool open)
        : id(id), name(name), open(open) {}

    void addItem(const string& item, int price) {
        menu[item] = price;
    }

    void display() {
        cout << "Hotel: " << name << (open ? " (Open)" : " (Closed)") << "\nMenu:\n";
        for (auto &i : menu)
            cout << "  " << i.first << " : Rs " << i.second << endl;
    }
};

/* ===================== ORDER ===================== */

class Order;

class State {
public:
    virtual void placed(Order*) = 0;
    virtual void preparing(Order*) = 0;
    virtual void delivered(Order*) = 0;
    virtual ~State() {}
};

class Order {
public:
    static int nextId;
    int orderId;
    vector<pair<string,int>> items;
    int total = 0;
    State* state;

    Order() {
        orderId = ++nextId;
        state = nullptr;
    }

    void addItem(const string& name, int price) {
        items.push_back({name, price});
        total += price;
    }

    void setState(State* s) {
        delete state;
        state = s;
    }

    void placed()     { state->placed(this); }
    void preparing()  { state->preparing(this); }
    void delivered()  { state->delivered(this); }

    void show() {
        cout << "Order ID: " << orderId << "\nItems:\n";
        for (auto &i : items)
            cout << "  " << i.first << " Rs " << i.second << endl;
        cout << "Total: Rs " << total << endl;
    }

    ~Order() { delete state; }
};

int Order::nextId = 0;

/* ===================== STATES ===================== */

class PlacedState : public State {
public:
    void placed(Order*) override {
        cout << "Order already placed\n";
    }
    void preparing(Order* o) override;
    void delivered(Order*) override {
        cout << "Order not prepared yet\n";
    }
};

class PreparingState : public State {
public:
    void placed(Order*) override {
        cout << "Order already placed\n";
    }
    void preparing(Order*) override {
        cout << "Order already preparing\n";
    }
    void delivered(Order* o) override;
};

class DeliveredState : public State {
public:
    void placed(Order*) override {
        cout << "Order already delivered\n";
    }
    void preparing(Order*) override {
        cout << "Order already delivered\n";
    }
    void delivered(Order*) override {
        cout << "Order already delivered\n";
    }
};

void PlacedState::preparing(Order* o) {
    cout << "Order " << o->orderId << " is being prepared\n";
    o->setState(new PreparingState());
}

void PreparingState::delivered(Order* o) {
    cout << "Order " << o->orderId << " delivered\n";
    o->setState(new DeliveredState());
}

/* ===================== APP ===================== */

class App {
    unordered_map<int,Hotel*> hotels;
    queue<pair<int,Order*>> orders;

public:
    void addHotel(Hotel* h) {
        hotels[h->id] = h;
    }

    void showHotels() {
        for (auto &h : hotels)
            h.second->display();
    }

    void placeOrder(int hotelId, Order* o) {
        if (!hotels.count(hotelId)) {
            cout << "Invalid hotel\n";
            return;
        }

        if (!hotels[hotelId]->open) {
            cout << "Hotel is closed\n";
            return;
        }

        orders.push({hotelId, o});
        process();
    }

    void process() {
        while (!orders.empty()) {
            auto [hid, order] = orders.front();
            orders.pop();

            cout << "\nProcessing order for hotel: "
                 << hotels[hid]->name << endl;

            order->setState(new PlacedState());
            order->placed();
            order->preparing();
            order->delivered();

            order->show();
            delete order;
        }
    }

    ~App() {
        for (auto &h : hotels)
            delete h.second;
    }
};

/* ===================== MAIN ===================== */

int main() {
    App app;

    Hotel* a2b = new Hotel(1, "A2B", true);
    a2b->addItem("Idly", 30);
    a2b->addItem("Dosa", 50);

    app.addHotel(a2b);
    app.showHotels();

    Order* o = new Order();
    o->addItem("Idly", 30);
    o->addItem("Dosa", 50);

    app.placeOrder(1, o);
    return 0;
}
