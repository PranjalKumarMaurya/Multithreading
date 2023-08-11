#include <iostream>
#include <thread>
#include <future>
#include <chrono>

using namespace std;

int work(int id) {
    for(int i = 0; i < 5; i++) {
        cout << "result " << id << endl;
        this_thread::sleep_for(chrono::milliseconds(1000));
    }
    return id*5;
}

int main() {
    async(launch::async, work, 0); 
    async(launch::async, work, 3); //both of these return a synchronous behavior, i.e, first work0 is completed and then work3 starts

    future<int> f1 = async(launch::async, work, 0);
    future<int> f2 = async(launch::async, work, 3);  // here both of them run asynchronously

    cout << f1.get() << endl;
    cout << f2.get() << endl;

    return 0;
}