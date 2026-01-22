#include <bits/stdc++.h>
#include <chrono>
#include <thread>

using namespace std;

/* ---------------- TIME UTILITY ---------------- */
long long now() {
    using namespace chrono;
    return duration_cast<seconds>(
        system_clock::now().time_since_epoch()
    ).count();
}

/* ---------------- USER ---------------- */
class User {
public:
    int id;
    User(int i) : id(i) {}
};

/* ---------------- BASE API ---------------- */
class Api {
protected:
    int limit;      // remaining requests
    int maxLimit;   // max requests per window
    int window;     // window in seconds
    long long start; // window start time

public:
    Api(int l, int w) : limit(l), maxLimit(l), window(w) {
        start = now();
    }

    virtual void process(int userId) = 0;
    virtual ~Api() {}
};

/* ---------------- LOGIN API ---------------- */
class Login : public Api {
public:
    Login(int l, int w) : Api(l, w) {}

    void process(int userId) override {
        // reset window if expired
        if (now() - start >= window) {
            limit = maxLimit;
            start = now();
            cout << "[Login] Window reset\n";
        }

        if (limit == 0) {
            cout << "[Login] Limit reached. Please wait...\n";
            return;
        }

        cout << "[Login] User " << userId << " logged in\n";
        limit--;
    }
};

/* ---------------- ORDER API ---------------- */
class Order : public Api {
public:
    Order(int l, int w) : Api(l, w) {}

    void process(int userId) override {
        // reset window if expired
        if (now() - start >= window) {
            limit = maxLimit;
            start = now();
            cout << "[Order] Window reset\n";
        }

        if (limit == 0) {
            cout << "[Order] Limit reached. Please wait...\n";
            return;
        }

        cout << "[Order] User " << userId << " placed an order\n";
        limit--;
    }
};

/* ---------------- MAIN ---------------- */
int main() {
    User u1(1);

    Api* loginApi = new Login(2, 5); // 2 logins per 5 seconds

    // Exceed limit
    loginApi->process(u1.id);
    loginApi->process(u1.id);
    loginApi->process(u1.id);

    cout << "\nSleeping for 5 seconds...\n\n";
    this_thread::sleep_for(chrono::seconds(5));

    // After window reset
    loginApi->process(u1.id);
    loginApi->process(u1.id);
    loginApi->process(u1.id);

    delete loginApi;
    return 0;
}
