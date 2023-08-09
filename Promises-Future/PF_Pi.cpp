#include <iostream>
#include <thread>
#include <cmath>
#include <future>
#include <iomanip>

using namespace std;

double Calculate_PI(int terms) {
    double sum{0.0};

    for(int i = 0; i < terms; i++) {
        int sign = pow(-1, i);
        double term = 1.0 / (i*2 + 1);
        sum += sign*term;
    }
    return sum*4;
}

int main() {

    promise<double> promise;

    auto PI = [&](int terms){
        auto result = Calculate_PI(terms);
        promise.set_value(result);
    };

    thread t1(PI, 1E6);

    future<double> future = promise.get_future();
    cout << setprecision(15) << future.get() << endl;

    t1.join();
    return 0;
}