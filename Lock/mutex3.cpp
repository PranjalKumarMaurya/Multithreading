#include <iostream>
#include <thread>
#include <atomic>
#include <chrono>
#include <mutex>

using namespace std;



int main() {
    int count{0}; 
    const int ITERATIONS = 1E6;

    mutex mtx; // mutual exclusion

    auto func = [&](){
        for(int i = 0; i < ITERATIONS; i++) {
            mtx.lock(); // locks the critical section (count), if any other thread isn't in CS else waits for that thread to complete
            ++count;
            mtx.unlock(); // unlocks the access to CS as soon as a thread exits it and if available another is scheduled.
            // if unlock isn't done, then other threads will wait indefinitely.
        }
    };

    thread t1(func); 
    thread t2(func); 
    t1.join();
    t2.join();

    

    cout << count << endl;
}