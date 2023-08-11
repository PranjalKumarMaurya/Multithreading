#include <iostream>
#include <future>
#include <chrono>
#include <thread>

using namespace std;

void work(int id)
{
    for (int i = 0; i < 5; i++)
    {
        cout << "running " << i << endl;
        this_thread::sleep_for(chrono::milliseconds(1000));
    }
}
int main()
{
    future<void> f1 = async(launch::async, work, 0); // if we use async here, then f1.get() need not to be called
                                                     // if we use deffered instead, then f1.get() should be called for an output
    return 0;
}