#include <thread>
#include <iostream>
#include <vector>
#include <future>
#include <chrono>
#include <queue>
#include <mutex>
#include <condition_variable>

using namespace std;
mutex mtx;

template <typename type>
class blockingQueue
{
private:
    condition_variable cond;
    int max_size;
    queue<type> Q;

public:
    blockingQueue(int max_size) : max_size(max_size)
    {
    }
    void push(type e)
    {
        unique_lock<mutex> lock(mtx);
        cond.wait(lock, [this]()
                  { return Q.size() < max_size; });
        Q.push(e);
        lock.unlock();
        cond.notify_one();
    }
    type front()
    {
        unique_lock<mutex> lock(mtx);
        cond.wait(lock, [this]()
                  { return !Q.empty(); }); 
        return Q.front();
    }
    void pop()
    {
        unique_lock<mutex> lock(mtx);
        cond.wait(lock, [this]()
                  { return !Q.empty(); });
            Q.pop();
        lock.unlock();
        cond.notify_one();
    }
    int size()
    {
        lock_guard<mutex> lock(mtx);
        return Q.size();
    }
};

int work(int id)
{
    unique_lock<mutex> lock(mtx);
    cout << "Result : " << id << endl;
    lock.unlock();

    this_thread::sleep_for(chrono::seconds(3));

    return id * 4;
};

int main()
{
    blockingQueue<shared_future<int>> futures(3);

    thread t([&](){
      for(int i = 0; i < 20; i++) {
          shared_future<int> f = async(launch::async, work, 3);
          futures.push(f);
    } });

    for(int i = 0; i < 20; i++) {
        shared_future<int> f = futures.front();
        int value = f.get();
        futures.pop();
        cout << "Returned : " << value << endl;
    }
    t.join();

    return 0;
}