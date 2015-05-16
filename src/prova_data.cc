#include <iostream>
#include "data.hh"
using namespace std;

int main() {
    Data d1 = {{4,2,0},{20,50}};
    Data d2 = {{3,2,1},{6,2}};
    cout << d1 << '\n' << d2 << endl;

    Data d3 = {{16,5,14},{15,50}};
    Data d4 = {{16,5,15},{15,50}};
    cout << (d3 < d4) << endl;
}
