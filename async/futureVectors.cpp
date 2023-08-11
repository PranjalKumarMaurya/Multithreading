#include <iostream>
#include <thread>
#include <future>
#include <chrono>
#include <vector>

using namespace std;

int work(int id) {
    cout << "running " << id << endl;
    this_thread::sleep_for(chrono::seconds(3));

    return id*3;
}

int main() {

    vector<shared_future<int>> futures;                         //vector is created to store all futures before they go out of scope
    for(int i = 0; i < thread::hardware_concurrency(); i++) {
        shared_future<int> f = async(launch::async, work, i);   //shared future is used as future can't be added in vectors as no copy 
        futures.push_back(f);                                   //constructor and shared does have a copy constructor for this
    }
    return 0;
}