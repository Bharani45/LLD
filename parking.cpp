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

    // Each vehicle decides its own parking cost
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

/* ================= PARKING LOT ================= */

class ParkingLot {
public:
    ParkingLot* ptr;
    void setnext(ParkingLot* next){
        ptr=next;
    }
    virtual void enter(Vehicle* vehicle, int entryTime)=0;
    virtual void leave(int vehicleNumber, int leaveTime)=0;
};

class GroundParking:public ParkingLot{
    private:
        unordered_map<int, ParkingRecord*> activeRecords;
    public:
    void enter(Vehicle* vehicle, int entryTime) {
        if(activeRecords.size()<5){
            int num = vehicle->getNumber();
            activeRecords[num] = new ParkingRecord(vehicle, entryTime);
            cout << "Vehicle " << num << " parked in Ground floor\n";
        }else{
            ptr->enter(vehicle,entryTime);
        }
    }
    void leave(int vehicleNumber, int leaveTime){
        if (activeRecords.find(vehicleNumber) == activeRecords.end()) {
            cout << "Vehicle not found\n";
            return;
        }
        ParkingRecord* record = activeRecords[vehicleNumber];
        Vehicle* vehicle = record->getVehicle();

        int duration = leaveTime - record->getEntryTime();
        int amount = duration * vehicle->getRatePerHour();

        cout << "Pay Rs " << amount << endl;

        delete vehicle;
        delete record;
        activeRecords.erase(vehicleNumber);
    }
};
class FirstFloorParking:public ParkingLot{
    private:
        unordered_map<int, ParkingRecord*> activeRecords;
    public:
    void enter(Vehicle* vehicle, int entryTime) {
        if(activeRecords.size()<10){
            int num = vehicle->getNumber();
            activeRecords[num] = new ParkingRecord(vehicle, entryTime);
            cout << "Vehicle " << num << " parked in 1st floor\n";
        }else{
            ptr->enter(vehicle,entryTime);
        }
    }
    void leave(int vehicleNumber, int leaveTime){
        if (activeRecords.find(vehicleNumber) == activeRecords.end()) {
            cout << "Vehicle not found\n";
            return;
        }
        ParkingRecord* record = activeRecords[vehicleNumber];
        Vehicle* vehicle = record->getVehicle();

        int duration = leaveTime - record->getEntryTime();
        int amount = duration * vehicle->getRatePerHour();

        cout << "Pay Rs " << amount << endl;

        delete vehicle;
        delete record;
        activeRecords.erase(vehicleNumber);
    }
};
class SecondFloorParking:public ParkingLot{
    private:
        unordered_map<int, ParkingRecord*> activeRecords;
    public:
    void enter(Vehicle* vehicle, int entryTime) {
        if(activeRecords.size()<15){
            int num = vehicle->getNumber();
            activeRecords[num] = new ParkingRecord(vehicle, entryTime);
            cout << "Vehicle " << num << " parked in 2nd floor\n";
        }else{
            cout<<"Parking full no space left"<<endl;
        }
    }
    void leave(int vehicleNumber, int leaveTime){
        if (activeRecords.find(vehicleNumber) == activeRecords.end()) {
            cout << "Vehicle not found\n";
            return;
        }
        ParkingRecord* record = activeRecords[vehicleNumber];
        Vehicle* vehicle = record->getVehicle();

        int duration = leaveTime - record->getEntryTime();
        int amount = duration * vehicle->getRatePerHour();

        cout << "Pay Rs " << amount << endl;

        delete vehicle;
        delete record;
        activeRecords.erase(vehicleNumber);
    }
};



/* ================= FACTORY ================= */

class VehicleFactory {
public:
    static Vehicle* createVehicle(const string& type, int number) {
        if (type == "car") return new Car(number);
        if (type == "bike") return new Bike(number);
        return nullptr;
    }
};

/* ================= MAIN ================= */

int main() {
    ParkingLot* gnd=new GroundParking();
    ParkingLot* first=new FirstFloorParking();
    ParkingLot* second=new SecondFloorParking();
    gnd->setnext(first);
    first->setnext(second);
    int choice = -1;
    while (choice != 4) {
        cout << "\n1. Park Vehicle\n2. Remove Vehicle\n4. Exit\n";
        cin >> choice;

        if (choice == 1) {
            string type;
            int number, time;

            cout << "Enter vehicle type (car/bike): ";
            cin >> type;
            cout << "Enter vehicle number: ";
            cin >> number;
            cout << "Enter entry time: ";
            cin >> time;

            Vehicle* vehicle = VehicleFactory::createVehicle(type, number);
            if (vehicle)
                gnd->enter(vehicle, time);
            else
                cout << "Invalid vehicle type\n";
        }
        else if (choice == 2) {
            int number, time;
            cout << "Enter vehicle number: ";
            cin >> number;
            cout << "Enter leave time: ";
            cin >> time;
            cout<<"Enter floor"<<endl;
            int k;
            cin>>k;
            if(k==0){
                gnd->leave(number, time);
            }else if(k==1){
                first->leave(number, time);
            }else{
                second->leave(number, time);
            }            
        }
    }

    return 0;
}
