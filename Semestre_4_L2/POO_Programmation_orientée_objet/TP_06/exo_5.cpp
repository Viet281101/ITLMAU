
#include <iostream>

using namespace std;


template <typename T>
T puissance(T a, int n) {
    if (n == 0) {
        return 1;
    }
    T temp = puissance(a, n / 2);
    if (n % 2 == 0) {
        return temp * temp;
    } else {
        return a * temp * temp;
    }
}

int main() {
    int a = 2;
    int n = 10;
    int result = puissance(a, n);
    cout << a << "^" << n << " = " << result << endl;
    return 0;
}


