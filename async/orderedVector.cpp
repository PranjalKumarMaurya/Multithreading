#include <iostream>
#include <thread>
#include <future>
#include <chrono>
#include <vector>
#include <mutex>

using namespace std;

mutex mtx;

int work(int id) {

    unique_lock<mutex> lock(mtx);     // this lock ensures that this fn is working asynchronously but still in a proper sequence
    cout << "Result " << id << endl;  // with each thread waiting for critical section
    lock.unlock();

    this_thread::sleep_for(chrono::seconds(3));    // for better understanding run futurevectors and then run this again

    return id*6;
};

int main() {

    vector<shared_future<int>> futures;

    for(int i = 0; i < thread::hardware_concurrency(); i++) {
        shared_future<int> f = async(launch::async, work, i);   // this won't be in order
        futures.push_back(f);
    }

    for(auto f: futures) cout << "Returned: " << f.get() << endl; // this would be in order because this was outputted from a vector

    return 0;
}