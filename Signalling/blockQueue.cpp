#include <iostream>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>

using namespace std;

template <typename type>
class blockingQueue
{
private:
    int max_size;
    queue<type> _queue;
    mutex mtx;
    condition_variable cond;

public:
    blockingQueue(int max_size) : max_size(max_size)
    {
    }
    void push(type e)
    {
        unique_lock<mutex> lock(mtx);
        cond.wait(lock, [this]()
                  { return _queue.size() < max_size; });
        _queue.push(e);
        lock.unlock();
        cond.notify_one();
    }
    type pop()
    {

        unique_lock<mutex> lock(mtx);
        cond.wait(lock, [this]()
                  { return !_queue.empty(); });

        type item = _queue.front();
        _queue.pop();

        lock.unlock();
        cond.notify_one();

        return item;
    }
};

int main()
{
    blockingQueue<int> qu(5);

    thread t1([&]()
              {
        for(int i = 0; i < 10; i++) qu.push(i); });
    thread t2([&]()
              {
        for(int i = 0; i < 10; i++) {
            auto item = qu.pop();
            cout << "Consumed: " << item << endl;
        } });

    t1.join();
    t2.join();

    return 0;
}