#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <future>

using namespace std;

int work(int id) {
    cout << "running " << id << endl;
    this_thread::sleep_for(chrono::seconds(3));

    return id;
}

int main() {
    for(int i = 0; i < thread::hardware_concurrency(); i++) {
        future<int> f = async(launch::async, work, i);         // here what happens is, future gets out of scope and 
    }                                                          //thus synchronous threading happens
    return 0;
}