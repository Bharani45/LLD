#include <bits/stdc++.h>
using namespace std;

// 1. Component Interface
class Pizza {
    public:
        virtual int cost() = 0;
        virtual ~Pizza() {} // Always good practice to have virtual destructor
};

// 2. Concrete Components
class Fpizza : public Pizza {
    public:
        int cost() override {
            return 200; // Farmhouse
        }
};

class Mpizza : public Pizza {
    public:
        int cost() override {
            return 100; // Margherita
        }
};

// 3. Decorator Base Class
// CRITICAL FIX: Decorator must inherit from Pizza!
class Decorator : public Pizza {
    public:
        Pizza* ptr;
        
        Decorator(Pizza* p) {
            ptr = p;
        }
        
        int cost() override {
            return ptr->cost();
        }
};

// 4. Concrete Decorators
class Mushroom : public Decorator {
    public:
        // CRITICAL FIX: Constructor to pass pointer to parent
        Mushroom(Pizza* p) : Decorator(p) {} 

        int cost() override {
            return ptr->cost() + 50;
        }
};

class Cheese : public Decorator {
    public:
        Cheese(Pizza* p) : Decorator(p) {}

        int cost() override {
            return ptr->cost() + 20;
        }
};

int main() {
    // 1. Order a plain Farmhouse (200)
    Pizza* myPizza = new Fpizza();
    cout << "Base Pizza: " << myPizza->cost() << endl;

    // 2. Add Mushroom (200 + 50 = 250)
    // We wrap 'myPizza' inside a new Mushroom object
    myPizza = new Mushroom(myPizza); 
    cout << "With Mushroom: " << myPizza->cost() << endl;

    // 3. Add Cheese (250 + 20 = 270)
    // We wrap the resulting object inside a Cheese object
    myPizza = new Cheese(myPizza);
    cout << "With Cheese: " << myPizza->cost() << endl;

    return 0;
}