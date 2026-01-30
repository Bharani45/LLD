#include <bits/stdc++.h>
using namespace std;

/* ================= COFFEE ================= */

class Coffee {
public:
    unordered_map<string,int> items;

    Coffee() {
        items = {
            {"milk",100},
            {"sugar",20},
            {"coffee",20}
        };
    }

    virtual int cost() {
        return 15;
    }

    virtual ~Coffee() {}
};

class Espresso : public Coffee {
public:
    Espresso() {
        items["espresso"] = 30;
    }
    int cost() override { return 20; }
};

class Lattee : public Coffee {
public:
    Lattee() {
        items["lattee"] = 30;
    }
    int cost() override { return 30; }
};

/* ================= INVENTORY ================= */

class Inventory {
public:
    unordered_map<string,int> store;

    Inventory() {
        store = {
            {"milk",2000},
            {"coffee",500},
            {"sugar",500},
            {"espresso",500},
            {"lattee",500}
        };
    }

    bool useitem(const string& item, int amt) {
        if (store[item] < amt) return false;
        store[item] -= amt;
        return true;
    }
};

/* ================= COFFEE MAKER ================= */

class CoffeeMaker {
public:
    Inventory* inv;

    CoffeeMaker(Inventory* i) : inv(i) {}

    Coffee* makecoffee(const string& name) {
        Coffee* c = nullptr;

        if (name == "coffee") c = new Coffee();
        else if (name == "espresso") c = new Espresso();
        else if (name == "lattee") c = new Lattee();
        else return nullptr;

        for (auto &i : c->items) {
            if (!inv->useitem(i.first, i.second)) {
                delete c;
                return nullptr;
            }
        }
        return c;
    }
};

/* ================= STATE PATTERN ================= */

class Machine;

class State {
public:
    virtual void select(Machine*, string) = 0;
    virtual void insertmoney(Machine*, int) = 0;
    virtual void dispense(Machine*) = 0;
    virtual ~State() {}
};

/* ================= MACHINE ================= */

class Machine {
public:
    CoffeeMaker* maker;
    State* curstate;
    string selectedItem;
    int money;

    Machine(CoffeeMaker* ptr);

    void setState(State* s) { curstate = s; }

    void select(string name) { curstate->select(this, name); }
    void pay(int amt) { curstate->insertmoney(this, amt); }
    void dispense() { curstate->dispense(this); }

    void prepareCoffee() {
        Coffee* c = maker->makecoffee(selectedItem);
        if (c) {
            cout << "☕ Dispensing " << selectedItem
                 << " | Cost ₹" << c->cost() << endl;
            delete c;
        } else {
            cout << "Unable to prepare coffee\n";
        }
    }
};

/* ================= STATES ================= */

class IdleState : public State {
public:
    void select(Machine* m, string name) override {
        cout << "Selected: " << name << endl;
        m->selectedItem = name;
        m->setState(new class HasSelectionState());
    }

    void insertmoney(Machine*, int) override {
        cout << "Please select item first\n";
    }

    void dispense(Machine*) override {
        cout << "Please select item first\n";
    }
};

class HasSelectionState : public State {
public:
    void select(Machine*, string) override {
        cout << "Item already selected\n";
    }

    void insertmoney(Machine* m, int amt) override {
        cout << "Money inserted: ₹" << amt << endl;
        m->money += amt;
        m->setState(new class HasMoneyState());
    }

    void dispense(Machine*) override {
        cout << "Insert money first\n";
    }
};

class HasMoneyState : public State {
public:
    void select(Machine*, string) override {
        cout << "Processing payment\n";
    }

    void insertmoney(Machine*, int) override {
        cout << "Already paid\n";
    }

    void dispense(Machine* m) override {
        m->prepareCoffee();
        m->money = 0;
        m->selectedItem = "";
        m->setState(new IdleState());
    }
};

/* ================= MACHINE CONSTRUCTOR ================= */

Machine::Machine(CoffeeMaker* ptr) {
    maker = ptr;
    money = 0;
    curstate = new IdleState();
}

/* ================= MAIN ================= */

int main() {
    Inventory inv;
    CoffeeMaker maker(&inv);
    Machine machine(&maker);

    machine.select("espresso");
    machine.pay(50);
    machine.dispense();

    cout << "----\n";

    machine.select("lattee");
    machine.pay(100);
    machine.dispense();

    return 0;
}
