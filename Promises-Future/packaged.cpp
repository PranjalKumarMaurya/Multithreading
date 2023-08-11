#include <iostream>
#include <iomanip>
#include <cmath>
#include <exception>
#include <future>
#include <thread>

using namespace std;

double CalculatePI(int terms) {
    if(terms < 1) throw runtime_error("Terms can't be less than 1");
    double sum{0.0};
    for(int i = 0; i < terms; i++) {
        int sign = pow(-1,i);
        double term = 1.0/(i*2+1);
        sum += term*sign;
    }
    return sum*4;
}

int main() {
    packaged_task<double(int)> task1(CalculatePI);
    future<double> future1 = task1.get_future();

    thread t1(move(task1), 0);

    try
    {
        cout << setprecision(15) << future1.get();
    }
    catch(const std::exception& e)
    {
        std::cerr << "Error! " << e.what() << '\n';
    }

    t1.join();
    return 0;
    
}