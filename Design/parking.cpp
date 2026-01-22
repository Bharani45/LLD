#include <bits/stdc++.h>
using namespace std;

/* ================= VEHICLE ================= */

class Vehicle {
protected:
    int vehicleNumber;

public:
    Vehicle(int num) : vehicleNumber(num) {}
    virtual ~Vehicle() {}

    int getNumber() const {
        return vehicleNumber;
    }

    virtual int getRatePerHour() const = 0;
};

class Car : public Vehicle {
public:
    Car(int num) : Vehicle(num) {}
    int getRatePerHour() const override {
        return 10;
    }
};

class Bike : public Vehicle {
public:
    Bike(int num) : Vehicle(num) {}
    int getRatePerHour() const override {
        return 5;
    }
};

/* ================= PARKING RECORD ================= */

class ParkingRecord {
    Vehicle* vehicle;
    int entryTime;

public:
    ParkingRecord(Vehicle* v, int time)
        : vehicle(v), entryTime(time) {}

    Vehicle* getVehicle() const {
        return vehicle;
    }

    int getEntryTime() const {
        return entryTime;
    }
};

/* ================= PARKING FLOOR ================= */

class ParkingFloor {
protected:
    int capacity;
    string name;
    ParkingFloor* nextFloor = nullptr;
    unordered_map<int, ParkingRecord*> records;

public:
    ParkingFloor(int cap, string n) : capacity(cap), name(n) {}
    virtual ~ParkingFloor() {}

    void setNext(ParkingFloor* next) {
        nextFloor = next;
    }

    virtual bool park(Vehicle* vehicle, int entryTime) {
        if (records.size() >= capacity) {
            if (nextFloor) return nextFloor->park(vehicle, entryTime);
            cout << "Parking Full. No space available.\n";
            return false;
        }

        int num = vehicle->getNumber();
        records[num] = new ParkingRecord(vehicle, entryTime);
        cout << "Vehicle " << num << " parked at " << name << endl;
        return true;
    }

    virtual bool remove(int vehicleNumber, int exitTime, int& fee) {
        if (records.count(vehicleNumber)) {
            ParkingRecord* rec = records[vehicleNumber];
            Vehicle* v = rec->getVehicle();

            int duration = exitTime - rec->getEntryTime();
            fee = duration * v->getRatePerHour();

            delete v;
            delete rec;
            records.erase(vehicleNumber);
            return true;
        }

        if (nextFloor) return nextFloor->remove(vehicleNumber, exitTime, fee);
        return false;
    }
};

/* ================= PARKING MANAGER ================= */

class ParkingManager {
    ParkingFloor* head;

public:
    ParkingManager(ParkingFloor* h) : head(h) {}

    void enter(Vehicle* v, int time) {
        head->park(v, time);
    }

    void leave(int vehicleNumber, int exitTime) {
        int fee = 0;
        if (head->remove(vehicleNumber, exitTime, fee)) {
            cout << "Pay Rs " << fee << endl;
        } else {
            cout << "Vehicle not found\n";
        }
    }
};

/* ================= FACTORY ================= */

class VehicleFactory {
public:
    static Vehicle* createVehicle(const string& type, int num) {
        if (type == "car") return new Car(num);
        if (type == "bike") return new Bike(num);
        return nullptr;
    }
};

/* ================= MAIN ================= */

int main() {
    ParkingFloor* ground = new ParkingFloor(5, "Ground Floor");
    ParkingFloor* first  = new ParkingFloor(10, "First Floor");
    ParkingFloor* second = new ParkingFloor(15, "Second Floor");

    ground->setNext(first);
    first->setNext(second);

    ParkingManager manager(ground);

    int choice = -1;
    while (choice != 3) {
        cout << "\n1. Park Vehicle\n2. Remove Vehicle\n3. Exit\n";
        cin >> choice;

        if (choice == 1) {
            string type;
            int num, time;
            cout << "Enter type (car/bike): ";
            cin >> type;
            cout << "Enter vehicle number: ";
            cin >> num;
            cout << "Enter entry time: ";
            cin >> time;

            Vehicle* v = VehicleFactory::createVehicle(type, num);
            if (v) manager.enter(v, time);
            else cout << "Invalid vehicle type\n";
        }

        else if (choice == 2) {
            int num, time;
            cout << "Enter vehicle number: ";
            cin >> num;
            cout << "Enter exit time: ";
            cin >> time;

            manager.leave(num, time);
        }
    }

    delete ground;
    delete first;
    delete second;
    return 0;
}
