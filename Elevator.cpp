#include <bits/stdc++.h>
using namespace std;

class Elevator;

/* ---------- State Interface ---------- */
class State {
public:
    virtual void move(Elevator* e) = 0;
    virtual string name() = 0;
    virtual ~State() {}
};

/* ---------- Elevator ---------- */
class Elevator {
public:
    int id;
    int floor;
    int target;
    State* state;

public:
    Elevator(int id, int f = 0) : id(id), floor(f), target(f), state(nullptr) {}

    int getId() { return id; }
    int getFloor() { return floor; }
    int getTarget() { return target; }

    bool isIdle() {
        return floor == target && state->name() == "IDLE";
    }

    void setTarget(int t) { target = t; }

    void setState(State* s) {
        if (state) delete state;
        state = s;
        cout << "[Elevator " << id << "] STATE → " << state->name() << endl;
    }

    void moveUp() {
        floor++;
        cout << "[Elevator " << id << "] UP → Floor " << floor << endl;
    }

    void moveDown() {
        floor--;
        cout << "[Elevator " << id << "] DOWN → Floor " << floor << endl;
    }

    void process() {
        state->move(this);
    }

    ~Elevator() { delete state; }

    friend class IdleState;
    friend class UpState;
    friend class DownState;
};

/* ---------- States ---------- */
class IdleState : public State {
public:
    void move(Elevator*) override {}
    string name() override { return "IDLE"; }
};

class UpState : public State {
public:
    void move(Elevator* e) override {
        if (e->floor < e->target) {
            e->moveUp();
            this_thread::sleep_for(chrono::milliseconds(300));
        } else {
            cout << "[Elevator " << e->id << "] Reached Floor " << e->floor << endl;
            e->setState(new IdleState());
        }
    }
    string name() override { return "MOVING UP"; }
};

class DownState : public State {
public:
    void move(Elevator* e) override {
        if (e->floor > e->target) {
            e->moveDown();
            this_thread::sleep_for(chrono::milliseconds(300));
        } else {
            cout << "[Elevator " << e->id << "] Reached Floor " << e->floor << endl;
            e->setState(new IdleState());
        }
    }
    string name() override { return "MOVING DOWN"; }
};

/* ---------- Elevator Controller ---------- */
class ElevatorController {
    vector<Elevator*> elevators;

public:
    ElevatorController(int n) {
        for (int i = 0; i < n; i++) {
            Elevator* e = new Elevator(i, 0);
            e->setState(new IdleState());
            elevators.push_back(e);
        }
    }

    Elevator* assignElevator(int requestFloor) {
        Elevator* best = nullptr;
        int minCost = INT_MAX;

        for (auto e : elevators) {
            int cost = abs(e->getFloor() - requestFloor);
            if (cost < minCost) {
                minCost = cost;
                best = e;
            }
        }
        return best;
    }

    void requestElevator(int floor) {
        Elevator* e = assignElevator(floor);
        cout << "\nAssigned Elevator " << e->getId()
             << " (Current Floor " << e->getFloor() << ")\n";

        e->setTarget(floor);

        if (e->getFloor() < floor)
            e->setState(new UpState());
        else if (e->getFloor() > floor)
            e->setState(new DownState());
    }

    void step() {
        for (auto e : elevators)
            e->process();
    }

    void status() {
        for (auto e : elevators) {
            cout << "Elevator " << e->getId()
                 << " | Floor: " << e->getFloor()
                 << " | State: " << e->state->name() << endl;
        }
    }

    ~ElevatorController() {
        for (auto e : elevators) delete e;
    }
};

/* ---------- Main ---------- */
int main() {
    int n;
    cout << "Enter number of elevators: ";
    cin >> n;

    ElevatorController controller(n);

    while (true) {
        cout << "\n1. Request Elevator\n2. Step Simulation\n3. Status\n4. Exit\nChoice: ";
        int ch;
        cin >> ch;

        if (ch == 1) {
            int f;
            cout << "Enter request floor: ";
            cin >> f;
            controller.requestElevator(f);
        }
        else if (ch == 2) {
            controller.step();
        }
        else if (ch == 3) {
            controller.status();
        }
        else {
            break;
        }
    }
    return 0;
}
