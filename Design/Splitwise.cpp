#include <bits/stdc++.h>
using namespace std;

/* ================= USER ================= */

class User {
public:
    int id;
    string name;
    static int nextId;

    User(string n) : name(n) {
        id = nextId++;
    }
};
int User::nextId = 0;

/* ================= USER REGISTRY ================= */

class UserManager {
    unordered_map<int, User*> users;

public:
    ~UserManager() {
        for (auto& u : users)
            delete u.second;
    }

    User* addUser(string name) {
        User* u = new User(name);
        users[u->id] = u;
        return u;
    }

    bool exists(int id) {
        return users.count(id);
    }
};

/* ================= STORAGE ================= */
/*
 balanceSheet[x][y] = amount x owes y
*/
class Storage {
    unordered_map<int, unordered_map<int, double>> balanceSheet;

public:
    void addDebt(int debtor, int creditor, double amount) {
        balanceSheet[debtor][creditor] += amount;
    }

    void display() {
        cout << "\n--- BALANCES ---\n";
        for (auto& [u1, debts] : balanceSheet) {
            for (auto& [u2, amount] : debts) {
                if (amount > 0.001)
                    cout << "User " << u1 << " owes User " << u2
                         << ": " << amount << endl;
            }
        }
    }
};

/* ================= SPLIT STRATEGY ================= */

class Split {
public:
    virtual void validateAndAdd(
        Storage* store,
        int payerId,
        double totalAmount,
        vector<int>& users,
        vector<double>& values
    ) = 0;

    virtual ~Split() {}
};

/* ================= EQUAL SPLIT ================= */

class EqualSplit : public Split {
public:
    void validateAndAdd(Storage* store, int payerId, double totalAmount,
                        vector<int>& users, vector<double>&) override {

        double splitAmount = totalAmount / users.size();

        for (int uid : users) {
            if (uid != payerId) {
                store->addDebt(uid, payerId, splitAmount);
            }
        }
    }
};

/* ================= EXACT SPLIT ================= */

class ExactSplit : public Split {
public:
    void validateAndAdd(Storage* store, int payerId, double totalAmount,
                        vector<int>& users, vector<double>& values) override {

        if (users.size() != values.size()) {
            cout << "Error: User and value count mismatch\n";
            return;
        }

        double sum = 0;
        for (double v : values) sum += v;

        if (abs(sum - totalAmount) > 0.001) {
            cout << "Error: Split values do not sum to total\n";
            return;
        }

        for (int i = 0; i < users.size(); i++) {
            if (users[i] != payerId) {
                store->addDebt(users[i], payerId, values[i]);
            }
        }
    }
};

/* ================= EXPENSE MANAGER ================= */

class ExpenseManager {
    Storage* storage;
    Split* strategy;

public:
    ExpenseManager(Storage* s) : storage(s), strategy(nullptr) {}

    void setStrategy(Split* s) {
        strategy = s;
    }

    void addExpense(int payerId, double amount,
                    vector<int> users,
                    vector<double> values) {

        if (!strategy) {
            cout << "No split strategy set\n";
            return;
        }

        strategy->validateAndAdd(storage, payerId, amount, users, values);
    }
};

/* ================= MAIN ================= */

int main() {
    UserManager userMgr;
    Storage storage;
    ExpenseManager manager(&storage);

    // Create users
    User* u0 = userMgr.addUser("Alice");
    User* u1 = userMgr.addUser("Bob");
    User* u2 = userMgr.addUser("Charlie");

    // Equal Split Example
    manager.setStrategy(new EqualSplit());

    vector<int> users = {u0->id, u1->id, u2->id};
    vector<double> empty;

    // Alice pays 300 for Alice, Bob, Charlie
    manager.addExpense(u0->id, 300, users, empty);

    storage.display();

    // Exact Split Example
    manager.setStrategy(new ExactSplit());

    vector<double> exact = {100, 100, 100};
    manager.addExpense(u0->id, 300, users, exact);

    storage.display();

    return 0;
}
