#include <bits/stdc++.h>
using namespace std;

/* ================= PRODUCT ================= */

class Product {
    int id;
    string name;
    int price;
    int quantity;

public:
    Product(int id, string name, int price, int qty)
        : id(id), name(name), price(price), quantity(qty) {}

    int getId() const { return id; }
    string getName() const { return name; }
    int getPrice() const { return price; }
    int getQuantity() const { return quantity; }

    bool isAvailable() const {
        return quantity > 0;
    }

    void reduceQuantity() {
        quantity--;
    }
};

/* ================= INVENTORY ================= */

class Inventory {
    unordered_map<int, Product*> products;

public:
    ~Inventory() {
        for (auto& p : products)
            delete p.second;
    }

    void addProduct(Product* p) {
        products[p->getId()] = p;
    }

    Product* getProduct(int id) {
        if (!products.count(id)) return nullptr;
        return products[id];
    }

    bool isAvailable(int id) {
        return products.count(id) && products[id]->isAvailable();
    }

    void reduceQuantity(int id) {
        products[id]->reduceQuantity();
    }

    void display() {
        cout << "\n---- PRODUCTS ----\n";
        for (auto& [id, p] : products) {
            cout << id << " | "
                 << p->getName() << " | Rs "
                 << p->getPrice() << " | Qty "
                 << p->getQuantity() << endl;
        }
    }
};

/* ================= STATE INTERFACE ================= */

class VendingMachine;

class State {
public:
    virtual void selectProduct(int id) = 0;
    virtual void insertMoney(int amount) = 0;
    virtual void dispense() = 0;
    virtual ~State() {}
};

/* ================= VENDING MACHINE ================= */

class VendingMachine {
    State* currentState;
    Inventory* inventory;

public:
    int selectedProductId = -1;
    int insertedAmount = 0;

    VendingMachine(Inventory* inv);

    void setState(State* state) {
        currentState = state;
    }

    Inventory* getInventory() {
        return inventory;
    }

    void selectProduct(int id) {
        currentState->selectProduct(id);
    }

    void insertMoney(int amount) {
        currentState->insertMoney(amount);
    }

    void dispense() {
        currentState->dispense();
    }
};

/* ================= STATES ================= */

class IdleState : public State {
    VendingMachine* machine;

public:
    IdleState(VendingMachine* m) : machine(m) {}

    void selectProduct(int id) override;
    void insertMoney(int) override {
        cout << "Select product first\n";
    }
    void dispense() override {
        cout << "No product selected\n";
    }
};

class HasSelectionState : public State {
    VendingMachine* machine;

public:
    HasSelectionState(VendingMachine* m) : machine(m) {}

    void selectProduct(int) override {
        cout << "Product already selected\n";
    }

    void insertMoney(int amount) override;
    void dispense() override {
        cout << "Insert sufficient money\n";
    }
};

class DispenseState : public State {
    VendingMachine* machine;

public:
    DispenseState(VendingMachine* m) : machine(m) {}

    void selectProduct(int) override {}
    void insertMoney(int) override {}
    void dispense() override;
};

/* ================= STATE IMPLEMENTATIONS ================= */

void IdleState::selectProduct(int id) {
    if (!machine->getInventory()->isAvailable(id)) {
        cout << "Product unavailable\n";
        return;
    }
    machine->selectedProductId = id;
    cout << "Product selected\n";
    machine->setState(new HasSelectionState(machine));
}

void HasSelectionState::insertMoney(int amount) {
    machine->insertedAmount += amount;

    Product* p = machine->getInventory()
                    ->getProduct(machine->selectedProductId);

    if (machine->insertedAmount >= p->getPrice()) {
        machine->setState(new DispenseState(machine));
    } else {
        cout << "Inserted Rs " << machine->insertedAmount
             << ". Need Rs " << p->getPrice() << endl;
    }
}

void DispenseState::dispense() {
    Product* p = machine->getInventory()
                    ->getProduct(machine->selectedProductId);

    machine->getInventory()->reduceQuantity(p->getId());

    int change = machine->insertedAmount - p->getPrice();

    cout << "Dispensing " << p->getName() << endl;
    if (change > 0)
        cout << "Return change: Rs " << change << endl;

    machine->insertedAmount = 0;
    machine->selectedProductId = -1;
    machine->setState(new IdleState(machine));
}

/* ================= MACHINE CTOR ================= */

VendingMachine::VendingMachine(Inventory* inv) {
    inventory = inv;
    currentState = new IdleState(this);
}

/* ================= MAIN ================= */

int main() {
    Inventory inventory;
    inventory.addProduct(new Product(1, "Coke", 40, 5));
    inventory.addProduct(new Product(2, "Pepsi", 35, 3));
    inventory.addProduct(new Product(3, "Water", 20, 10));

    VendingMachine vm(&inventory);

    while (true) {
        inventory.display();

        cout << "\n1.Select  2.Insert Money  3.Dispense  4.Exit\n";
        int choice;
        cin >> choice;

        if (choice == 4) break;

        if (choice == 1) {
            int id;
            cout << "Enter product id: ";
            cin >> id;
            vm.selectProduct(id);
        }
        else if (choice == 2) {
            int amt;
            cout << "Insert money: ";
            cin >> amt;
            vm.insertMoney(amt);
        }
        else if (choice == 3) {
            vm.dispense();
        }
    }

    return 0;
}
