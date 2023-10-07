
#include <iostream>
#include <algorithm> // pour la méthode 'sort'

using namespace std;

template <typename T>
T somme(int n, T* tab) {
    T result = 0;
    for (int i = 0; i < n; i++) {
        result += tab[i];
    }
    return result;
}

template <typename T>
void triGeneral(int n, T* tab) {
    sort(tab, tab + n);
}

template <typename T, typename H>
class couple_t {
private:
    T first;
    H second;

public:
    couple_t(T a, H b) {
        first = a;
        second = b;
    }

    T getFirst() {
        return first;
    }

    H getSecond() {
        return second;
    }

    couple_t operator+(const couple_t& autre) const {
        T newFirst = first + autre.first;
        H newSecond = second + autre.second;
        return couple_t(newFirst, newSecond);
    }

    bool operator<(const couple_t& autre) const {
        if (first < autre.first) {
            return true;
        } else if (first == autre.first) {
            return second < autre.second;
        } else {
            return false;
        }
    }
};

int main() {
    int tabInt[] = {1, 2, 3, 4, 5};
    cout << "Somme : " << somme(5, tabInt) << endl;

    double tabDouble[] = {1.1, 2.2, 3.3, 4.4, 5.5};
    cout << "Somme : " << somme(5, tabDouble) << endl;

    couple_t<int, double> couple1(1, 2.2);
    couple_t<int, double> couple2(3, 4.4);
    couple_t<int, double> couple3 = couple1 + couple2;

    cout << "Couple 1 : (" << couple1.getFirst() << ", " << couple1.getSecond() << ")" << endl;
    cout << "Couple 2 : (" << couple2.getFirst() << ", " << couple2.getSecond() << ")" << endl;
    cout << "Couple 3 : (" << couple3.getFirst() << ", " << couple3.getSecond() << ")" << endl;

    couple_t<int, double> arr[] = {couple_t<int, double>(2, 3.5), couple_t<int, double>(5, 2.3), couple_t<int, double>(3, 4.7)};
    int n = sizeof(arr) / sizeof(arr[0]);
    triGeneral(n, arr);
    for (int i = 0; i < n; i++) {
        cout << "(" << arr[i].getFirst() << ", " << arr[i].getSecond() << ") ";
    }
    cout << endl;

    return 0;
}


