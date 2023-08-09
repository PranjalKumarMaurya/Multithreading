#include <iostream>
#include <thread>
#include <atomic>
#include <chrono>
#include <mutex>

using namespace std;

class App
{
private:
  int count{0};
  mutex mtx;

public:
  void operator()()
  {
    for (int i = 0; i < 1E6; i++)
    {
      lock_guard<mutex> guard(mtx);
      ++count;
    }
  }
  int get_count()
  {
    return count;
  }
};

int main()
{
  auto start = std::chrono::high_resolution_clock::now();
  App app;
  // app();
  // app();      // if we call direct class it will be scheduled one after the another and thus takes more time, now
  // app();      // calling seperate threads will run each call parrallely and thus will take negligible time
  // app();

  thread t1(ref(app)); // reference is passed because mutex doesn't have a copy constructor and thus by value it
                       // won't work with the implicit copy constructor
                       // mutex is now part of a class and creating different instances of class will create diff. mutexes for each instance
                       // and we need to have one mutex so that it controls every thread to enter and exit the CS as the resourse to be accessed
                       // is same and shared bw them
                       // thus, reference is passed so that one mutex is used for every instance and if one updates the class var, other can continue
                       // for that point, not from beiginning
  thread t2(ref(app));
  thread t3(ref(app));
  thread t4(ref(app));

  auto end = std::chrono::high_resolution_clock::now();

  auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

  std::cout << "Execution time: " << duration << " milliseconds" << std::endl;

  t1.join();
  t2.join();
  t3.join();
  t4.join();

  cout << app.get_count() << endl;
}