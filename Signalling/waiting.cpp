#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

int main() {
    bool ready{false};
    thread t1([&](){
        this_thread::sleep_for(chrono::milliseconds(2000));
        ready = true;
    });
    while(!ready) {
        this_thread::sleep_for(chrono::milliseconds(100)); // here the main has to check every 100ms whether ready is true or not
    }                                                      // so what if we could signal from t1, that ready is true and others can act 
    cout << "ready" << endl;

    t1.join();
    return 0;
}