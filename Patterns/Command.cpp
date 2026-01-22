#include <iostream> // Use iostream instead of bits/stdc++.h for standard C++
using namespace std;

// 1. Receiver
class Light {
public:
    void on() {
        cout << "Light is ON" << endl;
    }
    void off() {
        cout << "Light is OFF" << endl;
    }
};

// 2. Command Interface
class Command {
public:
    virtual void execute() = 0;
    virtual void undo() = 0; // Renamed redo -> undo (standard name for reversing)
};

// 3. Concrete Commands
class LightOnCommand : public Command {
    Light* light; // moved here (Decoupling)

public:
    // Constructor to inject the specific light
    LightOnCommand(Light* l) : light(l) {}

    void execute() override {
        light->on();
    }
    void undo() override {
        light->off();
    }
};

class LightOffCommand : public Command {
    Light* light;

public:
    LightOffCommand(Light* l) : light(l) {}

    void execute() override {
        light->off();
    }
    void undo() override {
        light->on();
    }
};

// 4. Invoker (Remote)
class Remote {
    Command* cmd;
public:
    void setCommand(Command* c) {
        cmd = c;
    }

    void pressButton() {
        if (cmd) cmd->execute();
    }

    void pressUndo() {
        if (cmd) cmd->undo();
    }
};

int main() {
    // 1. Create the actual device
    Light* livingRoomLight = new Light();

    // 2. Create the commands and attach the device
    Command* lightsOn = new LightOnCommand(livingRoomLight);
    Command* lightsOff = new LightOffCommand(livingRoomLight);

    // 3. Use the Remote
    Remote* remote = new Remote();
    
    // Test ON
    remote->setCommand(lightsOn);
    remote->pressButton(); // Light is ON
    remote->pressUndo();   // Light is OFF (Reversed)

    // Test OFF
    remote->setCommand(lightsOff);
    remote->pressButton(); // Light is OFF
    
    return 0;
}