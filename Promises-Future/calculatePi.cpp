#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

double calculatePI(int terms) {
    double sum = 0.0;
    for(int i = 0; i < terms; i++) {
        int sign = pow(-1, i); // to calculate the alternating +,- signs
        double term = 1.0 / (i*2 + 1); // calculates single term like:- 1/3, 1/5, 1/9
        sum += sign*term; // implements alternating +,- within the terms :- 1 - 1/3 + 1/5 - 1/7...
    }
    return sum*4; // all above returns quater of PI, so multiple it by 4 to achieve full PI value
}

int main() {
    cout << setprecision(15) << calculatePI(50000) << endl; // greater the no. of terms in PI , higher the accuracy
    // sets the precision uptill 15 decimal points
    return 0;
}