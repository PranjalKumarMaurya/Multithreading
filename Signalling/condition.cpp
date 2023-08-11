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
        this_thread::sleep_for(chrono::milliseconds(2000));
        unique_lock<mutex> lock(mtx); //created a lock of unique type for unlock function
        ready = true;
        lock.unlock();
        condition.notify_one(); // notifies one thread apart from self to continue execution
    });

    unique_lock<mutex> lock(mtx); // lock should be put on the same mutex as in the t1 thread
    while(!ready) {
        condition.wait(lock); // waiting for the lock to unlock and will loop out as soon as ready is true
    }
    cout << "ready! " << endl;

    t1.join();
    return 0;
}