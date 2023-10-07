
#include <iostream>

using namespace std;

template <typename T>
// la bibliothèque standard de C++ contient déjà une fonction 'min' qui fait la même chose dons j'utilise 'minimum' à la place
T minimum(T const& a, T const& b) {
    return a < b ? a : b;
}

int main() {
    int x = 5;
    int y = 10;
    double a = 2.5;
    double b = 3.7;

    cout << "Le minimum entre " << x << " et " << y << " est : " << minimum(x, y) << endl;
    cout << "Le minimum entre " << a << " et " << b << " est : " << minimum(a, b) << endl;

    return 0;
}


