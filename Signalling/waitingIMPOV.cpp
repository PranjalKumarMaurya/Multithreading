#include <iostream>
#include <thread>
#include <chrono>
#include <condition_variable>

using namespace std;

int main() {
    condition_variable condition;
    mutex mtx;
    bool ready{false};

    thread t1([&](){
        cout << "Aquiring t1.." << endl;
        this_thread::sleep_for(chrono::milliseconds(2000));
        unique_lock<mutex> lock(mtx);
        ready = true;
        lock.unlock();
        condition.notify_one();
    });

    cout << "acquiring main thread.." << endl;
    unique_lock<mutex> lock(mtx);
    condition.wait(lock, [&](){ return ready; }); // no while loop to check for ready, lambda instead
    cout << "main finished." << endl;

    cout << "Ready!" << endl;

    t1.join();
    return 0;
}