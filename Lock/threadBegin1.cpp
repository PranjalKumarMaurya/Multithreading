#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

void work() {
    for(int i = 0; i < 10; i++) {
        cout << "Loop " << i << endl;
    }
}

int main() {
    thread t1(work); // this will terminate the main thread which was running and along with that it terminates this thread too.
    thread t2(work); // this will terminate the main thread which was running and along with that it terminates this thread too.
    t1.join();
    t2.join();
}