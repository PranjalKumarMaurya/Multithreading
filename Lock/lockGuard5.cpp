#include <iostream>
#include <thread>
#include <atomic>
#include <chrono>
#include <mutex>

using namespace std;

void work(int &count, mutex &mtx) {
    for(int i = 0; i < 1E6; i++) {
            lock_guard<mutex> guard(mtx); 
            // here unique_lock can also be used, alsi it has extra features to lock_guard like unique_lock_until (condition based).
            // but here lock_guard is sufficient
            ++count;
        }
}

int main() {
    int count{0}; 

    mutex mtx; // mutual exclusion

    thread t1(work, ref(count), ref(mtx)); 
    thread t2(work, ref(count), ref(mtx)); 
     
    t1.join();
    t2.join();

    

    cout << count << endl;
}