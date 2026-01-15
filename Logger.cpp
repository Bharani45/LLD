#include <bits/stdc++.h>
using namespace std;
#include <mutex> // for thread safety

class Logger {
private:
    // Private constructor: prevents external instantiation
    Logger() {
        cout << "Logger initialized" << endl;
    }

    // Delete copy constructor and assignment operator
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    // Static pointer to the single instance
    static Logger* instance;

    // Mutex for thread safety
    static mutex mtx;

public:
    // Static method to get the single instance
    static Logger* getInstance() {
        // Thread-safe lazy initialization
        if (instance == nullptr) {
            lock_guard<mutex> lock(mtx);
            if (instance == nullptr) { // double-checked locking
                instance = new Logger();
            }
        }
        return instance;
    }

    // Example method
    void log(const string& message) {
        cout << "[LOG] " << message << endl;
    }
};

// Initialize static members
Logger* Logger::instance = nullptr;
mutex Logger::mtx;

int main() {
    Logger* log1 = Logger::getInstance();
    Logger* log2 = Logger::getInstance();

    log1->log("System starting...");
    log2->log("Another log entry.");

    // Check if both pointers are same
    if (log1 == log2)
        cout << "Both are same instance ✅" << endl;
    else
        cout << "Different instances ❌" << endl;

    return 0;
}
