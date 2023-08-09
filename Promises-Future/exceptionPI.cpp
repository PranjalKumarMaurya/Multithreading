#include <iostream>
#include <thread>
#include <cmath>
#include <future>
#include <iomanip>
#include <exception>

using namespace std;

double Calculate_PI(int terms)
{
    if (terms < 1)
        throw runtime_error("Terms cannot be less than 1");

    double sum{0.0};

    for (int i = 0; i < terms; i++)
    {
        int sign = pow(-1, i);
        double term = 1.0 / (i * 2 + 1);
        sum += sign * term;
    }
    return sum * 4;
}

int main()
{

    promise<double> promise;

    auto PI = [&](int terms)
    {
        try
        {
            auto result = Calculate_PI(terms);
            promise.set_value(result);
        }
        catch (...)
        {
            promise.set_exception(current_exception());
        }
    };

    thread t1(PI, 0);

    future<double> future = promise.get_future();
    
    try
    {
        cout << setprecision(15) << future.get() << endl;
    }
    catch(const exception& e)
    {
        cerr << e.what() << endl;
    }
    

    t1.join();
    return 0;
}