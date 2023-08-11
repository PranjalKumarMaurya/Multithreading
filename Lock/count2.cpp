#include <iostream>
#include <thread>
#include <atomic>
#include <chrono>

using namespace std;

int main() {
    atomic<int> count{0}; //sometimes the different functions of count instead of incrementing each other's values end up overriding them, so atomic removes that overriding
    // when one thread increments the count and reads the previous data of count and at next instant it preempts, and when other
    // thread reads the same data(as it is not modified yet) it maybe increments it and after that thread is scheduled again and it has previous
    // data stored and thus it also increments the previous value and thus at the end no increment happens
    // atomic enables the variable declared to complete all of its execution of all of it lines, thus no preemption happens between that
    const int ITERATIONS = 1E6;

    thread t1([&count](){
        for(int i = 0; i < ITERATIONS; i++) {
            ++count;
        }
    }); 
    thread t2([&count](){
        for(int i =0; i < ITERATIONS; i++) {
            ++count;
        }
    }); 
    t1.join();
    t2.join();

    

    cout << count << endl;
}