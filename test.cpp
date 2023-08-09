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
        throw runtime_error("Cannot have terms less than 1.");
    double sum{0.0};
    for (int i = 0; i < terms; i++)
    {
        int sign = pow(-1, terms);
        double term = 1.0 / (i * 2 + 1);
        sum += term * sign;
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
            double result = Calculate_PI(terms);
            promise.set_value(result);
        }
        catch (...)
        {
            promise.set_exception(current_exception());
        }
    };

    thread t1(PI, 1E6);

    future<double> future = promise.get_future();

    try
    {
        cout << setprecision(15) << future.get() << endl;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
     

    t1.join();
    return 0;
}